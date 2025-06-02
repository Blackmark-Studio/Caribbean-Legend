// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
	case "quests":
		dialog.text = "Habla, estoy escuchando.";
		link.l1 = "Me equivoqué. Adiós.";
		link.l1.go = "Exit";
		// --> Тичингиту
		if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "true")
		{
			link.l1 = "Hay un indio bajo arresto. Fue capturado por Fadey el Moscovita. ¿Puedo hablar con él?";
			link.l1.go = "Tichingitu";
		}
		if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "commandante")
		{
			link.l1 = "Dime, ¿de verdad vas a colgar a este indio? ¿No es un castigo demasiado severo para un delito tan pequeño?";
			link.l1.go = "Tichingitu_3";
		}
		if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "pay")
		{
			link.l1 = "Soy yo de nuevo, comandante. Fadey el Moscovita ha escrito esta petición para liberar al indio. Aquí está.";
			link.l1.go = "Tichingitu_6";
		}
		// <-- Тичингиту
		// Jason --> Бесчестный конкурент
		if (CheckAttribute(pchar, "questTemp.Shadowtrader.Fort") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_prison")
		{
			link.l1 = "He venido a usted por petición del dueño de la tienda, su nombre es " + pchar.questTemp.Shadowtrader.Tradername + ". Me pidió que te diera esta carta.";
			link.l1.go = "Shadowtrader_prison";
		}

		if (CheckAttribute(pchar, "questTemp.Shadowtrader.SeekTrader") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_prison")
		{
			link.l1 = "Soy yo de nuevo. Tengo pruebas contundentes de que " + pchar.questTemp.Shadowtrader.Tradername + " es correcto.";
			link.l1.go = "Shadowtrader_prison2";
		}
		// Jason <-- Бесчестный конкурент
		// Sinistra --> Путеводная звезда
		if (CheckAttribute(pchar, "questTemp.PZ_BasTerTurma"))
		{
			link.l1 = "Busco a un hombre llamado Longway. Escuché que tú también lo estás buscando, Monsieur Oficial. ¿Has tenido suerte encontrándolo, o tal vez alguna pista?";
			link.l1.go = "PZ_IshemLongway_1";
		}
		// Sinistra <-- Путеводная звезда
		break;

	// --> Тичингиту
	case "Tichingitu":
		DelLandQuestMark(npchar);
		QuestPointerDelLoc("BasTer_town", "reload", "reload_jail");
		dialog.text = "¿A-ah, Fadey te ha contado su historia? No tengo razones para prohibirte echarle un vistazo, monsieur. No eres el primero que viene a ver a ese piel roja. Bueno, en diez días cada ciudadano podrá echarle un vistazo cuando lo colguemos para que se seque al sol...";
		link.l1 = "¿Puedo entrar a la prisión?";
		link.l1.go = "Tichingitu_1";
		break;

	case "Tichingitu_1":
		dialog.text = "Como ya te he dicho, 'no tengo razones para prohibírtelo'. Sigue adelante.";
		link.l1 = "¡Gracias!";
		link.l1.go = "Tichingitu_2";
		break;

	case "Tichingitu_2":
		DialogExit();
		pchar.questTemp.Sharlie.Tichingitu = "wait";
		pchar.questTemp.jailCanMove = true;
		break;

	case "Tichingitu_3":
		DelLandQuestMark(npchar);
		dialog.text = "Eres nuevo aquí, ¿no es así, monsieur? ¿Recién llegado de Europa? No entiendes la situación en las colonias. Esta ejecución será una lección para esos malditos pieles rojas que se atrevan a usurpar la propiedad de los colonos franceses. Además, el propio Fadey insiste en ello y es un hombre muy respetado aquí y un amigo cercano de nuestro gobernador.";
		link.l1 = "¿Hay alguna manera de suavizar el castigo? Sigo pensando que es demasiado severo...";
		link.l1.go = "Tichingitu_4";
		break;

	case "Tichingitu_4":
		dialog.text = "¡Oh, no te pongas filosófico! Ve a ver a Fadey y pide por este indio si realmente te importa tanto su destino. Si Fadey escribe una petición de liberación, la satisfaremos.";
		link.l1 = "Entendido, oficial. Iré a Fadey.";
		link.l1.go = "Tichingitu_5";
		break;

	case "Tichingitu_5":
		DialogExit();
		pchar.questTemp.Sharlie.Tichingitu = "fadey";
		AddLandQuestMark(characterFromId("fadey"), "questmarkmain");
		QuestPointerToLoc("BasTer_town", "reload", "houseSp1");
		break;

	case "Tichingitu_6":
		DelLandQuestMark(npchar);
		QuestPointerDelLoc("BasTer_town", "reload", "reload_jail");
		RemoveItems(pchar, "letter_1", 1);
		dialog.text = "(leyendo) Hm... Este Fadey es extraño... Ha exigido una ejecución demostrativa y ahora está pidiendo liberar a este indio... En fin, supongo que todos los amigos del gobernador son como él. Bien, puedes ir y llevarte a este piel roja.";
		link.l1 = "¡Mis gracias, oficial!";
		link.l1.go = "Tichingitu_7";
		break;

	case "Tichingitu_7":
		DialogExit();
		AddQuestRecord("Tichingitu", "3");
		pchar.questTemp.Sharlie.Tichingitu = "wait";
		pchar.questTemp.jailCanMove = true;
		sld = characterFromId("Tichingitu");
		sld.dialog.currentnode = "Tichingitu_6";
		AddLandQuestMark(sld, "questmarkmain");
		break;
	// <-- Тичингиту

	// Jason --> мини-квест Бесчестный конкурент
	case "Shadowtrader_prison":
		dialog.text = "¡Otra vez con sus quejas señor " + pchar.questTemp.Shadowtrader.Tradername + "! Está bien, veamos de que se trata esta vez... (lee detenidamente)";
		link.l1 = "...";
		link.l1.go = "Shadowtrader_prison_1";
		RemoveItems(PChar, "letter_1", 1);
		DeleteAttribute(pchar, "questTemp.Shadowtrader.Fort");
		DelLandQuestMark(npchar);
		break;

	case "Shadowtrader_prison_1":
		dialog.text = "¡Una vez más, conjeturas absurdas y ni una sola prueba contundente! Está bien. Dile que esto simplemente no es suficiente para que yo alerte a los guardias y les ordene que peinen la ciudad.";
		link.l1 = "¿Quieres que le diga eso?";
		link.l1.go = "Shadowtrader_prison_2";
		break;

	case "Shadowtrader_prison_2":
		dialog.text = "Exactamente, y preferiblemente, palabra por palabra. Él entenderá lo que quiero decir. No malgastaré papel para escribir una respuesta a ese pesado.";
		link.l1 = "Ya veo. Adiós, entonces.";
		link.l1.go = "exit";
		pchar.questTemp.Shadowtrader.Trouble = "true";
		NextDiag.TempNode = "First_officer";
		AddLandQuestMark(characterFromId("BasTer_trader"), "questmarkmain");
		break;

	case "Shadowtrader_prison2":
		dialog.text = "¿Y cuál es esa 'sustancial' evidencia que afirmas haber reunido?";
		link.l1 = "He llegado a un acuerdo con los contrabandistas para comprar mercancías a través de su tienda no oficial. Su agente vendrá hoy por la noche a la oficina de la autoridad portuaria para llevarme a su llamada 'tienda'.";
		link.l1.go = "Shadowtrader_prison2_1";
		DeleteAttribute(pchar, "questTemp.Shadowtrader.SeekTrader");
		pchar.quest.ShadowtraderTimeSmugglers_Over.over = "yes";
		pchar.quest.Shadowtrader_SMG.over = "yes"; // снять оба прерывания
		sld = characterFromID("ShadowAgent_1");
		sld.lifeday = 0;
		DelLandQuestMark(npchar);
		break;

	case "Shadowtrader_prison2_1":
		dialog.text = "Hum... Bueno, ¡excelente trabajo, capitán! Entonces actuaremos más. Enviaremos a nuestro hombre a su reunión, localizaremos su escondite y los arrestaremos a todos. ¡Gracias por tu iniciativa!";
		link.l1 = "Siempre me alegra ayudar. Estoy seguro de que tu operación será exitosa.";
		link.l1.go = "exit";
		pchar.questTemp.Shadowtrader.End.Fort = "true";
		AddQuestRecord("Shadowtrader", "7");
		AddQuestUserData("Shadowtrader", "sSex", GetSexPhrase("", "а"));
		SetTimerFunction("ShadowTrader_questmark", 0, 0, 1);
		AddCharacterExpToSkill(pchar, "Leadership", 50); // авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 100);	 // везение
		AddCharacterExpToSkill(pchar, "Sneak", 100);	 // скрытность
		NextDiag.TempNode = "First_officer";
		break;
	// <-- мини-квест Бесчестный конкурент

	// Sinistra - Квест "Путеводная звезда" ==>
	case "PZ_IshemLongway_1":
		DelLandQuestMark(npchar);
		dialog.text = "¿Quién? ¿Largo... Camino? No recuerdo a ningún inglés en nuestra ciudad recientemente.";
		link.l1 = "No, Longway es... chino.";
		link.l1.go = "PZ_IshemLongway_2";
		DeleteAttribute(pchar, "questTemp.PZ_BasTerTurma");
		DeleteQuestCondition("PZ_BasTerPeshera");
		break;

	case "PZ_IshemLongway_2":
		dialog.text = "Bueno, bueno. ¿Y por qué buscas a ese Longway tuyo, monsieur?";
		link.l1 = "Es un amigo mío. Ya he oído lo que pasó, es un triste malentendido, te lo aseguro.";
		link.l1.go = "PZ_IshemLongway_Zashita_1";
		if (pchar.location.from_sea != "BasTer_Town")
		{
			link.l2 = "Lo busco porque es un criminal conocido en el Archipiélago.";
			link.l2.go = "PZ_IshemLongway_OhotnikOtryad_1";
		}
		break;

	case "PZ_IshemLongway_Zashita_1":
		dialog.text = "Ah, un malentendido. No estábamos tratando de enderezarlo en el acto, si acaso. Solo queríamos hablar con él... para empezar. Sin embargo, este agresivo hombre amarillo tuyo no solo abatió a varios guardias de la ciudad, sino que también masacró a las unidades enviadas para perseguirlo en la jungla.";
		link.l1 = "¿Planeas enviar otra unidad? Podría ir con tus hombres, hablar con él, calmarlo y evitar otro desastre. ¿Bastaría con que cesaran los asesinatos y Longway abandonara la ciudad para siempre?";
		link.l1.go = "PZ_IshemLongway_Zashita_2";
		break;

	case "PZ_IshemLongway_Zashita_2":
		dialog.text = "Bajo circunstancias normales, podría estar de acuerdo contigo. Pero, ves, uno de los muertos era un oficial, un joven teniente prometedor, el favorito de Su Gracia. La ciudad está de luto. No se puede hacer la vista gorda o compensarlo. ¿Entiendes?";
		link.l1 = "Entiendo perfectamente. Me disculpo por las acciones de mi amigo. No le molestaré más.";
		link.l1.go = "PZ_IshemLongway_Uiti_1";
		link.l2 = "Sabes, solo Dios sabe lo que está pasando en la jungla. Cualquiera podría haber matado a esos hombres.";
		link.l2.go = "PZ_IshemLongway_Blef_1";
		break;

	case "PZ_IshemLongway_Blef_1":
		dialog.text = "¿Y quién crees que podría haber derribado a todo un escuadrón de patrulleros liderado por un oficial?";
		if (IsCharacterPerkOn(pchar, "Trustworthy"))
		{
			notification("Trustworthy", "Trustworthy");
			link.l1 = "(Confiables) Bandidos, ¿quién más? Me da vergüenza admitirlo, pero apenas escapé de una gran banda recientemente.";
			link.l1.go = "PZ_IshemLongway_Blef_2";
		}
		else
		{
			notification("Perk check failed", "Trustworthy");
			link.l1 = "¿Pero cómo lo sabría yo? Podría haber sido cualquiera: bandidos, piratas, espías...";
			link.l1.go = "PZ_IshemLongway_Blef_netVD_1";
		}
		break;

	case "PZ_IshemLongway_Blef_2":
		dialog.text = "Heh, no es sorprendente, considerando el tamaño de tu cuerpo, Capitán. Sí, tenemos a esos canallas en la isla estos días...";
		link.l1 = "¡Exactamente! Entonces, podrían haber masacrado a la patrulla y al pobre teniente junior.";
		link.l1.go = "PZ_IshemLongway_Blef_3";
		break;

	case "PZ_IshemLongway_Blef_3":
		dialog.text = "Desafortunadamente, eso es totalmente posible.";
		link.l1 = "Precisamente. Así que una vez más, te pido que me dejes unirme a la próxima partida de búsqueda, Longway me escuchará, y de esa manera podemos evitar más muertes.";
		link.l1.go = "PZ_IshemLongway_Blef_4";
		break;

	case "PZ_IshemLongway_Blef_4":
		dialog.text = "Está bien. Pero todavía hay un 'pero', señor.";
		link.l1 = "¿Y qué es eso?";
		link.l1.go = "PZ_IshemLongway_Blef_5";
		break;

	case "PZ_IshemLongway_Blef_5":
		dialog.text = "A diferencia de lo que ocurrió en la jungla, la culpabilidad de tu amigo en la ciudad es clara y totalmente comprobada. No quedará sin castigo. Así que, estas muertes deben ser compensadas si quieres que salga de la ciudad con vida.";
		link.l1 = "Justo. ¿Cuánto costará, Monsieur Officer?";
		link.l1.go = "PZ_IshemLongway_Blef_6";
		break;

	case "PZ_IshemLongway_Blef_6":
		dialog.text = "Trescientos doblones. Ese dinero irá a la ciudad, no a los charlatanes de la plaza del mercado.";
		if (PCharDublonsTotal() >= 300)
		{
			link.l1 = "Por supuesto. Trescientos doblones, aquí tienes.";
			link.l1.go = "PZ_IshemLongway_Blef_7";
		}
		link.l2 = "No traje mis doblones a la ciudad esta vez. Pero si me permites ir a buscarlos...";
		link.l2.go = "PZ_IshemLongway_NetDublonov_1";
		break;

	case "PZ_IshemLongway_Blef_7":
		dialog.text = "Excelente. Has demostrado tu responsabilidad. Estamos finalizando el informe para el próximo escuadrón. Te autorizo a unirte a él.";
		link.l1 = "Gracias. Adiós, Monsieur Oficial.";
		link.l1.go = "PZ_IshemLongway_BeryomOtryad";
		RemoveDublonsFromPCharTotal(300);
		pchar.questTemp.PZ_DrugOtryad = true;
		break;

	case "PZ_IshemLongway_NetDublonov_1":
		dialog.text = "No nací ayer. Sé que planeas escapar, no por doblones, sino por tu querido chino.";
		link.l1 = "Te doy mi palabra de que no me iré de la ciudad con Longway.";
		link.l1.go = "PZ_IshemLongway_NetDublonov_2";
		break;

	case "PZ_IshemLongway_NetDublonov_2":
		dialog.text = "Palabras, palabras... Estoy harto de tus charlas, Capitán. No irás a ningún lado hasta que capturemos a ese maldito hombre de piel amarilla nosotros mismos.";
		link.l1 = "Obedeceré su orden si promete no matar a Longway en el acto, señor oficial.";
		link.l1.go = "PZ_IshemLongway_Arest_1";
		link.l2 = "¿Pero violé personalmente las leyes de la ciudad hoy?";
		link.l2.go = "PZ_IshemLongway_Pobeg_1";
		break;

	case "PZ_IshemLongway_Blef_netVD_1":
		dialog.text = "Entonces no sabes. Me quedaré con mi corazonada actual: hay que atrapar al chino, cueste lo que cueste.";
		link.l1 = "¿Tu corazonada actual? Pero no tienes pruebas de que Longway mató a todos en la jungla.";
		link.l1.go = "PZ_IshemLongway_Blef_netVD_2";
		break;

	case "PZ_IshemLongway_Blef_netVD_2":
		dialog.text = "¿Y tienes pruebas de su inocencia? ¿No? Entonces deja de hacer un santo de tu hombre de piel amarilla. ¿Me entiendes?";
		link.l1 = "Entiendo perfectamente. Me disculpo por las acciones de mi amigo. No le molestaré más.";
		link.l1.go = "PZ_IshemLongway_Uiti_1";
		break;

	case "PZ_IshemLongway_Uiti_1":
		dialog.text = "Me temo que no puedo dejarle irse todavía, Capitán.";
		link.l1 = "¿Qué quieres decir?";
		link.l1.go = "PZ_IshemLongway_Uiti_2";
		break;

	case "PZ_IshemLongway_Uiti_2":
		dialog.text = "Lo que quiero decir es que, dado que este Longway es tu amigo, no hay garantía de que no corras tras él e intentes escapar con él. Así que tendré que retenerte hasta que capturemos a ese carnicero de piel amarilla nosotros mismos.";
		link.l1 = "Obedeceré su orden si promete no matar a Longway en el acto, señor oficial.";
		link.l1.go = "PZ_IshemLongway_Arest_1";
		link.l2 = "¿Pero violé personalmente las leyes de la ciudad hoy?";
		link.l2.go = "PZ_IshemLongway_Pobeg_1";
		break;

	case "PZ_IshemLongway_Arest_1":
		dialog.text = "No puedo prometer nada. Quién sabe qué tiene en mente tu amigo, o si comenzará otra masacre cuando nos vea. Mientras tanto, por favor disfruta de tu lujosa estancia, Capitán.";
		link.l1 = "Desternillante...";
		link.l1.go = "PZ_IshemLongway_Arest_2";
		break;

	case "PZ_IshemLongway_Arest_2":
		DialogExit();
		RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
		RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
		RemoveCharacterEquip(PChar, MUSKET_ITEM_TYPE);
		RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
		bDisableCharacterMenu = true;
		InterfaceStates.Buttons.Save.enable = false;
		bDisableFastReload = true;
		chrDisableReloadToLocation = true;
		DoQuestReloadToLocation("BasTer_prison", "goto", "goto9", "PZ_SharliePlennik_BadFinal");
		break;

	case "PZ_IshemLongway_Pobeg_1":
		dialog.text = "Entiende, no tengo nada en contra de ti personalmente. Y tienes razón, no has cometido ningún crimen. Pero necesitamos asegurarnos de que tu amigo de piel amarilla no escape de la justicia.";
		link.l1 = "Entiende entonces que no permitiré que me detengan de manera tan burda.";
		link.l1.go = "PZ_IshemLongway_Pobeg_2";
		break;

	case "PZ_IshemLongway_Pobeg_2":
		if (pchar.location.from_sea == "BasTer_Town")
		{
			dialog.text = "En ese caso, tendremos que silenciarte, señor.";
		}
		else
		{
			dialog.text = "¡Ya he tenido suficiente de esto! Sargento, lleva al escuadrón a esa maldita cueva y encuentra al chino. Me encargaré personalmente de este...";
		}
		link.l1 = "¡Al diablo con eso!";
		link.l1.go = "PZ_IshemLongway_Pobeg_3";
		break;

	case "PZ_IshemLongway_Pobeg_3":
		DialogExit();

		LAi_SetHuberType(NPChar);
		LAi_group_Attack(NPChar, Pchar);
		LAi_group_MoveCharacter(NPChar, "FRANCE_CITIZENS");
		LAi_group_Attack(characterFromId("BasTer_Mayor"), Pchar);
		ChangeCharacterNationReputation(pchar, FRANCE, -50);
		if (pchar.location.from_sea == "BasTer_Town")
		{
			PChar.quest.PZ_KorablPort_BadFinal.win_condition.l1 = "MapEnter";
			PChar.quest.PZ_KorablPort_BadFinal.win_condition = "PZ_KorablPort_BadFinal";
			AddQuestRecord("PZ", "10");
			LocatorReloadEnterDisable("BasTer_town", "gate_back", true);
			Island_SetReloadEnableGlobal("Guadeloupe", false);
		}
		else
		{
			PChar.quest.PZ_KorablBuhta_BadFinal.win_condition.l1 = "EnterToSea";
			PChar.quest.PZ_KorablBuhta_BadFinal.win_condition = "PZ_KorablBuhta_BadFinal";
			AddQuestRecord("PZ", "5");

			// Микро-диалог с Лонгвэем у пещеры, если мы побежали к пещере ему помочь после ссоры с комендантом
			PChar.quest.PZ_IshemLongway_SorraKomendant.win_condition.l1 = "location";
			PChar.quest.PZ_IshemLongway_SorraKomendant.win_condition.l1.location = "Guadeloupe_CaveEntrance";
			PChar.quest.PZ_IshemLongway_SorraKomendant.win_condition = "PZ_IshemLongway_SorraKomendant";

			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", true);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", true);
			// LAi_LocationDisableOfficersGen("Guadeloupe_Cave", true);
		}
		break;

	case "PZ_IshemLongway_OhotnikOtryad_1":
		dialog.text = "¿Un cazarrecompensas, eh? Normalmente, no me gusta tratar con los de tu calaña, pero en este caso, es de mi interés que nuestros intereses coincidan. Al parecer, este de piel amarilla es un asesino infame. Ha matado a muchos de mis hombres, tanto en la ciudad como en la jungla.";
		link.l1 = "Llevo persiguiéndolo por el Archipiélago desde hace ya un buen tiempo.";
		link.l1.go = "PZ_IshemLongway_OhotnikOtryad_2";
		break;

	case "PZ_IshemLongway_OhotnikOtryad_2":
		dialog.text = "¡Maldito bribón! Aquí está lo que haremos: reuniré otro escuadrón, y tú irás con ellos. Esta vez, no tiene a dónde correr, y con tu ayuda, tendremos una mejor oportunidad de éxito. No esperes una recompensa de mí, sin embargo, eres un cazador de recompensas, así que tu pago vendrá de quien te haya contratado. Deberías estar agradecido de que te deje cooperar conmigo en absoluto.";
		link.l1 = "Eso es bastante cierto. Hasta luego, oficial. Si alguno de tus hombres sobrevive a otro encuentro con nuestro amigo chino, te haré saber cómo fue.";
		link.l1.go = "PZ_IshemLongway_BeryomOtryad";
		pchar.questTemp.PZ_OhotnikOtryad = true;
		break;

	case "PZ_IshemLongway_BeryomOtryad":
		DialogExit();

		LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", true);
		LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", true);
		// LAi_LocationDisableOfficersGen("Guadeloupe_Cave", true);
		DoQuestReloadToLocation("Guadeloupe_jungle_02", "goto", "goto1", "PZ_IshemLongway_Otryad");
		break;

	case "PZ_BasTer_ComendantDialog_1":
		dialog.text = "Tienes razón. Ustedes dos se conocen, ¿no es así? ¿Quiénes son el uno para el otro?";
		link.l1 = "Es un oficial de navegación en mi barco, y...";
		link.l1.go = "PZ_BasTer_ComendantDialog_2";
		if (pchar.location.from_sea != "BasTer_Town")
		{
			link.l2 = "Lo busco porque es un criminal conocido en el Archipiélago.";
			link.l2.go = "PZ_IshemLongway_OhotnikOtryad_1";
		}
		break;

	case "PZ_BasTer_ComendantDialog_2":
		dialog.text = "Es mejor con las armas que con los mapas. ¿Tienes alguna idea de lo que ha hecho tu chinito?";
		link.l1 = "Para ser honesto, no, porque acabo de atracar y empecé a buscar. Estoy seguro de que todo fue un malentendido.";
		link.l1.go = "PZ_IshemLongway_Zashita_1";
		break;

	case "PZ_BasTer_ComendantDialog_Opozdal_1":
		dialog.text = "Exactamente. ¿Quién eres tú para él si lo quieres tanto? No importa, lo que importa es el propósito de tu visita a la ciudad.";
		link.l1 = "Nada ilegal, señor. Pero, ¿qué quiso decir con “ya no importa”? ¿Acaso él...?";
		link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_2";
		break;

	case "PZ_BasTer_ComendantDialog_Opozdal_2":
		dialog.text = "Sí. Fue enterrado detrás de una de las colinas, a cierta distancia del cementerio. Los santos padres no permitieron un entierro cristiano adecuado para un pagano.";
		link.l1 = "¿Cómo sucedió, si no es un secreto?";
		link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_3";
		break;

	case "PZ_BasTer_ComendantDialog_Opozdal_3":
		dialog.text = "Muy simple: llegó a la ciudad, husmeando sin parar. Intentamos hablar con él, para averiguar qué hacía aquí, pero mató a algunos hombres y huyó a la jungla. Envié varios grupos de búsqueda tras él, uno tras otro, ¡pero los eliminó a todos! ¡Tuvimos que atraparlo en una cueva, y los tiradores hicieron el resto!";
		link.l1 = "¿Y no sabes qué estaba buscando? Verás, nunca antes había hecho algo así: solía ser un navegante en mi barco. Pero luego me robó y se escapó.";
		link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_4";
		break;

	case "PZ_BasTer_ComendantDialog_Opozdal_4":
		dialog.text = "Simplemente se me olvidó, aye. ¿Así que tú también sufriste por sus acciones? Eso te dará una lección, Capitán. Sabrás mejor que contratar a alguien en quien no puedes confiar. Nunca confíes en un hombre de piel amarilla, ¡recuerda mis palabras!";
		link.l1 = "Sí, lo tendré en cuenta. ¿Encontraste algo en él?";
		link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_5";
		break;

	case "PZ_BasTer_ComendantDialog_Opozdal_5":
		dialog.text = "Oh, ¿quieres recuperar los bienes robados? Tenía algo de plata en los bolsillos, así que si te robó, ya lo ha gastado todo. Y había algunos otros papeles... ¿de tu libro de bitácora? No lo entendimos de todos modos, ¿algún tipo de código, tal vez? Todo estaba cubierto de sangre, así que no pudimos distinguir las partes no dañadas.";
		link.l1 = "Eh, sí. Gracias. Siempre me he preocupado por lo que sucedería si mis diarios y anotaciones fueran recogidos por alguien más...";
		link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_6";
		break;

	case "PZ_BasTer_ComendantDialog_Opozdal_6":
		dialog.text = "¿Y tener que idear un cifrado complejo por eso? ¿No te dio pena tu tiempo y esfuerzo? Aquí tienes. Y sobre la plata, no te enojes, pero la devolvimos a la ciudad. Ese chino mandó a muchos de mis hombres al infierno aquel día.";
		link.l1 = "Entonces no me atrevo a insistir. Adiós.";
		link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_7";
		break;

	case "PZ_BasTer_ComendantDialog_Opozdal_7":
		DialogExit();

		LAi_SetHuberType(npchar);
		AddQuestRecord("PZ", "9");
		CloseQuestHeader("PZ");
		bDisableLandEncounters = false;
		break;
		// <== Квест "Путеводная звезда" - Sinistra
	}
	UnloadSegment(NPChar.FileDialog2); // если где-то выход внутри switch  по return не забыть сделать анлод
}
