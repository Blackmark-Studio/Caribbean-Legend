// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Beszélj, hallgatlak.";
			link.l1 = "Tévedtem. Viszontlátásra.";
			link.l1.go = "Exit";
			/* //--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "jailskiper")
			{
				link.l1 = "Biztos úr, úgy hallottam, hogy van egy Folke Deluc nevû férfi a börtönében. Tehetek valamit, hogy kiszabadítsam?";
                link.l1.go = "Sharlie";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "freeskiper")
			{
				link.l1 = "Biztos úr, ismét én vagyok az, Folke Deluc fogolyról van szó. Megvásároltam az adósságát, és azt akarom, hogy engedjék szabadon és adják át nekem. Itt vannak az adósságpapírjai, nézze meg.";
                link.l1.go = "Sharlie_3";
			}	
			//<-- Бремя гасконца */
			
			//--> Миниквест "Делюк" (Делюк снова попал в тюрьму)
			if (CheckAttribute(pchar, "questTemp.Del_Deluck"))
			{
				link.l1 = "Jó napot, biztos úr! A legénységemrôl szeretnék érdeklôdni...";
                link.l1.go = "Del_Deluck";
			}
			if (CheckAttribute(pchar, "questTemp.Del_DeluckSvoboda"))
			{
				link.l1 = "Itt vannak a papírok, engedje el az emberemet.";
                link.l1.go = "Del_DeluckSvoboda";
			}
			//<-- Миниквест "Делюк"
		break;
		
		//--> Бремя гасконца
		case "Sharlie":
			DelLandQuestMark(npchar);
			dialog.text = "Ah, az a tengerész? Jelentôs összeget adott kölcsön a bankárunktól, nem adta vissza, és még meg is próbált megszökni. De hamar megtalálták. Azóta le van tartóztatva, és itt marad, amíg vissza nem fizeti az adósságát.";
			link.l1 = "Hm. És hogyan fogja ezt megtenni, amíg börtönben van?";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			dialog.text = "Nem érdekel, uram.";
			link.l1 = "Vicces... És mennyivel tartozik ez a szerencsétlen?";
			link.l1.go = "Sharlie_2";
		break;
		
		case "Sharlie_2":
			dialog.text = "Nem tudom. Kérdezze meg a bankárt, és ô majd megmondja a részleteket.";
			link.l1 = "Értem. Köszönöm az információt, biztos úr.";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "bankskiper";
			LocatorReloadEnterDisable("Fortfrance_town", "reload8_back", false);
			AddLandQuestMark(characterFromId("FortFrance_usurer"), "questmarkmain");
		break;
		
		case "Sharlie_3":
			Log_Info("Adósságpapírokat adtál");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "letter_open", 1);
			DelLandQuestMark(npchar);
			dialog.text = "Hm. Mindegyiküknek igaza van. Tényleg azt akarja, hogy elengedjem a foglyot?";
			link.l1 = "Igen. Szükségem van rá, hogy visszafizesse az adósságát, és tudom, hogyan teheti ezt meg.";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			dialog.text = "Rendben, nincs okom visszautasítani. Deluc-ot hamarosan idehozzák. De figyelmeztetnem kell, hogy ez a róka az elsô adandó alkalommal el fog szökni, úgyhogy ne legyenek illúzióid vele kapcsolatban.";
			link.l1 = "Értettem, biztos úr. És most el akarom vinni az adósomat.";
			link.l1.go = "Sharlie_5";
		break;
		
		case "Sharlie_5":
			dialog.text = "Igen, persze. Ôrmester! Hozza elô a foglyot! Folke Deluc, úgy tûnik, új gazdája van!";
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
			dialog.text = "Ha! Mondom, a pletykák a helyzetedrôl sokáig fogják Saint-Pierre-t szórakoztatni. De ne vegye magára, kapitány. Ön egyértelmûen a balszerencse áldozata. Jöjjön be, és ne aggódjon: a navigátora nem fogja megúszni ezt a beszélgetést, ha-ha!";
			link.l1 = "Fergeteges. Köszönöm, tiszt úr.";
            link.l1.go = "exit";
			AddDialogExitQuestFunction("Del_prison");
		break;
		
		case "Del_DeluckSvoboda":
			dialog.text = "Értettem, kapitány. Ennek megfelelôen fogunk eljárni.";
			link.l1 = "...";
			link.l1.go = "Del_DeluckSvoboda_2";
			Log_Info("Adósságpapírokat adtál");
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
