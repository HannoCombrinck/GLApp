--------------------------------------------------------------------------------
{-# LANGUAGE OverloadedStrings #-}
import           Hakyll
import           Text.Pandoc.Options
import           Text.Pandoc.Definition
import           Text.Read
import           Control.Applicative
import           Control.Arrow
import           Control.Monad
import           Data.Monoid
import           Data.Maybe
import           Data.Char
import qualified Data.Set as S


--------------------------------------------------------------------------------

logMsg :: String -> Compiler ()
logMsg s = debugCompiler $ "_logged_ " ++ s

cfg :: Configuration
cfg = def {ignoreFile  = uncurry (||) . (ignore &&& ignoreFile def) }
    where
        ignore "[fuf]" = True
        ignore "fuf" = True
        ignore _ = False

main :: IO ()
main = hakyllWith cfg $ do
    match "media/*" $ do
        route   idRoute
        compile copyFileCompiler

    match "css/*" $ do
        route   idRoute
        compile compressCssCompiler

    match (fromList ["about.md"]) $ do
        route   $ setExtension "html"
        compile $ pandocCompiler >>= _defTemplate postCtx

    match pages $ do
        route $ setExtension "html"
        compile $ _pandocReader
            >>= _pandocWriterPages 
            >>= _defTemplate postCtx

    match posts $ do
        route $ setExtension "html"
        compile $ _pandocReader
            >>= _pandocWriterPosts 
            >>= _defTemplate postCtx

    match slides $ do
        route $ setExtension "html"
        compile $ _pandocReader
            >>= _pandocWriterSlides
            >>= loadAndApplyTemplate "templates/slides.html" postCtx
            >>= relativizeUrls

    create ["archive.html"] $ do
        route idRoute
        compile $ do
            slides' <- pure . take 5 =<< recentFirst =<< loadAll slides
            posts'  <- pure . take 5 =<< recentFirst =<< loadAll posts
            let archiveCtx  = listField "slides" postCtx (return slides')
                            <> listField "posts" postCtx (return posts')
                            <> constField "title" "Archives"
                            <> defaultContext
            makeItem "" 
                >>= loadAndApplyTemplate "templates/archive.html" archiveCtx 
                >>= _defTemplate archiveCtx


    match "index.md" $ do
        route $ setExtension "html"
        compile $ do 
            slides' <- recentFirst =<< loadAll slides
            posts' <- recentFirst =<< loadAll posts
            let indexCtx    = listField "slides" postCtx (return slides')
                            <> listField "posts" postCtx (return posts')
                            <> constField "title" "Home"
                            <> defaultContext
            _pandocReader 
                >>= _pandocWriterPages 
                >>= loadAndApplyTemplate "templates/index.html" indexCtx 
                >>= _defTemplateNoContent indexCtx

    match "templates/*.html"  $ compile templateCompiler


--------------------------------------------------------------------------------

_defTemplate :: Context String -> Item String -> Compiler (Item String)
_defTemplate ctx = loadAndApplyTemplate "templates/default.html" ctx
                 >=> loadAndApplyTemplate "templates/default_no_content.html" ctx
                 >=> relativizeUrls

_defTemplateNoContent :: Context String -> Item String -> Compiler (Item String)
_defTemplateNoContent ctx = loadAndApplyTemplate "templates/default_no_content.html" ctx >=> relativizeUrls

postCtx :: Context String
postCtx = metadataField <> dateField "date" "%B %e, %Y" <> defaultContext

slides, posts, pages :: Pattern
slides = "slides/*.md" .||. "slides/*.lhs"
posts =  "posts/*.md" .||. "posts/*.lhs"
pages =  "pages/*.md" .||. "pages/*.lhs"


_pandocReader :: Compiler (Item Pandoc)
_pandocReader = logMsg "_pandocReader" >> readPandocWith rOps <$> getResourceBody
    where
        rOps  = def { readerExtensions = pandocExtensions `S.union` S.fromList [Ext_literate_haskell]
                    , readerSmart = True
                    }

_pandocWriterSlides :: Item Pandoc ->  Compiler (Item String)
_pandocWriterSlides  =  _pandocWriterWith $ def { writerSlideVariant = SlidySlides
                                               , writerSlideLevel = Just 1
                                               , writerIncremental = True 
                                               , writerHighlight = True
                                               , writerExtensions = S.fromList [Ext_literate_haskell]
                                               } 
_pandocWriterPosts :: Item Pandoc ->  Compiler (Item String)
_pandocWriterPosts  =  _pandocWriterWith $ def { writerHighlight = True
                                               , writerExtensions = S.fromList [Ext_literate_haskell]
                                               } 

_pandocWriterPages :: Item Pandoc ->  Compiler (Item String)
_pandocWriterPages  =  _pandocWriterWith $ def { writerHighlight = True
                                               , writerExtensions = S.fromList [Ext_literate_haskell]
                                               } 


_pandocWriterWith :: WriterOptions -> Item Pandoc -> Compiler (Item String)
_pandocWriterWith wOpts i = do
    let setOp ::  String -> (WriterOptions -> String -> WriterOptions) -> WriterOptions -> Compiler WriterOptions
        setOp k f o = logMsg ("setOp " ++ k) 
                    >> maybe o (f o) <$> getMetadataField (itemIdentifier i) k 
    logMsg "_pandocWriterWith"
    pure wOpts 
        >>= setOp "slideLevel"   (\o v-> o {writerSlideLevel = readMaybe v})
        >>= setOp "incremental"  (\o v-> o {writerIncremental = map toLower v == "true"})
        >>= setOp "highlight"    (\o v-> o {writerHighlight = map toLower v == "true"})
        >>= setOp "slideVariant" (\o v-> o {writerSlideVariant = NoSlides `fromMaybe` readMaybe v})
        >>= \ o -> return $ writePandocWith o i

