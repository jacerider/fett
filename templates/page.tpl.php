<div id="page" class="<?php print $classes; ?>" <?php print $attributes;?>>
<?php print render($page_prefix); ?>

  <header id="header">
    <div class="row">
      <div class="columns small-12">

        <!-- region.secondary-nav.start -->
        <?php if ($secondary_nav): ?>
          <?php print render($secondary_nav); ?>
        <?php endif; ?>
        <!-- region.main-nav.end -->

        <?php if ($linked_logo): ?>
          <?php print $linked_logo; ?>
        <?php endif; ?>

        <?php if ($site_name): ?>
          <div id="site-name" class="element-invisible">
            <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><?php print $site_name; ?></a>
          </div>
        <?php endif; ?>

        <!-- region.main-nav.start -->
        <?php print $offcanvas_main_nav_link; ?>
        <?php if ($main_nav): ?>
          <?php print render($main_nav); ?>
        <?php endif; ?>
        <!-- region.main-nav.end -->

        <?php if ($page['header']): ?>
          <?php print render($page['header']); ?>
        <?php endif; ?>

      </div>
    </div>
  </header><!-- /#header -->

  <?php if (!empty($messages)): ?>
    <section id="messages">
      <div class="row">
        <div class="columns small-12">
          <?php print render($messages); ?>
        </div>
      </div>
    </section><!--/#messages -->
  <?php endif; ?>

  <?php if (!empty($page['help'])): ?>
    <section id="help">
      <div class="row">
        <div class="columns small-12">
          <?php print render($page['help']); ?>
        </div>
      </div>
    </section><!--/#help -->
  <?php endif; ?>

  <div id="main" role="main" class="body">
    <a id="main-content"></a>

    <?php if ($title && !$is_front): ?>
      <?php print render($title_prefix); ?>
      <h1 id="page-title" class="title"><?php print $title; ?></h1>
      <?php print render($title_suffix); ?>
    <?php endif; ?>

    <div class="row">

      <section id="content"  class="<?php print $content_classes; ?> body">
        <?php print $offcanvas_sidebar_first_link; ?>
        <?php print $offcanvas_sidebar_second_link; ?>
        <?php print render($page['content']); ?>
      </section>

      <?php if (!empty($page['sidebar_first'])): ?>
        <aside id="sidebar-first" role="complementary" class="<?php print $sidebar_first_classes; ?> sidebar first">
          <?php print render($page['sidebar_first']); ?>
        </aside>
      <?php endif; ?>

      <?php if (!empty($page['sidebar_second'])): ?>
        <aside id="sidebar-second" role="complementary" class="<?php print $sidebar_second_classes; ?> sidebar second">
          <?php print render($page['sidebar_second']); ?>
        </aside>
      <?php endif; ?>
    </div><!-- /.row -->
  </div><!-- /#main -->

  <footer id="footer" role="contentinfo">
    <div class="row">
      <div class="columns small-12">
        <?php if (!empty($page['footer'])): ?>
          <?php print render($page['footer']); ?>
        <?php endif; ?>
        <?php print $copyright; ?>
      </div>
    </div>
  </footer>


<?php print render($page_suffix); ?>
</div>
