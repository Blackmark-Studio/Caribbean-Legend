// Лайонел Маскетт - мещанин
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
				dialog.text = "No quiero hablar contigo. Atacas a civiles pacíficos sin razón y los provocas a pelear. ¡Piérdete!";
				link.l1 = "Mm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Saludos, "+GetAddress_Form(NPChar)+". ¿Eres un recién llegado?";
				link.l1 = TimeGreeting()+". Mi nombre es "+GetFullName(pchar)+". Sí, lo soy.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"¡ "+TimeGreeting()+"¡¿Quieres algo?!";
				link.l1 = LinkRandPhrase("¿Tienes algo interesante que decir?","¿Ha ocurrido algo nuevo en la isla?","¿Me contarás los últimos chismes?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Quiero hacerte unas preguntas sobre la isla.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Solo quería saber cómo estás. ¡Nos vemos!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Mi nombre es Lionell. Encantado de conocerte. ¿Cómo llegaste aquí?";
			link.l1 = "En un bergantín... Oí que hay una base de contrabandistas y decidí explorarla... La exploré. El bergantín se hundió y aquí estoy.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "¿Realmente consideran la Isla como una base de contrabandistas?";
			link.l1 = "Bueno, no oficialmente. La mayoría ni siquiera cree en tu existencia.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "En serio... ¿Y por qué deberían? En realidad, no existimos. No puedes dejar este lugar. Aunque dicen que había una conexión con Cuba... Pero no lo recuerdo y he estado viviendo aquí casi ocho años.";
			link.l1 = "Ya veo. Fue un placer hablar contigo. ¡Nos vemos!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("¿Tienes algo interesante que decir?","¿Ha ocurrido algo nuevo en la isla?","¿Me contarás los últimos chismes?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Quiero hacerte unas preguntas sobre la isla.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Estoy escuchando.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "¿Cómo llegaste aquí?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "¿Te gustaría regresar al continente?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "¿Y qué hace la gente aquí, en la Isla?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "¿Y de dónde consigues todas las cosas aquí? ¿Comida, tela, bebidas?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sin preguntas. Perdón...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Esa es una historia extraña. Esta Isla es el único lugar de todos los Caribes que he visto. Cuando las cosas se pusieron mal para mí, navegué en un barco mercante desde la vieja Inglaterra. Iba a encontrar un trabajo en Belice, para ser un empleado de la oficina del puerto. Pero nunca llegamos a Belice\nNo soy marinero, así que no sé los detalles. Hubo una tormenta y al día siguiente nuestro barco fue destruido por los arrecifes. Nunca olvidaré ese terrible golpe, los gritos\nAlguien gritó que había un agujero en el casco, la gente empezó a saltar por la borda. Yo... no sé nadar. Así que me quedé. Irónicamente, eso salvó mi vida. El barco sobrevivió y la tormenta se calmó al amanecer\nTomé la única decisión correcta antes de dejar el barco. Tomé algo de comida, construí una balsa y navegué por un mar en calma hasta el anillo exterior. Así sobreviví, el único de toda la tripulación.";
			link.l1 = "Veo...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Fue mi único sueño durante los primeros dos años aquí. Pero ahora... ¿Qué hace a la Isla peor que cualquier otro lugar en el mundo? Sí, no hay campos verdes con ovejas, pero hay un mar magnífico y un cielo nocturno lleno de hermosas estrellas. Estoy bien alimentado, llevo una tela decente, que no podía permitirme mientras vivía en Inglaterra. Tengo muchos amigos\n No, señor, no quiero dejar este lugar. ¿Qué me espera allá afuera? ¿Un trabajo de oficina bajo un jefe ruidoso por trescientos pesos a la semana? ¡De ninguna manera! He encontrado todo lo que buscaba aquí, no necesito nada más.";
			link.l1 = "¡Entendido. Me alegro por ti!";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Lo que más les gusta. Los clanes juegan a la guerra, los piratas venden provisiones, Axel Yost compra y vende cosas, Sancho Carpentero sirve bebidas y entretiene a la gente, el hermano Julián reza, dice misa y vende medicinas. Loderdale y Solderra intrigan el uno contra el otro, al abad le gusta estar engreído, Jillian y Tanneke sueñan con el amor verdadero...";
			link.l1 = "Interesante...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "De los barcos, amigo, de los barcos. La actividad favorita de la mayoría es explorar los navíos del anillo exterior y sacar cosas de ellos. Puedes encontrar de todo allí, armas, medicinas, especias y ron. Muchos barcos aún no han sido explorados. La corriente del mar a menudo trae aquí otra víctima...";
			link.l1 = "Interesante...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("¿Qué estás haciendo ahí, eh? ¡Ladrón!","¡Solo mira eso! ¡Tan pronto como me perdí en la contemplación, decidiste revisar mi cofre!","¿Decidiste revisar mis cofres? ¡No te saldrás con la tuya!");
			link.l1 = "¡Maldita sea!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "¿Qué?! ¿Decidiste revisar mis cofres? ¡No te saldrás con la tuya!";
			link.l1 = "¡Chica insensata!";
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
			dialog.text = LinkRandPhrase("Escucha, será mejor que guardes tu arma. Me pone nervioso.","Sabes, correr con espada no se tolera aquí. Guárdala.","Escucha, no juegues al caballero medieval corriendo con una espada por ahí. Guárdala, no te queda bien...");
			link.l1 = LinkRandPhrase("Bien.","Está bien.","Como usted dice...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Escucha, soy ciudadano de la ciudad y te pediría que bajes tu espada.","Escucha, soy ciudadano de la ciudad y te pediría que bajaras tu espada.");
				link.l1 = LinkRandPhrase("Bien.","Está bien.","Como tú digas...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ten cuidado, camarada, al correr con un arma. Puedo ponerme nervioso...","No me gusta cuando los hombres caminan frente a mí con sus armas listas. Me asusta...");
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
