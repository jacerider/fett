<?php if ($top_bar_classes): ?>
  <div class="<?php print $top_bar_classes; ?>">
<?php endif; ?>
    <nav class="top-bar"<?php print $top_bar_options; ?> data-topbar>
      <ul class="title-area">
        <li class="name"><h1><?php print $linked_site_name; ?></h1></li>
        <li class="toggle-topbar menu-icon"><a href="#"><span><?php print $top_bar_menu_text; ?></span></a></li>
      </ul>
      <section class="top-bar-section">
        <?php if ($top_bar_main_menu) :?>
          <?php print $top_bar_main_menu; ?>
        <?php endif; ?>
        <?php if ($top_bar_secondary_menu) :?>
          <?php print $top_bar_secondary_menu; ?>
        <?php endif; ?>
      </section>
    </nav>
<?php if ($top_bar_classes): ?>
  </div>
<?php endif; ?>
