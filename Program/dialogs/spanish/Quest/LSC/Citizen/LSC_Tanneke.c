// Таннеке Эверс - просто девушка
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "¡No quiero hablar contigo! Atacas a civiles pacíficos sin razón y los provocas para pelear. ¡Lárgate!";
				link.l1 = "Mm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "¡Buen día! ¿Te conozco? No te he visto antes, eso es seguro...";
				link.l1 = TimeGreeting()+". Es cierto, soy un nuevo... visitante aquí. Mi nombre es "+GetFullName(pchar)+" y soy un capitán.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"¡ "+TimeGreeting()+"¡¿Quieres algo?!";
				link.l1 = LinkRandPhrase("¿Tienes algo interesante que decir?","¿Ha pasado algo nuevo en la isla?","¿Me contarás los últimos chismes?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Quiero hacerte algunas preguntas sobre la isla.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Solo quería saber cómo estás. ¡Nos vemos!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "¿Has sido capitán?";
			link.l1 = "¿Por qué he estado? Sigo siendo un capitán... ¡a-ah, lo entiendo! Crees que mi barco se ha hundido o ha sido destruido por los arrecifes. No. Ella está cerca de las costas de Tierra Firme occidental. Y he llegado a este lugar en una barca, aunque terminó mal, la barca tuvo un agujero en el casco y se hundió.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "¿Has venido aquí en un bergantín? ¿Y cómo lograste sobrevivir a la tormenta?";
			link.l1 = "¿Qué tormenta? No recuerdo ninguna tormenta...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "¿Pero cómo es eso? Siempre hay una tormenta alrededor de la Isla. Todos lo dicen.";
			link.l1 = "Bueno, no lo es o tuve la suerte de evitarlo. El mar estaba absolutamente en calma... disculpe, ¿puedo saber el nombre de una dama tan bonita?";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "¡Oh! Lo siento, me olvidé de presentarme... Me llamo Tanneke. Encantada de conocerte.";
			link.l1 = "Encantado de conocerte también, Tanneke... Es un placer.";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "¿Y por qué has decidido llegar a nuestra Isla en un bergantín? A-ah, ya entiendo, la corriente te trajo directamente aquí. Nadie sabe de la Isla y la gente siempre llega por casualidad.";
			link.l1 = "No es correcto. Hay chismes bastante ciertos sobre la Isla, incluyendo su ubicación. Así que he decidido verla con mis propios ojos...";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "Ahora veo. Eres igual que Adolf Barbier, leíste demasiado sobre el capitán Alvarado y decidiste buscar el oro del almirante de Betancourt. Ay, capitán, si un bribón tan astuto como Barbier no pudo encontrarlo, dudo que tú lo logres tampoco\nY realmente pienso que no hay oro del almirante, Antonio debe haberlo inventado solo para mostrarnos qué tan importante era su abuelo... Bueno, entonces te quedarás con nosotros. Llegar aquí fue fácil, pero irse debe ser imposible. Quiero decir, irse de aquí entero.";
			link.l1 = "No es nada. Creo que podré encargarme de eso, no me refiero al oro de Betancourt que has mencionado, es la primera vez que oigo hablar de ello, me refiero a dejar la Isla. Vivo. Fue un placer hablar contigo, Tanneke. ¡Hasta luego!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Pregunta, capitán...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "¿Cómo llegaste aquí?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "¿Alguna vez has intentado dejar la Isla?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "¿Cómo vivís aquí?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "¿Las chicas necesitan comprar comida al almirante o la obtienen gratis?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sin preguntas. Perdón...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Soy holandesa, pero vivíamos en Santiago. Mis padres me enviaron a trabajar como criada para la familia del banquero Geraldi. ¿Has oído hablar de ellos? Hace tres años, uno de ellos navegó hacia la Nueva España en un lugre correo. Me dijeron que lo acompañara. En el segundo día de nuestro viaje, fuimos atrapados por un bergantín bajo la bandera española. Su oficial subió a bordo de nuestra nave y habló con nuestro capitán, el capitán se enfureció y echó al oficial. Nos atacaron tan pronto como el visitante llegó a su barco. Intentamos huir, pero lograron abordarnos. Por lo que entendí, necesitaban a mi maestro Geraldi, porque se precipitaron dentro de una cabina, lo capturaron y se lo llevaron. A mí y a los marineros nos llevaron a la bodega y nos dejaron allí. Pensé que nos hundirían, pero simplemente se alejaron. Los marineros lograron salir de la bodega, pero nuestro capitán fue asesinado en combate y ninguno de los sobrevivientes sabía cómo navegar un rumbo correcto. Navegamos hacia algún lugar durante algún tiempo hasta que un fuerte vendaval nos llevó. Unas horas después, nuestro lugre fue arrojado al anillo exterior. Todavía está allí. Tuve la suerte de sobrevivir al caos, después del amanecer, yo y algunas otras personas 'afortunadas' llegamos a la Isla.";
			link.l1 = "Ya veo...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "No. ¿Y cómo te imaginas eso? No hay barcos listos para zarpar aquí y usar un bote es tan bueno como firmar tu propia sentencia de muerte. Como dije, aquí las tormentas son frecuentes. Solo recuerdo un intento de dejar este lugar: cinco ciudadanos construyeron un bote decente con velas y remos\nLucharon contra la corriente durante varias horas y finalmente llegaron al mar abierto. Días después, uno de ellos regresó al anillo exterior... atado a un mástil destrozado y muerto. Esto mató los deseos de otros de hacer tales hazañas valientes.";
			link.l1 = "Entendido...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Está bien. No es peor que ser un sirviente de la familia de ese usurero arrogante. Solo necesitas acostumbrarte a este lugar y después incluso podrías amarlo. Por cierto, no soy el único que piensa así. Y los clanes... no me molestan.";
			link.l1 = "Interesante...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Por supuesto que compramos. Oh, capitán, hay suficiente trabajo para una chica: limpiar, cocinar, ayudar a otros... no estamos ociosas, pero nadie se rompe la espalda aquí. Los piratas venden comida barata para los ciudadanos comunes, a diferencia de los clanes. Así que no pasamos hambre\nAyudo a Gillian y Natalie y ellas me ayudan si lo necesito. Somos amigas. Hay otra chica en la Isla, la española. Se llama Ramona pero está mayormente sola y no estamos realmente ansiosas por ser amigas de ella.";
			link.l1 = "¿Y por qué es eso?";
			link.l1.go = "ansewer_4_1";
		break;
		
		case "ansewer_4_1":
			dialog.text = "Bueno... digamos que tenemos diferentes puntos de vista sobre la vida. Habla con ella y lo entenderás.";
			link.l1 = "Interesante...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("¿Qué estás haciendo allí, eh? ¡Ladrón!","¡Solo mira eso! ¡Tan pronto como me perdí en la contemplación, decidiste revisar mi cofre!","¿Has decidido revisar mis cofres? ¡No te saldrás con la tuya!");
			link.l1 = "¡Maldición!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "¿Qué?! ¿Decidiste revisar mis cofres? ¡No te saldrás con la tuya!";
			link.l1 = "¡Chica tonta!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Escucha, será mejor que guardes tu arma. Me pone nervioso.","Sabes, correr con espada no se tolera aquí. Guárdala.","Escucha, no juegues a ser un caballero medieval corriendo con una espada por ahí. Guárdala, no te queda bien...");
			link.l1 = LinkRandPhrase("Bien.","Como desees...","Como usted diga...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Escucha, soy ciudadano de la ciudad y te pediría que bajes tu espada.","Escucha, soy ciudadano de la ciudad y te pediría que mantengas tu espada baja.");
				link.l1 = LinkRandPhrase("Bien.","Como desees...","Como usted diga...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ten cuidado, camarada, al correr con un arma. Puedo ponerme nervioso...","No me gusta cuando los hombres caminan delante de mí con sus armas listas. Me asusta...");
				link.l1 = RandPhraseSimple("Entendido.","Me lo estoy llevando.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
