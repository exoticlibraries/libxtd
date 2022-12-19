
import themata

project = 'libxtd'
copyright = '2022, Thecarisma - MIT License'
author = 'Adewale Azeez and Other Contributors'

html_theme = 'sugar'
master_doc = 'index'
html_favicon = 'libxtd.png'
main_doc = 'index'
html_static_path = ['_static']

html_css_files = {
    'css/libxtd.css'
}
html_js_files = {
    'js/libxtd.js'
}

extensions = ['m2r2', ]
source_suffix = ['.rst', '.md']

html_theme_options = {
    'index_is_single': False,
    'show_navigators_in_index': False,
    #'collapsible_sidebar': False,
    'collapsible_sidebar_display': 'block',
    'syntax_highlighter': 'prism',
    'code_block_editable': False,
    'syntax_highlighter_theme': 'okaidia',
    #'syntax_highlighter_iframe_embed': True,
    'navbar_links': [
        ('Download', 'download'),
        ('Modules', 'p/index'),
        ('View on Github', 'https://github.com/exoticlibraries/libxtd')
    ],
    'navbar_sec_links': [
        ('Containers', 'p/containers/index'),
        ('IO', 'p/io/index'),
        ('Algorithms', 'p/algorithms/index'),
        ('Math', 'p/math/index'),
        ('Util', 'p/util/index')
    ],
    #'has_left_sidebar': True,
    'has_right_sidebar': True,
    'show_navigators': True,
    'social_icons': [
        ('fab fa-twitter', 'https://twitter.com/exoticlibs'),
        ('fab fa-github', 'https://github.com/exoticlibraries/libxtd/')
    ],
    'no_sidebar': [
        'index'
    ],
    "source_root": "https://github.com/exoticlibraries/libxtd/main/docs",
    "metadata": {
        "enable": True,
        "url": "https://github.com/exoticlibraries/libxtd/",
        "type": "website",
        "title": "Simple yet powerful HTTP, WS client with cache and offline support for JavaScript. For both browser and node.js.",
        "description": "Simple yet powerful HTTP, WS client with cache and offline support for JavaScript. For both browser and node.js.",
        "image": "https://raw.githubusercontent.com/exoticlibraries/libxtd/main/docs/libxtd.png",
        "keywords": "thecarisma, http, websocket, cache, queue, offline, client, axios, javascript, react, react-native, nodejs",
        "author": "Adewale Azeez"
    },
    "twitter_metadata": {
        "enable": True,
        "card": "summary",
        "site": "@exoticlibs",
        "creator": "@iamthecarisma",
        "title": "Simple yet powerful HTTP, WS client with cache and offline support for JavaScript. For both browser and node.js.",
        "description": "Simple yet powerful HTTP, WS client with cache and offline support for JavaScript. For both browser and node.js.",
        "image": "https://raw.githubusercontent.com/exoticlibraries/libxtd/main/docs/libxtd.png",
    },

    "document_font_size": "17px",
    "header_background_color": "#353836",
    "header_sec_background_color": "black",
}