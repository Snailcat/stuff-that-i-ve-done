
$(document).ready(function(){
 
$(".mymagicoverbox").click(function()
{
        $('#myfond_gris').fadeIn(300);
        var iddiv = $(this).attr("iddiv");
        $('#'+iddiv).fadeIn(300);
        $('#myfond_gris').attr('opendiv',iddiv);
        return false;
});
 
$('#myfond_gris, .mymagicoverbox_fermer').click(function()
{
        var iddiv = $("#myfond_gris").attr('opendiv');
        $('#myfond_gris').fadeOut(300);
        $('#'+iddiv).fadeOut(300);
});
 
});

