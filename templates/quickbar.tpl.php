<nav id="quickbar-top-bar" class="top-bar" data-topbar="" data-options="is_hover: false">
    <ul class="title-area">
        <li class="name">
            <h1><?php print $title; ?></h1>
        </li>
        <li class="toggle-topbar menu-icon"><a href="#"><span></span></a></li>
    </ul>

    <section class="top-bar-section">
      <?php foreach ($tree_0 as $links): ?>
        <?php print $links; ?>
      <?php endforeach; ?>
    </section>
</nav>
