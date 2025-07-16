// Юрген Шмидт - оружейник
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp, iRem;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);

	string NodeName = Dialog.CurrentNode;
	string NodePrevName = "";
	if (CheckAttribute(NextDiag, "PrevNode"))
		NodePrevName = NextDiag.PrevNode;

	switch (Dialog.CurrentNode)
	{
	case "First time":
		if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
		{
			dialog.text = "Escucha, señor, ¿por qué dejaste que tus puños pelearan, eh? No tienes nada que hacer en mi taller hasta que seas nuestro enemigo. ¡Fuera!";
			link.l1 = "Mm...";
			link.l1.go = "exit";
			break;
		}
		if (npchar.quest.meeting == "0")
		{
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) // стал другом нарвалов
			{
				dialog.text = "Ah, " + GetFullName(pchar) + "¡He oído hablar de tus hazañas. Es bueno que te hayas convertido en amigo de Donald y en nuestro aliado. Los Narvales saben apreciar la amistad, te lo puedo asegurar.";
				link.l1 = "Eso espero. ¿Puedo contar con tus servicios ahora?";
				link.l1.go = "friend";
			}
			else
			{
				dialog.text = "¿Entonces? ¿Qué quieres?";
				link.l1 = TimeGreeting() + ". Mi nombre es " + GetFullName(pchar) + "Y solo estoy paseando, conociendo a la gente. ¿Te molesto?";
				link.l1.go = "meeting";
			}
			npchar.quest.meeting = "1";
		}
		else
		{
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) // стал другом нарвалов
			{
				dialog.text = "Ah, " + GetFullName(pchar) + "¡He oído hablar de tus hazañas. Es bueno que te hayas convertido en amigo de Donald y nuestro aliado. Los Narvales saben apreciar la amistad, te lo puedo asegurar.";
				link.l1 = "Eso espero. ¿Puedo contar con tus servicios ahora?";
				link.l1.go = "friend";
			}
			else
			{
				dialog.text = "Ah, " + GetFullName(pchar) + "¡¿Quieres hablar otra vez?!  Tengo que decepcionarte, no tengo tiempo ni ganas para eso.";
				link.l1 = "Está bien, no te molestaré.";
				link.l1.go = "exit";
			}
		}
		NextDiag.TempNode = "First time";
		break;

	case "meeting": // первая встреча
		dialog.text = "¡Exactamente! Me estás molestando, señor. Soy Jurgen Schmidt, armero y herrero del clan Narval. Proveo a nuestra gente con armas. Pero se necesita tiempo para hacer una buena hoja, llave, cerradura o para reparar el mecanismo del mosquete de torre. Se necesita mucho tiempo, paciencia y atención. Por eso no me gusta que la gente me moleste.";
		link.l1 = "¿Fabricas armas? ¿Puedo pedirte algo?";
		link.l1.go = "meeting_1";
		break;

	case "meeting_1":
		dialog.text = "No. Solo hago armas para los miembros del clan Narval. Este es mi principio y lo mantendré. Así que ni siquiera lo esperes, señor. Únete a nuestro clan o al menos conviértete en nuestro aliado y en ese caso hablaremos.";
		link.l1 = "Está bien. Entonces, te dejo. ¡Perdona por molestarte!";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	case "friend":
		dialog.text = "Puedes. Amigo de los Narvales es mi amigo también, así que te estoy escuchando.";
		link.l1 = "Me gustaría encargar un sable.";
		link.l1.go = "blade";
		if (CheckAttribute(npchar, "quest.narval_blade") && pchar.questTemp.LSC.Mary == "alive")
		{
			link.l2 = "He oído que hiciste una hoja especial para el difunto Alan Milrow. He visto ese espadón, es un arma magnífica. ¿Puedo encargar algo así?";
			link.l2.go = "narval";
		}
		link.l3 = "No tengo ideas todavía. ¡Lo pensaré y luego regresaré!";
		link.l3.go = "exit";
		NextDiag.TempNode = "Jurgen";
		break;

	case "Jurgen":
		if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
		{
			dialog.text = "Ja, " + GetFullName(pchar) + "¡Así que no te has ahogado? ¡Eso es algo! ¿Estás realmente vivo?";
			link.l1 = "No te preocupes, Jurgen. ¡Estoy vivo! No iba a ahogarme...";
			link.l1.go = "exit";
			npchar.quest.return_isl = "true";
			NextDiag.TempNode = "Jurgen";
			break;
		}
		dialog.text = "Ah, " + GetFullName(pchar) + ". ¿Qué quieres?";
		if (CheckAttribute(npchar, "quest.narval_blade") && npchar.quest.narval_blade == "ferrum")
		{
			if (GetCharacterItem(pchar, "jewelry11") >= 3)
			{
				link.l4 = "He traído tus tres piezas del hierro especial como pediste. Echa un vistazo, ¿es esto lo que quieres?";
				link.l4.go = "narval_7";
			}
			if (CheckCharacterItem(pchar, "meteorite"))
			{
				link.l5 = "Tómalo, Jurgen. He encontrado un lingote de hierro interesante en el fondo, pero pesa mucho más de lo que pediste. Cinco libras, no menos.";
				link.l5.go = "narval_7_1";
			}
		}
		if (!CheckAttribute(npchar, "quest.blade_done"))
		{
			link.l1 = "Me gustaría encargar una hoja.";
			if (!CheckAttribute(npchar, "quest.blade_rules"))
				link.l1.go = "blade";
			else
				link.l1.go = "blade_4";
		}
		if (CheckAttribute(npchar, "quest.blade_payseek"))
		{
			link.l1 = "He traído más doblones como pago por la espada.";
			link.l1.go = "blade_3";
		}
		if (CheckAttribute(npchar, "quest.narval_blade") && pchar.questTemp.LSC.Mary == "alive" && npchar.quest.narval_blade == "begin" && pchar.questTemp.LSC != "return") // patch-9
		{
			link.l2 = "He oído que has hecho una espada especial para el difunto Alan Milrow. He visto esa espada ancha, es un arma excelente. ¿Puedo pedir algo así?";
			link.l2.go = "narval";
		}
		if (CheckAttribute(npchar, "blade_date") && GetNpcQuestPastDayParam(npchar, "blade_date") >= 20)
		{
			link.l1 = "Estoy aquí por mi pedido. Ya debe estar listo, ¿verdad?";
			link.l1.go = "blade_done_2";
		}
		link.l3 = "No, no es nada, solo quería saludarte.";
		link.l3.go = "exit";
		NextDiag.TempNode = "Jurgen";
		break;

	// --> заказ клинков
	case "blade":
		dialog.text = "Está bien. Pero tengo algunos requisitos especiales para cualquier pedido, así que escucha con atención primero.";
		link.l1 = "Soy todo oídos.";
		link.l1.go = "blade_1";
		break;

	case "blade_1":
		dialog.text = "Puedes encargarme solo una hoja y solo una vez. No hago un arma específica, solo puedes nombrar el tipo: estoque, sable o espada ancha. Piensa sabiamente antes de elegir, las características finales y la calidad de la hoja dependerán de los materiales que posea en este momento\nAhora. Tomará veinte días fabricar tu pedido. Solo acepto doblones. Mil monedas. Dinero por adelantado.";
		link.l1 = "¡De veras! Caro...";
		link.l1.go = "blade_2";
		break;

	case "blade_2":
		dialog.text = "Es caro. Pero hago excelentes espadas, así que el precio es bastante justo. De todos modos, es tu decisión, sin presión.";
		link.l1 = "Tengo entendido, Jurgen. Sí, quiero hacer un pedido.";
		link.l1.go = "blade_3";
		link.l2 = "Hm. Necesito tiempo para pensar antes de ordenar algo de ti. ¡Hablaremos de esto más tarde!";
		link.l2.go = "exit";
		NextDiag.TempNode = "Jurgen";
		npchar.quest.blade_rules = "true";
		npchar.quest.blade_dublon = 1000;
		AddQuestRecord("LSC", "17");
		break;

	case "blade_3":
		dialog.text = "Muy bien. Dame tus doblones entonces.";
		if (CheckCharacterItem(pchar, "gold_dublon"))
		{
			npchar.quest.blade_pay = GetCharacterItem(pchar, "gold_dublon");
			link.l1 = "Aquí, por favor. Tengo " + FindRussianQtyString(sti(npchar.quest.blade_pay)) + ".";
			link.l1.go = "blade_pay";
		}
		link.l2 = "Hum. Desafortunadamente, no tengo ninguno conmigo ahora. Pero te los traeré seguro y continuaremos nuestra charla.";
		link.l2.go = "exit";
		NextDiag.TempNode = "Jurgen";
		break;

	case "blade_4":
		dialog.text = "¿Entonces es tu elección final? ¿Estás seguro?";
		link.l1 = "Sí, lo estoy.";
		link.l1.go = "blade_3";
		break;

	case "blade_pay":													  // оплата
		if (sti(npchar.quest.blade_dublon) < sti(npchar.quest.blade_pay)) // полная сумма
		{
			npchar.quest.blade_pay = sti(npchar.quest.blade_dublon);
			iTemp = 0;
		}
		else
			iTemp = sti(npchar.quest.blade_dublon) - sti(npchar.quest.blade_pay);
		npchar.quest.blade_dublon = iTemp; // запоминаем остаток
		RemoveItems(pchar, "gold_dublon", sti(npchar.quest.blade_pay));
		Log_Info("Has entregado " + sti(npchar.quest.blade_pay) + " doblones");
		PlaySound("interface\important_item.wav");
		if (iTemp == 0)
		{
			dialog.text = "Espléndido. Me has pagado por mi trabajo y materiales, así que puedo empezar ahora.";
			link.l1 = "¿Puedo hacer un pedido?";
			link.l1.go = "blade_done";
		}
		else
		{
			dialog.text = "Está bien. Acepto tus doblones. Tienes que traerme " + FindRussianQtyString(sti(npchar.quest.blade_dublon)) + " más.";
			link.l1 = "Te los traeré cuando los tenga.";
			link.l1.go = "exit";
			npchar.quest.blade_payseek = "true";
		}
		break;

	case "blade_done":
		DeleteAttribute(npchar, "quest.blade_payseek");
		dialog.text = "¡Claro! ¿Qué tipo te gusta más? ¿Rapiers, sables o espadones?";
		link.l1 = "Rapiers. Me gustan las armas elegantes y ligeras.";
		link.l1.go = "rapier";
		link.l2 = "Sables. Son óptimos en mi opinión.";
		link.l2.go = "sabre";
		link.l3 = "¡Espadones, sin duda! ¡Corta y raja!";
		link.l3.go = "palash";
		break;

	case "rapier":
		npchar.quest.blade_done = SelectJurgenBladeDone("rapier");
		dialog.text = "Como desees. Vuelve por tu pedido en veinte días, no antes.";
		link.l1 = "¡Gracias! Te veré en veinte días. Adiós, Jurgen.";
		link.l1.go = "blade_done_1";
		break;

	case "sabre":
		npchar.quest.blade_done = SelectJurgenBladeDone("sabre");
		dialog.text = "Como desees. Vuelve por tu pedido en veinte días, no antes.";
		link.l1 = "¡Gracias! Te veré en veinte días. Adiós, Jurgen.";
		link.l1.go = "blade_done_1";
		break;

	case "palash":
		npchar.quest.blade_done = SelectJurgenBladeDone("palash");
		dialog.text = "Como desees. Vuelve por tu pedido en veinte días, no antes.";
		link.l1 = "¡Gracias! Te veré en veinte días. Adiós, Jurgen.";
		link.l1.go = "blade_done_1";
		break;

	case "blade_done_1":
		DialogExit();
		SaveCurrentNpcQuestDateParam(npchar, "blade_date");
		NextDiag.CurrentNode = "Jurgen";
		AddQuestRecord("LSC", "18");
		break;

	case "blade_done_2":
		dialog.text = "Sí. Tu hoja está lista. Por favor, tómala y úsala. Comprenderás que vale su precio tan pronto como la toques.";
		link.l1 = "Gracias, Jurgen.";
		link.l1.go = "blade_done_3";
		break;

	case "blade_done_3":
		DialogExit();
		NextDiag.CurrentNode = "Jurgen";
		GiveItem2Character(pchar, npchar.quest.blade_done);
		PlaySound("interface\important_item.wav");
		DeleteAttribute(npchar, "blade_date");
		break;

	// заказ палаша Нарвал для Мэри
	case "narval":
		dialog.text = "¡Ay, mi amigo, tengo que rechazarlo por dos razones! Primero, solo haré tal espada ancha para un miembro del clan de los Narvales y solo para alguien especial. En segundo lugar, no tengo materiales para ello.";
		link.l1 = "¿Y cuál es ese hierro especial que necesitas? He oído que lo sacaron del fondo...";
		link.l1.go = "narval_1";
		break;

	case "narval_1":
		dialog.text = "Exactamente. Hay piezas de este metal dispersas por todo nuestro banco. No sé cómo llegaron allí. Pero el hierro es único, nunca se oxida y las hojas hechas de él nunca se desafilan. Así que si logras obtener el hierro, podríamos resolver el asunto. Pero aún hay un problema, no eres un Narval...";
		link.l1 = "¿Hm. Realmente importa?";
		link.l1.go = "narval_2";
		break;

	case "narval_2":
		dialog.text = "Sí. Puedes considerar eso como mi capricho, pero haré tal espadón solo para Narval.";
		link.l1 = "Bueno... Está bien, acepto eso. Pero tengo una idea. ¿Puedo encargar esta hoja para el miembro del clan Narval?";
		link.l1.go = "narval_3";
		break;

	case "narval_3":
		dialog.text = "Hm. Supongo que podrías hacerlo si me traes el hierro. No violará mis principios... ¿Y para quién quieres que haga el alfanje?";
		link.l1 = "Para la María Roja. Ella es del clan Narval y merece poseer un arma tan excelente.";
		link.l1.go = "narval_4";
		break;

	case "narval_4":
		dialog.text = "¡Ja! Podría haberlo adivinado yo mismo. Me estoy volviendo demasiado viejo... Bueno, estoy de acuerdo. Mary estará realmente feliz de recibir un regalo así, estoy seguro... Tráeme el hierro y haré el espadón. Tomaré para la hoja... ah, lo que sea, lo haré gratis. Será un regalo no solo de ti, sino de ambos.";
		link.l1 = "¡Gracias! ¿Cuánto hierro necesitarás?";
		link.l1.go = "narval_5";
		break;

	case "narval_5":
		dialog.text = "Esas piezas que hemos encontrado en el fondo eran bastante iguales - una libra cada una. Necesito tres piezas como esas.";
		link.l1 = "Está bien. Intentaré encontrarlos. Y volveremos a hablar.";
		link.l1.go = "narval_6";
		break;

	case "narval_6":
		DialogExit();
		npchar.quest.narval_blade = "ferrum";
		NextDiag.CurrentNode = "Jurgen";
		// кладем гигантский кусок метеорита на дно
		sld = ItemsFromID("meteorite");
		sld.shown = true;
		sld.startLocation = "underwater";
		sld.startLocator = "item" + (rand(7) + 1);
		Log_TestInfo("Meteorito en el localizador " + sld.startLocator);
		pchar.quest.LSC_narval_ferrum.win_condition.l1 = "item";
		pchar.quest.LSC_narval_ferrum.win_condition.l1.item = "meteorite";
		pchar.quest.LSC_narval_ferrum.function = "LSC_NarvalFerrum";
		AddQuestRecord("LSC", "19");
		break;

	case "narval_7":
		RemoveItems(pchar, "jewelry11", 3);
		PlaySound("interface\important_item.wav");
		dialog.text = "Déjame ver... ¡Sí lo es! ¿Fue difícil encontrar piezas tan pequeñas en el fondo?";
		link.l1 = "Bueno, ¿qué puedo decir...? Mary vale tales problemas, ¿no es así?";
		link.l1.go = "narval_8";
		pchar.quest.LSC_narval_ferrum.over = "yes"; // снять прерывание
		break;

	case "narval_7_1":
		RemoveItems(pchar, "meteorite", 1);
		PlaySound("interface\important_item.wav");
		dialog.text = "Déjame ver... ¡Eso sí que es algo! Sí, es el hierro de base, pero nunca antes había visto piezas tan grandes. Esta será suficiente para hacer el alfanje. ¿Fue difícil encontrarlo?";
		link.l1 = "Bueno, ¿qué puedo decir... Mary vale tales problemas, no es así?";
		link.l1.go = "narval_8";
		break;

	case "narval_8":
		dialog.text = "Me gustas cada vez más, " + pchar.name + "... Muy bien entonces. Ahora es mi turno de trabajar en nombre de nuestra hermosa Amazona. Me tomará dos días hacer el sable, dejaré de lado otros encargos.\nTráeme a Mary pasado mañana. No le digas, es una sorpresa. Estará feliz como una niña.";
		link.l1 = "¡Trato hecho, Jurgen! ¡Nos vemos pasado mañana!";
		link.l1.go = "narval_9";
		break;

	case "narval_9":
		DialogExit();
		npchar.quest.narval_blade = "work";
		NextDiag.CurrentNode = "narval_10";
		SetFunctionTimerCondition("LSC_NarvalBladeForMary", 0, 0, 2, false); // таймер
		AddQuestRecord("LSC", "21");
		break;

	case "narval_10":
		dialog.text = "" + pchar.name + ", no me molestes. Quieres que termine la espada ancha a tiempo, ¿verdad?";
		link.l1 = "Sí, claro. Me voy.";
		link.l1.go = "exit";
		NextDiag.TempNode = "narval_10";
		break;

		//----------------------------------------- специальные реакции -----------------------------------------------
		// обнаружение ГГ в сундуках
	case "Man_FackYou":
		dialog.text = LinkRandPhrase("¿Qué estás haciendo ahí, eh? ¡Ladrón!", "¡Solo mira eso! ¡Tan pronto como me perdí en la contemplación, decidiste revisar mi cofre!", "¿Decidiste revisar mis cofres? ¡No te saldrás con la tuya!");
		link.l1 = "¡Maldita sea!";
		link.l1.go = "fight";
		break;

	case "fight":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		LAi_SetOwnerTypeNoGroup(npchar);
		LAi_group_Attack(NPChar, Pchar);
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	// замечание по обнажённому оружию
	case "LSCNotBlade":
		dialog.text = LinkRandPhrase("Escucha, será mejor que guardes tu arma. Me pone nervioso.", "Sabes, correr con la hoja no se tolera aquí. Guárdala.", "Escucha, no juegues al caballero medieval corriendo con una espada por ahí. Guárdala, no te queda bien...");
		link.l1 = LinkRandPhrase("Bien.", "Bien.", "Como dices...");
		link.l1.go = "exit";
		NextDiag.TempNode = "First Time";
		break;

	case "CitizenNotBlade":
		if (loadedLocation.type == "town")
		{
			dialog.text = NPCharSexPhrase(NPChar, "Escucha, soy ciudadano de la ciudad y te pediría que bajes tu espada.", "Escucha, soy ciudadano de la ciudad y te pediría que bajes tu espada.");
			link.l1 = LinkRandPhrase("Bien.", "Bien.", "Como usted diga...");
		}
		else
		{
			dialog.text = NPCharSexPhrase(NPChar, "Ten cuidado, amigo, al correr con un arma. Puedo ponerme nervioso...", "No me gusta cuando los hombres caminan frente a mí con sus armas listas. Me asusta...");
			link.l1 = RandPhraseSimple("Entendido.", "Me lo estoy llevando.");
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

string SelectJurgenBladeDone(string _sType)
{
	string sBlade;
	switch (_sType)
	{
	case "rapier":
		if (sti(pchar.rank) > 15)
			sBlade = "q_blade_18";
		else
			sBlade = "q_blade_16";
		break;

	case "sabre":
		if (sti(pchar.rank) > 15)
			sBlade = "q_blade_19";
		else
			sBlade = "q_blade_10";
		break;

	case "palash":
		if (sti(pchar.rank) > 15)
			sBlade = "q_blade_21";
		else
			sBlade = "q_blade_13";
		break;
	}
	return sBlade;
}
