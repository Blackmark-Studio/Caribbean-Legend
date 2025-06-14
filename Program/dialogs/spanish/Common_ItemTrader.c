#include "DIALOGS\%language%\Rumours\Common_rumours.c" //Jason
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// вызов диалога по городам -->
	NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\ItemTrader\" + NPChar.City + "_ItemTrader.c ";
						 if (LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	// вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	// ============================================================================
	// ============================= блок angry ==========>>>>>>>>>>>>>>>>>>>>>>>>>
	if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
	{
		npchar.angry.ok = 1;
		if (!CheckAttribute(npchar, "angry.first")) // ловушка первого срабатывания
		{
			NextDiag.TempNode = NextDiag.CurrentNode;
			Dialog.CurrentNode = "AngryExitAgain";
			npchar.angry.first = 1;
		}
		else
		{
		}
	}
	// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
	// ============================================================================
	switch (Dialog.CurrentNode)
	{
	// -----------------------------------Диалог первый - первая встреча
	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "fight":
		DialogExit();
		NextDiag.CurrentNode = NextDiag.TempNode;
		LAi_group_Attack(NPChar, Pchar);
		break;

	case "First time":
		dialog.text = NPCharSexPhrase(npchar, "¿Le gustaría comprar equipo para usted o para sus oficiales, capitán? Si es así, ha venido justo a la persona correcta!", "¡Oh, capitán, sabía que te acercarías a mí! Puedo ofrecerte equipo para ti y tus oficiales, entre muchas otras cosas útiles.");
		link.l1 = "Muéstrame lo que tienes.";
		link.l1.go = "Trade_exit";

		/*link.l2 = "Vine por un negocio diferente.";
		link.l2.go = "quests";*/
		// --> Мангароса
		if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "find" && npchar.Merchant.type == "potion" && !CheckAttribute(npchar, "quest.mangarosa"))
		{
			link.l4 = "Oye, he encontrado una planta interesante por aquí. ¿Podrías decirme si se puede usar para preparar pociones o decocciones? Simplemente me parece interesante. ¿Puedes echarle un vistazo?";
			link.l4.go = "mangarosa";
		}
		// <-- Мангароса

		// Jason --> мини-квест Дефицитный товар
		if (CheckAttribute(pchar, "questTemp.Wine.bottle") && NPChar.location == pchar.questTemp.Wine.City + "_town" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
		{
			link.l4 = "Oye, ¿puedes venderme una botella de buen vino europeo?";
			link.l4.go = "Wine_ItemTrader";
		}
		if (CheckAttribute(pchar, "questTemp.Wine.bottles") && NPChar.location == pchar.questTemp.Wine.City + "_town" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
		{
			link.l4 = "Escucha, sé que estás vendiendo vino europeo. Necesito sesenta botellas.";
			link.l4.go = "Wine_Bottles";
		}
		if (CheckAttribute(pchar, "questTemp.Wine.Repeat1") && NPChar.location == pchar.questTemp.Wine.City + "_town" && npchar.id == pchar.questTemp.Wine.ItemTraderID && !CheckAttribute(pchar, "questTemp.Wine.fail"))
		{
			link.l4 = "Ese soy yo de nuevo. ¿Qué significa todo esto, eh?";
			link.l4.go = "Wine_Repeat1";
		}
		// <-- мини-квест Дефицитный товар

		// Sinistra --> мини-квест "Знакомство с индейцами"
		if (CheckAttribute(pchar, "questTemp.ZsI_PokupaemPistolety") && npchar.Merchant.type == "armourer")
		{
			link.l4 = "Necesito dos pistolas, junto con balas y pólvora para veinte disparos.";
			link.l4.go = "ZsI_PokupaemPistolety";
		}
		// <-- мини-квест "Знакомство с индейцами"

		// --> Цена чахотки
		if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
		{
			link.l4 = "Escucha, ¿el nombre 'Juan' te suena de algo?";
			link.l4.go = "Consumption";
		}
		// <-- Цена чахотки
		
		//--> Украденное воспоминание
			if(CheckAttribute(pchar, "questTemp.UV_Lavochniki") && !CheckAttribute(npchar, "quest.UV_Vopros") && npchar.city == "PortPax")
			{
				link.l4 = "Dime, ¿no tendrás algo verdaderamente valioso? Nada de baratijas, sino algo realmente refinado – como unos pendientes bonitos o un colgante elegante. Necesito un regalo para una dama de noble cuna.";
				link.l4.go = "UV_Lavochniki_1";
			}
            if(CheckAttribute(pchar, "questTemp.UV_Lavochniki_2") && !CheckAttribute(npchar, "quest.UV_Vopros") && npchar.city == "PortPax")
            {
				link.l4 = "¿No tendrás algo realmente valioso? Busco una joya digna incluso de la aristócrata más exigente – algo raro, elegante, no para plebeyos. Tal vez un colgante refinado o una pulsera exquisita.";
				link.l4.go = "UV_Lavochniki_2";
			}
			if(CheckAttribute(pchar, "questTemp.UV_Lavochniki_3") && !CheckAttribute(npchar, "quest.UV_Vopros") && npchar.city == "PortPax")
            {
				link.l4 = "Dime, ¿sabes algo de joyas? Necesito algo especial como regalo para una dama noble. Te aviso de inmediato – no me interesan baratijas. Quiero algo refinado: un broche ricamente decorado o un anillo lujoso.";
				link.l4.go = "UV_Lavochniki_3";
			}
			//<-- Украденное воспоминание

		// Jason --> генератор Неудачливый вор
		if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
		{
			link.l5 = "Escucha, estás lidiando con todo tipo de mercancías... Ayer o hoy, ¿alguien te ofreció venderte  " + pchar.GenQuest.Device.Shipyarder.Type + "?";
			link.l5.go = "Device_ItemTrader";
		}
		//<-- генератор Неудачливый вор

		link.l9 = "Gracias, no estoy interesado.";
		link.l9.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	case "Trade_exit":
		if (CheckNPCQuestDate(npchar, "Item_date"))
		{
			SetNPCQuestDate(npchar, "Item_date");
			GiveItemToTrader(npchar);
		}
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		LaunchItemsTrade(npchar, 0);
		break;

	// Jason --> мини-квест Дефицитный товар
	case "Wine_ItemTrader":
		dialog.text = "Claro. Setecientos pesos por botella.";
		if (makeint(Pchar.money) >= 700)
		{
			link.l1 = "Excelente. Toma el dinero y dámelo a mí.";
			link.l1.go = "Wine_ItemTrader_1";
		}
		link.l2 = "¡Excelente! Volveré una vez que decida comprar algo.";
		link.l2.go = "exit";
		break;

	case "Wine_ItemTrader_1":
		dialog.text = "Por favor, toma tu botella.";
		link.l1 = "¡Gracias!";
		link.l1.go = "exit";
		AddMoneyToCharacter(pchar, -700);
		TakeNItems(pchar, "potionwine", 1);
		PlaySound("interface\important_item.wav");
		DeleteAttribute(pchar, "questTemp.Wine.bottle");
		AddQuestRecord("Wine", "1_1");
		WineTraderQMDel();
		break;

	case "Wine_Bottles":
		dialog.text = "¡Ja! Solo soy un minorista, no un mayorista. Estaría vendiendo esa cantidad de botellas durante más de medio año, ese vino es raro y caro, y no todos pueden permitírselo, ya sabes. No tengo tantos.";
		link.l1 = "Está bien, no los tienes, no hay problema. Pero lo consigues en algún lugar para ti, ¿verdad? Tal vez podrías decirme el nombre de tu proveedor, y yo lo compraría directamente de él. ¿O se te entrega el vino desde Europa?";
		link.l1.go = "Wine_Bottles_1";
		break;

	case "Wine_Bottles_1":
		dialog.text = "No, no lo es. Lo consigo aquí. Pero no te diré quién es mi proveedor así como así. Pero por mil pesos... quizás, lo haría...";
		if (makeint(Pchar.money) >= 1000)
		{
			link.l1 = "Bien. Aquí tienes tu mil y ahora dime, ¿quién es tu proveedor?";
			link.l1.go = "Wine_Bottles_2";
		}
		link.l2 = "¡Ahora vosotros, mercachifles, os habéis vuelto demasiado descarados! ¿No sería demasiado bueno para vosotros? Me las arreglaré bien sin vuestro proveedor, gracias.";
		link.l2.go = "Wine_Bottles_fail";
		break;

	case "Wine_Bottles_free":
		dialog.text = "Supongo... está bien entonces. Aquí está tu nota, y espero que devuelvas el favor en el futuro.";
		link.l1 = "...";
		link.l1.go = "Wine_Bottles_free_1";
		break;

	case "Wine_Bottles_free_1":
		pchar.questTemp.Wine.TraderID = pchar.questTemp.Wine.City + "_trader";
		sld = characterFromId(pchar.questTemp.Wine.TraderID);
		pchar.questTemp.Wine.Name = GetFullName(sld);
		pchar.questTemp.Wine.ItemTraderID = npchar.id;
		dialog.text = "El nombre de mi proveedor de vino es " + pchar.questTemp.Wine.Name + ", él es el dueño de la tienda.";
		link.l1 = "¡Entendido! ¡Gracias!";
		link.l1.go = "exit";
		// pchar.questTemp.Wine.Trader = "true";
		DeleteAttribute(pchar, "questTemp.Wine.bottles");
		pchar.questTemp.Wine.Repeat2 = "true";
		TakeNItems(pchar, "letter_1", 1);
		ChangeItemDescribe("letter_1", "itmdescr_letter_1");
		PlaySound("interface\important_item.wav");
		break;

	case "Wine_Bottles_2":
		AddMoneyToCharacter(pchar, -1000);
		pchar.questTemp.Wine.TraderID = pchar.questTemp.Wine.City + "_trader";
		sld = characterFromId(pchar.questTemp.Wine.TraderID);
		AddLandQuestMark(sld, "questmarkmain");
		pchar.questTemp.Wine.Name = GetFullName(sld);
		pchar.questTemp.Wine.ItemTraderID = npchar.id;
		dialog.text = "El nombre de mi proveedor de vino es " + pchar.questTemp.Wine.Name + ", él es dueño de la tienda.";
		link.l1 = "¡Entendido! ¡Gracias!";
		link.l1.go = "exit";
		pchar.questTemp.Wine.Trader = "true";
		DeleteAttribute(pchar, "questTemp.Wine.bottles");
		AddQuestRecord("Wine", "3");
		AddQuestUserData("Wine", "sName", pchar.questTemp.Wine.Name);
		WineTraderQMDel();
		break;

	case "Wine_Bottles_fail":
		dialog.text = "Como desee, capitán. Todo lo mejor para usted.";
		link.l1 = "Nos vemos.";
		link.l1.go = "exit";
		DeleteAttribute(pchar, "questTemp.Wine.bottles");
		AddQuestRecord("Wine", "4");
		WineTraderQMDel();
		break;

	case "Wine_Repeat1":
		DeleteAttribute(pchar, "questTemp.Wine.Repeat1");
		dialog.text = "¿Qué quieres decir con eso? Explícate.";
		link.l1 = "¡Me has engañado, granuja! Acabo de estar en la tienda, " + pchar.questTemp.Wine.Name + " nunca comercia con vino, ¡él mismo me lo dijo! ¡Devuélveme mi dinero!";
		link.l1.go = "Wine_Repeat1_fail";
		link.l2 = "Hubo un malentendido... Fui al almacenista, y " + pchar.questTemp.Wine.Name + " afirmó que nunca ha comerciado con vino. ¿Cómo puedes explicarlo?";
		link.l2.go = "Wine_Repeat1_1";
		break;

	case "Wine_Repeat1_1":
		dialog.text = "¡Je! Él comercia con vino, eso es seguro demonios. Simplemente no vende vino a cualquiera, igual que con algunos otros productos. Y hay varias razones para eso... Si quieres comprarle vino, puedo escribirle una nota. Él me conoce y conoce mi letra, así que, después de que la lea, te venderá ese vino. Claro, este favor tampoco es gratis.";
		link.l1 = "¡Eso es un escándalo! ¡Acabas de quitarme un grand!";
		link.l1.go = "Wine_Repeat1_2";
		break;

	case "Wine_Repeat1_2":
		dialog.text = "Te quité mil por información. Y por una carta tendrás que pagar dos mil pesos aparte, y de ninguna manera menos que eso.";
		if (makeint(Pchar.money) >= 2000)
		{
			link.l1 = "Oh... Ustedes los comerciantes son tan malditamente codiciosos. No es de extrañar que a nadie le guste su tipo. Bueno, aquí está tu dinero, así que adelante y escribe la nota.";
			link.l1.go = "Wine_Bottles_3";
		}
		if (CheckCharacterPerk(pchar, "Trustworthy"))
		{
			notification("Trustworthy", "Trustworthy");
			link.l2 = "(Confiable) Hagamos un trato. Proporcionas una recomendación ahora, sin costo alguno, y yo te devolveré el favor con una recomendación para ti más tarde, también sin costo. Este trato de vino es solo el comienzo.";
			link.l2.go = "Wine_Bottles_free";
		}
		link.l3 = "¡Eso es completamente inaceptable! Prefiero abandonar todo el asunto, no voy a enriquecer a tal avaro astuto. Y por ese avaro me refiero a ti. Adiós.";
		link.l3.go = "Wine_Repeat1_goaway";
		break;
	case "Wine_Bottles_free":
		dialog.text = "Supongo... está bien entonces. Aquí tienes tu nota, y espero que devuelvas el favor en el futuro.";
		link.l1 = "...";
		link.l1.go = "Wine_Bottles_free_1";
		break;

	case "Wine_Bottles_free_1":
		pchar.questTemp.Wine.Repeat2 = "true";
		TakeNItems(pchar, "letter_1", 1);
		ChangeItemDescribe("letter_1", "itmdescr_letter_1");
		PlaySound("interface\important_item.wav");
		AddQuestRecord("Wine", "6_1");
		DelLandQuestMark(npchar);
		sld = characterFromId(pchar.questTemp.Wine.TraderID);
		AddLandQuestMark(sld, "questmarkmain");
		DialogExit();
		break;

	case "Wine_Bottles_3":
		AddMoneyToCharacter(pchar, -2000);
		dialog.text = "¡Eres un pájaro raro, capitán! Claro, entiendo que tu contramaestre se encarga de todas las finanzas, pero también deberías usar tu propia cabeza a veces. Tendrás la oportunidad de comprar un lote decente de vinos al por mayor sin mi margen de precio y obtener un beneficio considerable. Así que no nos impidamos el uno al otro hacer monedas, porque ahora pareces tú el avaro.\nCorrecto...(escribiendo) Aquí, toma esta carta, " + pchar.questTemp.Wine.Name + "  te venderá el vino sin hacer preguntas.";
		link.l1 = "Espero que sí... Si algo sale mal de nuevo, volveré. ¡Hasta luego!";
		link.l1.go = "Wine_Bottles_4";
		break;

	case "Wine_Bottles_4":
		pchar.questTemp.Wine.Repeat2 = "true";
		TakeNItems(pchar, "letter_1", 1);
		ChangeItemDescribe("letter_1", "itmdescr_letter_1");
		PlaySound("interface\important_item.wav");
		AddQuestRecord("Wine", "6");
		DelLandQuestMark(npchar);
		sld = characterFromId(pchar.questTemp.Wine.TraderID);
		AddLandQuestMark(sld, "questmarkmain");
		DialogExit();
		break;

	case "Wine_Repeat1_goaway":
		dialog.text = "Como desees, capitán. Adiós.";
		link.l1 = "...";
		link.l1.go = "exit";
		AddQuestRecord("Wine", "4");
		DelLandQuestMark(npchar);
		break;

	case "Wine_Repeat1_fail":
		dialog.text = "¡Oh!, ¿así que has venido aquí para ser grosero y amenazarme? ¡Llamaré a los guardias! ¡Eh, guardias! ¡Aquí mismo!";
		link.l1 = "¡Oh, cállate! Ganaste, ¡me voy! Maldito seas " + NPCharSexPhrase(npchar, "", "") + ", ¡cormorán, que te arruines!";
		link.l1.go = "exit";
		AddQuestRecord("Wine", "7");
		DelLandQuestMark(npchar);
		break;
	// <-- мини-квест Дефицитный товар

	// Sinistra --> мини-квест "Знакомство с индейцами"
	case "ZsI_PokupaemPistolety":
		sld = CharacterFromID("Tichingitu");
		if (sld.location == pchar.location && !LAi_IsDead(sld))
		{
			dialog.text = "Ah, ya veo. ¿Haciendo tratos con los nativos? Escuché que este ya te ha costado un buen dinero, ¡ja ja!";
		}
		else
		{
			dialog.text = "¿Esperando problemas, Capitán? ¿O planeando una aventura en la selva? ¡Ja-ja!";
		}
		link.l1 = "Entonces, ¿podemos hacer un trato?";
		link.l1.go = "ZsI_PokupaemPistolety_1";
		DelLandQuestMark(npchar);
		break;

	case "ZsI_PokupaemPistolety_1":
		dialog.text = "¡Por supuesto! Los clientes siempre son bienvenidos. Por tres mil pesos, obtendrás pistolas confiables, balas y pólvora como se solicitó.";
		if (sti(pchar.Money) > 2999)
		{
			link.l1 = "Caro, pero está bien. Lo tomaré.";
			link.l1.go = "ZsI_PokupaemPistolety_2";
		}
		if (sti(pchar.Money) > 2299)
		{
			link.l2 = "El precio parece injusto. ¿Qué tal un descuento para un amigo de Fadey Muscovite?";
			link.l2.go = "ZsI_Torg";
		}
		link.l3 = "¿Tres mil? ¡Eso es robo! Adiós, señor!";
		link.l3.go = "ZsI_NetDeneg";
		break;

	case "ZsI_NetDeneg":
		DialogExit();

		LocatorReloadEnterDisable("BasTer_town", "gate_back", false);
		PChar.quest.ZsI_Timer.over = "yes";
		sld = CharacterFromID("ListKakao");
		sld.lifeday = 0;
		DeleteAttribute(pchar, "questTemp.ZsI_PokupaemPistolety");
		break;

	case "ZsI_PokupaemPistolety_2":
		dialog.text = "¡Ten un buen día allí afuera, Capitán!";
		link.l1 = "Adiós, Señor.";
		link.l1.go = "ZsI_PokupaemPistolety_3";
		AddMoneyToCharacter(pchar, -3000);
		Log_info("¡Has adquirido las pistolas necesarias para Cocoa Leaf!");
		PlaySound("Interface\important_item.wav");
		break;

	case "ZsI_PokupaemPistolety_3":
		DialogExit();

		LocatorReloadEnterDisable("BasTer_town", "gate_back", false);
		DeleteAttribute(pchar, "questTemp.ZsI_PokupaemPistolety");
		PChar.quest.ZsI_Patrul.win_condition.l1 = "location";
		PChar.quest.ZsI_Patrul.win_condition.l1.location = "BasTer_ExitTown";
		PChar.quest.ZsI_Patrul.win_condition = "ZsI_Patrul";
		break;

	case "ZsI_Torg":
		if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) > 18)
		{
			notification("Skill Check Passed", SKILL_COMMERCE);
			dialog.text = "Ciertamente, Capitán. Los amigos de Fadey siempre son bienvenidos aquí. ¿Dos mil trescientos por el lote?";
			link.l1 = "Eso suena mejor. Lo tomaré.";
			link.l1.go = "ZsI_Torg_2";
			AddCharacterExpToSkill(pchar, "Commerce", 30);
		}
		else
		{
			notification("Skill Check Failed (19)", SKILL_COMMERCE);
			dialog.text = "Los amigos del señor Fadey siempre son bienvenidos, pero los precios no tienen amigos. Serán tres mil pesos, Capitán.";
			if (sti(pchar.Money) > 2999)
			{
				link.l1 = "Caro, pero está bien. Lo tomaré.";
				link.l1.go = "ZsI_PokupaemPistolety_2";
			}
			link.l2 = "¿Tres mil? ¡Eso es robo! Adiós, Monsieur!";
			link.l2.go = "ZsI_NetDeneg";
			// Log_info("¡Tu habilidad de comercio no es suficiente!");
			AddCharacterExpToSkill(pchar, "Commerce", -30);
		}
		break;

	case "ZsI_Torg_2":
		dialog.text = "¡Que lo pases bien allá fuera, Capitán!";
		link.l1 = "Adiós, señor.";
		link.l1.go = "ZsI_PokupaemPistolety_3";
		AddMoneyToCharacter(pchar, -2300);
		Log_info("¡Has adquirido las pistolas necesarias para Cocoa Leaf!");
		PlaySound("Interface\important_item.wav");
		break;
	// <-- мини-квест "Знакомство с индейцами"

	// --> Цена чахотки
	case "Consumption":
		dialog.text = "No, no lo hace... Ahora, por favor no me molestes, estoy bastante ocupado... Qué pregunta tan idiota...";
		link.l1 = "Ya veo. Lo siento por hacerle perder su tiempo...";
		link.l1.go = "exit";
		npchar.quest.Consumption = "true";
		break;
	// <-- Цена чахотки
	// Jason --> генератор Неудачливый вор
	case "Device_ItemTrader":
		dialog.text = "Mmm, " + pchar.GenQuest.Device.Shipyarder.Type + "¿Nunca he oído hablar de eso antes... ¿Qué es realmente? Nunca he oído hablar de tal cosa en todo mi tiempo" + NPCharSexPhrase(npchar, "", "") + ".";
		link.l1 = "Bueno, es una herramienta de carpintero de barcos, " + pchar.GenQuest.Device.Shipyarder.Describe + ". ¿Alguien te ofreció algo así?";
		link.l1.go = "Device_ItemTrader_1";
		npchar.quest.Device = "true";
		break;

	case "Device_ItemTrader_1":
		if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) > 0 && sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 4 && npchar.location.group == "merchant" && npchar.location.locator == "merchant" + sti(pchar.GenQuest.Device.Shipyarder.Chance1))
		{
			dialog.text = "Hmm... Sí, había un tipo extraño. Pero no me dijo qué era eso, solo intentó vendérmelo. ¿Pero para qué lo necesitaría, si no tenía idea de para qué sirve? ¿Cómo lo revendería? Así que, simplemente lo rechacé" + NPCharSexPhrase(npchar, "", "") + ", y se fue";
			link.l1 = "¿Y cómo lucía y hacia dónde se fue? Necesito ese instrumento con urgencia.";
			link.l1.go = "Device_Common";
		}
		else
		{
			dialog.text = "No, nada de eso. Lo siento, no puedo ayudarte. Pregunta por ahí.";
			link.l1 = "Ya veo. Bueno, ¡es hora de preguntar por ahí!";
			link.l1.go = "exit";
		}
		break;
	// <-- генератор Неудачливый вор

	// Мангароса
	case "mangarosa":
		// тут работает везение
		if (sti(pchar.questTemp.Mangarosa.m_count) == 5 || GetSummonSkillFromName(pchar, SKILL_FORTUNE) > 10 + hrand(30) + hrand(40, "1"))
		{
			dialog.text = "Muéstramelo... Sí, esa es una planta interesante. Y una muy, muy rara. Se llama Manga Rosa. No sé para qué se utiliza, pero había un hecho interesante relacionado con ella...";
			link.l1 = "¿Qué quieres decir?";
			link.l1.go = "mangarosa_1";
		}
		else
		{
			dialog.text = LinkRandPhrase("Muéstramelo... Sí, es una planta interesante. Pero, desafortunadamente, no puedo decirte más que eso. Si se usa de hecho para algún propósito, me es desconocido.", "Veamos... Hmm... Parece una planta medicinal, pero no sé nada al respecto. Lo siento, no puedo ayudarte.", "¿Dónde está? Hmm... No, nunca he visto este antes. Seguro que parece muy interesante, pero no tengo ni idea de para qué se utiliza...");
			link.l1 = "Ya veo. Bueno, preguntaré un poco más. Lo siento.";
			link.l1.go = "mangarosa_exit";
		}
		break;

	case "mangarosa_exit":
		DialogExit();
		pchar.questTemp.Mangarosa.m_count = sti(pchar.questTemp.Mangarosa.m_count) + 1;
		npchar.quest.mangarosa = "true";
		break;

	case "mangarosa_1":
		dialog.text = "Los gitanos nómadas y salvajes muestran gran interés en estas plantas. Una vez vi a un gitano pagando un puñado de oro por solo un tallo como este. Pero no tengo idea de por qué lo necesitarían.";
		link.l1 = "Ya veo... ¡Bueno, es algo al menos! Ahora sé dónde preguntar más. ¡Muchas gracias!";
		link.l1.go = "mangarosa_2";
		break;

	case "mangarosa_2":
		DialogExit();
		npchar.quest.mangarosa = "true";
		DeleteAttribute(pchar, "questTemp.Mangarosa.m_count");
		pchar.questTemp.Mangarosa = "gipsy";
		AddQuestRecord("Mangarosa", "2");
		break;
		
		//--> Украденное воспоминание
		case "UV_Lavochniki_1":
    		dialog.text = "Lo siento, "+GetAddress_Form(NPChar)+", pero hace mucho que no tengo nada de verdadero valor. La demanda de ese tipo de artículos es baja, ¿sabe? La gente común solo puede permitirse baratijas baratas, y la nobleza rara vez viene aquí a comprar.";
    		link.l1 = "Está bien...";
    		link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.UV_Lavochniki");
			pchar.questTemp.UV_Lavochniki_2 = true;
			npchar.quest.UV_Vopros;
 		break;
		
		case "UV_Lavochniki_2":
    		dialog.text = "Lo lamento, capitán, pero ya no comercia con ese tipo de mercancía. Los clientes ricos rara vez me visitan, y los plebeyos compran solo lo más barato.";
    		link.l1 = "Entiendo...";
    		link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.UV_Lavochniki_2");
			pchar.questTemp.UV_Lavochniki_3 = true;
			npchar.quest.UV_Vopros;
 		break;
		
		case "UV_Lavochniki_3":
    		dialog.text = "Capitán, me temo que ha llegado un poco tarde... Hace apenas un par de horas vendí un espléndido collar a un capitán adinerado. A veces tengo piezas que pueden conquistar el corazón de cualquier dama, incluso la más testaruda\nVuelva mañana, quizás Giselle... es decir... mis proveedores... puedan encontrarle una joya que cautive el corazón de cualquier mujer para siempre.";
    		link.l1 = "No tengo tiempo. Necesito esa joya ahora mismo. Dime, ¿cómo se llamaba el capitán al que vendiste el collar?";
    		link.l1.go = "UV_Lavochniki_3_1";
 		break;
		
		case "UV_Lavochniki_3_1":
    		dialog.text = "Tristan Renier, capitán de la 'Golden Seagull'. Su barco sigue anclado en el puerto. Aunque, para ser sincero, dudo que quiera desprenderse del collar. Si se niega, vuelva mañana. Le juro, capitán, que no se arrepentirá.";
    		link.l1 = "...";
    		link.l1.go = "UV_Lavochniki_exit";
			DeleteAttribute(pchar, "questTemp.UV_Lavochniki_3");
			AddDialogExitQuestFunction("UV_GoldSeagull");
		break;
		
		case "UV_Lavochniki_exit":
			DialogExit();
			AddQuestRecord("UV", "3");
			/*AddQuestUserData("UV", "sSex", NPCharSexPhrase(NPChar,"ца","ки"));
			AddQuestUserData("UV", "sSex1", NPCharSexPhrase(NPChar,"ец","ка"));
			AddQuestUserData("UV", "sSex2", NPCharSexPhrase(NPChar,"","а"));*/
		break;
		//<-- Украденное воспоминание

		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>

		////////////////////////////////////////////////////////////////////////////////////////////////
	case "AngryExitAgain":
		DialogExit();
		DeleteAttribute(npchar, "angry.ok") break;

		// <<<<<<<<<<<<============= блок нод angry =============================
	}
}
