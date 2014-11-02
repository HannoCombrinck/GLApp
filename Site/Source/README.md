Intro
====================

This directory is the source for the static site generated by Hakyll for the GLApp repository. We can use it as a place to
write posts and make slides for our computer graphics user group.

The site builder is a Haskell program that uses Hakyll. The idea is to make it easy to generate content using pandoc 
markdown which gets converted to either HTML slides, blog posts or just general pages.

Site Structure
=====================

Home Page
----------------------
What is displayed on the home page can be modified by editing the *index.md* markdown file.

About Page
----------------------
What is displayed on the about page can be modified by editing the *about.md* markdown file.

Slides
---------------------
Slides are generated from markdown files in the **slides** sub folder. The markdown files are named **YYYY-MM-DD-Slide_Title.md** so that
they are automatically ordered by date. The type of HTML slides produced are by default [HTML Slidy](http://www.w3.org/Talks/Tools/Slidy2) 
slides. Some of properties for defining the slides can be overridden by supplying YAML properties at the start of you HTML document.

Posts
---------------------
Posts are generated from markdown files in the **posts** sub folder. The markdown files are named **YYYY-MM-DD-Post_Title.md** so that
they are automatically ordered by date and post's date is derived from the file name. As with the slides YAML properties can be provided at
the start of the post although there is not many at the moment affecting how the posts are generated.

Pages
---------------------
General pages go in the **pages** sub folder and are free form pandoc markdown documents ending in **.md**.

Media
---------------------
Images and any other media go in the **media** sub folder and gets copied over as is to the site. The same media can be included in posts,
pages or slides by referencing it in the media folder.

CSS
---------------------
The style sheets used by the site are in the **css** sub folder and also are copied over as is.

HTML Templates and Site Look and Feel
---------------------
The site is generated by combining the HTML generated from the pandoc markdown files with the HTML templates specified in the 
**templates** sub folder. This defines the look and feel of the site and defines which style sheets are used. The site logo used is
**media/logo.png** and is just a temporary picture at the moment.

YAML Properties for Limited Customization
=================================
The following properties are can be provided in the YAML property block at the beginning of your pandoc markdown file.
* title - The title of the document
* author - The author of the document
* data - The date of the document (leave out for posts and slides since generated from the file name)
* slideLevel - Pandoc property *writerSlideLevel* default is 1
* incremental - Pandoc property *writerIncremental* default is *True*
* highlight - Pandoc property *writerHighlight* default is *True*
* slideVariant - Pandoc property *writerSlideVariant* default is *SlidySlides* 

Reference
=========================
The following links might be useful when generating content.
* [Pandoc's markdown](http://johnmacfarlane.net/pandoc/demo/example9/pandocs-markdown.html)
* [HTML Slidy](http://www.w3.org/Talks/Tools/Slidy2)
* [Hakyll](http://jaspervdj.be/hakyll/)
* [Creating github pages manually](https://help.github.com/articles/creating-project-pages-manually)
  * Basically you push your site to the orphan branch gh-pages
  * And you access your site through the url http://username.github.io/projectname (e.g. [http://HanStolpo.github.io/GLApp](http://HanStolpo.github.io/GLApp))

Building the Site on Windows
============================
For convenience the compiled site builder is committed to the repository as **Site.exe** and several batch files are provided to make it
easy to generate the site. The batch files are:
* __clean.bat__ - Cleans the site deleting all generated files.
* __build.bat__ - Builds the site.
* __rebuild.bat__ - Cleans and the builds the site from scratch.
* __watch.bat__ - Builds the site and starts a local server which can be used to view it. It automatically rebuilds the site when changes are detected.
* __deploy.bat__ - Mirrors the site that was build by either running **watch.bat**, **rebuild.bat**, or **build.bat** to the folder
  **../gh-pages**. If this is folder corresponds to a repository for the github-pages orphan branch then you can commit the changes
  there and push to the server to update the public site.

Building the Site Generator from Source
=======================================
To build the site generator from source you will need to do the following:

1. Install the [Haskell Platform 2014](https://www.haskell.org/platform) (for Windows install the 32 bit version not the 64 bit)
1. Update your cabal-install by running the following on the command line
    1. cabal update
     cabal install cabal-install
1. Make sure the new cabal-install takes precedence on the command line. On windows make sure that **C:\Users\UserName\AppData\Roaming\cabal\bin**
  is prepended to your path.
1. CD to the folder **GLAppRepo/Site/Source**
1. Create a sandox by typing **cabal sandbox init**
1. Build and then copy executable to **GLAppRepo/Site/Source** by either
  1. On windows running batch file **buildSiteExec.bat**
  1. Or manually running **cabal install** then copying **GLAppRepo/Site/Source/.cabal-sandbox/bin/Site.exe** to **GLAppRepo/Site/Source**