// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Hangi sorularınız var?","Size nasıl yardımcı olabilirim?"),"Az önce bana bir soru sormaya çalıştınız...","Benim tersanemde ya da bu kasabada böylesine meraklı insanlara hiç rastlamadım.","Bu kadar çok soru neden? Benim işim gemi yapmak. Hadi, onunla ilgilenelim.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şu anda konuşacak bir şeyim yok."),"Ah, hafızam nereye kayboldu...","Hm, peki...","Devam et...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Bana söyle, Juan ismi sana bir şey ifade ediyor mu?";
				link.l1.go = "Consumption";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "Efendim, Nisan 1654’te burada Miguel Dichoso’nun komutasında bir fırkateyn vardı. Hemen ardından ortadan kayboldu. Hiçbir şey hatırlamıyor musunuz? Belki Dichoso tamir için uğradı ve size bir şeyler söyledi...";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "Hayır. Hiçbir şey yok.";
			link.l1 = "Peki. Rahatsız ettiğim için kusura bakmayın...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
		
		case "guardoftruth":
			dialog.text = "Hmm. Hayır. Tamire uğramadı ve bana hiçbir şey söylemedi. Eğer böyle bir şey olduysa da hatırlamıyorum. Üzgünüm, size yardımcı olamıyorum, señor.";
			link.l1 = "Pekala. Gracias, amigo...";
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
