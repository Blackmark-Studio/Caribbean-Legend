// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Hangi sorularınız var?","Size nasıl yardımcı olabilirim?"),"Az önce bana bir soru sormaya çalıştınız...","Benim tersanemde ya da bu kasabada, böylesine meraklı insanlarla daha önce hiç karşılaşmadım.","Bu kadar çok soru neden? Benim işim gemi yapmak. Hadi onunla ilgilenelim.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şu anda konuşacak bir şeyim yok."),"Ah, hafızam nereye kayboldu...","Hm, şey...","Devam et...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "Blueweld'e bir parti kahveyle gidiyorum ve biraz daha mal almak istiyorum, ama şöyle bir sorun var: Bu savaş köpeğinden aldığım brigantin üzerinde tam 24 tane ağır top var, ki bu gerçekten abartı. Savaşa gitmiyorum sonuçta. Hepsini sana satmak ve yerine 12 tane altı librelik top almak istiyorum, korsanları korkutmaya yeter de artar bile. Geri kalan alanı da malzemeyle dolduracağım.";
                link.l1.go = "ShipyardDone";
			}
		break;
		
		case "ShipyardDone":
			dialog.text = "Evet, satabilirsiniz. Altı librelik toplardan her zaman yeterince var, ama ağır toplarla hep başım dertte; herkes sürekli satın alıyor, kimse satmak istemiyor, ancak tamamen hurda olursa satıyorlar. O yüzden, eğer toplarınız hâlâ çalışır durumdaysa, size iyi bir fiyat öderim.";
			link.l1 = "Harika, hemen emirleri vereceğim.";
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
