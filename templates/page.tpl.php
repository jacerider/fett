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

  <?php if (!empty($page['featured'])): ?>
    <section id="featured">
      <div class="row">
        <div class="columns small-12">
          <?php print render($page['featured']); ?>
        </div>
      </div>
    </section><!--/#featured -->
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

  <?php if (!empty($tabs)): ?>
    <section id="tabs">
      <div class="row">
        <div class="columns small-12">
          <?php print render($tabs); ?>
          <?php if (!empty($tabs2)): print render($tabs2); endif; ?>
        </div>
      </div>
    </section><!--/#tabs -->
  <?php endif; ?>

  <div id="content">
    <a id="main-content"></a>

    <div class="row">

      <main id="main" class="<?php print $content_classes; ?>">
        <?php if ($title && !$is_front): ?>
          <?php print render($title_prefix); ?>
          <h1 id="page-title" class="title"><?php print $title; ?></h1>
          <?php print render($title_suffix); ?>
        <?php endif; ?>
        <?php print $offcanvas_sidebar_first_link; ?>
        <?php print $offcanvas_sidebar_second_link; ?>
        <?php print render($page['content']); ?>
      </main>

      <?php if (!empty($page['sidebar_first'])): ?>
        <aside id="sidebar-first" class="<?php print $sidebar_first_classes; ?> sidebar first">
          <?php print render($page['sidebar_first']); ?>
        </aside>
      <?php endif; ?>

      <?php if (!empty($page['sidebar_second'])): ?>
        <aside id="sidebar-second" class="<?php print $sidebar_second_classes; ?> sidebar second">
          <?php print render($page['sidebar_second']); ?>
        </aside>
      <?php endif; ?>
    </div><!-- /.row -->
  </div><!-- /#content -->

  <footer id="footer">
    <div class="row">
      <div class="columns small-12">
        <?php if (!empty($page['footer'])): ?>
          <?php print render($page['footer']); ?>
        <?php endif; ?>
        <div id="copyright"><?php print $copyright; ?></div>
      </div>
    </div>
  </footer>


<?php print render($page_suffix); ?>
</div>
