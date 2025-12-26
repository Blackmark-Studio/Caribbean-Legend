// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Hangi sorularınız var?","Size nasıl yardımcı olabilirim?"),"Az önce bana bir soru sormaya çalıştınız...","Bu tersanemde ya da bu kasabada böylesine meraklı insanlarla hiç karşılaşmadım.","Bu kadar çok soru neden? Benim işim gemi yapmak. Hadi işimize bakalım.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şu anda konuşacak bir şeyim yok."),"Ah, hafızam nereye kayboldu...","Hm, peki...","Devam et...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		case "helendrinking_buy_rainbow":
			dialog.text = "... değerli bir seçim, efendim. Peki, anlaştık mı?";
			link.l1 = "E-evet! Şerefe! Paketleyin ve iskeleye gönderin. Ve acele edin, sokakta beni bekleyen bir hanımefendi var!";
			link.l1.go = "helendrinking_buy_rainbow_1";
			locCameraFromToPos(0.36, 1.86, 1.15, true, 2.06, -0.20, -4.38);
		break;
		
		case "helendrinking_buy_rainbow_1":
			dialog.text = "Hepsi için elli bin gümüş, efendim.";
			if (sti(pchar.money) >= 55000) {
				link.l1 = "N-ne kadar dediniz? E-elli bin mi? Alın, kendiniz sayın! Üstüne beş bin daha bahşiş olarak alın. Hadi gidelim!";
				link.l1.go = "helendrinking_buy_rainbow_yes";
			}
			
			link.l2 = "Yok yok, belki zenginim, hık! ...ama o kadarına almam. Hayır, efendim! Hoşça kal, kayıkçı.";
			link.l2.go = "helendrinking_buy_rainbow_no";
		break;
		
		case "helendrinking_buy_rainbow_yes":
			dialog.text = "Teşekkür ederim, kaptan. Umarım size iyi hizmet eder!";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "First time";
			
			AddMoneyToCharacter(pchar, -55000);
			pchar.questTemp.HelenDrinking.BoughtRainbow = true;
			
			AddDialogExitQuestFunction("HelenDrinking_GoToPerlas");
		break;
		
		case "helendrinking_buy_rainbow_no":
			dialog.text = "Evet, kaybol buradan, zengin çocuk. Üç saat önce kapattık.";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "First time";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToPerlas");
		break;
		
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
