#include "DIALOGS\%language%\Rumours\Common_rumours.c" //Jason
void ProcessDialogEvent()
{
 	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\ItemTrader\" + NPChar.City + "_ItemTrader.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
// ============================================================================
// ============================= блок angry ==========>>>>>>>>>>>>>>>>>>>>>>>>>
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
			
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
// ============================================================================	   
	switch(Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча
  		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;

  		case "First time":
			dialog.text = NPCharSexPhrase(npchar,"Kendiniz ya da subaylarınız için ekipman almak ister misiniz, kaptan? Eğer öyleyse, doğru kişiye geldiniz!","Ah, kaptan, geleceğini biliyordum! Sana ve subaylarına ekipman ve daha pek çok faydalı şey sunabilirim.");
			link.l1 = "Ne göstereceksin, görelim.";
			link.l1.go = "Trade_exit";
			
   			/*link.l2 = "Ben başka bir iş için geldim.";
			link.l2.go = "quests";*/
			// --> Мангароса
			if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "find" && npchar.Merchant.type == "potion" && !CheckAttribute(npchar, "quest.mangarosa"))
			{
				link.l4 = "Hey, yakında ilginç bir bitki buldum. Bana bunun iksir ya da demlik hazırlamak için kullanılıp kullanılamayacağını söyleyebilir misin? Sadece gözüme çarptı. Bir bakabilir misin?";
				link.l4.go = "mangarosa";
			}
			// <-- Мангароса
			

			//Jason --> мини-квест Дефицитный товар
			if (CheckAttribute(pchar, "questTemp.Wine.bottle") && NPChar.location == pchar.questTemp.Wine.City + "_town" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
   				link.l4 = "Bana kaliteli bir Avrupa şarabı satabilir misin?";
				link.l4.go = "Wine_ItemTrader";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.bottles") && NPChar.location == pchar.questTemp.Wine.City + "_town" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
   				link.l4 = "Dinle, Avrupa şarabı sattığını biliyorum. Altmış şişe lazım.";
				link.l4.go = "Wine_Bottles";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.Repeat1") && NPChar.location == pchar.questTemp.Wine.City + "_town" && npchar.id == pchar.questTemp.Wine.ItemTraderID && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
   				link.l4 = "Yine ben geldim. Bütün bunlar ne anlama geliyor, ha?";
				link.l4.go = "Wine_Repeat1";
			}
			// <-- мини-квест Дефицитный товар
			
			//Sinistra --> мини-квест "Знакомство с индейцами"
			if (CheckAttribute(pchar, "questTemp.ZsI_PokupaemPistolety") && npchar.Merchant.type == "armourer")
			{
   				link.l4 = "Yirmi atımlık barut ve mermiyle birlikte iki tabancaya ihtiyacım var.";
				link.l4.go = "ZsI_PokupaemPistolety";
			}
			// <-- мини-квест "Знакомство с индейцами"
			
			// --> Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l4 = "Dinle, 'Juan' ismi sana bir şey ifade ediyor mu?";
				link.l4.go = "Consumption";
			}
			// <-- Цена чахотки
			
			//--> Украденное воспоминание
			if(CheckAttribute(pchar, "questTemp.UV_Lavochniki") && !CheckAttribute(npchar, "quest.UV_Vopros") && npchar.city == "PortPax")
			{
				link.l4 = "İyi tüccar, olağan süslerden fazlasını arıyorum. Çoğunu tatmin eden sıradan takılar değil, gerçek bir zarafetin eseri—belki özenle işlenmiş bir çift küpe ya da aristokrat zevkine layık zarif bir kolye. Soylu bir hanımefendiyi memnun edecek bir hediye istiyorum.";
				link.l4.go = "UV_Lavochniki_1";
			}
			if(CheckAttribute(pchar, "questTemp.UV_Lavochniki_2") && !CheckAttribute(npchar, "quest.UV_Vopros") && npchar.city == "PortPax")
			{
				link.l4 = "Acaba envanterinizde, gerçekten değerli bir şey var mı? En seçici soylu kadının bile beğenisini kazanacak, sıradan halkı etkilemeyecek kadar özgün ve zarif bir parça arıyorum—belki sıradışı bir kolye ucu ya da ince bir bilezik?";
				link.l4.go = "UV_Lavochniki_2";
			}
			if(CheckAttribute(pchar, "questTemp.UV_Lavochniki_3") && !CheckAttribute(npchar, "quest.UV_Vopros") && npchar.city == "PortPax")
			{
				link.l4 = "Bana söyleyin, iyi tüccar, değerli mücevherler konusunda bilginiz var mı? Kaliteli bir hanıma sunmak üzere olağanüstü bir şey arıyorum. Açık konuşayım, sıradan süs eşyalarına hiç ilgim yok. Benim aradığım, gerçekten muhteşem bir parça: belki değerli taşlarla süslenmiş bir broş ya da eşsiz işçiliğe sahip bir yüzük.";
				link.l4.go = "UV_Lavochniki_3";
			}
			//<-- Украденное воспоминание
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l5 = "Dinle, her türlü malı alıp satıyorsun... Dün ya da bugün - sana birisi satmak için geldi mi  "+pchar.GenQuest.Device.Shipyarder.Type+"?";
				link.l5.go = "Device_ItemTrader";
			}
			//<-- генератор Неудачливый вор

			link.l9 = "Teşekkürler, ilgilenmiyorum.";
			link.l9.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Trade_exit":
            if (CheckNPCQuestDate(npchar, "Item_date"))
			{
				SetNPCQuestDate(npchar, "Item_date");
				GiveItemToTrader(npchar);
			}
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchItemsTrade(npchar, 0);
		break;
		
		//Jason --> мини-квест Дефицитный товар
		case "Wine_ItemTrader":
			dialog.text = "Tabii. Şişesi yedi yüz peso.";
			if (makeint(Pchar.money) >= 700)
			{
				link.l1 = "Mükemmel. Parayı al ve bana teslim et.";
				link.l1.go = "Wine_ItemTrader_1";
			}
			link.l2 = "Harika! Satın almaya karar verdiğimde geri geleceğim.";
			link.l2.go = "exit";
		break;
		
		case "Wine_ItemTrader_1":
			dialog.text = "Lütfen, şişenizi alın.";
			link.l1 = "Teşekkür ederim!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -700);
			TakeNItems(pchar, "potionwine", 1);
			PlaySound("interface\important_item.wav");
			DeleteAttribute(pchar, "questTemp.Wine.bottle");
			AddQuestRecord("Wine", "1_1");
			WineTraderQMDel();
		break;
		
		case "Wine_Bottles":
			dialog.text = "Ha! Ben sadece bir perakendeciyim, toptancı değilim. O kadar çok şişeyi satmam yarım yıldan fazla sürerdi – o şarap nadir ve pahalıdır, herkesin alabileceği bir şey değil, biliyorsun. O kadar fazlası elimde yok.";
			link.l1 = "Pekâlâ, sende yokmuş - sorun değil. Ama sonuçta bir yerden buluyorsun, değil mi? Belki tedarikçinin adını söyleyebilirsin, ben de doğrudan ondan alırım. Yoksa şarap sana Avrupa'dan mı geliyor?";
			link.l1.go = "Wine_Bottles_1";
		break;
		
		case "Wine_Bottles_1":
			dialog.text = "Hayır, değil. Buradan alıyorum. Ama tedarikçimin adını öylece vermem. Ama bin peso için... belki, verebilirim...";
			if (makeint(Pchar.money) >= 1000)
            {
				link.l1 = "Pekala. Al bin liranı – şimdi söyle bakalım, tedarikçin kim?";
				link.l1.go = "Wine_Bottles_2";
			}
			link.l2 = "Şimdi siz düzenbazlar iyice yüzsüzleştiniz! Bu size fazla iyi gelmez mi? Tedarikçinize ihtiyacım yok, sağ olun.";
			link.l2.go = "Wine_Bottles_fail";
		break;
		
		case "Wine_Bottles_free":
			dialog.text = "Sanırım... peki öyle olsun. İşte notun, umarım ileride sen de bana bir iyilik yaparsın.";
			link.l1 = "...";
			link.l1.go = "Wine_Bottles_free_1";
		break;
		
		case "Wine_Bottles_free_1":
			pchar.questTemp.Wine.TraderID = pchar.questTemp.Wine.City +"_trader";
			sld = characterFromId(pchar.questTemp.Wine.TraderID);
			pchar.questTemp.Wine.Name = GetFullName(sld);
			pchar.questTemp.Wine.ItemTraderID = npchar.id;
			dialog.text = "Şarap tedarikçimin adı "+pchar.questTemp.Wine.Name+", buradaki dükkânın sahibi.";
			link.l1 = "Anladım! Teşekkürler!";
			link.l1.go = "exit";
			//pchar.questTemp.Wine.Trader = "true";
			DeleteAttribute(pchar, "questTemp.Wine.bottles");
			pchar.questTemp.Wine.Repeat2 = "true";
			TakeNItems(pchar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_1");
			PlaySound("interface\important_item.wav");
		break;
		
		case "Wine_Bottles_2":
    		AddMoneyToCharacter(pchar, -1000);
			pchar.questTemp.Wine.TraderID = pchar.questTemp.Wine.City +"_trader";
			sld = characterFromId(pchar.questTemp.Wine.TraderID);
			AddLandQuestMark(sld, "questmarkmain");
			pchar.questTemp.Wine.Name = GetFullName(sld);
			pchar.questTemp.Wine.ItemTraderID = npchar.id;
			dialog.text = "Şarap tedarikçimin adı "+pchar.questTemp.Wine.Name+", buranın dükkanının sahibi.";
			link.l1 = "Anladım! Teşekkürler!";
			link.l1.go = "exit";
			pchar.questTemp.Wine.Trader = "true";
			DeleteAttribute(pchar, "questTemp.Wine.bottles");
			AddQuestRecord("Wine", "3");
			AddQuestUserData("Wine", "sName", pchar.questTemp.Wine.Name);
			WineTraderQMDel();
		break;
		
		case "Wine_Bottles_fail":
			dialog.text = "Dediğiniz gibi, kaptan. Size en iyisini dilerim.";
			link.l1 = "Görüşürüz.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Wine.bottles");
			AddQuestRecord("Wine", "4");
			WineTraderQMDel();
		break;
		
		case "Wine_Repeat1":
			DeleteAttribute(pchar, "questTemp.Wine.Repeat1");
			dialog.text = "Ne demek istiyorsun? Açıkla kendini.";
			link.l1 = "Beni kandırdın, seni düzenbaz! Az önce dükkandaydım, "+pchar.questTemp.Wine.Name+" asla şarapla iş yapmaz, bunu bana kendisi söyledi! Paramı geri ver!";
			link.l1.go = "Wine_Repeat1_fail";
			link.l2 = "Bir yanlış anlaşılma oldu... Depocuya gittim ve "+pchar.questTemp.Wine.Name+" şarap ticaretiyle hiç uğraşmadığını iddia etti. Bunu nasıl açıklarsın?";
			link.l2.go = "Wine_Repeat1_1";
		break;
		
		case "Wine_Repeat1_1":
			dialog.text = "Heh! Şarap işi yaptığı kesin, hem de lanet olası kesin. Ama öyle herkese şarap satmaz – bazı başka mallarda da aynı durum geçerli. Bunun birkaç sebebi var... Ondan şarap almak istiyorsan, sana bir not yazabilirim. Beni ve el yazımı tanır, notu okuduktan sonra sana o şarabı satar. Tabii, bu iyiliğin de bir bedeli var.";
			link.l1 = "Bu inanılmaz! Benden tam bin altın aldın!";
			link.l1.go = "Wine_Repeat1_2";
		break;
		
		case "Wine_Repeat1_2":
			dialog.text = "Senden bilgi için bin aldım. Mektup için ise ayrıca iki bin peso ödeyeceksin, hem de bundan aşağısı olmaz.";
			if (makeint(Pchar.money) >= 2000)
			{
				link.l1 = "Ah... Siz tüccarlar gerçekten de çok açgözlüsünüz. Sizi kimsenin sevmesine şaşmamalı. Neyse, al paranı, şimdi de notunu yaz.";
				link.l1.go = "Wine_Bottles_3";
			}
			if(CheckCharacterPerk(pchar, "Trustworthy"))
			{
				Notification_Perk(true, "Trustworthy");
				link.l2 = "(Güvenilir) Bir uzlaşmaya varalım. Şimdi bana ücretsiz bir tavsiye ver, ben de sana sonra karşılık olarak ücretsiz bir tavsiye sunayım. Bu şarap anlaşması sadece bir başlangıç.";
				link.l2.go = "Wine_Bottles_free";
			}
			link.l3 = "Now that's completely out of line! I'd rather abandon the whole affair; I will not enrich such a cunning miser. And by that miser I mean you. Farewell.";
			link.l3.go = "Wine_Repeat1_goaway";
		break;
		case "Wine_Bottles_free":
			dialog.text = "Sanırım... peki öyleyse. İşte notun, umarım gelecekte sen de bana aynı şekilde karşılık verirsin.";
			link.l1 = "...";
			link.l1.go = "Wine_Bottles_free_1";
		break;
		
		case "Wine_Bottles_free_1":
			pchar.questTemp.Wine.Repeat2 = "true";
			TakeNItems(pchar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_1");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Wine", "6_1");
			DelLandQuestMark(npchar);
			sld = characterFromId(pchar.questTemp.Wine.TraderID);
			AddLandQuestMark(sld, "questmarkmain");
			DialogExit();
		break;
		
		case "Wine_Bottles_3":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "Sen tuhaf bir kaptansın! Evet, muhasebecinin tüm mali işleri yürüttüğünü biliyorum, ama bazen kendi kafanı da kullanmalısın. Sana, benim komisyonum olmadan toptan iyi bir şarap partisi alma ve güzel bir kâr elde etme fırsatı çıkacak. O yüzden, birbirimizin kazancına engel olmayalım; çünkü şu anda açgözlü görünen sensin.\nPeki... (yazıyor) Al, bu mektubu götür - "+pchar.questTemp.Wine.Name+"  sana şarabı hiçbir soru sormadan satarım.";
			link.l1 = "Umarım öyle olur... Bir şeyler yine ters giderse, geri dönerim. Görüşürüz!";
			link.l1.go = "Wine_Bottles_4";
		break;
		
		case "Wine_Bottles_4":
			pchar.questTemp.Wine.Repeat2 = "true";
			TakeNItems(pchar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_1");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Wine", "6");
			DelLandQuestMark(npchar);
			sld = characterFromId(pchar.questTemp.Wine.TraderID);
			AddLandQuestMark(sld, "questmarkmain");
			DialogExit();
		break;
		
		case "Wine_Repeat1_goaway":
			dialog.text = "Dediğiniz gibi, kaptan. Elveda.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddQuestRecord("Wine", "4");
			DelLandQuestMark(npchar);
		break;
		
		case "Wine_Repeat1_fail":
			dialog.text = "Yani, buraya gelip bana tehditler savurup kaba mı davranacaksın? O zaman muhafızları çağırıyorum! Hey, muhafızlar! Buraya gelin!";
			link.l1 = "Ah, kapa çeneni! Kazandın, gidiyorum! Kahrolası herif "+NPCharSexPhrase(npchar,"","")+", karabatak, mahvolasın!";
			link.l1.go = "exit";
			AddQuestRecord("Wine", "7");
			DelLandQuestMark(npchar);
		break;
		// <-- мини-квест Дефицитный товар
		
		//Sinistra --> мини-квест "Знакомство с индейцами"
		case "ZsI_PokupaemPistolety":
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				dialog.text = "Anladım. Yerlilerle anlaşmalar mı yapıyorsun? Duyduğuma göre bu sana epey pahalıya patlamış, ha ha!";
			}
			else
			{
				dialog.text = "Bir bela mı bekliyorsunuz, Kaptan? Yoksa ormanda bir macera mı planlıyorsunuz? Ha-ha!";
			}
			link.l1 = "Peki, bir anlaşma yapabilir miyiz?";
			link.l1.go = "ZsI_PokupaemPistolety_1";
			DelLandQuestMark(npchar);
		break;
		
		case "ZsI_PokupaemPistolety_1":
			dialog.text = "Elbette! Müşterilerimiz her zaman hoş karşılanır. Üç bin peso karşılığında, istediğiniz gibi güvenilir tabancalar, mermiler ve barut alırsınız.";
			if (sti(pchar.Money) > 2999)
			{
				link.l1 = "Pahalı, ama olsun. Alıyorum.";
				link.l1.go = "ZsI_PokupaemPistolety_2";
			}
			if (sti(pchar.Money) > 2299)
			{
				link.l2 = "Fadey Moskof'un dostuna biraz indirim yapamaz mısın? Bu fiyat haksızca görünüyor.";
				link.l2.go = "ZsI_Torg";
			}
			link.l3 = "Üç bin mi? Bu resmen soygun! Hoşça kalın, Mösyö!";
			link.l3.go = "ZsI_NetDeneg";
		break;
		
		case "ZsI_NetDeneg":
			DialogExit();
			
			LocatorReloadEnterDisable("BasTer_town", "gate_back", false);
			PChar.quest.ZsI_Timer.over = "yes";
			sld = CharacterFromID("ListKakao");
			sld.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.ZsI_PokupaemPistolety");
		break;
		
		case "ZsI_PokupaemPistolety_2":
			dialog.text = "Oralarda iyi şanslar, Kaptan!";
			link.l1 = "Elveda, Mösyö.";
			link.l1.go = "ZsI_PokupaemPistolety_3";
			AddMoneyToCharacter(pchar, -3000);
			Log_info("You have acquired the required pistols for Cocoa Leaf");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "ZsI_PokupaemPistolety_3":
			DialogExit();
			
			LocatorReloadEnterDisable("BasTer_town", "gate_back", false);
			DeleteAttribute(pchar, "questTemp.ZsI_PokupaemPistolety");
			PChar.quest.ZsI_Patrul.win_condition.l1 = "location";
			PChar.quest.ZsI_Patrul.win_condition.l1.location = "BasTer_ExitTown";
			PChar.quest.ZsI_Patrul.win_condition = "ZsI_Patrul";
		break;
		
		case "ZsI_Torg":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) > 18)
			{
				Notification_Skill(true, 19, SKILL_COMMERCE);
				dialog.text = "Elbette, Kaptan. Fadey'nin dostları burada her zaman hoş karşılanır. Hepsi için iki bin üç yüz uygun mu?";
				link.l1 = "Bu kulağa daha iyi geliyor. Kabul ediyorum.";
				link.l1.go = "ZsI_Torg_2";
				AddCharacterExpToSkill(pchar, "Commerce", 30);
			}
			else
			{
				Notification_Skill(false, 19, SKILL_COMMERCE);
				dialog.text = "Monsieur Fadey'nin dostları her zaman hoş karşılanır, ama fiyatların dostu olmaz. Üç bin peso tutar, Kaptan.";
				if (sti(pchar.Money) > 2999)
				{
					link.l1 = "Pahalı, ama tamam. Alıyorum.";
					link.l1.go = "ZsI_PokupaemPistolety_2";
				}
				link.l2 = "Üç bin mi? Bu resmen soygun! Hoşça kalın, Mösyö!";
				link.l2.go = "ZsI_NetDeneg";
				//Log_info("Trading skill is not sufficient");
				AddCharacterExpToSkill(pchar, "Commerce", -30);
			}
		break;
		
		case "ZsI_Torg_2":
			dialog.text = "Oralarda iyi şanslar, Kaptan!";
			link.l1 = "Elveda, Mösyö.";
			link.l1.go = "ZsI_PokupaemPistolety_3";
			AddMoneyToCharacter(pchar, -2300);
			Log_info("You have acquired the required pistols for Cocoa Leaf");
			PlaySound("Interface\important_item.wav");
		break;
		// <-- мини-квест "Знакомство с индейцами"
		
		// --> Цена чахотки
		case "Consumption":
			dialog.text = "Hayır, etmiyor... Şimdi lütfen beni rahatsız etme, oldukça meşgulüm... Ne saçma bir soru...";
			link.l1 = "Anladım. Zamanınızı boşa harcadığım için üzgünüm...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
		// <-- Цена чахотки
		//Jason --> генератор Неудачливый вор
		case "Device_ItemTrader":
			dialog.text = "Hmm, "+pchar.GenQuest.Device.Shipyarder.Type+"? Daha önce hiç duymadım... Aslında nedir bu? Bunca zamandır böyle bir şey duymadım"+NPCharSexPhrase(npchar,"","")+".";
			link.l1 = "Eh, bu bir gemi yapımcısının aleti, "+pchar.GenQuest.Device.Shipyarder.Describe+". Sana böyle bir şey teklif eden oldu mu?";
			link.l1.go = "Device_ItemTrader_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_ItemTrader_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) > 0 && sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 4 && npchar.location.group == "merchant" && npchar.location.locator == "merchant"+sti(pchar.GenQuest.Device.Shipyarder.Chance1))
			{
				dialog.text = "Hmm... Evet, tuhaf bir adam vardı. Ama bana o şeyin ne olduğunu söylemedi, sadece satmaya çalıştı. Ama ne işe yaradığını bilmeden ben onu ne yapayım? Nasıl tekrar satabilirim ki? O yüzden reddettim."+NPCharSexPhrase(npchar,"","")+", ve uzaklaştı";
				link.l1 = "Nasıl biriydi ve nereye gitti? O alete gerçekten ihtiyacım var.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "Hayır, öyle bir şey yok. Üzgünüm, sana yardımcı olamam. Etrafına sor.";
				link.l1 = "Anladım. O zaman, biraz soruşturmanın vakti geldi!";
				link.l1.go = "exit";
			}
		break;
		// <-- генератор Неудачливый вор
		
		// Мангароса
		case "mangarosa":
			// тут работает везение
			if (sti(pchar.questTemp.Mangarosa.m_count) == 5 || GetSummonSkillFromName(pchar, SKILL_FORTUNE) > 10+hrand(30)+hrand(40, "1"))
			{
				dialog.text = "Bana göster... Evet, bu ilginç bir bitki. Hem de çok, çok nadir bulunan bir tür. Adı Manga Rosa. Ne işe yaradığını bilmiyorum ama bununla ilgili ilginç bir bilgi var...";
				link.l1 = "Ne demek istiyorsun?";
				link.l1.go = "mangarosa_1";
			}
			else
			{
				dialog.text = LinkRandPhrase("Bana göster... Evet, bu ilginç bir bitki. Ama ne yazık ki sana bundan fazlasını söyleyemem. Eğer gerçekten bir amaç için kullanılıyorsa, ben bundan habersizim.","Bakalım... Hmm... Şifalı bir bitkiye benziyor, ama hakkında hiçbir şey bilmiyorum. Üzgünüm, sana yardımcı olamam.","Nerede bu? Hmm... Hayır, bunu daha önce hiç görmedim. Gerçekten çok ilginç görünüyor ama ne işe yaradığını hiç bilmiyorum...");
				link.l1 = "Anladım. Pekâlâ, biraz daha soruşturacağım. Üzgünüm.";
				link.l1.go = "mangarosa_exit";
			}
		break;
		
		case "mangarosa_exit":
			DialogExit();
			pchar.questTemp.Mangarosa.m_count = sti(pchar.questTemp.Mangarosa.m_count)+1;
			npchar.quest.mangarosa = "true";
		break;
		
		case "mangarosa_1":
			dialog.text = " Göçebe çingeneler ve vahşiler bu bitkilere büyük ilgi gösteriyor. Bir keresinde bir çingenenin böyle bir dal için avuç dolusu altın ödediğini gördüm. Ama neden ihtiyaç duyduklarını hiç bilmiyorum.";
			link.l1 = "Anladım... Hiç yoktan iyidir! Şimdi bir sonraki soracağım yeri biliyorum. Çok teşekkür ederim!";
			link.l1.go = "mangarosa_2";
		break;
		
		case "mangarosa_2":
			DialogExit();
			npchar.quest.mangarosa = "true";
			DeleteAttribute(pchar, "questTemp.Mangarosa.m_count");
			pchar.questTemp.Mangarosa = "gipsy";
			AddQuestRecord("Mangarosa", "2");
		break;
		
		//--> Украденное воспоминание
		case "UV_Lavochniki_1":
			dialog.text = "Ne yazık ki, "+GetAddress_Form(NPChar)+",   dükkanım aylardır böyle kaliteli mallar görmedi. Bu zor zamanlarda lükse olan iştah azaldı. Dükkanıma gelen sıradan insanlar ancak mütevazı süs eşyalarını alabiliyor, soylular ise nadiren benim mütevazı mallarıma göz atma lütfunda bulunuyor.";
			link.l1 = "Pekala...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.UV_Lavochniki");
			pchar.questTemp.UV_Lavochniki_2 = true;
			npchar.quest.UV_Vopros;
		break;

		case "UV_Lavochniki_2":
			dialog.text = "Ne yazık ki, Kaptan, böylesine nadide parçalar uzun zamandır dükkânıma uğramadı. Bu limanın zengin müşterileri nadiren mütevazı dükkânıma uğrar, düzenli müşterilerim ise ancak cüzdanlarının yettiği kadarını alabilir.";
			link.l1 = "Pekâlâ...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.UV_Lavochniki_2");
			pchar.questTemp.UV_Lavochniki_3 = true;
			npchar.quest.UV_Vopros;
		break;

		case "UV_Lavochniki_3":
			dialog.text = "Ah, Kaptan, tam zamanında geldiniz diyemem... Sadece birkaç saat önce, gerçekten muhteşem bir kolyeyi başka bir varlıklı deniz kaptanına sattım. Mekânımda, en seçici hanımefendinin bile kalbini eritecek mücevherler sıkça bulunur\nBelki yarın tekrar uğrarsınız? Giselle... yani... tedarikçilerim... size hayran olduğunuz kişiyi sonsuza dek kendinize bağlayacak bir hazine bulabilirler.";
			link.l1 = "Time is a luxury I do not possess; I require such a piece without delay. Pray tell, what is the name of this fortunate captain who acquired the necklace you speak of?";
			link.l1.go = "UV_Lavochniki_3_1";
		break;

		case "UV_Lavochniki_3_1":
			dialog.text = "Tristan Renier, 'Altın Martı'nın kaptanı. Gemisi hâlâ limanımızda demirli. Fakat itiraf etmeliyim ki, böyle bir ganimeti bırakmaya razı olur mu, emin değilim. Eğer razı gelmezse, yarın bana tekrar gelin. Şerefim üzerine, Kaptan, bu düzenlemeyi son derece memnuniyet verici bulacaksınız.";
			link.l1 = "...";
			link.l1.go = "UV_Lavochniki_exit";
			DeleteAttribute(pchar, "questTemp.UV_Lavochniki_3");
			AddDialogExitQuestFunction("UV_GoldSeagull");
		break;
		
		case "UV_Lavochniki_exit":
			DialogExit();
			AddQuestRecord("UV", "3");
			/*AddQuestUserData("UV", "sSex", NPCharSexPhrase(NPChar,"ца","ки"));
			AddQuestUserData("UV", "sSex1", NPCharSexPhrase(NPChar,"ец","ка"));
			AddQuestUserData("UV", "sSex2", NPCharSexPhrase(NPChar,"","а"));*/
		break;
		//<-- Украденное воспоминание
		
// ======================== блок нод angry ===============>>>>>>>>>>>>>>>

////////////////////////////////////////////////////////////////////////////////////////////////
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok")
		break;

// <<<<<<<<<<<<============= блок нод angry =============================
	}
}
