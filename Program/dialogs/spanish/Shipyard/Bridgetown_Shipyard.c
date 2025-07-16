// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("¿Qué preguntas tienes?","¿En qué puedo ayudarle?"),"Intentaste hacerme una pregunta hace un rato...","Jamás he conocido personas con tal curiosidad en mi astillero o en cualquier otro lugar de esta ciudad.","¿Por qué tantas preguntas? Mi trabajo es construir barcos. Ocupémonos de eso.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("He cambiado de opinión...","No tengo nada de qué hablar en este momento."),"Umph, ¿dónde se ha ido mi memoria...?","Mm, bueno...","Adelante...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "Voy de camino a Blueweld con una carga de café y me gustaría comprar más mercancía, pero aquí está el problema: en este bergantín, que he comprado a un perro de guerra, hay una cantidad abominable de cañones pesados, un total de 24. No voy camino a una guerra, ¿sabes? Me gustaría vendértelos todos y comprar 12 de seis libras, más que suficientes para asustar a algunos piratas. Y el resto del espacio que tengo lo llenaré con mercancía.";
                link.l1.go = "ShipyardDone";
			}
		break;
		
		case "ShipyardDone":
			dialog.text = "Sí, por favor, véndelos. Siempre tengo suficientes cañones de seis libras, pero tengo problemas con los cañones pesados, ya que todos los compran todo el tiempo y nadie quiere venderlos. Así que te pagaré un precio decente por ellos, si todavía están en buenas condiciones, por supuesto.";
			link.l1 = "¡Vaya, genial! Voy a dar las órdenes de inmediato.";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-10");
			DelLandQuestMark(npchar);
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
			AddQuestRecord("Holl_Gambit", "2-6");
			pchar.quest.GotoBridgetownOver.over = "yes";//снять таймер
			DelMapQuestMarkCity("Bridgetown");
			pchar.questTemp.HWIC.Eng = "SeekVanBerg";
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
				//if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_VALCIRIA || GetCompanionQuantity(pchar) > 1) AddDialogExitQuestFunction("FailVanBergInWorld");
				//else AddDialogExitQuestFunction("CreateVanBergInWorld");
			}
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
