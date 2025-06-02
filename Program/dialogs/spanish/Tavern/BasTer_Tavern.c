// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué preguntas tienes?","¿Cómo puedo ayudarte, "+GetAddress_Form(NPChar)+"?"),"¿Qué es, "+GetAddress_Form(NPChar)+"...","Esta es la tercera vez que me molestas ahora...","Más preguntas, supongo?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Cambié de opinión...","No tengo nada de qué hablar en este momento."),"Umph, ¿dónde se ha ido mi memoria...?","Sí, realmente es la tercera vez...","No, ¿qué preguntas?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Jason, суп из черепахи
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "baster" && !CheckAttribute(npchar, "quest.terrapin"))
			{
				link.l1 = "Estoy buscando a mi viejo camarada Fernand Luc. Tengo un par de preguntas para él. Escuché que se lo pasó muy bien aquí hace una semana...";
				link.l1.go = "terrapin";
			}
			//Sinistra Путеводная звезда
			if (CheckAttribute(pchar, "questTemp.PZ_BasTerTavern"))
			{
				link.l1 = "Mi amigo y yo acordamos encontrarnos aquí, pero no lo veo por ninguna parte. ¿Sabes a dónde fue? ¿Sigue en el pueblo, o al menos en la isla? Su nombre es Longway, es chino.";
				link.l1.go = "PZ_BasTerTavern_1";
			}
			//--> Торговля по закону
			if (CheckAttribute(pchar, "questTemp.TPZ_Tavern_2"))
			{
				link.l1 = "Buenas noticias, "+npchar.name+". Tengo justo lo que puede salvar la situación. Cien botellas de excelente vino y cien botellas de ron. Con este cargamento, sus clientes volverán a beber a raudales. ¿Está dispuesto a aflojar la bolsa?";
				link.l1.go = "TPZ_Tavern2_1";
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Tavern_3"))
			{
				link.l1 = "Bueno, "+npchar.name+", ¿está listo para discutir los términos del trato?";
				link.l1.go = "TPZ_Tavern2_11";
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Tavern_4"))
			{
				link.l1 = "Entonces, "+npchar.name+". Por mi parte todo está arreglado y la mercancía ya está en camino a la taberna. ¿Pasamos al pago?";
				link.l1.go = "TPZ_Tavern3_1";
			}
			//<-- Торговля по закону
		break;
		
		//суп из черепахи
		case "terrapin":
			dialog.text = "Puede que todavía se lo esté pasando bien mientras está en el infierno. Tu compañero está muerto, así que llegas un poco tarde, capitán. Ese hombre allá sentado en la mesa más lejana pagó por su funeral, aunque tengo la sensación de que es el mismo hombre que lo causó. Tiene cara de horca, como dicen. Se llama Robert Martene. Si quieres, puedes acercarte y preguntárselo tú mismo. ";
			link.l1 = "Gracias, camarada. Iré a hablar con monsieur Robert. Beberemos por el alma del pobre viejo Luc, para que su alma descanse en paz...";
			link.l1.go = "terrapin_1";
			npchar.quest.terrapin = "true";
		break;
		
		case "terrapin_1":
			DialogExit();
			AddQuestRecord("Terrapin", "4");
			pchar.questTemp.Terrapin = "rober";
		break;
		
		// Sinistra - Квест "Длинные тени старых грехов" ==>
		case "DTSG_BasTerTavern_1":
			dialog.text = "¿Qué hay que discutir? Él te atacó a ti y a tu amigo, tú te defendiste, veo esto casi todos los días. Buen trabajo. Ahora solo tengo que limpiar el desastre...";
			Link.l1 = "Lo limpiarás, estoy seguro de que ya estás acostumbrado. ¿Qué sabes de él?";
			Link.l1.go = "DTSG_BasTerTavern_2";
		break;
		
		case "DTSG_BasTerTavern_2":
			dialog.text = "No mucho, en realidad. Apareció hace un par de días. Le gustó estar aquí, incluso alquiló una casa a las afueras del pueblo. Venía a menudo, pagaba con regularidad. Y, lo más importante, se comportó bien todo este tiempo, nunca dijo una mala palabra a nadie. Todavía estoy sorprendido de que te haya atacado a ti y a tu amigo. Pensé que podría establecerse aquí para siempre.";
			Link.l1 = "En cierto modo, lo hizo. Bueno, no es mucho, pero gracias por eso, mi amigo. Nos vemos.";
			Link.l1.go = "DTSG_BasTerTavern_3";
		break;
		
		case "DTSG_BasTerTavern_3":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DTSG_BasTerTavern");
			LAi_LocationDisableOfficersGen("BasTer_tavern", false);
			SetQuestHeader("DTSG");
			AddQuestRecord("DTSG", "1");
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			sld = CharacterFromID("Knippel");
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			sld.Dialog.CurrentNode = "Knippel_officer";
			sld.location = "None";
			
			PChar.quest.DTSG_BasTerDom.win_condition.l1 = "locator";
			PChar.quest.DTSG_BasTerDom.win_condition.l1.location = "BasTer_town";
			PChar.quest.DTSG_BasTerDom.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_BasTerDom.win_condition.l1.locator = "HutFish1";
			PChar.quest.DTSG_BasTerDom.win_condition = "DTSG_BasTerDom";
			
			SetTimerCondition("DTSG_BasTerDom_Timer", 0, 0, 7, false);
			SetTimerCondition("DTSG_Etap2", 0, 0, 14, false);
		break;
		// <== Квест "Длинные тени старых грехов" - Sinistra
		
		// Sinistra - Квест "Путеводная звезда" ==>
		
		case "PZ_BasTerTavern_1":
			dialog.text = "Ese nombre no significa nada para mí, y generalmente, no dejo entrar a mi establecimiento a personas como él, ni me interesan.";
			Link.l1 = "Está bien. De acuerdo, nos vemos más tarde.";
			Link.l1.go = "PZ_BasTerTavern_2";
		break;
		
		case "PZ_BasTerTavern_2":
			DialogExit();
			bDisableLandEncounters = true;
			DeleteAttribute(pchar, "questTemp.PZ_BasTerTavern");
			DeleteAttribute(pchar, "questTemp.PZ_BasTerAlkash");
			pchar.questTemp.PZ_BasTerTavern2 = true;
			DeleteQuestCondition("PZ_BasTer_Opozdal");
			DelMapQuestMarkIsland("Guadeloupe");
			
			PChar.quest.PZ_BasTer_Strazha.win_condition.l1 = "location";
			PChar.quest.PZ_BasTer_Strazha.win_condition.l1.location = "BasTer_town";
			PChar.quest.PZ_BasTer_Strazha.win_condition = "PZ_BasTer_Strazha";
		break;
		
		// <== Квест "Путеводная звезда" - Sinistra

		//--> Торговля по закону
		case "TPZ_Tavern_1":
			dialog.text = "Oh, "+GetAddress_Form(NPChar)+", la situación es aún peor. Mi proveedor en Antigua perdió su destilería: los piratas atacaron y todo se quemó hasta los cimientos. Ahora dice que no habrá ron ni vino en al menos dos meses.";
			link.l1 = "Entonces busque un nuevo proveedor. ¿No va a quedarse de brazos cruzados durante dos meses?";
			link.l1.go = "TPZ_Tavern_2";
		break;

		case "TPZ_Tavern_2":
			dialog.text = "Encontrar un buen proveedor no es tarea fácil. He intentado tratar con pequeños comerciantes, pero son poco fiables. A veces llega la mercancía, a veces no. Con un proveedor grande, todo funciona como un reloj: entregas estables y calidad superior.";
			link.l1 = "Bueno, si hay tantos problemas con los proveedores habituales, tal vez debería buscar entre aquellos que operan en la sombra. Normalmente no fallan, y siempre tienen mercancía disponible.";
			link.l1.go = "TPZ_Tavern_3";
		break;

		case "TPZ_Tavern_3":
			dialog.text = "Usted comprende, "+GetAddress_Form(NPChar)+", la taberna está a la vista de todos. No quiero problemas con las autoridades. Si alguien con buena reputación trajera la mercancía, no solo compraría el lote, sino que también cerraría los ojos al origen de la mercancía.\nDespués de todo, cuando el problema es tan grave, ¿quién prestará atención a tales detalles? Lo principal es que no haya sospechas desde fuera. Pero a largo plazo, solo trabajaré con comerciantes serios y honestos.";
			link.l1 = "Entiendo. Bueno, tal vez vuelva a visitarlo. Todos los problemas son solucionables si se abordan con inteligencia.";
			link.l1.go = "TPZ_Tavern_4";
		break;

		case "TPZ_Tavern_4":
			DialogExit();
			AddQuestRecord("TPZ", "2");
			pchar.questTemp.TPZ_ContraInfo = true;
			AddLandQuestMark(characterFromId("BasTer_Smuggler"), "questmarkmain");
		break;
		
		case "TPZ_Tavern2_1":
			dialog.text = "¡Capitán, esto es simplemente increíble! ¿Cómo lo logró? Aunque no importa. Dígame mejor, ¿qué desea a cambio de un cargamento tan magnífico de alcohol? ¿Y todo estará en regla con los documentos?";
			if (sti(pchar.reputation.nobility) >= 40)
			{
				link.l1 = "¿Con los documentos? Por supuesto, todo está en perfecto orden. No pensará revisarlos, ¿verdad?";
				link.l1.go = "TPZ_Tavern2_2";
				notification("Prueba de honor superada", "None");
			}
			else
			{
				link.l1 = "¿Con los documentos?";
				link.l1.go = "TPZ_Tavern2_2_badrep";
				notification("¡Nivel de honor demasiado bajo! ("+XI_ConvertString(GetReputationName(40))+")", "None");
			}
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_2");
			DelLandQuestMark(npchar);
		break;

		case "TPZ_Tavern2_2_badrep":
			dialog.text = "Capitán, comprenda, es vital para mí obtener este lote de licor. Pero la libertad y la reputación son igualmente valiosas para mí. El gobernador es implacable con los comerciantes en la sombra, incluso con los más pequeños. Si tuviera una buena reputación, podría pasar por alto la falta de documentos, pero ahora... Usted atrae demasiada atención no deseada...";
			link.l1 = "Parece que es hora de hacer buenas obras. Espéreme, regresaré pronto.";
			link.l1.go = "exit";
			pchar.questTemp.TPZ_Tavern_3 = true;
		break;

		case "TPZ_Tavern2_2":
			dialog.text = "Esta vez, supongo que le creeré. Entonces, ¿cuánto quiere por este lote?";
			link.l1 = "Por cada diez botellas de vino quiero treinta doblones, por el ron - cinco doblones. Todo el lote de cien botellas de ron y la misma cantidad de vino le costará trescientos cincuenta doblones.";
			link.l1.go = "TPZ_Tavern2_3";
		break;

		case "TPZ_Tavern2_3":
			dialog.text = "¡Permítame, capitán! ¡Eso es un robo en toda regla! Sí, mi situación es realmente desesperada, pero aún así no trabajaré con pérdidas.";
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 50)
			{
				link.l1 = "Quizás pueda ofrecerle un descuento. Pero eso no es todo. Quiero convertirme en su proveedor permanente. Le garantizo que no habrá problemas con las entregas. Alquilaré un almacén en Bass-Terre, y usted recibirá la mercancía directamente desde allí, sin demoras. Siempre habrá suficiente licor para anticiparse a cualquier tipo de interrupciones. En cuanto a la suma, con el descuento será de doscientos cuarenta doblones. ¿Qué dice?";
				link.l1.go = "TPZ_Tavern2_4";
				notification("Prueba superada", SKILL_COMMERCE);
			}
			else
			{
				link.l1 = "Bueno, estoy dispuest"+GetSexPhrase("o","a")+" a reducir el precio a doscientos cuarenta doblones por lote, ya que estoy interesado en una cooperación a largo plazo. En el futuro, podré satisfacer completamente todas sus necesidades y asegurar entregas sin interrupciones. ¿Qué dice?";
				link.l1.go = "TPZ_Tavern2_7";
				notification("Habilidad insuficiente (50)", SKILL_COMMERCE);
			}
		break;

		case "TPZ_Tavern2_4":
			dialog.text = "Eso sigue siendo más de lo que pagaba antes. Pero he aprendido la lección: la estabilidad cuesta más. Acepto sus condiciones, pero sepa: un error, y buscaré otro proveedor. Debo entender por qué pago más. Y además. ¿Cómo piensa resolver el asunto con las autoridades de la isla?";
			link.l1 = "Me ocuparé de eso de inmediato. Tan pronto como todo esté resuelto, volveré con la mercancía.";
			link.l1.go = "TPZ_Tavern2_5";
		break;

		case "TPZ_Tavern2_5":
			dialog.text = "Por favor, no se demore. Estoy ansioso por llenar las jarras de mis clientes lo antes posible.";
			link.l1 = "No se preocupe, no le haré esperar mucho.";
			link.l1.go = "TPZ_Tavern2_6";
		break;

		case "TPZ_Tavern2_6":
			DialogExit();
			AddQuestRecord("TPZ", "5");
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_3");
			AddLandQuestMark(characterFromId("BasTer_Mayor"), "questmarkmain");
			pchar.questTemp.TPZ_guber_1 = true;
			pchar.questTemp.TPZ_Vino240 = true;

			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;
		
				case "TPZ_Tavern2_7":
			dialog.text = "Sigue siendo demasiado caro, capitán. Este precio es más alto que el de mi proveedor anterior. Incluso si acepto ahora, en un par de meses tendré que volver a él cuando se reanude la producción. No veo razón para pagar de más.";
			link.l1 = "Entiendo. De acuerdo. Mi última oferta: doscientos doblones. Si esto tampoco le convence, no tiene sentido seguir hablando.";
			link.l1.go = "TPZ_Tavern2_8";
		break;
		
		case "TPZ_Tavern2_8":
			dialog.text = "Está bien, trato hecho. Doscientos me parece bien. Pero dígame, ¿cómo piensa resolver el asunto con las autoridades de la isla? Como ya le dije, el gobernador protege con esmero la isla del contrabando, y no permitirá transacciones a sus espaldas.";
			link.l1 = "Ja, ja, bueno, sobre eso podría discutirse. Pero no se preocupe: tengo la intención"+GetSexPhrase("","a")+" de resolver todos los trámites burocráticos lo antes posible.";
			link.l1.go = "TPZ_Tavern2_9";
		break;
		
		case "TPZ_Tavern2_9":
			dialog.text = "Le ruego que no se demore. Estoy impaciente por llenar las jarras de mis clientes.";
			link.l1 = "No se preocupe, no me haré esperar.";
			link.l1.go = "TPZ_Tavern2_10";
		break;
		
		case "TPZ_Tavern2_10":
			DialogExit();
			AddQuestRecord("TPZ", "6");
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_3");
			AddLandQuestMark(characterFromId("BasTer_Mayor"), "questmarkmain");
			pchar.questTemp.TPZ_guber_1 = true;
			pchar.questTemp.TPZ_Vino200 = true;
		break;
		
		case "TPZ_Tavern2_11":
			if (sti(pchar.reputation.nobility) >= 40)
			{
				dialog.text = "¡Por supuesto, capitán! Entonces, ¿cuánto quiere por su cargamento?";
				link.l1 = "Por cada diez botellas de vino quiero treinta doblones, y por el ron, cinco doblones. Todo el lote de cien botellas de ron y cien de vino le costará trescientos cincuenta doblones.";
				link.l1.go = "TPZ_Tavern2_3";
				notification("¡Reputación honorable verificada!", "None");
			}
			else
			{
				dialog.text = "Lo lamento, capitán, pero su reputación aún deja mucho que desear.";
				link.l1 = "¡Maldita sea...";
				link.l1.go = "exit";
				notification("¡Nivel de honor demasiado bajo! ("+XI_ConvertString(GetReputationName(40))+")", "None");
			}
		break;
		
		case "TPZ_Tavern3_1":
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino240"))
			{
				dialog.text = "¡Por supuesto, capitán, por supuesto! 240 doblones, tal como acordamos. ¡Tome!";
				link.l1 = "¡Un placer hacer negocios con usted! Ahora la taberna volverá a rebosar de ron y vino.";
				link.l1.go = "TPZ_Tavern3_2";
				AddItems(pchar, "gold_dublon", 240);
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino200"))
			{
				dialog.text = "¡Por supuesto, capitán, por supuesto! 200 doblones, tal como acordamos. ¡Tome!";
				link.l1 = "¡Un placer hacer negocios con usted! Ahora la taberna volverá a rebosar de ron y vino.";
				link.l1.go = "TPZ_Tavern3_2";
				AddItems(pchar, "gold_dublon", 200);
			}
			DelLandQuestMark(npchar);
		break;

		case "TPZ_Tavern3_2":
			dialog.text = "¡Por los cielos, capitán, usted es mi salvación encarnada! Esperaré envíos idénticos cada dos semanas. Confío en que cumplirá sus compromisos con la máxima fidelidad. Mi humilde taberna no sobreviviría a otra sequía semejante...";
			link.l1 = "No tema, buen "+npchar.name+". Mi agente en la ciudad, un tal Christian Deluce, se encargará de que su taberna no sufra escasez de vino ni ron.";
			link.l1.go = "TPZ_Tavern3_3";
		break;

		case "TPZ_Tavern3_3":
			dialog.text = "¿Christian, dice? Conozco al sujeto: una persona responsable, aunque algo... Bueno, no importa. Ya que ha arreglado todo con las autoridades, creo que puedo confiar en él.";
			link.l1 = "Excelente. Ahora, ruego me disculpe, tengo un último asunto que atender en este puerto.";
			link.l1.go = "TPZ_Tavern3_4";
		break;

		case "TPZ_Tavern3_4":
			dialog.text = "¡Vuelva a honrarnos con su presencia más a menudo!";
			link.l1 = "Desde luego.";
			link.l1.go = "TPZ_Tavern3_5";
		break;

		case "TPZ_Tavern3_5":
			DialogExit();
			AddQuestRecord("TPZ", "7");
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_4");
			
			sld = CharacterFromID("TPZ_Kristian");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest\MiniEvents\TradingByLaw_dialog.c";
			sld.dialog.currentnode = "Kristian_31";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		//<-- Торговля по закону
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
