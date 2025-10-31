#include "DIALOGS\%language%\Common_Duel.c"

#define MAX_PGG_STORIES 9
#define MAX_PGG_QUEST_STORIES 3
#define MAX_PGG_MEET_REP 5

string PGG_Stories[MAX_PGG_STORIES] = {
	"... ¡Demonios, solo yo sé la ubicación y el último hombre en pie los matará a todos!..\n",
	"... Y Maynard dijo: 'No espero misericordia, así que no deberías'...\n",
	"... Él era ese borracho que propuso organizar ese infierno tan especial, solo para ver quién de nosotros aguantaría más tiempo...\n",
	"... Divertida historia de mi viejo amigo de Portobello...\n",
	"... No, caballero, esas son unas anécdotas de mierda. Tengo algunas buenas historias para tus oídos...\n",
	"... No puedo decir mucho sobre el Holandés Errante, nunca lo he visto. Una vez abordé un extraño bergantín que estaba vacío, sin una sola alma a bordo. ¡Adivina qué! ¡Había 1.700 barriles de buen vino en su bodega! ¡Eso es lo que yo llamo suerte!\n",
	"... Tiendo a creer que toda esa basura del 'Holandés Errante' es falsa...\n",
	"... ¿Alguna vez escuchaste que acabó con neurosis de guerra en Key West?...\n",
	"... ¡ja-ja-ja!... Muy buena...\n"};

string PGG_QuestStories[MAX_PGG_QUEST_STORIES] = {
	"... Me quedé atrapado en Florida una vez...",
	"... No puedo decir mucho sobre el Holandés Errante, nunca lo he visto. Una vez abordé un extraño bergantín que estaba vacío, sin una sola alma a bordo. ¡Adivina qué! ¡Había 1.700 barriles de buen vino en su bodega! ¡Eso es lo que yo llamo suerte!",
	"... Ella mató a ese pobre bastardo justo en medio de la taberna, después de que él le sugiriera probar sus 'habilidades oficiales' en el piso de arriba..."}

string PGG_Meet_GoodRep[MAX_PGG_MEET_REP] = {
	"Los capitanes decentes son raros en estas aguas.",
	"La nobleza está pasada de moda en estos días.",
	"¡Oh, este es un capitán decente! ¡No como vosotros, asesinos! ¡Je-je!",
	"Caballeros, tenemos un capitán decente en nuestra mesa, que ha superado el fuego y el agua innumerables veces. ¿Qué nos puede decir, estimado?",
	"Ahora solo soy otro glorioso corsario, que no está acostumbrado a seguir las directrices reales.",
};

string PGG_Meet_BadRep[MAX_PGG_MEET_REP] = {
	"¡He aquí otro pirata!",
	"Caballeros, ¿Supongo que tenemos a un buscador de fortuna en nuestra mesa?",
	"¡Huelo a pólvora y sangre! ¡Un filibustero hasta la médula!",
	"Oh caballeros, ahora este es un corsario experimentado, que seguramente tiene algo que contar con la encantadora compañía de una jarra de ron... ¿Te gustaría unirte a nosotros?",
	"Oh, huelo a pólvora... caballeros, tenemos aquí a otro glorioso corsario. Estoy seguro de que ha estado en el infierno y tendrá mucho que contar en confesión... ¡Ja, ja, ja!",
};

void ProcessDialogEvent()
{
	int i, n;
	int iRnd = -1;
	int iAns;
	bool bOk;
	float locx, locy, locz;
	string sTmp, sLoc;
	ref NPChar, sld;
	aref link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessDuelDialog(NPChar, link, NextDiag);

	if (Dialog.CurrentNode == "First time" && CheckAttribute(NPChar, "meeting"))
		Dialog.CurrentNode = "Second time";
	switch (Dialog.CurrentNode)
	{
		//	Dialog.Text = "Si veis un fallo... informadlo a AT, para la Marina.";
		//	link.l1 = "¡Ciertamente!";
		//	link.l1.go = "exit.";
	case "First time":
		if (CheckAttribute(NPChar, "PGGAi.location.town.back") && CheckAttribute(pchar, "questTemp.PGGContra.Know"))
		{
			Dialog.text = "¡Eh, lárgate, no lo harás! Si arruinas mi trato, ¡arrancaré tu corazón!";
			link.l1 = RandPhraseSimple("¿Te atreves a amenazarme, canalla?!", "¡Te haré tragarte tus palabras, canalla!");
			link.l1.go = "Exit_Smugglers_Fight";
			link.l2 = "Oh, ya veo. Los negocios son negocios. Buena suerte.";
			link.l2.go = "Exit";
			break;
		}
		//		Dialog.Text = "Buenas tardes, mi nombre es "+GetFullName(NPChar)+", ¿y el tuyo?";
		if (rand(10) == 3)
		{
			iRnd = rand(MAX_PGG_QUEST_STORIES - 1);
			Dialog.Text = PGG_QuestStories[iRnd];
		}
		else
		{
			iRnd = rand(MAX_PGG_STORIES - 1);
			iAns = rand(MAX_PGG_MEET_REP - 1);
			Dialog.Text = PGG_Stories[iRnd] + PCharRepPhrase(PGG_Meet_GoodRep[iAns], PGG_Meet_BadRep[iAns]);
		}
		//		link.l1 = "Mi nombre es "+GetFullName(pchar)+".";
		link.l1 = PCharRepPhrase(RandSwear() + RandPhraseSimple("¡Ron para todos! Yo soy el capitán " + GetFullName(pchar) + ".", "Soy el capitán de '" + PChar.Ship.Name + " y un par de cientos de auténticos diablos! ¡Je-je! Mi nombre es " + GetFullName(pchar) + "."), RandPhraseSimple("Permítanme presentarme, caballeros. Soy el capitán " + GetFullName(pchar) + ".", "Aún no nos hemos presentado. Soy el capitán del '" + PChar.Ship.Name + " bajo la bandera de " + NationNameGenitive(sti(PChar.nation)) + ". Mi nombre es " + GetFullName(pchar) + "."));
		link.l1.go = "Meeting";
		break;

	case "Meeting":
		Dialog.Text = "¡Bueno, todos me conocen aquí! Yo soy " + GetFullName(NPChar) + ". ¡Mucho gusto! ¿Qué puedo hacer por ti?";
		link.l1 = RandPhraseSimple("¡Tengo negocios contigo!", "Quiero hablar contigo...");
		link.l1.go = "quest";
		if (sti(pchar.Ship.Type) != SHIP_NOTUSED && sti(NPChar.Ship.Type) != SHIP_NOTUSED)
		{
			sld = GetRealShip(sti(NPChar.Ship.Type));

			Dialog.Text = "¡Bueno, todo el mundo me conoce aquí! Yo soy " + GetFullName(NPChar) + ", capitán " + xiStr(sld.BaseName + "Acc") + " " + NPChar.Ship.Name + ".";
			link.l2 = "¿Qué tal si te unes a mí? Dos barcos son mejor que uno. Podemos hacer buenos negocios juntos.";
			link.l2.go = "companion";
		}
		if (sti(NPChar.Ship.Type) == SHIP_NOTUSED)
		{
			link.l3 = RandPhraseSimple("¿Querrías servir como oficial en mi barco?", "Creo que te iría bien como oficial en mi barco. ¿Qué dices?");
			link.l3.go = "officer";
		}
		if (bBettaTestMode)
		{
			link.l7 = "(Beta-test) Misiones.";
			link.l7.go = "BT_Quest";
			link.l8 = "(Beta-prueba) Duelos.";
			link.l8.go = "outraged";
		}
		link.l9 = "Nada.";
		link.l9.go = "exit";
		NextDiag.TempNode = "Second time";
		NPChar.meeting = true;
		break;

	case "Second time":
		if (CheckAttribute(NPChar, "PGGAi.location.town.back") && CheckAttribute(pchar, "questTemp.PGGContra.Know"))
		{
			Dialog.text = "¡Eh, lárgate, no te parece! Si arruinas mi trato, ¡te arrancaré el corazón!";
			link.l1 = RandPhraseSimple("¿Te atreves a amenazarme, canalla?!", "¡Te haré atragantarte con tus propias palabras, granuja!");
			link.l1.go = "Exit_Smugglers_Fight";
			link.l2 = "Oh, ya veo. Los negocios son negocios. Buena suerte.";
			link.l2.go = "Exit";
			break;
		}

		if (CheckAttribute(NPChar, "QuestTalk") && GetNpcQuestPastDayParam(NPChar, "QuestTalk") < 1)
		{
			Dialog.Text = "¡Ya te he contado todo por hoy!";
			link.l1 = "Ah, sí...";
			link.l1.go = "exit";
			break;
		}

		Dialog.text = RandPhraseSimple("¿Qué necesitas?" + GetFullName(pchar) + "?", "¿Quién es ese? Ah, tú... Pierde de vista, no estoy de humor...");
		link.l1 = RandPhraseSimple("¿Qué tal un negocio?", "Quería hablar contigo...");
		link.l1.go = "quest";

		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) > 49)
		{
			//			Dialog.Text = RandPhraseSimple("¡Oh, mira quién está aquí! Es "+GetFullName(pchar)+". ¿Algúnas noticias?","¿Cómo te va? ¿Qué puedo hacer por ti?");
			if (rand(10) == 3)
			{
				iRnd = rand(MAX_PGG_QUEST_STORIES - 1);
				Dialog.Text = PGG_QuestStories[iRnd] + PCharRepPhrase("¿Cuáles son las noticias?", "¿Cuáles son las noticias en el archipiélago?");
			}
			else
			{
				iRnd = rand(MAX_PGG_STORIES - 1);
				iAns = rand(MAX_PGG_MEET_REP - 1);
				Dialog.Text = PGG_Stories[iRnd] + PCharRepPhrase(PGG_Meet_GoodRep[iAns] + "¿Cuáles son las noticias?", PGG_Meet_BadRep[iAns] + "¿Cuáles son las noticias en el archipiélago?");
			}
			if (sti(pchar.Ship.Type) != SHIP_NOTUSED && sti(NPChar.Ship.Type) != SHIP_NOTUSED)
			{
				link.l2 = RandPhraseSimple("¿Qué tal si te unes a mí? Dos barcos son mejor que uno. Podemos hacer buenos negocios juntos.", "Pareces un capitán experimentado. ¿Quieres navegar bajo mi bandera?");
				link.l2.go = "companion";
			}
			if (sti(NPChar.Ship.Type) == SHIP_NOTUSED)
			{
				Dialog.Text = RandPhraseSimple("¡Ay de mí... Mi barco se hundió!", "¡Mira quién está aquí?! ¿Qué te ha traído aquí? Por cierto, perdí mi barco...");
				link.l3 = RandPhraseSimple("Una lástima. Quizás tengas mejor suerte la próxima vez.", "Vaya, no me digas... Bueno, es hora de que me vaya. Nos vemos.");
				link.l3.go = "exit";
				if (FindFreeRandomOfficer() > 0)
				{
					link.l3 = RandPhraseSimple("¿Te gustaría servir como oficial en mi barco?", "Creo que te iría bien como oficial en mi barco. ¿Qué dices?");
					link.l3.go = "officer";
				}
			}
			//			link.l4 = "¿Cuáles son las noticias?";
			//			link.l4.go = "rumours_capitan";
		}
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) < 20 || bBettaTestMode)
		{
			link.l8 = PCharRepPhrase("Qué hocico más feo. Simplemente pide una paliza.", "Oh, nuestro 'amigo'. ¿Te gustaría un par de nuevos agujeros en el pecho?");
			link.l8.go = "outraged";
		}
		link.l9 = "Nada.";
		link.l9.go = "exit";
		NextDiag.TempNode = "Second time";
		break;

	case "no_ship":
		break;

		//==================================================
		// Officer
		//==================================================
	case "officer":
		// раз в день.
		if (CheckAttribute(NPChar, "Officer_Talk") && GetNpcQuestPastDayParam(NPChar, "Officer_Talk") < 1 && !bPGGLogShow)
		{
			Dialog.Text = RandPhraseSimple("Ya te he dicho que no estoy interesado.", "Pensé que ya habíamos discutido todo.");
			link.l1 = RandPhraseSimple("¿Cómo podría olvidar?", "Justo suficiente. Adiós.");
			link.l1.go = "exit";
			break;
		}
		// если уже был офицером, то посылает нафиг.
		if (CheckAttribute(NPChar, "PGGAi.Officer"))
		{
			Dialog.Text = RandPhraseSimple("Hmm... quizás no. No una segunda vez.", "¿Y pensaste que picaría el anzuelo dos veces?!");
			link.l1 = RandPhraseSimple("Bueno, como quieras...", "Está bien. Hasta luego, entonces.");
			link.l1.go = "exit";
			break;
		}
		// если отношение ниже 70, то в 70% случаев откажет...
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) < 70 && rand(100) < 70)
		{
			Dialog.Text = RandPhraseSimple("Hmm... No, supongo que no.", "No, soy un capitán, y no quiero servir como oficial.");
			link.l1 = RandPhraseSimple("Bueno, como desees...", "Está bien. Nos vemos, entonces.");
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(NPChar, "Officer_Talk");
			break;
		}
		// Проверка на ПИРАТЕС, не было! :) //navy 04.04.07
		if (FindFreeRandomOfficer() < 1)
		{
			Dialog.Text = RandPhraseSimple("Ya tienes un set completo.", "No creo que estés listo para darme órdenes.");
			link.l1 = RandPhraseSimple("Lástima...", "Bueno, el destino decretó de otra manera.");
			link.l1.go = "exit";
			break;
		}
		if (!CheckAttribute(NPChar, "Quest.Officer.Price"))
		{
			NPChar.Quest.Officer.Price = 10000 + sti(NPChar.rank) * 500 * MOD_SKILL_ENEMY_RATE - MakeInt(GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE) * 1000);
		}
		Dialog.Text = NPCharRepPhrase(NPChar, RandSwear() + RandPhraseSimple("¡Eso es justo lo que necesitaba! ¡Nuestras espadas probarán la sangre de nuestros enemigos! Pero hay un problema - todavía necesito " + NPChar.Quest.Officer.Price + " pesos para pagar mis deudas.", "Pareces un verdadero viejo lobo de mar. Y si estás dispuesto a pagar " + NPChar.Quest.Officer.Price + " pesos, podríamos trabajar bien juntos."), LinkRandPhrase("Tu oferta es bastante halagadora para mí. Aceptaré trabajar para ti por una tarifa bastante modesta de " + NPChar.Quest.Officer.Price + " pesos.", "Hmm... Pareces un marinero experimentado. Quizás, debería aceptar tu oferta si estás dispuesto a pagarme " + NPChar.Quest.Officer.Price + " pesos.", "Creo que trabajaremos bien juntos, capitán. Solo " + NPChar.Quest.Officer.Price + " pesos, y tenemos un trato."));

		MakeRandomLinkOrderTwo(link, PCharRepPhrase(RandSwear() + RandPhraseSimple("Me parece bien. Sólo espero que no me cobren a diario.", "Es muy caro, pero espero que merezca la pena."), LinkRandPhrase("Estoy de acuerdo. Considérate parte de la tripulación.", "Creo que puedo permitírmelo.", "Parece que vales la pena. ¡Coge las monedas!")), "officer_hired",
							   PCharRepPhrase(RandSwear() + RandPhraseSimple("No vales tanto. Nos vemos...", "Demasiado caro para mí."),
											  LinkRandPhrase("Sí... La codicia no es un pecado...", "¿Te estás riendo de mí? Puedo comprar una docena como tú por ese dinero.", "Eso es una estafa. ¿Dónde se supone que voy a encontrar tanto dinero?")),
							   "exit");
		link.l3 = "¿Hmm... y qué tan calificado estás?";
		link.l3.go = "Exit_ShowParam";
		break;

	case "officer_hired":
		if (sti(pchar.money) < sti(NPChar.Quest.Officer.Price))
		{
			Dialog.Text = "Creo que tienes problemas con el dinero, capitán.";
			link.l1 = "Oh... en efecto.";
			link.l1.go = "exit";
			break;
		}
		pchar.questTemp.HiringOfficerIDX = NPChar.index;
		AddMoneyToCharacter(pchar, -(makeint(NPChar.Quest.Officer.Price)));
		AddDialogExitQuestFunction("PGG_BecomeHiredOfficer");
		NPChar.loyality = MakeInt(PGG_ChangeRelation2MainCharacter(NPChar, 0) * 0.3)

			DeleteAttribute(NPChar, "Quest.Officer");
		DeleteAttribute(NPChar, "PGGAi.Task");
		DeleteAttribute(NPChar, "PGGAi.LockService");

		Dialog.Text = RandPhraseSimple("¡Excelente!", "Nunca dudé de ti, capitán.");
		link.l1 = "No llegues tarde a la partida.";
		link.l1.go = "exit";
		break;

		//==================================================
		// Companion
		//==================================================
	case "companion":
		Dialog.Text = "Un error, informa a los desarrolladores";
		link.l1 = "¡Lo haré!";
		link.l1.go = "exit";
		// раз в день.
		if (CheckAttribute(NPChar, "Companion_Talk") && GetNpcQuestPastDayParam(NPChar, "Companion_Talk") < 1 && !bPGGLogShow)
		{
			Dialog.Text = RandPhraseSimple("Ya te he dicho que no estoy interesado.", "Pensé que ya habíamos discutido todo.");
			link.l1 = RandPhraseSimple("¿Cómo podría olvidar?", "Justo suficiente. Adiós.");
			link.l1.go = "exit";
			break;
		}
		// разница в один класс.. нефиг халявить
		if (GetCharacterShipClass(NPChar) < GetCharacterShipClass(PChar) - 1)
		{
			Dialog.Text = RandPhraseSimple("¿Navegar contigo?! ¡Primero madura un poco!", "¡No creo que esté interesado en eso!");
			link.l1 = RandPhraseSimple("Bueno, como desees...", "Está bien. Nos vemos, entonces.");
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(NPChar, "Companion_Talk");
			break;
		}
		// если отношение ниже 70, то в 70% случаев откажет...
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) < 70 && rand(100) < 70)
		{
			Dialog.Text = RandPhraseSimple("Hmm... No, supongo que no.", "No, gracias. No me gusta servir bajo nadie.");
			link.l1 = RandPhraseSimple("Bueno, como desees...", "Está bien. Hasta luego, entonces.");
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(NPChar, "Companion_Talk");
			break;
		}
		// есть ли место для компаньона.
		if (SetCompanionIndex(pchar, -1, sti(NPChar.index)) != -1)
		{
			Dialog.Text = NPCharRepPhrase(NPChar, RandSwear() + RandPhraseSimple("¡Me caes bien! ¡Has conseguido un trato! ¡Ya puedo oír el tintineo de los pesos en nuestros bolsillos!", "Eres un listo " + GetSexPhrase("hombre", "chica") + "... ¡Deberíamos trabajar bien juntos!"), LinkRandPhrase("Me gusta tu oferta. Estoy de acuerdo.", "Eso es interesante. Sabes, creo que juntos podemos hacer más!", "Eso debería ser divertido. ¡Tienes un trato!"));
			link.l1 = RandPhraseSimple("¡Genial! ¡Te estaré esperando en el mar!", "¡Trato hecho! Seremos una gran tripulación.");
			link.l1.go = "exit";
			NPChar.PGGAi.IsPGG = false;
			NPChar.PGGAi.location.town = "none";
			NPChar.Dialog.TempNode = "hired";
			NPChar.Dialog.FileName = "Enc_Officer_dialog.c";
			NPChar.Payment = true;
			NPChar.Money = 0;

			SetBaseShipData(NPChar);
			DeleteAttribute(NPChar, "ship.sails");
			DeleteAttribute(NPChar, "ship.masts");
			DeleteAttribute(NPChar, "ship.blots");
			DeleteAttribute(NPChar, "ship.hulls");

			Fantom_SetCannons(NPChar, "pirate");
			Fantom_SetBalls(NPChar, "pirate");

			DeleteAttribute(NPChar, "PGGAi.Task");
			DeleteAttribute(NPChar, "PGGAi.LockService");
			SetCharacterRemovable(NPChar, true);
			SaveCurrentNpcQuestDateParam(NPChar, "Companion.CheckRelation");
		}
		else
		{
			Dialog.Text = RandPhraseSimple("Creo que ya tienes suficientes compañeros.", "Ya tienes suficientes barcos, ¿por qué necesitarías más?");
			link.l1 = "Sí... Quizás, tienes razón.";
			link.l1.go = "exit";
		}
		break;

	case "companion_leave":
		Dialog.Text = RandSwear() + " " + NPCharRepPhrase(NPChar, RandPhraseSimple("¡Estoy aburrido de ti!!! ¡Estoy dejando tu escuadrón!", "¡Mi paciencia ha terminado! Me voy."), RandPhraseSimple("Estoy cansado de tus escapadas, 'almirante'... Permíteme tomar mi licencia.", "Estoy harto de tu mando y me voy de tu escuadrón."));
		link.l1 = PCharRepPhrase(RandPhraseSimple("Bien, piérdete, entonces.", "Está bien, ve a donde quieras."), RandPhraseSimple("Bien. No te voy a retener.", "Esa es tu elección. Te deseo viento favorable."));
		link.l1.go = "Exit_Companion_Leave";
		link.l2 = PCharRepPhrase(RandPhraseSimple("Ehh... ¿qué tal una pequeña prima?", "¡Rayos! Oh, diablos, ¿quizás te quedarías? ¡Incluso puedo pagarle a tu tripulación algo extra!"), RandPhraseSimple("Me dolería mucho separarme de ti... Quizás, una pequeña compensación pueda resolver nuestras disputas?", "¿Qué te parece si aumentamos tu salario?"));
		link.l2.go = "companion_stay";
		break;

	case "companion_stay":
		if (CheckAttribute(NPChar, "Quest.Companion"))
		{
			Dialog.Text = RandPhraseSimple("Una vez fue suficiente para mí. ¡No confiaré más en tus promesas!", "¡No me seducirás con dinero! ¡Mi decisión es final!");
			link.l1 = RandPhraseSimple("Bien, así que mucha suerte para ti.", "¡Entonces piérdete y asegúrate de que nunca más te veré!");
			link.l1.go = "Exit_Companion_Leave";
			break;
		}
		NPChar.Quest.Companion.Price = 2 * GetSalaryForShip(NPChar);
		Dialog.Text = RandSwear() + " " + NPCharRepPhrase(NPChar, RandPhraseSimple("¿Un premio? ¡Está bien! Una suma de " + NPChar.Quest.Companion.Price + " pesos me vendrán bien.", "Bueno, quizás, si estás listo para pagar a mi tripulación " + NPChar.Quest.Companion.Price + " pesos, podría persuadirlos para que se queden."), RandPhraseSimple("¡Bien! Puedo quedarme por una pequeña prima de " + NPChar.Quest.Companion.Price + "¡pesos!", NPChar.Quest.Companion.Price + " satisfará a mí y a mi tripulación por un tiempo."));
		link.l1 = PCharRepPhrase(RandPhraseSimple("¿Te estás riendo de mí o qué?! ¡Lárgate, ahora!", "¡Ja! Preferiría gastar este dinero en algo más útil!"), RandPhraseSimple("¡Oh no. No soy tan rico!", "Adiós. Voy a pagar esta cantidad."));
		link.l1.go = "Exit_Companion_Leave";
		if (sti(pchar.money) >= sti(NPChar.Quest.Companion.Price))
		{
			link.l2 = PCharRepPhrase(RandPhraseSimple("¡Excelente! ¡Aquí está tu prima!", "¡Nunca dudé, que todo era por dinero!"), RandPhraseSimple("¡Excelente! Me alegra que te quedes.", "Aquí está lo que prometí."));
			link.l2.go = "Exit_Companion_Stay";
		}
		break;

	case "Exit_Companion_Leave":
		chrDisableReloadToLocation = false;
		RemoveCharacterCompanion(pchar, NPChar);

		NPChar.PGGAi.IsPGG = true;
		NPChar.RebirthPhantom = true;
		NPChar.PGGAi.location.town = GetCurrentTown();

		LAi_SetWarriorTypeNoGroup(NPChar);
		NextDiag.CurrentNode = "Second Time";
		DialogExit();
		break;

	case "Exit_Companion_Stay":
		GetCharacterPos(NPChar, &locx, &locy, &locz);
		sTmp = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
		LAi_ActorGoToLocation(NPChar, "reload", sTmp, "none", "", "", "", 5.0);

		AddMoneyToCharacter(pchar, -(makeint(NPChar.Quest.Companion.Price)));
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

		//==================================================
		// Quests
		//==================================================
		//==== BETTA_TEST ====
	case "BT_Quest":
		Dialog.Text = "¡Selecciona plantilla!";
		link.l1 = "Plantilla de la misión 1 - mar.";
		link.l1.go = "BT_Quest_1";
		link.l2 = "¡SELECCIONADO! Plantilla de búsqueda 1 - tierra.";
		link.l2.go = "BT_Quest_2";
		break;

	case "BT_Quest_1":
		NPChar.PGGAi.ActiveQuest.QstNumber = 0;
		NPChar.PGGAi.ActiveQuest.QstNumber.Template = 1;
		Dialog.Text = "Plantilla de misión 1 - mar.";
		link.l1 = "Ah, sí...";
		link.l1.go = "quest";
		break;
	case "BT_Quest_2":
		NPChar.PGGAi.ActiveQuest.QstNumber = 0;
		NPChar.PGGAi.ActiveQuest.QstNumber.Template = 0;
		Dialog.Text = "¡SELECCIONADO! Plantilla de la Misión 1 - tierra.";
		link.l1 = "Ah, sí...";
		link.l1.go = "quest";
		break;
		//==== BETTA_TEST ====

	case "quest":
		chrDisableReloadToLocation = false;
		if (CheckAttribute(NPChar, "QuestTalk") && GetNpcQuestPastDayParam(NPChar, "QuestTalk") < 1)
		{
			Dialog.Text = "¡Ya te he contado todo!";
			link.l1 = "Ah, sí...";
			link.l1.go = "exit";
			break;
		}
		Dialog.Text = RandPhraseSimple("¿Qué negocio?.. ¡Hic! No ves yo mismo y mis colegas estamos pasando un buen rato!.. ¡Hic...", "Ehh... ¡No hay negocio hoy!");
		link.l1 = "Ya veo...";
		link.l1.go = "exit";
		if (!PGG_IsQuestAvaible())
			break; // квест нельзя брать.
		// if (!CheckAttribute(NPChar, "PGGAi.ActiveQuest") && !bBettaTestMode) break; //для релиза возможно надо будет закрыть. если закоментить, то ГГ сам может предложить дело
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest.QstNumber"))
			iRnd = sti(NPChar.PGGAi.ActiveQuest.QstNumber); // тип квеста, который хочет от нас ПГГ
		if (iRnd == -1 && !CheckAttribute(pchar, "GenQuest.PGG_Quest"))
			iRnd = rand(1); // может и не быть
		switch (iRnd)
		{
		case 0:
			if (sti(NPChar.Ship.Type) != SHIP_NOTUSED && sti(PChar.Ship.Type) != SHIP_NOTUSED && GetCharacterShipClass(PChar) <= 4 && GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				// квест от ПГГ
				/*if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
				{ */
				if (!CheckAttribute(pchar, "GenQuest.PGG_Quest"))
				{ // не занят другими квестами ПГГ
					Dialog.Text = "¿De qué hablas? Aunque, estás a tiempo. ¡Cuando se trata de negocios, siempre estoy listo!";
					link.l1 = "¿Hmm. De qué estás hablando?";
					link.l1.go = "Quest_1_Work";
					NPChar.PGGAi.ActiveQuest = 1; // чтоб говорил от своего имени
					PChar.GenQuest.PGG_Quest = 1; // чтоб не достовали другие ПГГ
				}
				/* }
				//квест от ГГ
				else
				{
					if ()
					{
						Log_TestInfo("The test sentence of the protagonist");

						Dialog.Text = LinkRandPhrase("...solo yo y el diablo conocemos ese lugar, y el último que quede vivo se lo llevará todo!..","...y Meinard respondió: 'No espero clemencia de ti y tampoco te la daré'","...y una vez en mar abierto, cuando ya estaba un poco ebrio, sugirió: 'Hagamos nuestro propio infierno allí y veamos quién aguanta hasta el final'.")+PCharRepPhrase(LinkRandPhrase("¡Ahora hay otro pirata!","Caballeros, supongo que tenemos un caballero de fortuna en nuestra mesa, ¿verdad?","¡Huelo pólvora y sangre! ¡Un filibustero a estribor!"),LinkRandPhrase("Los capitanes decentes son una raza rara en estas aguas.","La nobleza está pasada de moda estos días.","¡Oh, ahora hay un capitán decente, nada como tú, degolladores! ¡Je-je!"));
						link.l1 = "¡No estoy gritando, te lo estoy diciendo - hay un trato rentable!";
						link.l1.go = "Quest_1_Work";
					}
				}  /**/
			}
			break;
		}
		SaveCurrentNpcQuestDateParam(NPChar, "QuestTalk");
		break;

	case "quest_onStay": // ПГГ сам подходит
		chrDisableReloadToLocation = false;
		Dialog.Text = "¡Cuidado, cuidado! ¡Oh! Te conozco. Eres " + GetFullName(PChar) + ". He oído mucho de ti.";
		if (!CheckAttribute(NPChar, "meeting") || !sti(NPChar.meeting))
		{
			link.l1 = PCharRepPhrase(RandSwear() + RandPhraseSimple("Soy capitán " + GetFullName(pchar) + ".", "Soy el capitán del '" + PChar.Ship.Name + " ¡y un par de cientos de verdaderos diablos! ¡Je-je! Mi nombre es " + GetFullName(pchar) + ".") + " Pero no te recuerdo.", RandPhraseSimple("Permítanme presentarme, caballeros. Soy el capitán " + GetFullName(pchar) + ".", "No nos hemos presentado todavía. Soy el capitán del '" + PChar.Ship.Name + " bajo la bandera de " + NationNameGenitive(sti(PChar.nation)) + ". Mi nombre es " + GetFullName(pchar) + ".") + " Pero no te recuerdo.");
			//			link.l1 = "¿Hmm... y quién eres tú? No te recuerdo.";
			link.l1.go = "Quest_1_Meeting";
		}
		else
		{
			link.l1 = "Hola, " + GetFullName(NPChar) + "¿Cómo va la vida?";
			link.l1.go = "Quest_1_Work";
		}
		SaveCurrentNpcQuestDateParam(NPChar, "QuestTalk");
		break;

	//=========== Первый квест ==========
	case "Quest_1_Meeting":
		sld = GetRealShip(sti(NPChar.Ship.Type));
		Dialog.Text = "Soy " + GetFullName(NPChar) + ", capitán " + xiStr(sld.BaseName + "Acc") + " " + NPChar.Ship.Name + NPCharRepPhrase(NPChar, ". El corsario más notorio de todo el Mar Español.", ". Solo un marinero.");
		link.l1 = "Sí, ahora te recordaré.";
		link.l1.go = "Quest_1_Work";
		NPChar.meeting = true;
		break;

	case "Quest_1_Work":
		PChar.GenQuest.PGG_Quest.Template = rand(1);
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest.QstNumber.Template"))
		{
			PChar.GenQuest.PGG_Quest.Template = NPChar.PGGAi.ActiveQuest.QstNumber.Template;
		}
		PChar.GenQuest.PGG_Quest.Parts = GetCompanionQuantity(PChar) + 1;
		PChar.GenQuest.PGG_Quest.Nation = rand(NON_PIRATES);
		PChar.GenQuest.PGG_Quest.Island = GetRandomIslandId();
		while (PChar.GenQuest.PGG_Quest.Island == Islands[GetCharacterCurrentIsland(pchar)].id)
		{
			PChar.GenQuest.PGG_Quest.Island = GetRandomIslandId();
		}
		PChar.GenQuest.PGG_Quest.Island.Shore = GetIslandRandomShoreId(PChar.GenQuest.PGG_Quest.Island);
		while (PChar.GenQuest.PGG_Quest.Island.Shore == "")
		{
			PChar.GenQuest.PGG_Quest.Island = GetRandomIslandId();
			PChar.GenQuest.PGG_Quest.Island.Shore = GetIslandRandomShoreId(PChar.GenQuest.PGG_Quest.Island);
			if (sti(PChar.GenQuest.PGG_Quest.Template))
			{
				if (!isLocationFreeForQuests(PChar.GenQuest.PGG_Quest.Island))
					PChar.GenQuest.PGG_Quest.Island.Shore = "";
			}
			else
			{
				if (!isLocationFreeForQuests(PChar.GenQuest.PGG_Quest.Island.Shore))
					PChar.GenQuest.PGG_Quest.Island.Shore = "";
			}
		}
		PChar.GenQuest.PGG_Quest.Island.Town = FindTownOnIsland(PChar.GenQuest.PGG_Quest.Island);
		PChar.GenQuest.PGG_Quest.Days = 3 + GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(pchar)].id, PChar.GenQuest.PGG_Quest.Island);
		PChar.GenQuest.PGG_Quest.Goods = GetRandomGood(FLAG_GOODS_TYPE_CROWN, FLAG_GOODS_NONE);
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			//			Dialog.Text = "Tengo negocios contigo, "+GetSexPhrase("compañero","muchacha")+". Sé que puedo confiar en ti, pero simplemente no puedo discutirlo en la taberna, demasiadas orejas equivocadas. Te estaré esperando a bordo de mi barco. El nombre de mi viejo casco es '"+NPChar.Ship.Name+"'.'";
			//			link.l1 = "Escúpelo ya, no tengo tiempo para visitas.";
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("Tengo un asunto interesante para ti y tus degolladores.", "Si unimos fuerzas, ¡podríamos ganar un premio realmente grande! Claro, tendremos que matar a alguien en el proceso. Je-je."), RandPhraseSimple("Tengo una oferta de negocio para ti, capitán.", "Capitán, vuestra reputación no tiene parangón, y por eso os ofrezco participar en un asunto tentador.")) + RandPhraseSimple("Solamente entre nosotros dos. Discutámoslo en el cuarto de guerra de '" + NPChar.Ship.Name + " sobre el barril de la cerveza más selecta. Hoy.", "No deberíamos discutirlo allí, negociemos los detalles en '" + NPChar.Ship.Name + " en paz y tranquilidad. Y por favor no tardes mucho.");
			link.l1 = PCharRepPhrase(RandSwear() + RandPhraseSimple("¡Al diablo con estos retrasos! Si es bueno, quiero saberlo de inmediato, ¡y aún más si es malo!", "¡No tiene sentido tener cables tan cortos! Hay una habitación adecuada en la taberna, ¡vamos para allá!"), RandPhraseSimple("¿Y por qué no podemos discutir tu oferta ahora mismo, en la sala de la taberna?", "Temo que tengo poco deseo de visitar tu barco. Si necesitas algo, escúpelo aquí y ahora mismo!"));
		}
		else
		{
			PChar.GenQuest.PGG_Quest.Nation = FindEnemyNation2NationWithoutPirates(sti(PChar.Nation));
			Dialog.Text = "Pssst... No deberíamos discutir negocios en la taberna, demasiados oídos equivocados. Te estoy esperando en mi barco '" + NPChar.Ship.Name + ". Hablaremos allí.";
			link.l1 = "No tengo tiempo y no me gusta visitar.";
		}
		link.l1.go = "Quest_1_Work_1";
		link.l2 = PCharRepPhrase(RandPhraseSimple("Vendré. Pero si solo estabas perdiendo mi tiempo, ¡te arrancaré la lengua!", RandSwear() + "Está bien, espérame. Espero que tu oferta valga la pena. ¡Y ni siquiera pienses en engañarme!"), RandPhraseSimple("Aceptaré con gusto tu invitación, capitán.", "Me has intrigado. Por supuesto, vendré."));
		link.l2.go = "Exit_Quest_1_AfterTavernTalk";
		break;

	case "Quest_1_Work_1":
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("¡Oh, estás mareado, verdad? ¡Corre y escóndete bajo la falda de tu madre!", "¿Demasiado asustado?! ¡Lárgate!"), RandPhraseSimple("No puedo hacerlo. Si no te importa el oro, es tu decisión.", "Es así y de ninguna otra manera. Si no lo quieres, está bien, hay muchos otros."));
		link.l1 = PCharRepPhrase(RandPhraseSimple("¡Ja! Eres valiente, ¿no? ¡Está bien, voy!", "Veo que puedes aferrarte a tus cañones, capitán. Está bien, espérame."), RandPhraseSimple("Bien, estoy de acuerdo.", "Eres bastante parlanchín. Estoy listo para discutir negocios en tu navío."));
		link.l1.go = "Exit_Quest_1_AfterTavernTalk";
		link.l2 = PCharRepPhrase(RandPhraseSimple("¡Ja! ¿Pensaste atraerme a tu barco y matarme allí? ¡Eso no servirá!", "¡Tus palabras no valen un centavo! ¡No tendré ningún trato contigo!"), "Oferta dudosa. Tengo que rechazarla.");
		link.l2.go = "Quest_1_NotWork";
		break;

	case "Quest_1_NotWork":
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("¡Ron para mí! ¡Y tú desapareces de mi vista!", "¿No hemos discutido ya todo?"), RandPhraseSimple("Ocúpate de tus asuntos. Tengo cosas que hacer.", "No creo que tengamos nada de qué hablar."));
		link.l1 = RandSwear();
		link.l1.go = "exit_2";
		break;

	case "Quest_1_Work_2":
		Dialog.Text = "¡Te dije que te estaría esperando en mi barco!";
		link.l1 = "Oh... claro...";
		link.l1.go = "exit";
		NextDiag.TempNode = "Quest_1_Work_2";
		break;

	case "Exit_Quest_1_AfterTavernTalk":
		PChar.GenQuest.PGG_Quest = 1;
		PChar.GenQuest.PGG_Quest.Stage = 0;
		PChar.GenQuest.PGG_Quest.PGGid = NPChar.id;

		Group_AddCharacter("PGGQuest", NPChar.id);
		Group_SetGroupCommander("PGGQuest", NPChar.id);
		Group_SetAddress("PGGQuest", Islands[GetCharacterCurrentIsland(PChar)].id, "Quest_Ships", "Quest_Ship_1");
		Group_SetTaskNone("PGGQuest");

		SetTimerConditionParam("PGGQuest1_RemoveShip_Timer", "PGGQuest1_RemoveShip_Timer", 0, 0, 0, MakeInt(GetHour() + 6), false);
		PChar.Quest.PGGQuest1_RemoveShip_Timer.function = "PGG_Q1RemoveShip";

		NPChar.Ship.Mode = "Pirate";
		NPChar.DeckDialogNode = "Quest_1_Ship";
		NPChar.Nation.Bak = NPChar.Nation;
		NPChar.Nation = GetCityNation(GetCurrentTown());
		NPChar.AlwaysFriend = true;
		NPChar.Abordage.Enable = false; // нельзя брать на абордаж
		SetCharacterRelationBoth(sti(PChar.index), sti(NPChar.index), RELATION_FRIEND);

		ReOpenQuestHeader("Gen_PGGQuest1");
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Tavern");
		}
		else
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Tavern_1");
			AddQuestUserData("Gen_PGGQuest1", "sSex", GetSexPhrase("", ""));
		}
		AddQuestUserData("Gen_PGGQuest1", "sShipName", NPChar.Ship.Name);

		NextDiag.CurrentNode = "Quest_1_Work_2";
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor")
			LAi_SetWarriorTypeNoGroup(NPChar);
		break;

	case "Quest_1_Ship":
		PChar.Quest.PGGQuest1_RemoveShip_Timer.Over = "yes";
		if (GetCompanionQuantity(PChar) == COMPANION_MAX)
		{
			Dialog.Text = RandPhraseSimple("Oh, no, eso no servirá... ¿No son demasiados barcos para ti, " + GetSexPhrase("compañero", "muchacha") + "?", "¡Ja! En una compañía tan grande no hay forma de mantener las cosas en secreto. Lárgate.");
			link.l1 = RandPhraseSimple("¡Como desees!", "Está bien. No es que me importe.");
			link.l1.go = "Exit";
			PChar.Quest.PGGQuest1_RemoveEnd.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_RemoveEnd.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_RemoveEnd.function = "PGG_Q1RemoveShip";
			break;
		}
		PChar.GenQuest.PGG_Quest.Stage = 1;
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			//			Dialog.Text = "Genial. Ahora estoy seguro de que no hay oídos equivocados alrededor, y mis marineros ya han sido informados. Entonces mi oferta es adquirir algunas cosas sin dueño.";
			//			link.l1 = "¿Y qué tiene de difícil eso? ¿Por qué me necesitarías para eso, en primer lugar?";
			Dialog.Text = RandPhraseSimple("¡Bienvenido a bordo, capitán!", "Estupendo. Ahora estoy seguro de que no hay oídos equivocados alrededor, y mis marineros ya han sido informados. Así que mi oferta es adquirir algunas cosas sin dueño.") + "Entonces mi oferta es adquirir algunas cosas sin dueño.";
			link.l1 = RandPhraseSimple("¿Y qué tiene de difícil? ¿Por qué me necesitarías para eso, en primer lugar?", "¿Sin dueño?! ¡Debe estar bromeando!");
		}
		else
		{
			Dialog.Text = "Ahora estoy seguro de que no hay oídos equivocados alrededor, ¡vamos, escúpelo!";
			link.l1 = "Entonces mi oferta es adquirir algunas cosas sin dueño.";
		}
		link.l1.go = "Quest_1_Ship_1";
		break;

	case "Quest_1_Ship_1":
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			Dialog.Text = RandPhraseSimple("Bueno, hay personas que lo consideran suyo y necesitan ser convencidos de lo contrario.", "Por supuesto, alguien tendrá que ser asesinado, pero ciertamente esto no va a ser un problema, ¿verdad?");
			link.l1 = PCharRepPhrase(RandSwear() + RandPhraseSimple("¡Al grano!", "¡Eso huele a matanza! ¿Y dónde están?"), RandPhraseSimple("Me gustaría saber más detalles sobre tu oferta.", "¿Qué exactamente me estás ofreciendo?"));
			link.l1.go = "Quest_1_Ship_Detail";
			link.l2 = PCharRepPhrase(RandPhraseSimple("Me estás tomando el pelo. ¡No voy a participar en eso!", "¡Eso parece fácil, pero no confío en ti! ¿Quieres que saque las castañas del fuego por ti? ¡Pues, no estoy de acuerdo!"), RandPhraseSimple("Suena prometedor, pero voy a pasar.", "No, no robo, me gusta cuando me dan regalos en su lugar."));
			link.l2.go = "Quest_1_Ship_Refuse";
		}
		else
		{
			Dialog.Text = "¿Y qué tiene de difícil? ¿Por qué me necesitarías para eso, en primer lugar?";
			link.l1 = "Bueno, hay personas que lo consideran suyo y necesitan ser convencidos de lo contrario.";
			link.l1.go = "Quest_1_Ship_Detail";
		}
		break;

	case "Quest_1_Ship_Detail":
		sTmp = "Un convoy perteneciente a " + NationNameGenitive(sti(PChar.GenQuest.PGG_Quest.Nation)) + ", que transporta ";
		if (sti(PChar.GenQuest.PGG_Quest.Goods) == GOOD_SLAVES)
		{
			sTmp += "Slaves";
			PChar.GenQuest.PGG_Quest.Goods.Text = "Slaves";
		}
		else
		{
			sTmp += XI_ConvertString(Goods[sti(PChar.GenQuest.PGG_Quest.Goods)].Name);
			PChar.GenQuest.PGG_Quest.Goods.Text = XI_ConvertString(Goods[sti(PChar.GenQuest.PGG_Quest.Goods)].Name);
		}

		if (PChar.GenQuest.PGG_Quest.Island.Town == "" || PChar.GenQuest.PGG_Quest.Island.Town == "Caiman" ||
			PChar.GenQuest.PGG_Quest.Island.Town == "Terks" || PChar.GenQuest.PGG_Quest.Island.Town == "Dominica")
		{
			sLoc = GetConvertStr(PChar.GenQuest.PGG_Quest.Island, "LocLables.txt") + "");
		}
		else
		{
			sLoc = XI_ConvertString("Colony" + PChar.GenQuest.PGG_Quest.Island.Town + "Gen");
		}

		if (sti(PChar.GenQuest.PGG_Quest.Template))
		{
			sTmp += ", se detuvo no lejos de " + sLoc + " en la cala de " + GetConvertStr(PChar.GenQuest.PGG_Quest.Island.Shore, "LocLables.txt") + " para reabastecerse.";
		}
		else
		{
			sTmp += ", quedó atrapado en la tormenta no lejos de " + sLoc + " y bajó. Pero consiguieron asegurar parte de la carga y desembarcaron en la cala de " + GetConvertStr(PChar.GenQuest.PGG_Quest.Island.Shore, "LocLables.txt") +
					" Ahora están esperando que llegue su escuadrón.";
		}

		Dialog.Text = sTmp;
		link.l1 = PCharRepPhrase(RandSwear() + RandPhraseSimple("¡No te demores, suéltalo ya!", "Tenía razón sobre ti, ¿qué más sabes?"), RandPhraseSimple("¡Eso es muy interesante, por favor continúa!", "Una soy " + GetSexPhrase("todo", "todo") + "¡orejas!"));
		link.l1.go = "Quest_1_Ship_Detail_1";

		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			link.l2 = PCharRepPhrase(RandPhraseSimple("Eso suena como un asunto tentador, pero aún me niego. No necesito pelear con " + NationNameAblative(sti(PChar.GenQuest.PGG_Quest.Nation)) + ".", "¿Una caravana? ¡¿Sin dueño?! ¡Debería haber mil soldados custodiándola! No, eso no servirá. Me estoy yendo."), RandPhraseSimple("No, no estoy en guerra con " + NationNameAblative(sti(PChar.GenQuest.PGG_Quest.Nation)) + ", así que no estoy interesado.", "¡Mi respuesta es no! No voy a arruinar mis relaciones con " + NationNameAblative(sti(PChar.GenQuest.PGG_Quest.Nation)) + "¡!"));
			link.l2.go = NPCharRepPhrase(NPChar, "Quest_1_Ship_BadWay", "Quest_1_Ship_Refuse");
		}
		else
		{
			Dialog.Text = "¡Eso huele a masacre! ¿Qué hay de los detalles?";
			link.l1 = sTmp;
		}
		if (sti(PChar.GenQuest.PGG_Quest.Template))
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Detail_A");
		}
		else
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Detail_B");
		}
		AddQuestUserData("Gen_PGGQuest1", "sNation", NationNameGenitive(sti(PChar.GenQuest.PGG_Quest.Nation)));
		AddQuestUserData("Gen_PGGQuest1", "sGoods", PChar.GenQuest.PGG_Quest.Goods.Text));
		AddQuestUserData("Gen_PGGQuest1", "sColony", sLoc);
		AddQuestUserData("Gen_PGGQuest1", "sShore", GetConvertStr(PChar.GenQuest.PGG_Quest.Island.Shore, "LocLables.txt"));
		break;

	case "Quest_1_Ship_Detail_1":
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			//			Dialog.Text = "Solo tenemos "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+" para interceptarlos.";
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("En " + FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)) + " la caravana se irá demasiado lejos, y no podremos alcanzarla.", "Tenemos exactamente " + FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)) + " días para matarlos a todos y conseguir el botín!"), RandPhraseSimple("Solo tenemos " + FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)) + " días para toda la operación a nuestra disposición.", "Deberíamos apurarnos, " + PChar.Name + ". Solo tenemos " + FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)) + "."));
			link.l1 = RandPhraseSimple("¡Lo haremos a tiempo! Zarparemos hoy.", "No perdamos tiempo, entonces. Ordena zarpar hoy.");
			link.l1.go = "Exit_Quest_1_Accept";
			AddQuestRecord("Gen_PGGQuest1", "q1_Accept");
		}
		else
		{
			Dialog.Text = "Eso es muy interesante, por favor continúa.";
			link.l1 = "Solo tenemos " + FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)) + " para interceptarlos.";
			link.l1.go = "Quest_1_Ship_Accept";
			AddQuestRecord("Gen_PGGQuest1", "q1_Accept_1");
		}
		AddQuestUserData("Gen_PGGQuest1", "nDays", FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)));
		break;

	case "Quest_1_Ship_Accept":
		Dialog.Text = "¡No perdamos tiempo! ¡Vámonos!";
		link.l1 = "¡Nos vamos!";
		link.l1.go = "Exit_Quest_1_Accept";
		break;

	case "Exit_Quest_1_Accept":
		if (sti(PChar.GenQuest.PGG_Quest.Stage) < 2)
		{
			PChar.GenQuest.PGG_Quest.Stage = 2;
			PGG_Q1RemoveShip("");

			if (sti(PChar.GenQuest.PGG_Quest.Template))
			{
				PGG_Q1PlaceShipsNearIsland();
			}
			else
			{
				Locations[FindLocation(PChar.GenQuest.PGG_Quest.Island.Shore)].DisableEncounters = true;

				PChar.Quest.PGGQuest1_CheckStartState.win_condition.l1 = "Location";
				PChar.Quest.PGGQuest1_CheckStartState.win_condition.l1.Location = PChar.GenQuest.PGG_Quest.Island.Shore;
				PChar.Quest.PGGQuest1_CheckStartState.function = "PGG_Q1CheckStartState";
			}
			PChar.Quest.PGGQuest1_PGGDead.win_condition.l1 = "NPC_Death";
			PChar.Quest.PGGQuest1_PGGDead.win_condition.l1.Character = PChar.GenQuest.PGG_Quest.PGGid;
			PChar.Quest.PGGQuest1_PGGDead.function = "PGG_Q1PGGDead";

			SetTimerCondition("PGGQuest1_Time2Late", 0, 0, sti(PChar.GenQuest.PGG_Quest.Days), false);
			PChar.Quest.PGGQuest1_Time2Late.function = "PGG_Q1Time2Late";

			NPChar.PGGAi.IsPGG = false;
			NPChar.PGGAi.location.town = "none";
			DeleteAttribute(NPChar, "PGGAi.Task");
			DeleteAttribute(NPChar, "PGGAi.LockService");
			DeleteAttribute(NPChar, "AlwaysFriend");

			SetCompanionIndex(PChar, -1, sti(NPChar.index));
			SetCharacterRemovable(NPChar, false);

			SetBaseShipData(NPChar);
			DeleteAttribute(NPChar, "ship.sails");
			DeleteAttribute(NPChar, "ship.masts");
			DeleteAttribute(NPChar, "ship.blots");
			DeleteAttribute(NPChar, "ship.hulls");

			Fantom_SetCannons(NPChar, "pirate");
			Fantom_SetBalls(NPChar, "pirate");
		}
		NextDiag.CurrentNode = "Quest_1_Ship_Accept";
		DialogExit();
		break;

	case "Quest_1_Ship_Refuse":
		Dialog.Text = RandSwear()+"Me has decepcionado, capitán. ¿Pensaste que iba a invitarte a "+RandPhraseSimple("¿¡Misa dominical?!!","¿un juego de niños!??"));
		link.l1 = PCharRepPhrase(RandPhraseSimple("Eso es asunto tuyo. Y es mi decisión.", "No voy a colgarme de la soga por un par de pesos."), RandPhraseSimple("Mi decisión es definitiva, capitán.", "No tenemos nada más que discutir."));
		link.l1.go = "Exit_Quest_1_Refuse";
		break;

	case "Exit_Quest_1_Refuse":
		if (sti(PChar.GenQuest.PGG_Quest.Stage) != -1)
		{
			PChar.GenQuest.PGG_Quest.Stage = -1;
			PChar.Quest.PGGQuest1_RemoveShip.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_RemoveShip.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_RemoveShip.function = "PGG_Q1RemoveShip";

			AddQuestRecord("Gen_PGGQuest1", "q1_Close");
			AddQuestUserData("Gen_PGGQuest1", "sSex", GetSexPhrase("", ""));
			CloseQuestHeader("Gen_PGGQuest1");
			DeleteAttribute(NPChar, "AlwaysFriend");
		}
		NPChar.Dialog.CurrentNode = "Quest_1_Ship_Refuse";
		NPChar.DeckDialogNode = "Quest_1_Ship_Refuse";
		DialogExit();
		break;

	case "Quest_1_Ship_BadWay":
		Dialog.Text = PCharRepPhrase("¡Vamos, vamos! Todo procederá sin problemas, y nadie sabrá nada. Mataremos a todos."),RandPhraseSimple("¿A dónde vas, capitán? ¿A las autoridades, quizás?","Es bastante imprudente entrar en la guarida de un tigre pensando que podrás salir de ella fácilmente."));
		link.l1 = PCharRepPhrase(RandSwear() + RandPhraseSimple("¡Ve a besar al diablo del mar! Soy el capitán " + GetFullName(PChar) + " ¡y no me importas! ¡Me voy!", "¡Juro por el diablo, realmente me estás volviendo loco!"), RandPhraseSimple("Tu propuesta no me interesa en absoluto, y no hay nada más que discutir. Adiós.", "Creo que no hay nada más que discutir entre nosotros. Lo siento, estoy ocupado y necesito irme."));
		link.l1.go = "Quest_1_Ship_BadWay_1";
		break;

	case "Quest_1_Ship_BadWay_1":
		Dialog.Text = RandSwear() + PCharRepPhrase(RandPhraseSimple("¡Capturad" + GetSexPhrase("lo", "la") + "! ¡Amarrad" + GetSexPhrase("lo", "la") + "al cañón! Veamos de qué color " + GetSexPhrase("", "") + "son sus tripas", "¡Eh! ¡Johnny! ¡Henderson! Atrapen a es" + GetSexPhrase("e granuja", "a chica") + "¡No permitan que " + GetSexPhrase("", "") + "llegue al bote salvavidas!"), RandPhraseSimple("¡Una lástima, capitán! Espero que te guste nuestra bodega. Luego decidiremos qué hacer contigo.", "Los esclavos blancos no suelen vivir mucho, capitán, así que elige: o Hends te dispara en la cabeza, o pasas el resto de tu vida en una cantera."));
		link.l1 = PCharRepPhrase(RandPhraseSimple("Te haré comer tus asquerosas tripas, " + GetFullName(NPChar) + "¡¡¡", "¡Apartaos! ¡Granujas! ¡Os mataré donde estáis parados!"), RandPhraseSimple("Tu oferta es inaceptable... ¡¡¡Y muy imprudente!!!", "No eres tan hospitalario, por lo que puedo ver... ¡Haz camino!!!"));
		link.l1.go = "Exit_Quest_1_DeckFight";
		break;

	case "Exit_Quest_1_DeckFight":
		GetCharacterPos(NPChar, &locx, &locy, &locz);
		DeleteAttribute(NPChar, "AlwaysFriend");
		sTmp = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
		LAi_SetImmortal(NPChar, true);
		LAi_SetActorType(NPChar);
		LAi_ActorRunToLocation(NPChar, "reload", sTmp, "none", "", "", "", 5.0);

		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		// группа может быть занята, а проверок по группам у нас нет... :(
		if (!CheckAttribute(pchar, "questTemp.PGGContra.Know"))
		{
			sTmp = "PGGTmp";
		}
		else
		{
			sTmp = "PGGQst";
		}
		PChar.GenQuest.PGG_Quest.GrpID = sTmp;

		for (i = 1; i < 5; i++)
		{
			sld = CharacterFromID("saylor_0" + i);
			LAi_group_MoveCharacter(sld, sTmp);
		}
		LAi_group_FightGroups(LAI_GROUP_PLAYER, sTmp, true);
		LAi_group_SetCheck(sTmp, "PGG_Q1AfterDeckFight");
		chrDisableReloadToLocation = true;

		PGG_ChangeRelation2MainCharacter(NPChar, -20);
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		LAi_SetFightMode(pchar, true);
		break;

	case "Quest_1_Time2Late":
		chrDisableReloadToLocation = false;

		// перенес сюда.. х.з. вроде будет лучше (Баг Изгоя.)
		PChar.Quest.PGGQuest1_PGGDead.Over = "Yes";
		PChar.Quest.PGGQuest1_GroupDead.Over = "Yes";
		PChar.Quest.PGGQuest1_CheckStartState.Over = "Yes";

		//		Dialog.Text = "Entonces, "+GetFullName(PChar)+", veo que cometí un error al mezclarme contigo. Ahora no hay botín para nosotros. ¡Adiós!";
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("¡Maldita sea! Llegamos tarde, y todo por culpa de esos imbéciles perezosos. Ahora no hay botín para compartir contigo, " + GetFullName(PChar) + ". ¡Iza la vela de estay! ¡Nos largamos de aquí! ", "Entonces, " + GetFullName(PChar) + ", Veo que cometí un error al mezclarme contigo. Ahora no hay botín para nosotros. ¡Adiós!"), RandPhraseSimple("¡Desaparecieron, y todo por tu tardanza! Ahora, vamos por caminos diferentes, " + GetFullName(PChar) + ".", "De ninguna manera podemos alcanzar a la caravana ahora. Cometí un error al involucrarme contigo. ¡Adiós!")) link.l1 = PCharRepPhrase(RandPhraseSimple("¡Al diablo con esa caravana! Los buzos de perlas son incluso mejores, ¡y no hay ningún riesgo involucrado!", "La suerte está con nosotros y mañana es otro día! Hay montones de lamentables mercaderes en los mares esperando a que les quitemos su dinero!"), RandPhraseSimple("¡Una lástima, en efecto, que tal brillante operación resultó ser un fracaso total! ¡Adiós!", "El hombre propone y Dios dispone... ¡Adiós!"));
		link.l1.go = "Exit_Quest_1_2Late";

		AddQuestRecord("Gen_PGGQuest1", "q1_Time2Late");
		CloseQuestHeader("Gen_PGGQuest1");
		break;

	case "Exit_Quest_1_2Late":
		LAi_SetPlayerType(PChar);
		if (sti(PChar.GenQuest.PGG_Quest.Stage) != -1)
		{
			PChar.GenQuest.PGG_Quest.Stage = -1;
			RemoveCharacterCompanion(pchar, NPChar);

			NPChar.PGGAi.IsPGG = true;
			NPChar.RebirthPhantom = true;

			LAi_SetWarriorTypeNoGroup(NPChar);
			LAi_group_MoveCharacter(NPChar, "GroupDeck");

			PChar.Quest.PGGQuest1_Clear.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_Clear.win_condition.l1.Location = PChar.location;
			if (PChar.location == "Ship_deck")
			{
				/*				PChar.Quest.PGGQuest1_RemoveShip.win_condition.l1 = "ExitFromSea";
								PChar.Quest.PGGQuest1_RemoveShip.function = "PGG_Q1RemoveShip";
								PChar.Quest.PGGQuest1_Clear.win_condition.l1 = "ExitFromSea";
				*/
				PChar.quest.Munity = "Deads";
			}
			PChar.Quest.PGGQuest1_Clear.function = "PGG_Q1EndClear";
		}
		NextDiag.CurrentNode = "Quest_1_Failed";
		DialogExit();
		break;

	case "Quest_1_CheckResult":
		if (PChar.location == PChar.GenQuest.PGG_Quest.Island.Shore)
		{
			Locations[FindLocation(PChar.GenQuest.PGG_Quest.Island.Shore)].DisableEncounters = false;
		}
		else
		{
			PChar.quest.Munity = "Deads";
		}
		chrDisableReloadToLocation = false;

		// не взяли груз...
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			PChar.GenQuest.PGG_Quest.FailedPaySum = sti(PChar.GenQuest.PGG_Quest.Days) * 10000;
			//			Dialog.Text = "Oh, ¿por qué diablos me he metido contigo? Lo has arruinado todo. Así que, ahora debes pagarme una multa de "+FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum))+".";
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("" + GetSexPhrase("Sanguinario bastardo", "Sanguinaria idiota") + ". ¡Todo se fue directo al fondo del mar, diablos!" + FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum)) + " pesos en el acto, ¡y sal de mi vista!", "¿Te has imaginado a ti mismo como el almirante Nelson? ¡Hundiste todo el botín, " + GetSexPhrase("idiota", "mujer idiota") + "! ¡Dame " + FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum)) + " pesos ahora y lárgate!"), RandPhraseSimple("¡Decidiste iniciar una guerra aquí! ¡Esto no sirvió para nada! Pero supongo que podemos olvidarlo si nos pagas " + FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum)) + " pesos.", "¡Tus métodos son completamente inaceptables! ¡Has arruinado todo el asunto! Páganos inmediatamente nuestra parte, " + FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum)) + " pesos, y lárgate."));
			link.l1 = PCharRepPhrase(RandPhraseSimple("Si no fuera por mí, ya estarías alimentando a los cangrejos, ¡avaricioso bastardo!", "¡Oh sí, debería haber dejado que su buque insignia te abordara, entonces no estarías envenenando el aire ahora, balanceándote en el patio!"), RandPhraseSimple("¡Tus exigencias están fuera de lugar, y tus insinuaciones son insultantes!", "¡No hemos acordado la pena, así que no te voy a pagar nada!"));
			link.l1.go = "Quest_1_NotPay";
			if (sti(pchar.money) >= sti(PChar.GenQuest.PGG_Quest.FailedPaySum))
			{
				link.l2 = PCharRepPhrase(RandPhraseSimple("¡No puedo darte batalla ahora mismo, y lo sabes! ¡Ahógate con tus pesos!", "¿¡¡Pesos?!! Bueno, la Señora Fortuna ciertamente no me sonríe este día. Estoy de acuerdo."), RandPhraseSimple("Tus demandas son escandalosas, pero creo que no tengo elección.", "¡Tus apetitos son excesivos, pero tengo que estar de acuerdo!"));
				link.l2.go = "Exit_Quest_1_Failed";
			}
		}
		else
		{
			PChar.GenQuest.PGG_Quest.Stage = -1;
			Dialog.Text = "¡Oh, por qué demonios me he mezclado contigo. Lo has arruinado todo.";
			link.l1 = "¡Vamos, vamos! Viste por ti mismo que no había otra manera.";
			link.l1.go = "Exit_Quest_1_Failed";
		}

		// минимум треть если взял, то гуд!
		if (sti(PChar.GenQuest.PGG_Quest.Goods.Taken) > MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Qty) / 3))
		{
			PChar.GenQuest.PGG_Quest.Ok = 1;
			//			Dialog.Text = "Entonces, nuestro botín suma "+PChar.GenQuest.PGG_Quest.Goods.Taken+" "+PChar.GenQuest.PGG_Quest.Goods.Text+". Vamos a separarnos.";
			Dialog.Text = PCharRepPhrase("¡Eso fue un trato candente! Entonces, nuestro botín suma " + PChar.GenQuest.PGG_Quest.Goods.Taken + " " + PChar.GenQuest.PGG_Quest.Goods.Text + ".", "¡Excelente trabajo, capitán! Nuestro botín suma " + PChar.GenQuest.PGG_Quest.Goods.Taken + " " + PChar.GenQuest.PGG_Quest.Goods.Text + ".");
			i = sti(PChar.GenQuest.PGG_Quest.Parts);
			PChar.GenQuest.PGG_Quest.Goods.Part = MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Taken) / i);
			if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
			{
				Dialog.Text = Dialog.Text + PCharRepPhrase(" Mi parte es ", " La parte de mi barco, ");
			}
			else
			{
				Dialog.Text = Dialog.Text + " Tu parte es ";
			}
			Dialog.Text = Dialog.Text + PChar.GenQuest.PGG_Quest.Goods.Part + ".";
			link.l1 = PCharRepPhrase(RandPhraseSimple("¡Todo está correcto! ¡Los barcos ya están siendo cargados!", "Sí, todo está correcto. Un trato es un trato."), RandPhraseSimple("Tus cálculos son correctos. Estoy de acuerdo.", "Cuando se trata de dividir, eres irreprochable."));
			link.l1.go = "Exit_Quest_1_End";
			link.l2 = PCharRepPhrase(RandPhraseSimple("¿Te atreves a exigir tu parte? ¡Deberías ser colgado en el patio de inmediato!", "¿Tu parte? Aquí cada hombre es para sí mismo. Si no quedaba nada para ti, ¡es tu problema!"), RandPhraseSimple("No creo que puedas esperar ninguna parte.", "¡Mi respuesta es no! ¡No compartiré con canallas como tú!"));
			link.l2.go = "Quest_1_NotPay";
		}
		else
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Fail");
		}
		break;

	case "Quest_1_NotPay":
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("¡Bueno, está bien entonces, no voy a discutir! ¡Adiós!", "¡No derramemos sangre y empeoremos las cosas! ¡La próxima vez tendremos mejor suerte!"), RandPhraseSimple("Bueno, adiós, capitán, no estoy en posición de hacer demandas...", "Las pérdidas y daños a mi navío no me permiten insistir en una decisión justa. Lo dejo en tu conciencia, ¡capitán!"));
		link.l1 = PCharRepPhrase(RandPhraseSimple("¡Viento favorable para ti!", "¡Siete pies bajo la quilla!"), RandPhraseSimple("¡Adiós! ¡Espero que el fresco aire del mar te sea beneficioso!", "¡Espero que nuestras desgracias no te hagan aún más insoportable, capitán! ¡Adiós!"));
		link.l1.go = "Exit_Quest_1_Failed";
		PChar.GenQuest.PGG_Quest.Stage = -1;

		bOk = makeint(NPChar.reputation) < 41 && PGG_ChangeRelation2MainCharacter(NPChar, 0) < 75;
		if (bOk || CheckAttribute(PChar, "GenQuest.PGG_Quest.Ok"))
		{
			PChar.GenQuest.PGG_Quest.Stage = 4;
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("¿No lo entendiste! ¡Podrías comprar tu vida en su lugar! ¡Agarra al bastardo!", "¿O piensas que estamos jugando contigo? Bueno, una vez que te hagamos caminar por la quilla, deberías volverte más obediente!"), RandPhraseSimple("¡Tendremos que acortar tu vida, entonces, capitán! Si no vas a ir de manera amistosa, ¡pronto conocerás a San Martín!", "Me dejas sin opción, " + GetFullName(PChar) + "¡Tomaré lo que es mío, te guste o no!"));
			link.l1 = PCharRepPhrase(RandPhraseSimple("¡Juro por el diablo, pagarás por esto!!!", "¡Yo-ho! Entonces ven a buscarme, capitán " + GetFullName(PChar) + "¡ "), RandPhraseSimple("¡El corte será largo y profundo!", "¿Te gustaría morir rápidamente o con un poco de sufrimiento?"));
			link.l1.go = "Exit_Quest_1_FailedFight";
		}
		break;

	case "Exit_Quest_1_Failed":
		if (sti(PChar.GenQuest.PGG_Quest.Stage) != -1)
		{
			AddMoneyToCharacter(PChar, -(sti(PChar.GenQuest.PGG_Quest.FailedPaySum)));
			AddQuestRecord("Gen_PGGQuest1", "q1_FailPay");
			AddQuestUserData("Gen_PGGQuest1", "sSex", GetSexPhrase("", ""));
			AddQuestUserData("Gen_PGGQuest1", "sSex1", GetSexPhrase("", ""));
		}
		CloseQuestHeader("Gen_PGGQuest1");
		RemoveCharacterCompanion(pchar, NPChar);

		if (PChar.Location == "Ship_deck")
		{
			PChar.Quest.PGGQuest1_FailedExitSea.win_condition.l1 = "ExitFromSea";
			PChar.Quest.PGGQuest1_FailedExitSea.function = "PGG_Q1EndClear";
		}
		else
		{
			PChar.Quest.PGGQuest1_FailedExitLoc.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_FailedExitLoc.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_FailedExitLoc.function = "PGG_Q1EndClear";
		}
		PGG_ChangeRelation2MainCharacter(NPChar, -5);

		LAi_SetImmortal(NPChar, true);
		// что б не били сопровождение.
		for (i = 1; i < sti(PChar.GenQuest.PGG_Quest.GrpID.Qty); i++)
		{
			sld = CharacterFromID("pirate_" + i);
			LAi_SetImmortal(sld, true);
		}

		NextDiag.CurrentNode = "Quest_1_Failed";
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor")
			LAi_SetWarriorTypeNoGroup(NPChar);
		break;

	case "Quest_1_Failed":
		Dialog.Text = "¡Ya no quiero tratar contigo!";
		link.l1 = "En absoluto ningún problema.";
		link.l1.go = "Exit";
		NextDiag.TempNode = "Quest_1_Failed";
		break;

	case "Quest_1_End":
		Dialog.Text = "Un placer hacer negocios contigo. Buena suerte.";
		link.l1 = "Y lo mismo para ti.";
		link.l1.go = "Exit";
		NextDiag.TempNode = "Quest_1_End";
		break;

	case "Exit_Quest_1_FailedFight":
		RemoveCharacterCompanion(pchar, NPChar);

		LAi_LockFightMode(pchar, false);
		LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
		LAi_group_SetRelation("PGGTmp", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups(LAI_GROUP_PLAYER, "PGGTmp", true);
		LAi_group_SetCheck("PGGTmp", "PGG_Q1AfterDeckFight");

		PChar.GenQuest.PGG_Quest.GrpID = "PGGTmp";
		chrDisableReloadToLocation = true;

		Group_AddCharacter("PGGQuest", NPChar.id);
		Group_SetGroupCommander("PGGQuest", NPChar.id);
		Group_SetAddress("PGGQuest", PChar.GenQuest.PGG_Quest.GrpLocation, "Quest_Ships", PChar.GenQuest.PGG_Quest.GrpLoc);
		Group_SetTaskNone("PGGQuest");

		PGG_ChangeRelation2MainCharacter(NPChar, -15);

		GetCharacterPos(NPChar, &locx, &locy, &locz);
		sTmp = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
		NextDiag.CurrentNode = "Second Time";
		DialogExit();

		Log_TestInfo("ir a " + sTmp + " " + NPChar.location);
		NPChar.location = PChar.location;
		if (PChar.location != "Ship_Deck")
			sTmp = "reload1_back";

		PChar.questTemp.Chr2Remove = NPChar.id;
		LAi_ActorRunToLocator(NPChar, "reload", sTmp, "RemoveCharacterFromLocation", 5.0);

		LAi_SetImmortal(NPChar, true);
		LAi_SetFightMode(pchar, true);
		break;

	case "Exit_Quest_1_End":
		RemoveCharacterCompanion(PChar, NPChar);

		i = sti(PChar.GenQuest.PGG_Quest.Goods.Part);
		/*		i *= (sti(PChar.GenQuest.PGG_Quest.Parts)-1);
				i += sti(PChar.GenQuest.PGG_Quest.StartGoods);
				n = GetCompanionQuantity(PChar);
				SetCharacterGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods), i);
				for (i = 1; i < n; i++)
				{
					iRnd = GetCompanionIndex(PChar, i);
					if (iRnd != -1)
					{
						sld = GetCharacter(iRnd);
						if (GetRemovable(sld))
						{
							Log_TestInfo("" + sld.id);
							SetCharacterGoods(sld, sti(PChar.GenQuest.PGG_Quest.Goods), 0);
						}
					}
				}
		*/
		RemoveCharacterGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods), i);
		/*		if (PChar.Location == "Ship_deck")
				{
					PChar.Quest.PGGQuest1_EndExitSea.win_condition.l1 = "ExitFromSea";
					PChar.Quest.PGGQuest1_EndExitSea.function = "PGG_Q1EndClear";
				}
				else
				{*/
		PChar.Quest.PGGQuest1_EndExitLoc.win_condition.l1 = "ExitFromLocation";
		PChar.Quest.PGGQuest1_EndExitLoc.win_condition.l1.Location = PChar.location;
		PChar.Quest.PGGQuest1_EndExitLoc.function = "PGG_Q1EndClear";
		//}
		AddQuestRecord("Gen_PGGQuest1", "q1_OkShare");
		CloseQuestHeader("Gen_PGGQuest1");

		// что б не били сопровождение.
		for (i = 1; i < sti(PChar.GenQuest.PGG_Quest.GrpID.Qty); i++)
		{
			sld = CharacterFromID("pirate_" + i);
			LAi_SetImmortal(sld, true);
		}

		LAi_SetImmortal(NPChar, true);
		NextDiag.CurrentNode = "Quest_1_End";
		DialogExit();
		LAi_SetWarriorType(NPChar); // сброс группы ГГ
		LAi_group_MoveCharacter(NPChar, LAI_GROUP_PLAYER);
		break;

	case "Quest_1_SharePrise":
		chrDisableReloadToLocation = false;
		Dialog.Text = PCharRepPhrase("¡Eso fue una verdadera masacre! ¡Lástima que no hubiera mozas con ellos! El botín compensa  " + PChar.GenQuest.PGG_Quest.Goods.Taken + " " + PChar.GenQuest.PGG_Quest.Goods.Text + ".", "¡No está mal, capitán! El botín compensa " + PChar.GenQuest.PGG_Quest.Goods.Taken + " " + PChar.GenQuest.PGG_Quest.Goods.Text + ".");

		i = sti(PChar.GenQuest.PGG_Quest.Parts);
		PChar.GenQuest.PGG_Quest.Goods.Part = MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Taken) / i);
		SetCharacterGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods), sti(PChar.GenQuest.PGG_Quest.Goods.Taken) + GetCargoGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods)));
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			Dialog.Text = Dialog.Text + " Mi parte es ";
		}
		else
		{
			Dialog.Text = Dialog.Text + " Tu parte es ";
		}
		Dialog.Text = Dialog.Text + PChar.GenQuest.PGG_Quest.Goods.Part + ".";
		link.l1 = PCharRepPhrase(RandPhraseSimple("¡Totalmente justo, maldita sea!", "¡Todo está perfectamente bien, maldita sea!"), RandPhraseSimple("Tus cálculos son correctos. Estoy de acuerdo.", "Cuando se trata de dividir, eres irreprochable."));
		link.l1.go = "Exit_Quest_1_End";
		break;
		//===================================
		//              Exits
		//===================================
	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor")
			LAi_SetWarriorTypeNoGroup(NPChar);
		break;

	case "Exit_2":
		if (CheckAttribute(pchar, "GenQuest.PGG_Quest"))
			DeleteAttribute(pchar, "GenQuest.PGG_Quest"); // fix
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor")
			LAi_SetWarriorTypeNoGroup(NPChar);
		break;

	case "Exit_Smugglers_Fight":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();

		LAi_group_FightGroups(LAI_GROUP_PLAYER, "PGGTmp", true);
		LAi_SetFightMode(pchar, true);
		break;

	case "Exit_ShowParam":
		NextDiag.CurrentNode = "Second Time";
		//		NPChar.quest.meeting = true;
		DialogExit();

		PChar.SystemInfo.OnlyShowCharacter = true;
		LaunchCharacter(NPChar);
		break;
	}
}
/* TEMPLATE
		Dialog.Text = "";
		link.l1 = "";
		link.l1.go = "";
		link.l2 = "";
		link.l2.go = "";
		link.l3 = "";
		link.l3.go = "";
*/
