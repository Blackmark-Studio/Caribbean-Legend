// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Hangi sorularınız var?","Size nasıl yardımcı olabilirim?"),"Biraz önce bana bir soru sormaya çalıştın...","Benim tersanemde ya da bu kasabada, böylesine meraklı insanlara hiç rastlamadım.","Bu kadar çok soru neden? Benim işim gemi yapmak. Hadi onunla ilgilenelim.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şu anda konuşacak bir şeyim yok."),"Ah, hafızam nereye gitti...","Hm, şey...","Devam et...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon 2016-1 Jason пиратскаЯ линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx"))
            {
				if (pchar.questTemp.Mtraxx == "silk_2" || pchar.questTemp.Mtraxx == "silk_3")
				{
					link.l1 = "Bu tersanenin gemilerin hızını artırmada uzman olduğunu duydum. Bunun için çok nadir bulunan ipek yelken bezi gerekiyor. Acaba... bunu konuşmak ister misiniz?";
					link.l1.go = "mtraxx";
				}
			}
			if (CheckAttribute(npchar, "quest.upgradeship")) {
				link.l2 = "Ben Miss MacArthur'dan geliyorum, hakkında...";
				link.l2.go = "helen_upgradeship";
			}
			
			if (CheckAttribute(npchar, "quest.upgradeship.money") && HelenCanUpgrade()) {
				link.l2 = "Geminin büyük onarımını başlat!";
				link.l2.go = "helen_upgradeship_money";
			}
		break;
		
		// Addon 2016-1 Jason пиратскаЯ линейка
		case "mtraxx":
            dialog.text = "Daha açık olabilir misin, genç adam? Seni buraya tam olarak ne getirdi? Eğer gemini geliştirmek istiyorsan, hemen işe koyulalım.";
			link.l1 = "Tam olarak değil. Sunduğunuz hizmetler, dükkânda kolayca bulunmayan malzemeler gerektiriyor. Size ihtiyaç duyabileceğiniz aynı türden malzemeleri sunmak isterim.";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = "Well, well... Hmm... Are you aware that only the authorities of this colony are permitted to deal with such strategic goods? You are free to provide your own silk for me to use in improving your ship; however, selling it is strictly forbidden. As is buying it from me—such activities will be fined rather heavily.";
			link.l1 = "Bakın, burası ne bir dükkan ne de bir gümrük ofisi...";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "Tüm ipek yelken bezlerini doğrudan müşterilerimden temin ederim ya da valinin özel izniyle sınırlı miktarda satın alırım. Başka bir sorunuz yoksa, lütfen işime geri dönmeme izin verin.";
			link.l1 = "Hmm... Peki. İyi günler, efendim.";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            DialogExit();
			AddQuestRecord("Roger_2", "5");
			pchar.questTemp.Mtraxx = "silk_4";
		break;
		
		case "helen_upgradeship":
			dialog.text = "Oh, I know! Lucky you, Captain. Is it about a complete overhaul of the ship? We'll take care of everything; our shipyard is on par with those in Plymouth!";
			link.l1 = "Bunun ücretsiz bir hizmet olmayacağını tahmin ediyorum?";
			link.l1.go = "helen_upgradeship_1";
		break;
		
		case "helen_upgradeship_1":
			dialog.text = "Elbette, Kaptan, böyle hizmetler bedava olmaz, Cromwell için bile! Ama sözüm söz, sadece para alırım – kaçakçılık yapmana gerek kalmayacak.";
			link.l1 = "Anlaşıldı. Ne kadar?";
			link.l1.go = "helen_upgradeship_2";
		break;
		
		case "helen_upgradeship_2":
			dialog.text = "Amiral geminizin büyüklüğüne bağlı, Kaptan. Birinci sınıf bir gemi size beş bin dublona mal olur, beşinci sınıf ise sadece bin dublon tutar.";
			link.l1 = "Pekala, kararımı verdiğimde sana geleceğim.";
			link.l1.go = "exit";
			
			npchar.quest.upgradeship.money = true;
		break;
		
		case "helen_upgradeship_money":
			dialog.text = "Harika, şimdi ihtiyacım olan her şey elimde. O halde işe koyuluyorum.";
			link.l1 = "Bekliyorum.";
			link.l1.go = "helen_upgradeship_money_1";
			
			iTemp = GetCharacterShipType(pchar);
			sld = GetRealShip(iTemp);
			iTemp = (7 - sti(sld.class)) * 1000;
			RemoveDublonsFromPCharTotal(iTemp);
		break;
		
		case "helen_upgradeship_money_1":
			AddTimeToCurrent(6, 30);
			dialog.text = "... Sanırım bu kadar... Kaliteye garanti veriyorum.";
			link.l1 = "Teşekkürler! Bir göz atacağım.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenUpgradeShip2");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

bool HelenCanUpgrade() {
	int shipIndex = GetCharacterShipType(pchar);
	if (shipIndex == SHIP_NOTUSED) {
		return false;
	}
	
	sld = GetRealShip(shipIndex);
	if (sti(sld.class) == 7) {
		return false;
	}
	
	int cost = (7 - sti(sld.class)) * 1000;
	return (PCharDublonsTotal() >= cost);
}
