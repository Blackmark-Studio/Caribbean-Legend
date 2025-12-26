// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Que perguntas você tem?","Como posso ajudar você?"),"Você tentou me fazer uma pergunta há pouco tempo...","Eu nunca conheci pessoas tão curiosas no meu estaleiro ou em qualquer outro lugar desta cidade.","Por que tantas perguntas? Meu trabalho é construir navios. Vamos cuidar disso.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia...","Não tenho nada para conversar no momento."),"Ah, onde foi parar minha memória...","Hum, bem...","Pode prosseguir...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "Estou a caminho de Blueweld com uma carga de café e quero comprar mais mercadorias, mas tem um problema: neste brigue, que comprei de um cão de guerra, há um número absurdo de canhões pesados, ao todo 24. Não estou indo para uma guerra, sabe? Quero vender todos eles para você e comprar 12 canhões de seis libras, que já são mais do que suficientes para assustar alguns piratas. E o resto do espaço que sobrar eu vou preencher com mercadorias.";
                link.l1.go = "ShipyardDone";
			}
		break;
		
		case "ShipyardDone":
			dialog.text = "Sim, vá em frente e venda-os. Sempre tenho canhões de seis libras suficientes, mas sempre tenho problemas com os canhões pesados, já que todo mundo compra o tempo todo e ninguém quer vender, a não ser que estejam completamente quebrados, então vou te pagar um preço justo por eles, se, é claro, ainda estiverem em boas condições de uso.";
			link.l1 = "Ótimo! Vou dar as ordens imediatamente.";
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
