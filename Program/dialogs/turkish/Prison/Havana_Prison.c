// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Konuş, dinliyorum";
			link.l1 = "Yanılmışım. Hoşça kal.";
			link.l1.go = "Exit";
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_4")
			{
				link.l1 = "Subay, 'Cantavro' gemisinin bir subayının burada tutulduğunu öğrendim. Doğru mu?";
                link.l1.go = "Mtraxx";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_8")
			{
				link.l1 = "Subay, Don Lope hakkında tekrar bilgi almaya geldim. Onun salıverilme emri elinize ulaştı mı?";
                link.l1.go = "Mtraxx_5";
			}
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "Mtraxx":
            dialog.text = "'Cantavro'nun subayı mı? Don Lope Montoro? Evet, burada tutuluyor. Sana ne bundan?";
			link.l1 = "Onu ziyaret etmek için izin istiyorum.";
			link.l1.go = "Mtraxx_1";
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId("Lope"), "questmarkmain");
		break;
		
		case "Mtraxx_1":
            dialog.text = "Affedersiniz, ama hangi gerekçeyle?";
			link.l1 = "Bu sadece kişisel bir mesele. Onu Avrupa'dan tanıyordum, hapse atıldığını duyunca ve şehirde yayılan dedikoduları işitince çok şaşırdım. Onunla konuşmak istiyorum.";
			link.l1.go = "Mtraxx_2";
		break;
		
		case "Mtraxx_2":
            dialog.text = "Hm...";
			link.l1 = "Memur bey, belki de... ona ziyaretime izin verdiğiniz için size bir 'teşekkür' borçluyumdur?";
			link.l1.go = "Mtraxx_3";
		break;
		
		case "Mtraxx_3":
            dialog.text = "Buna gerek yok. Don Montoro ile görüşmene izin veriyorum. Gardiyanlar seni geçirecek.";
			link.l1 = "Teşekkür ederim!";
			link.l1.go = "Mtraxx_4";
		break;
		
		case "Mtraxx_4":
			DialogExit();
            pchar.questTemp.jailCanMove = true;
			pchar.questTemp.Mtraxx = "jewelry_5";
		break;
		
		case "Mtraxx_5":
            dialog.text = "Gerçekten de, emirlerim Don Lope Montoro'yu doğrudan komutana teslim etmek. Ama sanırım birkaç hafta boyunca hücresinden çıkmayacak. Yine de, hâlâ buradayken onu görebilirsin.";
			link.l1 = "Teşekkür ederim, subayım, bu yüzden buradayım.";
			link.l1.go = "Mtraxx_6";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtraxx_6":
            DialogExit();
            pchar.questTemp.jailCanMove = true;
			pchar.questTemp.Mtraxx = "jewelry_9";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
