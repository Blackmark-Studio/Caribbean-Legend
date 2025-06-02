// Джиллиан Стайнер - просто девушка
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
				dialog.text = "No quiero hablar contigo. Atacas a civiles pacíficos sin razón y los provocas a luchar. ¡Piérdete!";
				link.l1 = "Mm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Oh... ¡hola! Me asustaste. Has aparecido tan silenciosamente... ¿Qué quieres?";
				link.l1 = TimeGreeting()+". Mi nombre es "+GetFullName(pchar)+". Soy un recién llegado aquí y estoy conociendo a los lugareños y finalmente he decidido venir a hablar con una dama tan bonita como tú. ¿Cuál es tu nombre?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"¡ "+TimeGreeting()+"¡¿Quieres algo?!";
				link.l1 = LinkRandPhrase("¿Tienes algo interesante que decir?","¿Ha sucedido algo nuevo en la isla?","¿Me contarás los últimos chismes?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Quiero hacerte unas preguntas sobre la isla.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Solo quería saber cómo estás. ¡Nos vemos!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Haces que me sonroje, señor, pero es un placer de todos modos. Gracias por el cumplido. Mi nombre es Jillian, Jillian Steiner. Encantada de conocerte.";
			link.l1 = "Yo también, Jillian.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "¿Eres nuevo aquí? ¿Y cómo llegaste aquí, dime? ¿Has sobrevivido al naufragio?";
			link.l1 = "Bueno... algo así. Estaba navegando aquí en un barco y casi logré pasar los arrecifes, pero desafortunadamente choqué con los escombros de los barcos y mi bote se hundió. Y nadé hasta aquí por mi cuenta.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "¡Oh! ¿Así que has venido aquí por tu propia elección? ¡Increíble!";
			link.l1 = "Sí, estoy tan loco. Decidí encontrar esa Isla Justicia y finalmente la he encontrado. Aunque ahora no sé cómo salir de ella.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Eres muy valiente o imprudente. Navegar aquí en una barca... Ahora vivirás con nosotros aquí porque nadie ha podido dejar este lugar en la última década.";
			link.l1 = "Todavía tengo esperanza. Está bien, Jillian, no te molestaré. ¡Nos vemos!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Sí, claro, "+pchar.name+" . Estoy escuchando.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "¿Cómo llegaste aquí?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "¿Quieres abandonar la Isla?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "¿Y cómo va tu día? ¿Qué haces?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Dices que no estás casada... ¿No tiene una chica tan bonita pretendientes aquí?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sin preguntas. Perdón...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Estaba navegando desde Inglaterra con mis padres. Queríamos comenzar una nueva vida, y... he comenzado una nueva vida aquí. Mis padres murieron y yo apenas sobreviví. Alcancé un barco del anillo exterior y estuve tendido allí inconsciente por un día hasta que uno que pasaba por ahí me encontró. Habría muerto allí si no me hubiera encontrado.";
			link.l1 = "Veo...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "¿Y adónde? ¿Quién me necesita y dónde? No tengo hogar, ni esposo, ni dinero. Nunca he estado en ningún lugar excepto en esta Isla y en los barrios bajos de Londres. Parece que es mi destino vivir aquí...";
			link.l1 = "¿Estás seguro de eso?";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Principalmente ayudo al hermano Julián en la iglesia. También hago algún trabajo sencillo en la tienda de Axel. Así es como gano monedas. Soy una chica y no puedo trepar por los escombros del barco en el anillo exterior.";
			link.l1 = "Claro...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Tee-hee... hay admiradores, sí, pero no tienen valor. No me gusta ninguno de ellos y no quiero vivir con un hombre que no me gusta. Los hombres que me gustan no me prestan atención. Bueno, solo soy una pobre chica común...";
			link.l1 = "Es solo el comienzo de una nueva vida para ti...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("¿Qué haces ahí, eh? ¡Ladrón!","¡Solo mira eso! ¡Tan pronto como me perdí en la contemplación, decidiste revisar mi cofre!","¿Has decidido revisar mis cofres? ¡No te saldrás con la tuya!");
			link.l1 = "¡Mierda!";
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
			dialog.text = LinkRandPhrase("Escucha, será mejor que guardes tu arma. Me pone nervioso.","Sabes, correr con espada no se tolera aquí. Guárdala.","Escucha, no hagas el papel de un caballero medieval corriendo con una espada. Guárdala, no te queda bien...");
			link.l1 = LinkRandPhrase("Bien.","Bien.","Como dices...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Escucha, soy ciudadano de la ciudad y te pediría que bajes tu espada.","Escucha, soy ciudadano de la ciudad y te pediría que mantuvieras tu espada baja.");
				link.l1 = LinkRandPhrase("Bien.","Lo que sea entonces.","Como tú digas...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ten cuidado, amigo, al correr con un arma. Puedo ponerme nervioso...","No me gusta cuando los hombres caminan frente a mí con sus armas listas. Me asusta...");
				link.l1 = RandPhraseSimple("Entendido.","Me lo llevo.");
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
