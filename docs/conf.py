# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Path setup --------------------------------------------------------------
# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#
# import sys
# sys.path.insert(0, os.path.abspath('.'))
import os
import re

# -- Project information -----------------------------------------------------
# Scrape some meta data from a single source (e.g. root CMakeLists.txt)
git_describe = os.popen('git describe --always --dirty --tags').read().strip()
meta_file = "../CMakeLists.txt"
with open(meta_file) as config:
    contents = config.read()
project_regex = f"project[\s]*\(([\S]*) VERSION [0-9]+\.[0-9]+\.[0-9]\)"
project_search = re.search(project_regex, contents)
release_regex = f"project[\s]*\([\S]* VERSION ([0-9]+\.[0-9]+\.[0-9])\)"
release_search = re.search(release_regex, contents)

# Hardcoded project information
copyright = '2020, Nathan A. Miller and Kyle A. Brindley'
author = 'Nathan A. Miller and Kyle A. Brindley'

# Scrape meta_file for project name or fail
if project_search:
    project = project_search.group(1)
else:
    raise RuntimeError(f'Could not find project name in {meta_file} with "{project_regex}" regex pattern')

# Scrape meta_file for version or fall back to git info
version = f"{git_describe}".replace('-','.')
if release_search:
    release = release_search.group(1)
else:
    release = version

# -- Project Variables -------------------------------------------------------
rst_prolog = f'.. |project| replace:: {project}\n.. include:: targets.txt'

# -- General configuration ---------------------------------------------------
# Add custom style sheet to make the html docs wider
def setup(app):
    app.add_css_file('custom.css')

# Add any Sphinx extension module names here, as strings.
extensions = ["breathe", 'sphinxcontrib.bibtex', 'sphinx.ext.extlinks']
bibtex_bibfiles = ['software.bib']

# Breathe Configuration
breathe_projects = {project: "../build/docs/doxygen/xml"}
breathe_default_project = project

# Links to PRs, Jira issues.
extlinks = {
     "pull": ("https://xcp-stash.lanl.gov/projects/MM/repos/abaqus_tools/pull-requests/%s/overview", "PR"),
     "jira": ("https://xcp-jira.lanl.gov/browse/VIP-%s", "VIP-"),
}

# Add any paths that contain templates here, relative to this directory.
templates_path = ['_templates']

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path.
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']

# -- Options for HTML output -------------------------------------------------
# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
html_theme = 'sphinx_rtd_theme'

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = ['_static']
