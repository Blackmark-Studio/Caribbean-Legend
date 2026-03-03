// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Ne tür sorular, "+GetSexPhrase("evladım","kızım")+"?","Sor, dinliyorum..."),"Dinliyorum, şimdi konuş. "+GetSexPhrase("evladım","kızım")+"...","Üçüncü kez, "+GetSexPhrase("evladım","kızım")+", neye ihtiyacın varsa sor.","Bir din adamının yapacak çok işi var ve sen beni oyalıyorsun, "+GetSexPhrase("evladım","kızım")+"...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şu anda değil, padre..."),"Söyleyecek bir şeyim yok, özür dilerim.","Daha sonra soracağım. Beni affedin, baba.","Affedersiniz, kutsal baba...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Jason Долго и счастливо
			if (CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "choose" && !CheckAttribute(npchar, "quest.LongHappy"))
			{
				link.l1 = "Kutsal Baba, Başrahip Benoit'u arıyorum, ona acil bir meselem var. Bana onu nerede bulabileceğimi söyleyebilir misiniz?";
				link.l1.go = "LH_church";
			}
		break;
		
		// Jason Долго и счастливо
		case "LH_church":
			dialog.text = "Başrahip Benoit, Yeni Dünya'daki İspanyol Katolik misyonunun temsilcileriyle kilise işleri için şehirden ayrıldı. Ayrıntıları bilmiyorum, fakat Başrahip Benoit o kadar uzun süredir yok ki, görüşmelerin uzadığını ya da yolda bir şeyler olmuş olabileceğini düşünüyoruz. Hepimiz huzursuzuz, ama elimizden sadece dua edip haber beklemek geliyor.";
			link.l1 = "Her şeyin kolay olacağını varsayamayız. Aziz Baba, Abbot Benoit'nun tam olarak nereye gittiğini bana söyleyebilir misiniz? Onu mümkün olan en kısa sürede bulmam gerekiyor.";
			link.l1.go = "LH_church_1";
		break;
		
		case "LH_church_1":
			dialog.text = "Korkarım ki yapamam, evladım. Bildiğim kadarıyla Başrahip Benoit, Yeni İspanya Piskoposu ve Engizisyon başrahibi Vincento Palotti ile görüşmeye gitti, fakat buluşmanın nerede olacağını belirtmedi.";
			link.l1 = "Bu yeterli olur, Kutsal Baba, teşekkür ederim. Baba Palotti'yi bir şekilde tanıyorum... Santiago'da biraz bakınacağım.";
			link.l1.go = "LH_church_2";
		break;
		
		case "LH_church_2":
			DialogExit();
			npchar.quest.LongHappy = "true";
			LongHappy_GoToSantiago();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
