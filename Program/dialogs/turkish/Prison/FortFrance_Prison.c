// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Konuş, dinliyorum";
			link.l1 = "Yanılmışım. Hoşça kal.";
			link.l1.go = "Exit";
			/* //--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "jailskiper")
			{
				link.l1 = "Memur bey, hapishanenizde Folke Deluc adında bir adam olduğunu duydum. Onun serbest bırakılması için yapabileceğim bir şey var mı?";
                link.l1.go = "Sharlie";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "freeskiper")
			{
				link.l1 = "Subay, yine Folke Deluc adlı mahkum için geldim. Borcunun haklarını satın aldım ve bu adamın serbest bırakılıp bana teslim edilmesini istiyorum. İşte borç belgeleri, buyurun bakın.";
                link.l1.go = "Sharlie_3";
			}	
			//<-- Бремя гасконца */
			
			//--> Миниквест "Делюк" (Делюк снова попал в тюрьму)
			if (CheckAttribute(pchar, "questTemp.Del_Deluck"))
			{
				link.l1 = "İyi günler, subayım. Mürettebatımdan biri hakkında bilgi almak istiyorum...";
                link.l1.go = "Del_Deluck";
			}
			if (CheckAttribute(pchar, "questTemp.Del_DeluckSvoboda"))
			{
				link.l1 = "İşte belgeler, şimdi adamımı serbest bırak.";
                link.l1.go = "Del_DeluckSvoboda";
			}
			//<-- Миниквест "Делюк"
		break;
		
		//--> Бремя гасконца
		case "Sharlie":
			DelLandQuestMark(npchar);
			dialog.text = "Ah, o denizci mi? Bankacımızdan hatırı sayılır bir miktar borç aldı, geri ödemedi ve kaçmaya bile kalkıştı. Ama hemen yakalandı. O zamandan beri tutuklu ve borcunu ödeyene kadar burada kalacak.";
			link.l1 = "Hm. Peki bunu hapiste kalırken nasıl yapacak?";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			dialog.text = "Umurumda değil, monsieur.";
			link.l1 = "Komikmiş... Peki bu zavallı ruhun ne kadar borcu var?";
			link.l1.go = "Sharlie_2";
		break;
		
		case "Sharlie_2":
			dialog.text = "Bilmiyorum. Bankacıya sor, sana ayrıntıları anlatacaktır.";
			link.l1 = "Anladım. Bilgi için teşekkürler, memur.";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "bankskiper";
			LocatorReloadEnterDisable("Fortfrance_town", "reload8_back", false);
			AddLandQuestMark(characterFromId("FortFrance_usurer"), "questmarkmain");
		break;
		
		case "Sharlie_3":
			Log_Info("You have given debt papers");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "letter_open", 1);
			DelLandQuestMark(npchar);
			dialog.text = "Hm. Hepsi doğru. O mahkumu gerçekten serbest bırakmamı istiyor musunuz?";
			link.l1 = "Evet. Borcunu ödemesi için ona ihtiyacım var ve bunu nasıl yapabileceğini biliyorum.";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			dialog.text = "Pekâlâ, seni reddetmem için bir sebebim yok. Deluc yakında buraya getirilecek. Ama seni uyarmam gerek, bu tilki ilk fırsatta kaçacaktır, o yüzden onun hakkında fazla hayal kurma.";
			link.l1 = "Anladım, memur bey. Şimdi borçlumu almak istiyorum.";
			link.l1.go = "Sharlie_5";
		break;
		
		case "Sharlie_5":
			dialog.text = "Evet, elbette. Çavuş! Mahkumu getir! Folke Deluc, anlaşılan artık yeni bir efendisi var!";
			link.l1 = "...";
			link.l1.go = "Sharlie_6";
		break;
		
		case "Sharlie_6":
			DialogExit();
			// создаем штурмана
			sld = InitFolke("Folke", "Deluc");
			pchar.questTemp.Sharlie = "takeskiper";	
			ForceHeroAutolevel(sld);
			AddDialogExitQuestFunction("Del_Turma");
		break;
		//<-- Бремя гасконца
		
		//--> Миниквест "Делюк" (Делюк снова попал в тюрьму)
		case "Del_Deluck":
			DelLandQuestMark(npchar);
			dialog.text = "Ha! Şunu söyleyeyim, başınıza gelenler hakkında yapılan dedikodular Saint-Pierre’i uzun süre oyalayacak. Ama kişisel algılamayın, Kaptan. Belli ki talihsizliğin kurbanısınız. Buyurun içeri, endişelenmeyin: seyrüseferciniz bu konuşmadan kaçamayacak, ha ha!";
			link.l1 = "Çok komik. Teşekkürler, memur.";
            link.l1.go = "exit";
			AddDialogExitQuestFunction("Del_prison");
		break;
		
		case "Del_DeluckSvoboda":
			dialog.text = "Anlaşıldı, Kaptan. Buna göre hareket edeceğiz.";
			link.l1 = "...";
			link.l1.go = "Del_DeluckSvoboda_2";
			Log_Info("You have given debt papers");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "letter_open", 1);
			DelLandQuestMark(npchar);
		break;
		
		case "Del_DeluckSvoboda_2":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Del_DeluckSvoboda");
			
			sld = CharacterFromID("Folke");
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "Del_Folke_10";
			
			AddDialogExitQuestFunction("Del_Turma");
		break;
		//<-- Миниквест "Делюк"
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
