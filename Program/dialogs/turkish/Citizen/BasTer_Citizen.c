// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Ne tür sorular?","Ne istiyorsun?");
			link.l1 = RandPhraseSimple("Fikrimi değiştirdim.'","Şu anda söyleyecek bir şeyim yok.");
		    link.l1.go = "exit";
		break;
		
		case "info":
			dialog.text = LinkRandPhrase("Kiminle ilgileniyorsun?","Kimi kastediyorsun?","Peki, kimmiş?");
			link.l1 = "Fadey Moskof hakkında daha fazla bilgi almak istiyorum.";
			link.l1.go = "fadey";
			link.l2 = "Kimse yok, boşver.";
			link.l2.go = "new question";
		break;
		
		case "town":
			dialog.text = LinkRandPhrase("Nereye gitmek istiyorsun?","Ne arıyorsun?","Tam olarak neye ihtiyacınız var?");
            link.l1 = "Fadey'nin evi nerede?";
			link.l1.go = "fadey_house";
			link.l2 = "Hadi başka bir şey konuşalım...";
			link.l2.go = "new question";
		break;
		
		case "fadey":
			dialog.text = RandPhraseSimple("Ah, önemli bir adam. Yerel fabrikanın sahibi ve Basse-Terre'in yüksek sosyetesiyle yakın. Ağır bir aksanı var ve içki içmeyi çok sever... ama asla sarhoş olmaz.","O büyük bir adam ve valinin dostu. Fadey burada bir fabrika sahibi. Kuzeyde, buradan çok çok uzak bir ülkeden gelmiş... Adını bile bilmiyorum. Güçlü elleri var ve bir fıçı romu içip sarhoş olmadan ayakta kalabilir.");
			link.l1 = "Teşekkür ederim.";
			link.l1.go = "exit";
		break;
		
		case "fadey_house":
			dialog.text = RandPhraseSimple("İskeleden dümdüz gidin, meydana vardığınızda soldaki ev Fadey'nin malikanesi.","Valinin konutundan meydana doğru gidip iskeleye ulaş, sağdaki ev Fadey'in malikanesi.");
			link.l1 = "Teşekkür ederim.";
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
