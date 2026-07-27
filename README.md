# Comment Search

## Description

Provides a dedicated **Comments** search tab at `/search/comment`. Each
published comment is indexed individually so that search results link
directly to the matched comment via the Backdrop comment permalink
(`/comment/[cid]`), which redirects to the correct page of the comment
thread and lands on the right anchor.

The module also implements `hook_search_combined_result()` to integrate with the
[Search Combined](https://github.com/backdrop-contrib/search_combined) module so
that comment search results also appear on the integrated **Combined** search
tab that module provides when it is configured to include comments.

## How it differs from core content search

Backdrop's core search indexes comment text as part of the parent node's
search entry. Through chat discussion, people in the Backdrop community
identified details on how it works. This is something that has been present
since Drupal 5/6/7 and inherited by Backdrop.

**Pager-limited indexing.** Core's `comment_node_update_index()` uses the
same pager-limited function that renders comments where only the first page of
comments is ever indexed per node - comments on page two and beyond are silently
omitted from the search index entirely.

When a search term matches comment text, the result links to the top of the
parent node. The user has no indication which comment matched or where on the
node to find it, which may be frustrating on nodes with many comments, although
the browser find on page may help.

Despite these two apparent limitations, there may also be a use case for this:
where a search that matches the node content or comments on the first page will
direct the person to the node itself and they will see the content followed by
the comments providing context. This may be beneficial for Forums created with
views and other applications.

This module provides the option to preserve the original behavior for backward
compatibility and for any use case where it is desired by unchecking
**Exclude comments from Content search tab results**. When the module is first
enabled the default is unchecked.

The main purpose of this module is to provide a search for all comments and this
is done in a separate tab on the Search form. The module maintains a separate
index where each comment is its own entry. Search results link directly to the
comment via Backdrop's comment permalink path (`/comment/[cid]`), that redirects
to the correct page of the comment thread and jumps to the comment anchor. Users
land where the match is, regardless of which page of comments it appears on.

The optional setting to **Exclude comments from Content search tab results** can
be enabled to completely separate the content search from the comment search.
When it is enabled comment text is removed from the node index entirely, so the
Content tab returns only node matches while the Comments tab handles comment
matches with accurate and useful result links.

## Dependencies

- Core **Comment** module
- Core **Search** module

## Installation

Install this module using the official Backdrop CMS instructions at https://backdropcms.org/guide/modules.

## Configuration and use

After enabling:

1. Go to **Admin > Configuration > Search > Search settings**
   (`admin/config/search/settings`) and ensure **Comments** appears in the
   active search modules list and is checked.
2. Run cron to build the comment index (`bee cron` or via
   **Admin > Reports > Status report > Run cron manually**).
3. The Comments tab will appear at `/search/comment`.

Indexing progress is shown on the search settings page for Content and other
active search modules.

## Search results

Each result shows:

- **Title**: the comment subject, linking to `/comment/[cid]#comment-[cid]`
- **Snippet**: an excerpt of the comment body with the search term highlighted
- **Author**: linked to the user profile for registered users; omitted for
  anonymous commenters
- **Date**: the comment's last-modified date
- **In**: the title of the parent node, linking to the node page

Results respect node and comment access controls - unpublished nodes and
unpublished comments are excluded from both indexing and results.

## Settings

An **Exclude comments from Content search tab results** checkbox is added
to the existing **Search items** section on **Admin > Configuration >
Search > Search settings** (`admin/config/search/settings`). When checked,
comment text is not indexed as part of Content (node) search results. Comments
remain fully searchable via the Comments tab. Changing this setting
automatically triggers a re-index of all nodes on the next cron run so the
Content search index reflects the change.

## Pager

The Comments tab uses the same results-per-page setting as the Content tab,
configured at **Admin > Configuration > Search > Search settings**.
The Comments tab displays 10 results per page, matching Backdrop core's
hardcoded default for search results. Core does not expose a results-per-page
configuration key in search settings.

## Keeping the index current

The index is updated on each cron run. Individual comments are also flagged
for re-indexing automatically when they are created, updated, published, or
unpublished. Deleted comments are removed from the index immediately.

To rebuild the entire index (e.g. after changing indexed content), go to
**Admin > Configuration > Search > Search settings** and click
**Rebuild Search Index**. This marks all comment index entries for re-indexing
on the next cron run.

## Extending

Other modules can add extra text to a comment's index entry by implementing
`hook_comment_search_index($comment, $node)` and returning a string. This
is useful for indexing additional fields attached to comments.

## Documentation

Additional documentation is located in the Wiki:
https://github.com/backdrop-contrib/comment_search/wiki/Documentation.

## Issues

Bugs and Feature requests should be reported in the Issue Queue:
https://github.com/backdrop-contrib/comment_search/issues.

## Current Maintainers
- [izmeez](https://github.com/izmeez).
- Seeking additional maintainers.

## Credits

Created for Backdrop CMS by [izmeez](https://github.com/izmeez) with AI assistance.

## License

This project is GPL v2 software.
See the LICENSE.txt file in this directory for complete text.
