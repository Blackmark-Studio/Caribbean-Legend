// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Ne tür sorular?","Ne istiyorsun?");
			link.l1 = RandPhraseSimple("Fikrimi değiştirdim.'","Şu anda söyleyecek bir şeyim yok.");
		    link.l1.go = "exit";
			
			// Rebbebion, "Путеводная звезда"
			if (CheckAttribute(pchar, "questTemp.PZ.TortugaCitizensAsk") && npchar.sex == "man")
			{
				link.l1 = "Sen Joep van der Vink adında birini tanıyor olamazsın, değil mi?";
				link.l1.go = "PZ_1";
			}
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Sence ben gizli serviste mi çalışıyorum "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "Pekâlâ... hayır. O halde hoşça kal.";
			link.l1.go = "exit";
			link.l2 = "Başka sorunuz var mı, peki?";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "Ben soruşturma bürosu muyum? Bilmiyorum, hiçbir şey bilmiyorum.";

            link.l1 = "Sen tam bir şaşkınsın! Defol.";
			link.l1.go = "exit";
			link.l2 = "Başka bir sorunuz var mı?";
			link.l2.go = "new question";
		break;
		
		case "PZ_1":
			dialog.text = "Doğrudan tanımam ama onu burada ara sıra görürüm. Neden sordunuz?";
			link.l1 = "Ona şahsen bir paket teslim etmem istendi. Ama kimse onun hakkında konuşmak istemiyor, nedenini de bilmiyorum. Sen biliyor musun? Kötü biri mi? Dürüst fikrini paylaşırsan sevinirim.";
			link.l1.go = "PZ_2";
		break;
		
		case "PZ_2":
			dialog.text = "Yine de, birbirimizi şahsen tanımıyoruz, bu yüzden neredeyse hiçbir şey bilmiyorum. Ama onun şehirde yakın bir arkadaşı var ve sık sık beraber görülüyorlar. Ona git – sana daha fazlasını anlatıp anlatmamaya o karar verir. Arkadaşının adı Rober Martene.";
			link.l1 = "Rober Martene, diyorsun... Kim bu? Onu nerede bulabilirim?";
			link.l1.go = "PZ_3";
		break;
		
		case "PZ_3":
			dialog.text = "Çeşitli yerlerde olur, ama şu anda fenerimizde — korkunç bir fırtınadan sonra kalyonunu tamir ediyor. Adı 'Voltigeur'.";
			link.l1 = "Çok teşekkür ederim! Bana ne kadar yardımcı olduğunun farkında bile değilsin.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_CreateRobertMartin");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
