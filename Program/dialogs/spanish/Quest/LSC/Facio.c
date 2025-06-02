// посредник-дипломат кланов Джузеппе Фацио
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;
	string sTemp;
	float locx, locy, locz;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		if (npchar.quest.meeting == "0")
		{
			dialog.text = "Hola, hola... ¿Eres nuevo aquí? No recuerdo tu cara. Permíteme presentarme - soy Giuseppe Fazio, un especialista en resolver problemas en esta pequeña isla.";
			link.l1 = TimeGreeting() + ". Me llamo " + GetFullName(pchar) + " Tienes razón, soy nuevo aquí. Perdona mi curiosidad, pero ¿qué tipo de problemas resuelves?";
			link.l1.go = "meeting";
			npchar.quest.meeting = "1";
		}
		else
		{
			dialog.text = "Ah, tú otra vez, querido " + pchar.name + ". ¿Qué te trae a mi humilde casa?";
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict") || CheckAttribute(pchar, "GenQuest.RivadosConflict") || CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				link.l10 = "Fazio, tengo un grave conflicto con un clan. Necesito resolver este problema.";
				link.l10.go = "conflict";
			}
			// --> квестовые ветки
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_3")
			{
				link.l4 = "Giuseppe, estoy buscando a un hombre llamado Adolf Barbier. Me han dicho que estuviste bebiendo con él en la taberna recientemente...";
				link.l4.go = "adolf";
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Drink") && pchar.questTemp.LSC.Drink == "begin")
			{
				link.l5 = "Giuseppe, dicen que eres completamente resistente a las bebidas. No importa cuánto bebas, aún te mantienes en pie.";
				link.l5.go = "drink";
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Drink") && GetCharacterItem(pchar, "gold_dublon") >= 100 && pchar.questTemp.LSC.Drink == "wait")
			{
				link.l5 = "Estoy listo para jugar tu juego. Aquí está mi apuesta.";
				link.l5.go = "drink_4";
			}
			// <-- квестовые ветки
			if (CheckAttribute(npchar, "quest.parol"))
			{
				link.l1 = "Quiero saber la contraseña actual de los clanes para entrar en sus territorios.";
				link.l1.go = "parol_choice";
			}
			link.l2 = LinkRandPhrase("¿Tienes algo interesante que decir?", "¿Ha ocurrido algo nuevo en la isla?", "¿Me contarás los últimos chismes?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Nada especial, Giuseppe. Solo quería verte.";
			link.l3.go = "exit";
		}
		NextDiag.TempNode = "First time";
		break;

	case "meeting":
		dialog.text = "De todo tipo, mi querido, de todo tipo. Por ejemplo, suavizo las cosas entre el almirante y los clanes. Como ya sabrás, Rivados, Narvales y el almirante son enemigos mutuos. Actúo como mediador cuando las cosas se ponen complicadas.\nAdemás, a menudo asumo el papel de una parte neutral cuando el almirante vende provisiones a los clanes. Pero esto es solo una pequeña parte de mi negocio. Así que si tienes problemas con Rivados o Narvales, no dudes en pedir mi ayuda, veremos qué se puede hacer.";
		link.l1 = "Bien. Lo consideraré.";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	// пароли
	case "parol_choice":
		dialog.text = "¿Qué clan?";
		link.l1 = "Narvales.";
		link.l1.go = "parol_nrv";
		link.l2 = "Rivados.";
		link.l2.go = "parol_rvd";
		break;

	case "parol_nrv":
		dialog.text = "¿Quieres ver a Donald Greenspen, verdad?";
		link.l1 = "Correcto. ¿Entonces conoces la contraseña?";
		link.l1.go = "parol";
		pchar.questTemp.LSC.parol = "Narwals";
		sTotalTemp = sNrvParol;
		break;

	case "parol_rvd":
		dialog.text = "¿Quieres ver a Eddie el Negro, ¿verdad?";
		link.l1 = "Algo así. ¿Entonces conoces la contraseña?";
		link.l1.go = "parol";
		pchar.questTemp.LSC.parol = "Rivados";
		sTotalTemp = sRvdParol;
		break;

	case "parol":
		if (!CheckAttribute(npchar, "quest.parolrules"))
		{
			dialog.text = "¡Claro! Pero déjame darte algunos detalles primero. Las contraseñas contienen solo una palabra y cambian cada semana. Cada séptimo, decimocuarto, vigésimo primero y vigésimo octavo día del mes.\nAsí que vigila la fecha actual para evitar errores. Finalmente, como debes entender, esto no es una obra de caridad. Cincuenta doblones por una contraseña. Recuerda, solo doblones.";
			link.l1 = "¿Cincuenta doblones? ¡Es una suma enorme!";
			link.l1.go = "parol_1";
		}
		else
		{
			dialog.text = "Claro, muchacho. Sabes el precio. ¿Tienes cincuenta doblones?";
			if (GetCharacterItem(pchar, "gold_dublon") >= 50)
			{
				link.l1 = "Sí. Toma tus monedas.";
				link.l1.go = "parol_pay";
			}
			link.l2 = "Lamentablemente, no lo sé. Tal vez más tarde...";
			link.l2.go = "exit";
		}
		NextDiag.TempNode = "First time";
		break;

	case "parol_1":
		dialog.text = "Bueno-bueno, muchacho, cálmate. No seas codicioso, confía en mí: conozco el verdadero precio de mi información. No vas a simplemente pasear por los barcos de " + pchar.questTemp.LSC.parol + " ¿verdad? Correcto. Así que tienes que estar listo para perder algunas monedas... Entonces, ¿estás listo para pagar cincuenta doblones?";
		if (GetCharacterItem(pchar, "gold_dublon") >= 50)
		{
			link.l1 = "Sí. Toma tus monedas.";
			link.l1.go = "parol_pay";
		}
		link.l2 = "Lamentablemente, no tengo tal dinero. Tal vez más tarde...";
		link.l2.go = "exit";
		NextDiag.TempNode = "First time";
		npchar.quest.parolrules = "true";
		break;

	case "parol_pay":
		RemoveItems(pchar, "gold_dublon", 50);
		dialog.text = "¡Estupendo! Un placer hacer negocios contigo. La contraseña actual para " + pchar.questTemp.LSC.parol + "es: '" + sTotalTemp + "'. Recuérdalo bien y no te equivoques o no daré ni una sola moneda por tu vida.";
		link.l1 = "Lo sé, lo sé... ¡Gracias!";
		link.l1.go = "exit";
		AddQuestRecord("LSC", "parol");
		AddQuestUserData("LSC", "sText", pchar.questTemp.LSC.parol);
		AddQuestUserData("LSC", "sParol", sTotalTemp);
		if (pchar.questTemp.LSC.parol == "Rivados")
			pchar.questTemp.LSC.RParol_bye = "true";
		else
			pchar.questTemp.LSC.NParol_bye = "true";
		break;

	case "adolf":
		dialog.text = "¡Ah, por supuesto, mi buen viejo Adolfo! Sí, hablé con él. Mira, querido, me alegré de recuperar mi dinero, ¡el dinero que pensé que nunca volvería a ver! Adolfo pidió prestada una gran suma con la garantía de su destacado fusil y tuvo problemas para devolverme el dinero.\nPerdí toda esperanza de recuperarlo y estaba a punto de vender ese stutzen a nuestro querido Axel Yost. ¡Pero de repente, el querido Adolfo me trajo mi oro! Resultó que consiguió suficientes monedas no solo para redimir su stutzen, sino también para comprar la cabaña de Sessile Gallard en la proa del 'Santa Florentina'.\nClaro, esto es mucho mejor que vivir en una bodega medio inundada.\nPor lo tanto, Adolfo tiene su rifle de vuelta, un nuevo hogar y yo tengo mi dinero. ¿Por qué iba a negarme a tomar una copa con él, especialmente cuando él estaba invitando?";
		link.l1 = "¡Ah, claro! Tenías muchas cosas por las que brindar. Y gratis... Gracias, Giuseppe, me has ayudado mucho. Ahora sé dónde encontrar a Adolf.";
		link.l1.go = "adolf_1";
		break;

	case "adolf_1":
		dialog.text = "Siempre es un placer, querido. Pero no busques a Adolfo en su camarote hasta que caiga la noche, está muy ocupado, corriendo de aquí para allá con algunos asuntos... Sí, ¡y visítame más a menudo para charlar!";
		link.l1 = "Te invitaré cuando tenga mi propia cabina... ¡Adiós y buena suerte!";
		link.l1.go = "adolf_2";
		break;

	case "adolf_2":
		DialogExit();
		LSC_CreateAdolfClone();							  // заменяем Адольфа клоном
		pchar.questTemp.Saga.SharkHunt = "search_mush_4"; // флаг на Адольфа в каюте
		AddQuestRecord("SharkHunt", "14");
		break;

	case "whiskey":
		switch (sti(npchar.quest.poisonnode))
		{
		case 1: // у себя
			dialog.text = "¿Ah? ¿Por qué invades mi lugar como si hubiera un incendio? ¿Quién crees que eres??";
			link.l1 = "¡Tu justicia... envenenador!";
			link.l1.go = "whiskey_1";
			break;

		case 2: // на Эве
			dialog.text = "¡Perdóname! ¡Lo juro, me han forzado! Me han puesto una pistola contra mi...";
			link.l1 = "¡Cállate. Lo sé. ¿Dónde está el último bastardo? ¿Dónde está Marcello Cíclope?!";
			link.l1.go = "whiskey_3";
			SetFunctionTimerCondition("LSC_FacioReturn", 0, 0, 1, false); // вертаем на место Фацио через сутки
			break;

		case 3: // у Акулы
			dialog.text = "¡Lo juro, me han obligado! ¡Ya le he contado todo al almirante! No pude resistirles, ellos...";
			link.l1 = "Cállate. Lo sé. ¿Dónde está el último bastardo? ¿Dónde está Marcello Cíclope?!";
			link.l1.go = "whiskey_3";
			SetFunctionTimerCondition("LSC_FacioReturn", 0, 0, 1, false); // вертаем на место Фацио через сутки
			break;
		}
		break;

	case "whiskey_1":
		dialog.text = "¿Qué... qué dijiste?";
		link.l1 = "Lo sé todo, bastardo. Has estado trabajando con Chad Kapper. Has traído un barril de ron envenenado al almirante. Ahora reza, miserable maricón...";
		link.l1.go = "whiskey_2";
		break;

	case "whiskey_2":
		dialog.text = "¡Espera! ¡Detente! ¡Perdóname! ¡Lo juro, me han obligado! Tenían un arma contra mi...";
		link.l1 = "Cállate. Lo sé. ¿Dónde está el último bastardo? ¿Dónde está Marcello Cíclope?!";
		link.l1.go = "whiskey_3";
		break;

	case "whiskey_3":
		dialog.text = "¡Yo... yo... yo no sé!";
		link.l1 = "¡Estás mintiendo, canalla! Lo veo. ¿Dónde está Cíclope?";
		if (pchar.questTemp.LSC.Mary == "die")
			link.l1.go = "whiskey_10"; // ушел на Флерон
		else
			link.l1.go = "whiskey_4";
		break;

	case "whiskey_4":
		dialog.text = "Él... él recibió alguna orden de Kapper y se ha ido. ¡No sé dónde está!";
		link.l1 = "Mintiendo de nuevo. Sabes todo. No seas cobarde, criatura inmunda - Kapper está muerto y no te hará daño. Pero si no me dices dónde está Marcello, ¡te destazaré como a un cerdo ahora mismo! ¿Qué ordenó Chad al Cíclope?";
		link.l1.go = "whiskey_5";
		break;

	case "whiskey_5":
		dialog.text = "Lo envió a matar... a María la Roja.";
		link.l1 = "¿Qué?! Habla ahora, ¿cómo piensa hacer eso? ¡Es imposible entrar en su camarote! ¿Cómo planea matarla?!";
		link.l1.go = "whiskey_6";
		break;

	case "whiskey_6":
		dialog.text = "Se meterá en el camarote de Jurgen mientras el herrero esté fuera. Luego se moverá al fondo de la bodega, la cruzará y llegará al camarote de Mary. \nEntonces lo único que necesitará es esperar hasta que la chica le dé la espalda o se quede dormida. Eso es lo que me dijo Chad. No sé nada más, ¡lo juro!";
		link.l1 = "Eso será suficiente. ¿Cuándo se fue? ¿Cuándo, te pregunto, se fue Cíclope a la 'Herrería Ceres'?";
		link.l1.go = "whiskey_7";
		break;

	case "whiskey_7":
		dialog.text = "Ya debe estar en la cabina de Jurgen... o bajando a la bodega...";
		link.l1 = "¡Maldita sea! ¡No tengo tiempo para nadar alrededor de la Isla! ¡Dime la contraseña de los barcos de los Narvales! ¡Habla, y si me mientes, yo seguiré vivo de todos modos, pero tú morirás seguro!";
		link.l1.go = "whiskey_8";
		break;

	case "whiskey_8":
		dialog.text = "'" + sNrvParol + "...";
		link.l1 = "Entendido. Ahora reza para que la chica sobreviva.";
		link.l1.go = "whiskey_9";
		break;

	case "whiskey_9":
		DialogExit();
		chrDisableReloadToLocation = false; // открыть локацию
		NextDiag.CurrentNode = "whiskey_repeat";
		pchar.quest.LSC_RescueMary.win_condition.l1 = "location";
		pchar.quest.LSC_RescueMary.win_condition.l1.location = "LostShipsCity_town";
		pchar.quest.LSC_RescueMary.function = "LSC_RescueMary";
		AddQuestRecord("SharkHunt", "46");
		AddQuestUserData("SharkHunt", "sParol", sNrvParol);
		pchar.questTemp.LSC.NParol_bye = "true";
		break;

	case "whiskey_repeat":
		dialog.text = "¡Ya te he dicho todo lo que sabía! ¡Lo juro!";
		link.l1 = "...";
		link.l1.go = "exit";
		NextDiag.TempNode = "whiskey_repeat";
		break;

	case "whiskey_10":
		dialog.text = "Él... Él está en algún lugar dentro del 'Fleron'. Chad le ha ordenado esconderse allí y esperar sus próximas órdenes.";
		link.l1 = "Ya veo. Más te vale que sea la verdad...";
		link.l1.go = "whiskey_11";
		break;

	case "whiskey_11":
		DialogExit();
		chrDisableReloadToLocation = false; // открыть локацию
		pchar.quest.LSC_FindCyclop.win_condition.l1 = "location";
		pchar.quest.LSC_FindCyclop.win_condition.l1.location = "FleuronTavern";
		pchar.quest.LSC_FindCyclop.function = "LSC_SetCyclop_Fl";
		NextDiag.CurrentNode = "whiskey_repeat";
		AddQuestRecord("SharkHunt", "51");

		break;

	// --> конфликты
	case "conflict":
		dialog.text = "¿Es así? Bueno, muchacho, ¿qué clan te está molestando?";
		if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
		{
			link.l1 = "Narvales.";
			link.l1.go = "narval";
			npchar.quest.clan = "narval";
		}
		if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
		{
			link.l2 = "Rivados.";
			link.l2.go = "rivados";
			npchar.quest.clan = "rivados";
		}
		if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
		{
			link.l3 = "Piratas del Almirante.";
			link.l3.go = "shark";
			npchar.quest.clan = "shark";
		}
		link.l4 = "No hay tal cosa. Estaba bromeando, Giuseppe, estoy bien.";
		link.l4.go = "exit";
		break;

	case "narval":
		npchar.quest.price = sti(pchar.GenQuest.NarvalConflict) * 50;
		if (sti(pchar.GenQuest.NarvalConflict) < 3)
			dialog.text = "Bueno, no es realmente un conflicto, solo un pequeño malentendido, je-je. " + sti(npchar.quest.price) + "  doblones y tu problema se resolverá en un día.";
		else
		{
			if (sti(pchar.GenQuest.NarvalConflict) >= 3 && sti(pchar.GenQuest.NarvalConflict) < 10)
				dialog.text = "Claro, he oído sobre eso. Hiciste un gran alboroto, mi querido. Pero hay una salida. " + sti(npchar.quest.price) + " doblones y tu problema se resolverá en un día.";
			else
				dialog.text = "Toda la Isla está al tanto de la matanza que hiciste. No será fácil ayudarte, pero hay una posibilidad. " + sti(npchar.quest.price) + " doblones y trataré de resolver tu problema.";
		}
		if (GetCharacterItem(pchar, "gold_dublon") >= sti(npchar.quest.price))
		{
			link.l1 = "Aquí, toma tus monedas y resuélvelo.";
			link.l1.go = "pay";
		}
		link.l2 = "Lamentablemente, no tengo suficientes doblones conmigo en este momento. Pero los traeré más tarde, y volveremos a hablar.";
		link.l2.go = "exit";
		break;

	case "rivados":
		npchar.quest.price = sti(pchar.GenQuest.RivadosConflict) * 50;
		if (sti(pchar.GenQuest.RivadosConflict) < 3)
			dialog.text = "Bueno, no es realmente un conflicto, solo un pequeño malentendido, je-je. " + sti(npchar.quest.price) + "  doblones y tu problema se resolverá en un día.";
		else
		{
			if (sti(pchar.GenQuest.RivadosConflict) >= 3 && sti(pchar.GenQuest.RivadosConflict) < 10)
				dialog.text = "Claro, he oído sobre eso. Has hecho un gran lío, mi querido. Pero hay una salida. " + sti(npchar.quest.price) + "  doblones y tu problema se resolverá en un día.";
			else
				dialog.text = "Toda la Isla es consciente de la masacre que hiciste. No será fácil ayudarte, pero hay una posibilidad.  " + sti(npchar.quest.price) + " doblones y trataré de resolver tu problema.";
		}
		if (GetCharacterItem(pchar, "gold_dublon") >= sti(npchar.quest.price))
		{
			link.l1 = "Aquí, toma tus monedas y ocúpate de ello.";
			link.l1.go = "pay";
		}
		link.l2 = "Desafortunadamente, no tengo suficientes doblones conmigo en este momento. Pero los traeré más tarde, y hablaremos de nuevo.";
		link.l2.go = "exit";
		break;

	case "shark":
		npchar.quest.price = sti(pchar.GenQuest.SharkConflict) * 50;
		if (sti(pchar.GenQuest.SharkConflict) < 3)
			dialog.text = "Bueno, en realidad no es un conflicto, solo un pequeño malentendido, je-je. " + sti(npchar.quest.price) + "doblones y tu problema se resolverá en un día.";
		else
		{
			if (sti(pchar.GenQuest.SharkConflict) >= 3 && sti(pchar.GenQuest.SharkConflict) < 10)
				dialog.text = "Claro, he oído sobre eso. Has hecho un gran lío, mi querido. Pero hay una salida. " + sti(npchar.quest.price) + "doblones y tu problema se resolverá en un día.";
			else
				dialog.text = "Toda la Isla está al tanto de la masacre que cometiste. No será fácil ayudarte, pero hay una posibilidad. " + sti(npchar.quest.price) + "  doblones y trataré de resolver tu problema.";
		}
		if (GetCharacterItem(pchar, "gold_dublon") >= sti(npchar.quest.price))
		{
			link.l1 = "Aquí, toma tus monedas y ocúpate de ello.";
			link.l1.go = "pay";
		}
		link.l2 = "Lamentablemente, no tengo suficientes doblones conmigo ahora mismo. Pero los traeré más tarde, y hablaremos de nuevo.";
		link.l2.go = "exit";
		break;

	case "pay":
		RemoveItems(pchar, "gold_dublon", sti(npchar.quest.price));
		PlaySound("interface\important_item.wav");
		Log_Info("Has entregado " + sti(npchar.quest.price) + " doblones");
		dialog.text = "Espléndido. Ahora toma asiento y descansa. Será mejor que te quedes en mi camarote hasta que resuelva tu problema. No quiero que lo empeores aún más, mi querido.";
		link.l1 = "Bien...";
		link.l1.go = "peace";
		break;

	case "peace":
		DialogExit();
		GetCharacterPos(pchar, &locx, &locy, &locz);
		pchar.locx = locx;
		pchar.locy = locy;
		pchar.locz = locz;
		SetLaunchFrameFormParam("Un día después..." + NewStr() + "Fazio ha solucionado el conflicto", "Reload_To_Location", 0.1, 5.0);
		SetLaunchFrameReloadLocationParam(pchar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"), "LocTeleport");
		WaitDate("", 0, 0, 1, 3, 10); // крутим время
		LaunchFrameForm();
		RefreshLandTime();
		RecalculateJumpTable();
		Whr_UpdateWeather();
		switch (npchar.quest.clan)
		{
		case "narval":
			DeleteAttribute(pchar, "GenQuest.NarvalConflict"); // мирим
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend") || !CheckAttribute(pchar, "questTemp.LSC.rvd_friend"))
				LocatorReloadEnterDisable("LostShipsCity_town", "reload48", false); // открыть вход к Дональду
			LAi_group_SetRelation("LSC_NARVAL", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
			break;

		case "rivados":
			DeleteAttribute(pchar, "GenQuest.RivadosConflict"); // мирим
			if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend") || !CheckAttribute(pchar, "questTemp.LSC.nrv_friend"))
				LocatorReloadEnterDisable("LostShipsCity_town", "reload33", false); // открыть вход к Эдди
			LAi_group_SetRelation("LSC_RIVADOS", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
			break;

		case "shark":
			DeleteAttribute(pchar, "GenQuest.SharkConflict"); // мирим
			LSC_OpenSanAvgustinDoors();						  // открыть сан-августин
			LSC_OpenTartarusDoors();						  // открыть тартарус
			LAi_group_SetRelation("LSC_SHARK", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
			break;
		}
		DeleteAttribute(npchar, "quest.clan");
		DeleteAttribute(npchar, "quest.price");
		break;

	// --> пей до дна
	case "drink":
		dialog.text = "¡Vamos, muchacho! Mienten, todos mienten, je-je. Mi cabeza es solo un poco más dura que una cabeza promedio, pero soy un ser humano igual que tú, así que también me emborracho con ron. La gente bebe ron para emborracharse, ese es su único propósito. ¿Alguna vez has pensado en eso, querido?";
		link.l1 = "Ciertamente.";
		link.l1.go = "drink_1";
		break;

	case "drink_1":
		dialog.text = "¿Quieres jugar un juego divertido conmigo? ¡Se llama 'beber hasta el fondo!', ¡ja-ja! Estoy seguro de que ya has oído hablar de él. ¿Verdad?";
		link.l1 = "Sí, hubo algunos susurros sobre eso... Yo lo llamaría 'cara sobre la mesa'.";
		link.l1.go = "drink_2";
		break;

	case "drink_2":
		dialog.text = "Ja-ja-ja, mi querido muchacho, ¡has hecho reír al viejo, qué más puedo decir! '¡Cara en la mesa!' Lo recordaré... ¿Qué dices? ¿Jugamos por cien doblones?";
		link.l1 = "¿Cien doblones?";
		link.l1.go = "drink_3";
		break;

	case "drink_3":
		dialog.text = "Sí, y el perdedor paga las bebidas. ¿Trato?";
		if (GetCharacterItem(pchar, "gold_dublon") >= 100)
		{
			link.l1 = "Sí, trato hecho. Aquí está mi apuesta.";
			link.l1.go = "drink_4";
		}
		link.l2 = "Hm. No tengo tantos doblones.";
		link.l2.go = "drink_wait";
		break;

	case "drink_wait":
		dialog.text = "Bueno, ven a verme cuando los tengas, ¡y jugaremos!";
		link.l1 = "Bien...";
		link.l1.go = "exit";
		pchar.questTemp.LSC.Drink = "wait";
		break;

	case "drink_4":
		RemoveItems(pchar, "gold_dublon", 100);
		Log_Info("Has entregado 100 doblones");
		PlaySound("interface\important_item.wav");
		dialog.text = "¡Excelente, mi querido! Entonces encuéntrame a las nueve de la noche en la taberna de Sancho. Sí, tu apuesta se quedará conmigo si llegas tarde, esta es una de las reglas. Pero no llegarás tarde, ¿verdad, muchacho?";
		link.l1 = "Claro, Giuseppe. ¡Prepárate para una pelea de botellas!";
		link.l1.go = "drink_5";
		break;

	case "drink_5":
		dialog.text = "¡Y tú, y tú, mi querida! ¡Cara en la mesa! ¡Ja-ja!";
		link.l1 = "¡Nos vemos a las nueve en la taberna!";
		link.l1.go = "drink_6";
		break;

	case "drink_6":
		DialogExit();
		pchar.questTemp.LSC.Drink = "start";
		pchar.quest.LSC_DrinkOver.over = "yes"; // снять таймер
		pchar.quest.LSC_Drink.win_condition.l1 = "Timer";
		pchar.quest.LSC_Drink.win_condition.l1.date.hour = 21.0;
		pchar.quest.LSC_Drink.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
		pchar.quest.LSC_Drink.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
		pchar.quest.LSC_Drink.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
		pchar.quest.LSC_Drink.function = "LSC_DrinkPrepare";
		pchar.quest.LSC_Drink_Over.win_condition.l1 = "Timer";
		pchar.quest.LSC_Drink_Over.win_condition.l1.date.hour = 23.0;
		pchar.quest.LSC_Drink_Over.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
		pchar.quest.LSC_Drink_Over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
		pchar.quest.LSC_Drink_Over.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
		pchar.quest.LSC_Drink_Over.function = "LSC_DrinkDelete";
		AddQuestRecord("LSC_Drink", "2");
		break;

	case "drink_8":
		dialog.text = "Bueno, querida, ¿estás lista para besar la mesa, je-je? El buen Sancho ya nos ha traído ron. No necesito decirte las reglas, ¿verdad? Son bastante simples: bebemos de la misma botella hasta que uno de nosotros caiga.\nSí, podemos hablar, ¡debemos hablar! Hablar con gente decente es genial, ¿verdad? Y si ganas, puedes obtener tu premio de Sancho. ¿Lista?";
		link.l1 = "Diría que sí. ¡Empecemos, Giuseppe!";
		link.l1.go = "drink_9";
		break;

	case "drink_9":
		DialogExit();
		pchar.questTemp.LSC.Drink = "go";
		pchar.quest.LSC_Drink_Over.over = "yes"; // снять таймер
		ChangeCharacterAddressGroup(pchar, "FleuronTavern", "quest", "sit1");
		LAi_SetActorType(pchar);
		LAi_ActorSetSitMode(pchar);
		ChangeCharacterAddressGroup(npchar, "FleuronTavern", "quest", "sit2");
		LAi_SetActorType(npchar);
		LAi_ActorSetSitMode(npchar);
		DoQuestFunctionDelay("LSC_DrinkGo", 0.6);
		break;

	case "drunk":
		dialog.text = "Quince hombres muertos... ¡hic! ¡Ajá! Yo-ho-ho-ja... Y... botella...";
		link.l1 = "Glorioso...";
		link.l1.go = "exit";
		NextDiag.TempNode = "drunk";
		break;
		// <-- пей до дна

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}
