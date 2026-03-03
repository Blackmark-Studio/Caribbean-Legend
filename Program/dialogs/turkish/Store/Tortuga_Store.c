// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Hangi sorularınız var?","Size nasıl yardımcı olabilirim?"),"Bana kısa bir süre önce bir soru sormaya çalıştınız...","Uzun zamandır Tortuga'daki bir dükkânda kimse böyle sorular sormadı...","Sorular, sorular ve daha fazla soru...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şu anda konuşacak bir şeyim yok."),"Ah, hafızam nereye gitti böyle...","Pekâlâ, uzun zaman oldu.","Daha da mı çok soru, ha...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "tortuga2")
			{
				link.l1 = "Dinle, Gaius Marchais'i bulmam gerekiyor. Bana onun korsanlık işlerine bulaştığı ve İspanyollardan harika bir kalyon aldığı için iyi bir pazarlıkçı haline geldiği söylendi. Senden ticaret için herhangi bir mal satın aldı mı, biliyor musun?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Gaius Marchais? Ah evet, tabii ki onu hatırlıyorum! Ama hiçbir şey satın almadı. Gemisini nakliye için teklif etti. Tam da geniş ambarlı bir gemiye ihtiyacım vardı – büyük bir ham deri partisi.";
			link.l1 = "Ve boşaltma noktası neredeydi?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Philipsburg, Saint Maarten.";
			link.l1 = "Pekâlâ. Teşekkür ederim, bana çok yardımcı oldunuz!";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Her zaman beklerim, kaptan. Ne zaman isterseniz dükkânıma uğrayın!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddQuestRecord("Guardoftruth", "10");
			pchar.questTemp.Guardoftruth = "maarten";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
