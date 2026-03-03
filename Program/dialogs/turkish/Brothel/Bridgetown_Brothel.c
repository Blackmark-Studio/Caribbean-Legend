// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Ne tür sorular, "+GetSexPhrase("genç adam","genç hanımefendi")+"?","Ne istiyorsun, "+GetSexPhrase("yakışıklı","güzelim")+"? Sor bakalım."),"Yine mi sorular?","Tee-hee, eğer sizin için fark etmezse - sorular...",""+GetSexPhrase("Hm, neden kendin için bir güzellik seçmiyorsun? Senden şüphelenmeye başlıyorum...","Hm, neden kendin için bir güzellik seçmiyorsun? Ne yazık ki burada hiç erkek yok, haha...")+"","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim, affedersiniz.","Aslında, boşver..."),"Ben... özür dilerim, şu anda sorum yok.","Haklısınız, bu zaten üçüncü sefer. Affedin beni.","Belki bir dahaki sefere, Madam.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "Ticarete yönelik bir maun yükü aldım ve Blueweld'e gidiyorum. Yolum hâlâ uzun, adamlarım az ve tedirgin ... Elli denizcinin burada bir gece dinlenmesi neye mal olur?";
                link.l1.go = "BrothelDone";
            }
		break;
		
		case "BrothelDone":
			dialog.text = "Elli denizci - on beş bin.";
			link.l1 = "Büyük bir meblağ... Bunu düşünmem gerek.";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-7");
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
