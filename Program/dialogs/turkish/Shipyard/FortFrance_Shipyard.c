// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Hangi sorularınız var?","Size nasıl yardımcı olabilirim?"),"Az önce bana bir soru sormaya çalıştınız...","Bu tersanemde ya da bu kasabada böylesine meraklı insanlarla hiç karşılaşmadım.","Bu kadar çok soru neden? Benim işim gemi yapmak. Hadi onunla ilgilenelim.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şu anda konuşacak bir şeyim yok."),"Ah, hafızam nereye kayboldu...","Hm, şey...","Devam et...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon-2016 Jason ”ЊЉ-Њартиника
			if (CheckAttribute(pchar, "questTemp.FMQM") && pchar.questTemp.FMQM == "begin")
            {
                link.l1 = "Adamınız benimle görüşmek istediğinizi söyledi. Sizi dinliyorum.";
                link.l1.go = "FMQM";
            }
			if (CheckAttribute(pchar, "questTemp.FMQM") && pchar.questTemp.FMQM == "oil" && GetSquadronGoods(pchar, GOOD_OIL) >= 50)
            {
                link.l1 = "İşi bitirdim. "+FindRussianQtyString(GetSquadronGoods(pchar,GOOD_OIL))+" varil reçine ambarlarımda duruyor.";
                link.l1.go = "FMQM_9";
            }
		break;
		
		// Addon-2016 Jason ”ЊЉ-Њартиника
		case "FMQM":
			pchar.quest.FMQM_Denial.over = "yes";
			dialog.text = "Evet, evet, kaptan "+GetFullName(pchar)+". Limanımıza girişinizi gördüm ve hemen uşağımı size gönderdim. Lafı uzatmadan konuya gireyim: Yeni gelmişsiniz ama çoktan deneyimli bir denizci olmuşsunuz ve şansınız da yaver gidiyormuş. Bu yüzden size bir iş teklifim var.";
			link.l1 = "İlginç! Devam et, anlat bakalım.";
			link.l1.go = "FMQM_1";
			DelLandQuestMark(npchar);
		break;
		
		case "FMQM_1":
			dialog.text = "Have you ever heard of a special resin the Spaniards produce on the island of Trinidad? It is a rare resource of strategic value, used to fortify the hulls of ships. Every barrel costs a hefty sum because the Spanish direct all the resin to the needs of their Navy. Every colonial authority keeps trade in this good under strict control; to put it simply, it's pure contraband.   I need this resin for a special order. Of course, our store doesn't have it, and the same can be said about our local military warehouses—or perhaps they simply didn't want to sell it. It's irrelevant, really. What matters is that I need the resin, and I know where to get some. All I need is a captain who is comfortable with boardings.";
			link.l1 = "Sanırım ne demek istediğini anlamaya başlıyorum...";
			link.l1.go = "FMQM_2";
		break;
		
		case "FMQM_2":
			dialog.text = "Harika. Şimdi dinle, küçük bir ticaret konvoyu Trinidad yakınlarında, daha doğrusu San Jose limanında görüldü. Gemilerden biri, tam da çok ihtiyacım olan kaliteli bir reçine partisi taşıyor. Eğer milletimizin düşmanlarını yağmalama fikri hoşuna giderse, sana daha fazlasını anlatırım. Ne diyorsun?";
			link.l1 = "Teklifinizi beğendim. Denemeye hazırım.";
			link.l1.go = "FMQM_3";
			link.l2 = "Bu seferlik pas geçeceğim, monsieur. Şu anda ne gemim ne de mürettebatım en iyi durumda değil.";
			link.l2.go = "FMQM_exit";
		break;
		
		case "FMQM_exit":
			dialog.text = "Pekala, istediğiniz gibi yapmaya hakkınız var. Zamanınızı aldığım için üzgünüm, kaptan.";
			link.l1 = "Hoşça kal.";
			link.l1.go = "FMQM_exit_1";
		break;
		
		case "FMQM_exit_1":
			DialogExit();
			pchar.questTemp.FMQM = "fail";
			AddQuestRecord("FMQ_Martinique", "3");
			CloseQuestHeader("FMQ_Martinique");
		break;
		
		case "FMQM_3":
			string sTemp = "barquentine";
			if (MOD_SKILL_ENEMY_RATE < 7) sTemp = "barque";// Addon 2016-1 Jason пиратскаЯ линейка
			dialog.text = "O halde dinle: konvoy üç gemiden oluşuyor, reçine diğer malların arasında olacak "+sTemp+" 'Bensecho' adında bir gemi. Bu senin asıl hedefin. Daha önce de söylediğim gibi, İspanyollar San Jose - Trinidad'dan San Juan - Porto Riko'ya yelken açıyorlar. Yarın denize açılacaklar, bu yüzden onlara nerede saldıracağına sen karar verebilirsin.";
			link.l1 = "Anladım.   Peki ya ödül?";
			link.l1.go = "FMQM_4";
		break;
		
		case "FMQM_4":
			dialog.text = "Benim ilgilendiğim tek şey reçine. Her bir fıçısı için on beş altın dublon ödeyeceğim. Aldığım bilgilere göre, 'Bensecho' yaklaşık yüz fıçı taşıyor.";
			link.l1 = "Aman Tanrım! Bu oldukça yüklü bir meblağ!";
			link.l1.go = "FMQM_5";
		break;
		
		case "FMQM_5":
			dialog.text = "Evet. Zaten bu özel malın çok pahalı ve nadir olduğunu söylemiştim.";
			link.l1 = "Bunun kaçak mal olduğunu da bana sen söyledin.";
			link.l1.go = "FMQM_6";
		break;
		
		case "FMQM_6":
			dialog.text = "Endişelenme, ne mağazaya ne de kaçakçılara götürmene gerek kalmayacak. İş bitince yanıma gel, gemini tersaneme çekeceğiz, onarımı yaparken de tüm yükü gece gizlice boşaltacağız. Kimsenin haberi bile olmayacak.";
			link.l1 = "Benden önce düşünüyorsun, usta. Pekala. O halde vakit kaybetmeyelim. Yelken açmaya gidiyorum.";
			link.l1.go = "FMQM_7";
		break;
		
		case "FMQM_7":
			dialog.text = "Yolun açık olsun, kaptan.";
			link.l1 = "...";
			link.l1.go = "FMQM_8";
		break;
		
		case "FMQM_8":
			DialogExit();
			pchar.questTemp.FMQM = "convoy";
			AddQuestRecord("FMQ_Martinique", "4");
			SetFunctionTimerCondition("FMQM_ConvoyStart", 0, 0, 1, false);
		break;
		
		case "FMQM_9":
			dialog.text = "Harika! Anlaştığımız gibi geminizi rıhtıma alalım. Bu gece orada boşaltacağız. Siz geminize dönün, ben de paranızı hazırlayayım.";
			link.l1 = "Hadi başlayalım.";
			link.l1.go = "FMQM_10";
			DelLandQuestMark(npchar);
		break;
		
		case "FMQM_10":
			pchar.quest.FMQM_Late.over = "yes";
			DialogExit();
			InterfaceStates.Buttons.Save.enable = false;
			chrDisableReloadToLocation = true;
			pchar.GenQuest.FrameLockEsc = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			pchar.questTemp.FMQM = "remove_oil";
			pchar.questTemp.FMQM.Oil = "true";
			pchar.questTemp.FMQM.Qty = GetSquadronGoods(pchar, GOOD_OIL);
			DoQuestFunctionDelay("FMQM_WaitTime", 1.0);
			RemoveCharacterGoods(pchar, GOOD_OIL, GetSquadronGoods(pchar, GOOD_OIL));
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
