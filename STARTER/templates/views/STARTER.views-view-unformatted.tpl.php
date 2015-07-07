<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * Integrated wrapping elements into if statement. If a class isn't
 * added to a views row the entire wrapping element is dropped.
 *
 * @ingroup views_templates
 */
?>
<?php if (!empty($title)): ?>
  <h3><?php print $title; ?></h3>
<?php endif; ?>

<?php foreach ($rows as $id => $row): ?>
  <?php if (isset($classes_array[$id])) { print '<div class="' . $classes_array[$id] .'">';  } ?>
    <?php print $row; ?>
  <?php if (isset($classes_array[$id])) { print '</div>'; } ?>
<?php endforeach; ?>
