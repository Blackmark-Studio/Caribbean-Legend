// Куранай - индеец
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
				dialog.text = "No quiero hablar contigo. Atacas a civiles pacíficos sin motivo y los provocas a pelear. ¡Piérdete!";
				link.l1 = "Mm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "¿Qué quiere el hermano blanco?";
				link.l1 = TimeGreeting()+". ¿Hermano blanco? Dime, ¿por qué ustedes, los indios, nos llaman o hermanos blancos o perros pálidos, eh?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"¡ "+TimeGreeting()+"¡¿Quieres algo?!";
				link.l1 = LinkRandPhrase("¿Tienes algo interesante que contar?","¿Ha pasado algo nuevo en la isla?","¿Me contarás los últimos chismes?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Quiero hacerte unas preguntas sobre la isla.";
				link.l2.go = "int_quests"; //информационный блок
				if (CheckAttribute(npchar, "quest.answer_2"))
				{
					link.l3 = "Muestra lo que pudiste encontrar. Quizás, compraría algo...";
					link.l3.go = "trade";
				}
				link.l5 = "Solo quería saber cómo estás. ¡Nos vemos!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Todos vivimos en paz aquí, hermano blanco. Curanai no llama al hermano blanco el perro cara pálida. No todos los cara pálida son perros. Puedo llamar a muchos indios el perro piel roja.";
			link.l1 = "Mm. Supongo que eres un filósofo...";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Curanai no te entiende, hermano blanco. ¿Qué significa filósofo?";
			link.l1 = "No importa, hermano piel roja. Me gusta cómo piensas. ¿Dices que te llamas Curanai? Mi nombre es "+GetFullName(pchar)+" Encantado de conocerte.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Curanai se alegra de saber el nombre del hermano blanco.";
			link.l1 = "Bien. ¡Nos vemos!";
			link.l1.go = "exit";
			link.l3 = "Quiero hacerte unas preguntas sobre la isla.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		case "trade":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 4)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Pregunta, hermano rostro pálido, Curanai responde.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "¿Cómo llegaste aquí?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "¿Qué haces en la Isla?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "¿Quieres llegar a casa?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "¿Vives pacíficamente en la Isla Justicia? ¿Aquí ocurren peleas o disputas?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sin preguntas. Perdón...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Yo y varios guerreros de mi tribu decidimos navegar hacia una pequeña isla cerca de nuestra tierra, visible en un día claro. Hicimos una balsa de bambú y navegamos. Pero la tormenta nos sorprendió de repente y nos llevó al mar abierto. No nos dimos cuenta de lo rápido que nuestra tierra y la isla desaparecieron.\nNavegamos por el mar muchas, muchas noches y días. Todos mis hermanos murieron de sed y hambre. Me quedé solo - los espíritus se apiadaron de Curanai y llevaron la balsa a esta isla. Sobreviví.";
			link.l1 = "Sí... Triste historia.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Curanai pesca. Curanai golpea al pez con arpón. Raramente, muy raramente, golpea un gran cangrejo. Entonces Curanai está feliz - el cangrejo es sabroso, muy sabroso. Una pinza es suficiente para unos cuantos días. Y Curanai también se sumerge al fondo en un lugar. No hay grandes cangrejos allí. Curanai recoge piedra amarilla, piedra azul, piedra negra y perla. Grandes y pequeñas. Luego Curanai las vende al rostro pálido.";
			link.l1 = "Veo...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Curanai quiere ir a casa. Pero ¿dónde está mi hogar? Curanai no sabe dónde está su aldea ni cómo llegar a ella.";
			link.l1 = "Hum. ¿Qué puedo decir...?";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Narvales y Rivados pelean a menudo uno contra otro. Vivimos en paz y no hacemos daño a nadie. A veces los rostros pálidos beben agua de fuego y maldicen, pero no matan. Hay dos oficiales-guerreros, uno odia al otro. Un día uno matará al otro. Curanai lo sabe.";
			link.l1 = "Veo...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("¿Qué haces ahí, eh? ¡Ladrón!","¡Solo mira eso! Tan pronto como me perdí en la contemplación, decidiste revisar mi cofre.","¿Decidiste revisar mis cofres? ¡No te saldrás con la tuya!");
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
			dialog.text = LinkRandPhrase("Escucha, será mejor que guardes tu arma. Me pone nervioso.","Sabes, correr con la hoja no se tolera aquí. Quítala de en medio.","Escucha, no juegues al caballero medieval corriendo con una espada. Guárdala, no te queda bien...");
			link.l1 = LinkRandPhrase("Bien.","Seguro.","Como usted diga...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Escucha, soy ciudadano de la ciudad y te pediría que guardes tu espada.","Escucha, soy ciudadano de la ciudad y te pediría que mantuvieras tu espada en su lugar.");
				link.l1 = LinkRandPhrase("Bien.","Entonces, lo que sea.","Como dices...");
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
