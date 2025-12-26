// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Hangi sorularınız var?","Size nasıl yardımcı olabilirim?"),"Bana bu soruyu kısa süre önce sormuştunuz...","Evet, dur bakayım... Yine aynı şeyleri mi dönüp duruyorsun?","Dinle, burada finans işlerini ben hallederim, sorulara cevap vermem...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şu anda konuşacak bir şeyim yok."),"Ah, hafızam nereye gitti böyle...","Doğru tahmin ettiniz, üzgünüm...","Anlıyorum...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			// --> Sinistra Длинные тени старых грехов	
			if (CheckAttribute(pchar, "questTemp.DTSG_depozit"))
			{
				link.l1 = "Söylesene, Albay seni ziyaret etti mi? Bana bir ödül hazırladığını söylemişti.";
				link.l1.go = "DTSG_depozit_1";
			}
			// <-- Длинные тени старых грехов
		break;
		
		// --> Sinistra Длинные тени старых грехов	
		case "DTSG_depozit_1":
			dialog.text = "Hangi Albay?";
			link.l1 = "Thomas Lynch.";
			link.l1.go = "DTSG_depozit_2";
		break;
		
		case "DTSG_depozit_2":
			dialog.text = "Sessiz konuşun! O adamı tanıyorum. Evet, uğradı. Ödülünüz sizi bekliyor, Kaptan.";
			link.l1 = "Ve ne kadar var?";
			link.l1.go = "DTSG_depozit_3";
		break;
		
		case "DTSG_depozit_3":
			dialog.text = "Tam on bin altın. Tek bir peso bile yok - hepsi altın.";
			link.l1 = "En azından otuz gümüş değil...";
			link.l1.go = "DTSG_depozit_4";
			AddItems(pchar, "chest", 70);
			Log_Info("You have received 70 chests");
			PlaySound("interface\important_item.wav");
		break;
		
		case "DTSG_depozit_4":
			dialog.text = "Ne oldu o?";
			link.l1 = "Ah, önemli bir şey yok... Teşekkür ederim. Hoşça kalın.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.DTSG_depozit");
		break;
		// <-- Длинные тени старых грехов
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
