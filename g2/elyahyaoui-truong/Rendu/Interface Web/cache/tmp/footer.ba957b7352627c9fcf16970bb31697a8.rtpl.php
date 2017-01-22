<?php if(!class_exists('raintpl')){exit;}?><!--
 @nom: footer
 @auteur: Idleman (idleman@idleman.fr)
 @description: Page de bas de page commun a toutes les vues
-->

      <hr>

      <footer>
        <p>HCC &copy; IdleBlog <?php echo $copyYears;?></p>
      </footer>

    </div><!-- /container -->

    <!-- Le javascript
    ================================================== -->
    <script src="./templates/hcc/././js/jquery.min.js"></script>
    <script src="./templates/hcc/././js/bootstrap.min.js"></script>
	
	<script type="text/javascript">
	
	$('#myTab a').click(function (e) {
		e.preventDefault();
		$(this).tab('show');
    })
	
	</script>

  </body>
</html>
