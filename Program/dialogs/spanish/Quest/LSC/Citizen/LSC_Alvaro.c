// Альваро Гомец - капитан
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
				dialog.text = "¡Oh, una cara nueva! Saludos. ¿Y cuándo llegaste aquí? No recuerdo ningún naufragio reciente.";
				link.l1 = TimeGreeting()+". Mi nombre es "+GetFullName(pchar)+". Y mi barco se hundió tan silenciosa y rápidamente que nadie lo notó. Y llegué a la Isla rápida y silenciosamente también. Así, tal cual...";
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
			dialog.text = "Veo, oh, olvidé presentarme. Perdóname, señor. Mi nombre es Álvaro Gómez y una vez fui capitán de mi propio bergantín. Eh, ahora mi hermoso bergantín yace en el fondo justo detrás del anillo exterior... Mucha agua ha corrido bajo el puente desde entonces. Ah, lo que sea. ¡Encantado de conocerte!";
			link.l1 = "Encantado de conocerte también, señor Gomez.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("¿Tienes algo interesante que decir?","¿Ha sucedido algo nuevo en la isla?","¿Me contarás los últimos chismes?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Quiero hacerte algunas preguntas sobre la isla.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Estoy escuchando, señor.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Dijiste que habías sido capitán. ¿Cómo llegaste a la isla?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "¿Qué puedes decirme sobre la vida en la isla?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Dime, ¿los lugareños viven aquí en paz o no? No hablo de los clanes, por supuesto.";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "¿Y de dónde obtienen los lugareños las provisiones?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sin preguntas. Perdón...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Como todos los demás. La tormenta me atrapó, perdí mi mástil y el control del timón. La corriente nos arrastró y nos lanzó contra los arrecifes. Mi barco ni siquiera llegó al anillo exterior y fue destruido. Solo unos pocos hombres sobrevivieron.";
			link.l1 = "Historia triste...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "¿Qué puedo decir? Tenemos todo lo necesario para vivir adecuadamente. Aunque a veces se vuelve realmente aburrido aquí. Y esa melancolía... El primer año fue el peor, pero luego me acostumbré. Me siento mal por mi pobre esposa Sabrina, debe estar segura de que morí. Espero que haya logrado casarse de nuevo\nNo te preocupes, te acostumbrarás. Visita la taberna, la tienda, la iglesia, conoce a otras personas. No vayas a los Narvales o a los Rivados hasta que realmente sea necesario, son unos bastardos astutos.";
			link.l1 = "Veo...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Es cierto, las peleas y riñas están secretamente prohibidas aquí. Si golpeas a alguien sin una razón adecuada o, Dios no lo quiera, matas, entonces acabarás siendo aislado. Podrías incluso ser arrojado por la borda una noche. Hubo algunos peleadores antes en la Isla. El primero simplemente desapareció, el segundo murió en una celda del Tártaro después de pasar meses dentro. Claro, eso no significa que no puedas protegerte. Pero los locales son bastante pacíficos en realidad. Abbott es ostentoso, pero no agresivo. Kassel es un verdadero bastardo, pero mantiene sus manos limpias. Pratt es un ex convicto, pero es inofensivo. Tenemos dos ex oficiales de la marina aquí, Loderdale y Solderra. Llegaron aquí mientras tenían una batalla no muy lejos. Irónicamente, ambos sobrevivieron para seguir haciendo planes sanguinarios el uno contra el otro.";
			link.l1 = "Entendido...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "De las bodegas, por supuesto. Todas las provisiones, recogidas de otros barcos, solían almacenarse en San Agustín y compartirse entre todos hasta que aparecieron los piratas. Ahora aprietan la Isla en su puño porque son dueños de los suministros\nClaro, tenemos nuestros propios escondites, así que está bien. También cazamos aves y pescamos... Pero la mejor caza termina con la muerte de un cangrejo gigante. Tienen una carne muy sabrosa y nutritiva. Aunque solo se pueden ver en el anillo exterior\nBucear para cazarlos es demasiado arriesgado. Hubo uno lo suficientemente valiente para cazarlos bajo el agua. Un día él mismo se convirtió en presa. Nadie quiere cazar cangrejos allí desde entonces.";
			link.l1 = "Interesante...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("¿Qué estás haciendo ahí, eh? ¡Ladrón!","¡Solo mira eso! Tan pronto como me perdí en la contemplación, ¡decidiste revisar mi cofre!","¿Has decidido revisar mis cofres? ¡No te saldrás con la tuya!");
			link.l1 = "¡Maldita sea!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "¿Qué?! ¿Decidiste revisar mis cofres? ¡No te saldrás con la tuya!";
			link.l1 = "¡Muchacha tonta!";
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
			dialog.text = LinkRandPhrase("Escucha, será mejor que guardes tu arma. Me pone nervioso.","Sabes, correr con espada no se tolera aquí. Guárdala.","Escucha, no te hagas el caballero medieval corriendo con una espada por ahí. Guárdala, no te queda bien...");
			link.l1 = LinkRandPhrase("Bien.","Claro.","Como dices...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Escucha, soy ciudadano de la ciudad y te pediría que bajes tu espada.","Escucha, soy ciudadano de la ciudad y te pediría que mantengas tu espada baja.");
				link.l1 = LinkRandPhrase("Bien.","Lo que sea entonces.","Como tú digas...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ten cuidado, camarada, al correr con un arma. Puedo ponerme nervioso...","No me gusta cuando los hombres caminan frente a mí con su arma lista. Me asusta...");
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
