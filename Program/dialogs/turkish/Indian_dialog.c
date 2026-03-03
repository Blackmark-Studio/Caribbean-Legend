// диалог индейцев в поселениях
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Konuşacak hiçbir şeyimiz yok!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		// ==> индейцы в поселении
		case "IndianMan":
			NextDiag.TempNode = "IndianMan";
			dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Solgun surat","Beyaz kadın")+" konuşmak mı istiyor?","Yine sen, "+GetSexPhrase("Beyaz Surat","Beyaz kadın")+".",""+GetSexPhrase("Solgun suratlı konuşmayı seviyor. Bir de kadın gibi görünüyor.","Beyaz kadın konuşmayı seviyor.")+"","Ruhlar solgun yüzümü buraya getirdi "+GetSexPhrase("kardeşim","kız kardeş")+" bana.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Evet.","Evet, yine ben.","Çok şiirsel.","Seni gördüğüme ben de sevindim.",npchar,Dialog.CurrentNode);
			link.l1.go = "IndPearlMan_1";
		break;
		
		case "IndPearlMan_1":
			dialog.text = "Söylesene, neden geldin, solgun yüz?";
			link.l1 = "Ah, özel bir şey yok, sadece ne söyleyeceğini duymak istedim...";
			link.l1.go = "exit";
		break;
		
		case "IndianWoman":
			NextDiag.TempNode = "IndianWoman";
			dialog.text = NPCStringReactionRepeat("Beyaz adam konuşmak mı istiyor?","Yine sen, solgun surat?","Solgun surat konuşmayı sever.","Ruhlar, solgun yüzlü kardeşimi bana getirdi.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Evet.","Evet, yine ben.","Çok şiirsel.","Seni görmekten ben de memnunum.",npchar,Dialog.CurrentNode);
			link.l1.go = "IndianWoman_1";
		break;
		
		case "IndianWoman_1":
			dialog.text = LinkRandPhrase(""+npchar.name+" seni dinliyorum, denizin oğlu.","Senden ne istiyorsun "+npchar.name+", soluk suratlı?","Sözlerinizi dinlemeye hazırım, yabancı.");
			if (CheckIndianGift() && !CheckAttribute(npchar, "quest.gift"))
			{
				link.l1 = LinkRandPhrase("Sana verecek bir şeyim var. Bakmak ister misin?","Gerçekten ilginç bir şeye bakmak ister misin? Eminim hoşuna gidecek...","Seni memnun edecek bir şeyim var, ormanın çocuğu. Göz atmak ister misin?");
				link.l1.go = "gift";
			}
			link.l9 = "Ah, özel bir şey yok, sadece ne söyleyeceğini duymak istedim...";
			link.l9.go = "exit";
		break;
		
		case "gift":
			iTemp = 2;
			dialog.text = RandPhraseSimple(""+npchar.name+"   bakmak istiyor. Göster.",""+npchar.name+" ilgileniyor. Göster bana.");
			if (CheckCharacterItem(pchar, "mineral6"))
			{
				link.l1 = "Bana bir ayna ver.";
				link.l1.go = "gift_1";
			}
			for (i=50; i>=47; i--)
			{
				if (CheckCharacterItem(pchar, "jewelry"+i))
				{
					sTemp = "l"+iTemp;
					link.(sTemp) = "Give"+XI_ConvertString("jewelry"+i)+".";
					link.(sTemp).go = "gift_"+i;
					iTemp++;				
				}
			}
		break;
		
		case "gift_1":
			RemoveItems(pchar, "mineral6", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Oh! Şimdi "+npchar.name+" kendine sadece nehirdeki suda bakmak zorunda değilmiş! Teşekkürler, iyi yürekli yabancı!";
			link.l1 = "Tabii, artık yüzünü dilediğin kadar hayranlıkla izleyebilirsin...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_47":
			RemoveItems(pchar, "jewelry47", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Ah! Ne kadar güzel! Bu bilezik   "+npchar.name+"? Teşekkür ederim, iyi yürekli yabancı!";
			link.l1 = "Bunu esmer eline tak, güzelim, harika görüneceksin...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_48":
			RemoveItems(pchar, "jewelry48", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Ah! Ne kadar güzel bir yüzük! Bu   "+npchar.name+", evet mi? Teşekkür ederim, iyi yürekli yabancı!";
			link.l1 = "Bunu parmağına tak, tüm arkadaşların kıskanacak...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_49":
			RemoveItems(pchar, "jewelry49", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Ah! O güzel yeşil boncuklar   "+npchar.name+"? Ne kadar güzel! Teşekkür ederim, iyi yürekli yabancı!";
			link.l1 = "Boynunu onlarla süsle, selvanın kızı. Herkes sana hayran kalacak...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_50":
			RemoveItems(pchar, "jewelry50", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Ah, ne kadar güzel bir yeşil yüzük! Bu bir hediye mi "+npchar.name+"? Teşekkür ederim, iyi yürekli yabancı!";
			link.l1 = "Elinde harika duracak, güzelim...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_exit":
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Women")) // Addon 2016-1 Jason Пиратская линейка
			{
				dialog.text = "Sormak istiyordum "+npchar.name+" Bir şey mi var, denizin oğlu?";
				link.l1 = "Haklısın, güzelim. Ben ve korkusuz savaşçılarım ormana, dağlar arasındaki İspanyol yerleşimine gidiyoruz ve bir rehber arıyoruz. Hem o adama hem de eşine cömert olacağım. Çok zenginliğim var: güzel tüfekler, sihirli gözlükler, aynalar, kolyeler, bilezikler ve yüzükler. Belki de aradığımız rehber senin kocandır?";
				link.l1.go = "hayamee";
			}
			else
			{
				DialogExit();
			}
			ChangeIndianRelation(1.00);
			npchar.quest.gift = true;
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		// Кумвана, вождь деревни араваков
		case "cumvana":
			dialog.text = "Denizin oğlu, selamlar. Ben Kumwana, Locono halkının Kaplumbağa klanının reisiyim. Köyüme hangi iş için geldin?";
			if (GetCharacterFreeItem(pchar, "pistol5") > 0 || CheckCharacterItem(pchar, "compass1") || GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l1 = "Sana bir hediye getirdim, reis. Bir bak, hoşuna gidecek.";
				link.l1.go = "cumvana_2";
			}
			else 
			{
				link.l1 = "Reis, yardımınızı istemeye geldim. Merida adında bir İspanyol yerleşimine ulaşmak istiyorum. Sizin selvanızdaki dağların arasında bulunuyor, ama sorun şu ki oraya nasıl gideceğimi bilmiyorum.";
				link.l1.go = "cumvana_no";
			}
			DelLandQuestMark(npchar);
		break;
		
		case "cumvana_no":
			dialog.text = "Bu senin için çok iyi, denizin oğlu, oraya giden yolu bilmemek. O yol ormandan geçer, korkusuz Capong kabilesinin topraklarından. Onlar gerçek jaguarlar, oh-ey! Ben asla o İspanyol yerine gitmem. Benim halkım - barışçıl insanlar, Capong topraklarına gitmeyiz. Kumwana sana tavsiye veremez. Yol çok tehlikeli.";
			link.l1 = "Ama İspanyollar oraya bir yol buldu! Ve o İspanyol horozlarından korkacak değilim...";
			link.l1.go = "cumvana_no_1";
		break;
		
		case "cumvana_no_1":
			dialog.text = "Ama yapmalısın. Onlar zalim insanlar. Ormanda benim birçok insanımı öldürdüler. Kumwana her şeyi anlattı.";
			link.l1 = "Vay kahretsin...";
			link.l1.go = "cumvana_no_2";
		break;
		
		case "cumvana_no_2":
			DialogExit();
			AddQuestRecord("Roger_5", "5");
			npchar.dialog.currentnode = "cumvana_1";
		break;
		
		case "cumvana_1":
			dialog.text = "Oh-ey! Yine sen, denizin oğlu. Kumwana'ya ne söylemek istiyorsun?";
			if (GetCharacterFreeItem(pchar, "pistol5") > 0 || CheckCharacterItem(pchar, "compass1") || GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l1 = "Sana bir hediye getirdim, reis. Bir bak, hoşuna gidecek.";
				link.l1.go = "cumvana_2";
			}
			else 
			{
				link.l1 = "Merida'yı bulma umudum hâlâ içimde...";
				link.l1.go = "cumvana_1_1";
			}
		break;
		
		case "cumvana_1_1":
			DialogExit();
			npchar.dialog.currentnode = "cumvana_1";
		break;
		
		case "cumvana_2":
			dialog.text = "Locono her zaman iyi dostlarını görmekten mutluluk duyar.";
			if (GetCharacterFreeItem(pchar, "pistol5") > 0)
			{
				link.l1 = "Bir tabanca hediye et."; // 5
				link.l1.go = "cumvana_2_1";
			}
			if (CheckCharacterItem(pchar, "compass1")) // 3
			{
				link.l2 = "Bir pusula hediye et.";
				link.l2.go = "cumvana_2_2";
			}
			if (GetCharacterFreeItem(pchar, "spyglass1") > 0)
			{
				link.l3 = "Ucuz bir dürbünü hediye olarak ver.";
				link.l3.go = "cumvana_2_3";
			}
			if (GetCharacterFreeItem(pchar, "spyglass2") > 0)
			{
				link.l4 = "Sıradan bir dürbünü hediye et."; // 2
				link.l4.go = "cumvana_2_4";
			}
			if (GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l5 = "Doğru düzgün bir dürbün ver."; // 4
				link.l5.go = "cumvana_2_5";
			}
		break;
		
		case "cumvana_2_1":
			Log_Info("You have given a pistol");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "pistol5", 1);
			GiveItem2Character(pchar, "obereg_9");
			GiveItem2Character(pchar, "indian_7");
			GiveItem2Character(pchar, "obereg_3");
			dialog.text = "Oh-ey! Ne güzel bir soluk yüzlü silah! Kumwana hediyeni kabul ediyor! Sen de, denizin oğlu, Kumwana ve Locono halkından bir hediye kabul et.";
			link.l1 = "Teşekkürler, şef!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_2":
			Log_Info("You have given a compass");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "compass1", 1);
			GiveItem2Character(pchar, "indian_10");
			GiveItem2Character(pchar, "indian_6");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = "Oh-ey! Soluk yüzlülerin sihirli tılsımı! Kumwana hediyeni kabul ediyor! Sen de, denizin oğlu, Kumwana ve Locono halkından bir hediye kabul et.";
			link.l1 = "Teşekkür ederim, reis!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_3":
			Log_Info("You have given a cheap spy glass");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass1", 1);
			GiveItem2Character(pchar, "obereg_2");
			GiveItem2Character(pchar, "indian_5");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = "Oh-ey! Soluk yüzlülerin sihirli borusu! Kumwana hediyeni kabul ediyor! Sen de, denizin oğlu, Kumwana ve Locono halkından bir hediye kabul et.";
			link.l1 = "Teşekkürler, şef!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_4":
			Log_Info("You have given a common spy glass");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass2", 1);
			GiveItem2Character(pchar, "obereg_6");
			GiveItem2Character(pchar, "indian_6");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = "Oh-ey! Soluk yüzlülerin sihirli borusu! Kumwana hediyeni kabul ediyor! Sen de, denizin oğlu, Kumwana ve Locono halkından bir hediye kabul et.";
			link.l1 = "Teşekkür ederim, şef!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_5":
			Log_Info("You have given a decent spy glass");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass3", 1);
			GiveItem2Character(pchar, "obereg_9");
			GiveItem2Character(pchar, "indian_7");
			GiveItem2Character(pchar, "obereg_5");
			dialog.text = "Oh-ey! Soluk yüzlülerin sihirli borusu! Kumwana hediyeni kabul ediyor! Sen de, denizin oğlu, Kumwana ve Locono halkından bir hediye kabul et.";
			link.l1 = "Teşekkür ederim, reis!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_3":
			dialog.text = "Denizin oğlu, köyümüze seni ne getirdi?";
			link.l1 = "Chief, I've come to ask for your assistance. I want to reach a Spanish settlement called Merida; it's located among the mountains in your selva. The problem is, I don't know how to get there. Perhaps you could provide me with a brave warrior who could show us the way?";
			link.l1.go = "cumvana_4";
		break;
		
		case "cumvana_4":
			dialog.text = "Oh-ey! Tehlikeli yol, tehlikeli. Oraya giden yol, korkusuz Capong kabilesinin ormanından geçer. Gerçek jaguarlar onlar, oh-ey! Ben o İspanyol yerine hiç gitmem. Benim halkım - barışçıl insanlar, Capong'un topraklarına gitmeyiz biz.";
			link.l1 = "Gerçekten Merida'ya gitmem gerekiyor. Kumwana, lütfen adamlarına sor, belki birisi birliğime katılmayı kabul eder? Benim savaşçılarım tecrübeli, iyi silahlanmış ve hiçbir şeyden, şeytandan bile korkmazlar. Rehberi koruyacağız ve iş bitince onu cömertçe ödüllendireceğiz.";
			link.l1.go = "cumvana_5";
		break;
		
		case "cumvana_5":
			dialog.text = "Pekâlâ, denizin oğlu. Bir grup savaşçı toplayıp onlara dileklerinden bahsedeceğim. Şafaktan sonra yarın yanıma gel.";
			link.l1 = "Teşekkürler, şef!";
			link.l1.go = "cumvana_6";
		break;
		
		case "cumvana_6":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_SetStayType(pchar);
			npchar.dialog.currentnode = "cumvana_7";
			//AddQuestRecord("Roger_5", "6");
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			SetLaunchFrameFormParam("The next day...", "Mtraxx_MeridaVozhdDialog", 0, 4.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 1, 0, 0);
			RecalculateJumpTable();
		break;
		
		case "cumvana_7":
			dialog.text = "Oh-ey! Yine sen, denizin oğlu. Kumwana'ya ne söylemek istiyorsun?";
			link.l1 = "Henüz bir şey yok, şef.";
			link.l1.go = "cumvana_7x";
			if(CheckAttribute(pchar,"questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "merida_hayamee")
			{
				link.l2 = " Dinle, Kumwana. Benim halkım ve ben nehrin karşısına geçip şu lanet küçük kasabaya ulaşmak zorundayız. Bunun bizim için ne kadar hayati olduğunu sana açıklamama izin ver.";
				link.l2.go = "cumvana_hard";
			}
		break;
		
		case "cumvana_hard":
			dialog.text = "Avcılarım sana zaten haber verdi...";
			link.l1 = "Tekrar etmene gerek yok, Kumwana. Ama dışarıya bak – ve yeteneklerini fazla abartma. Buraya İspanyol taşları için gelen cesur adamlarım köyünün dört bir yanına dağılmış durumda. Ve sabırları tükenmek üzere. Sonunda tamamen tükendiğinde ne olacağını bilmesen senin için daha iyi olur – bana inan.";
			link.l1.go = "cumvana_medium_1";
			link.l2 = "Çeneni kapa ve dinle, kızıl tenli maymun. Benim halkım bu lanet Kaponglardan çok daha korkutucu olabilir. Şu anki nezaketimize aldanma. Sana basit bir seçenek sunuyorum: ya yirmi dört saat içinde bir rehber bulursun, ya da hepinizin ellerini bağlayıp mangamızın önünde ormana yollarız. Bizi yanlış yöne götürürsen, ya bataklıklarda kendin geberirsin ya da ellerin bağlı halde Kaponglarla dövüşmeye gidersin. Anladın mı?";
			link.l2.go = "cumvana_hard_1";
			link.l3 = "Kumwana, bu rehbere ihtiyacım var. Uzun bir yol geldik ve adamlarıma her şeyin boşuna olduğunu söylemek istemiyorum.";
			link.l3.go = "cumvana_good_1";
			pchar.questTemp.Mtraxx_MeridaZapugivanieIndeets = true;
		break;
		
		case "cumvana_good_1":
			dialog.text = "Kumwana zaten söyledi, Lokono'lardan hiçbiri soluk benizliyle gitmek istemiyor.";
			link.l1 = "Ve sen hiçbir şey yapamıyor musun? Birine bizzat sor. Sonuçta bir emir ver. Sonuçta başkan sen misin, değil misin?";
			link.l1.go = "cumvana_good_2";
		break;
		
		case "cumvana_good_2":
			dialog.text = "Şef, yerlilere zorla bir şey yaptırmaz. Şef yönetir ve halkı için huzur ister. Yerliler bilir ki - Kapong, Lokono'nun beyazları getirdiğini görecek. Kafalarını Kanaima alacak. Onlar Lokono'dan intikam almaya geliyor. Kapong - öldürmek için. Lokono'yu yakala, köle yap.";
			link.l1 = "Ve kafalarınızı kim aldı? Hangi ruh ya da iblis, yerlileri bu kadar korkak ve aşağılık yaptı? Belki de gerçekten Merida'ya karşı yürüttüğüm seferden vazgeçmem gerekecek. Ama bir şeyi unutma, reis. Bana Lokonolar hakkında ne bildiğim sorulduğunda, her defasında aynı cevabı vereceğim: Onlar değersiz korkaklardan oluşan bir kabile. Kendi halkı kadar korkak ve dar görüşlü bir hükümdar tarafından yönetiliyorlar; Kapongları hatırladığında yüzü dehşetle buruşuyor. Yerliler arasında şan kazanamayacaksın, biz beyazlar arasında da saygı göremeyeceksin.";
			link.l1.go = "cumvana_good_3";
		break;
		
		case "cumvana_good_3":
			dialog.text = "Solgun yüz, Kızılderililerin geleneklerini bilmiyor...";
			link.l1 = "Kızılderililerin kime korkak, kime cesur savaşçı dediğini bilecek kadar çok şey biliyorum. Elveda, Kumwana. Ve sözlerimi unutma. Sen korkak ve dar görüşlü bir yöneticisin.";
			link.l1.go = "cumvana_good_4";
		break;
		
		case "cumvana_good_4":
			DialogExit();
			ChangeIndianRelation(5.00);
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Women")) DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			pchar.questTemp.Mtraxx = "fail";
			
			pchar.quest.Mtraxx_MeridaHayameeGoodDialog.win_condition.l1 = "location";
			pchar.quest.Mtraxx_MeridaHayameeGoodDialog.win_condition.l1.location = "Locono_village";
			pchar.quest.Mtraxx_MeridaHayameeGoodDialog.function = "Mtraxx_MeridaHayameeGoodDialog";
		break;
		
		case "cumvana_medium_1":
			dialog.text = "Neden bana böyle tehditler savuruyorsun? Biz seni iyi biri olarak görüyoruz...";
			link.l1 = "Ben iyiyim, sen işbirliği yaptığın sürece, anladın mı? Sana bir gün veriyorum. Ve bana güven, adamlarım ne emredersem yapar. Biz daha güçlüyüz. Ve eğer şüphe ediyorsan... Karını gördüm. Kızlarını da. Sanırım mesajı aldın artık.";
			link.l1.go = "cumvana_hard_2";
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;
		
		case "cumvana_hard_1":
			dialog.text = "Neden bana böyle tehditler savuruyorsun? Biz seni iyi biri sanıyorduk...";
			link.l1 = "Ben iyiyim, yeter ki iş birliği yap. Anladın mı? Sana bir gün veriyorum. Ve bana güven, adamlarım ne emredersem yapar. Biz daha güçlüyüz. Şüphen varsa... Karını gördüm. Kızlarını da. Sanırım şimdi mesajı aldın.";
			link.l1.go = "cumvana_hard_2";
		break;
		
		case "cumvana_hard_2":
			dialog.text = "Kumwana anladı, solgun yüz. Köyde Tagofa adında bir avcı var. Belki seni yerleşkeye götürebilir...";
			link.l1 = "Yirmi dört saat içinde döneceğim. Charlie Prince'in ekleyecek başka bir şeyi yok, vahşi.";
			link.l1.go = "cumvana_hard_3";
		break;
		
		case "cumvana_hard_3":
			DialogExit();
			ref Hayam = characterFromId("Hayamee");
			ChangeCharacterAddressGroup(Hayam, "none", "", "");
			Hayam.lifeday = 0;
			pchar.questTemp.Mtraxx = "merida_hayamee_hard";
			npchar.dialog.currentnode = "cumvana_7";
			SetFunctionTimerCondition("Mtraxx_MeridaHayameeHardTagofaWait", 0, 0, 1, false);
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Women")) DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			ChangeCharacterComplexReputation(pchar, "nobility", -80);
			ChangeOfficersLoyality("bad", 5);
			ChangeIndianRelation(-50.0);
			//log_Info("The attitude of the Indians has decreased");
			AddQuestRecord("Roger_5", "8a");
			pchar.GenQuest.CannotWait = true; //запретить отдыхать
			
			pchar.quest.Mtraxx_MeridaHayameeHardLepriconDialog.win_condition.l1 = "location";
			pchar.quest.Mtraxx_MeridaHayameeHardLepriconDialog.win_condition.l1.location = "Locono_village";
			pchar.quest.Mtraxx_MeridaHayameeHardLepriconDialog.function = "Mtraxx_MeridaHayameeHardLepriconDialog";
		break;
		
		case "cumvana_7x":
			DialogExit();
			npchar.dialog.currentnode = "cumvana_7";
		break;
		
		case "cumvana_8":
			dialog.text = "Denizin oğlu, sensin bu. Kumwana, Locono savaşçılarıyla konuştu.";
			link.l1 = "Peki? Gönüllü olan var mı?";
			link.l1.go = "cumvana_9";
		break;
		
		case "cumvana_9":
			dialog.text = "Oralarda bulunmuş birkaç avcımız var. Ama Capong'lardan korkuyorlar, jaguarlar savaş yolunda. Gitmeyeceklerini söylüyorlar, Capong birliğini öldürür diyorlar. Soluk yüzlülerden korkmuyorlar.";
			link.l1 = "Savaşçılarım onların hepsinden çok daha üstün! Birliğimin bir kısmı ömrünü ormanda geçirdi! Biz sıradan acemiler değiliz!";
			link.l1.go = "cumvana_10";
		break;
		
		case "cumvana_10":
			dialog.text = "Üzgünüm, denizin oğlu. Avcılarım korkuyor, Caponglar çok, çok tehlikeli.";
			link.l1 = "Pekâlâ, o zaman oraya nasıl gidileceğini ayrıntılı olarak anlatabilirler mi?";
			link.l1.go = "cumvana_11";
		break;
		
		case "cumvana_11":
			dialog.text = "Oraya gitmek için nehir boyunca ilerleyip belirli bir noktada karaya çıkmalısın. Yanlış yeri seçersen bataklığa saplanır ve ölürsün. Selvamız tehlikelerle doludur. Orayı kendi başına bulamazsın, denizin oğlu.";
			link.l1 = RandSwear()+"Peki, o zaman ne yapmalıyım? Avcılarını nasıl ikna edebilirim?";
			link.l1.go = "cumvana_12";
		break;
		
		case "cumvana_12":
			dialog.text = "Kumwana, daha fazla söyleme, denizin oğlu.";
			link.l1 = "Peki...";
			link.l1.go = "cumvana_13";
		break;
		
		case "cumvana_13":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetPlayerType(pchar);
			npchar.dialog.currentnode = "cumvana_7";
			AddQuestRecord("Roger_5", "7");
			pchar.questTemp.Mtraxx = "merida_advice";
			LAi_SetHuberType(npchar);
			AddLandQuestMark(characterFromId("Lepricon"), "questmarkmain");
		break;
		
		// Хайами
		case "hayamee":
			if (npchar.id == "Hayamee")
			{
				dialog.text = "Kocam Tagofa, kabilenin en iyi avcısıdır. Oh-ey! "+npchar.name+" kocasıyla gurur duyuyor. "+npchar.name+" sık sık Tagofa ile Selva'ya gider. Uzaklara giderler. Tagofa, İspanyol yerleşiminin nerede olduğunu bilir.";
				if (IsCharacterPerkOn(pchar, "Trustworthy") && stf(pchar.questTemp.Indian.relation) >= 40.0)
				{
					link.l1 = "Tagofa, soluk yüzlülerin Merida dediği İspanyol şehrinin yolunu biliyor mu?";
					link.l1.go = "hayamee_1";
				}
				else
				{
					link.l1 = "Pekâlâ, pekâlâ... Tagofa İspanyol şehrine nasıl gidileceğini biliyor mu?";
					link.l1.go = "hayamee_bad_1";
				}
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = RandPhraseSimple(RandPhraseSimple("Kocam selva'ya gitmez, denizin oğlu. Balık tutar. İyi balıkçı, oh-ey! ","Kocam iyi bir avcıdır, oh-ey, ama ormanın derinliklerine gitmez."),RandPhraseSimple("Bir jaguar avdayken kocamı yaraladı. Şimdi köyde oturup ok yapıyor, ah-hey!","Altı ay önce, üç Capong kocama saldırdı. Şimdi köyden uzağa avlanmaya gitmiyor. Asla! Oh-ey!"));
				link.l1 = LinkRandPhrase("Yazık...","Ne yazık...","Ne yazık..."));
				link.l1.go = "exit";
			}
		break;
		
		case "hayamee_bad_1":
			dialog.text = "Tagofa bu ormanda büyüdü. Etrafındaki her ağacı ve her taşı bilir!";
			link.l1 = "Sizi ve Tagofa'yı oraya götürürse size birçok hediye vereceğim. Mücevherler, silahlar, ne isterseniz. Tabii ki makul olan her şeyi, haha. Kocanızla nasıl konuşabilirim?";
			link.l1.go = "hayamee_bad_2";
		break;
		
		case "hayamee_bad_2":
			dialog.text = "Tagofa soluk yüzlüyle gitmeyecek. Tagofa köyde kalacak. Avlanmaya git. Kapong'la kavga etme.";
			link.l1 = "O, Kapong'larla savaşmak zorunda kalmayacak. Onları görür görmez saklanabilir. Sadece benim adamlarım savaşacak.";
			link.l1.go = "hayamee_bad_3";
		break;
		
		case "hayamee_bad_3":
			dialog.text = "Hayır, yalanaui. Soluk yüzlü asla sözünde durmaz. Soluk yüzlü konuşur – ve sözü hemen havaya uçar, kaybolur. Kapong önce Tagofa'yı öldürecek, sonra köyümüze gelip Lokono'yu öldürecek.";
			link.l1 = "Sence endişelenmen gereken tek şey bu Kaponglar mı? Çok yanılıyorsun...";
			link.l1.go = "hayamee_bad_4";
			if (stf(pchar.questTemp.Indian.relation) < 40.0) notification("The Indians don't respect you "+stf(pchar.questTemp.Indian.relation)+"/40", "None");
			if (!IsCharacterPerkOn(pchar, "Trustworthy")) Notification_Perk(false, "Trustworthy");
		break;
		
		case "hayamee_bad_4":
			dialog.text = "Yahahu, soluk yüzlülerin arasına girecek! Hayami artık yalanaui ile konuşmayacak.";
			link.l1 = "Pekâlâ, pekâlâ...";
			link.l1.go = "hayamee_bad_5";
		break;
		
		case "hayamee_bad_5":
			DialogExit();
			pchar.questTemp.Mtraxx = "merida_hayamee";
			DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			LAi_CharacterDisableDialog(npchar);
		break;
		case "hayamee_1":
			dialog.text = "Tagofa went hunting a day ago. Promised to come back tomorrow when the sun sleeps. Come tomorrow, son of the sea, I will be with Tagofa in that hut; as you walk into the village, walk to the right. I will ask him if he will go or not go with you.";
			link.l1 = "Tagofa'ya en güzel tabancayı hediye edeceğimi söyle. Sana ise bir sürü mücevher hediye edeceğim.";
link.l1.go = "hayamee_1_1";
		break;
		
		case "hayamee_1_1":
			dialog.text = "Lokono, Yalanaui'ye güvenmez. Yalanaui, Hintliyi kandırır, Hintliyi köle yapar. Ama Lokono senin adını duydu, beyaz yüz. Sana güveniyorum. Yarın gün batımından sonra gel, denizin oğlu. O kulübede Tagofa ile olacağım. Ona, seninle gidip gitmeyeceğini soracağım.";
			link.l1 = "Tagofa'ya en iyi tabancamı vereceğimi söyle. Ve senin için de birçok mücevherim var.";
			link.l1.go = "hayamee_2";
			notification("The Indians respect you "+stf(pchar.questTemp.Indian.relation)+"/40", "None");
			Notification_Perk(true, "Trustworthy");
		break;
		
		case "hayamee_2":
			dialog.text = "Oh-ey!";
			link.l1 = "...";
			link.l1.go = "hayamee_3";
		break;
		
		case "hayamee_3":
			DialogExit();
			AddQuestRecord("Roger_5", "9");
			DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			LAi_CharacterDisableDialog(npchar);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.hour  = 22.0;
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.function = "Mtraxx_MeridaHayameeTimer";
		break;
		
		case "hayamee_4":
			pchar.quest.Mtraxx_MeridaPotionLate.over = "yes";
			dialog.text = ""+npchar.name+" denizlerin oğlunu görmekten memnun. Tagofa geri döndü. Ama çok fazla kasheeri içti ve şimdi uyuyor. Onu uyandırma, Tagofa dinleniyor. Ben konuşacağım.";
			link.l1 = "Pekala, "+npchar.name+" . Kocanız bizi Merida'ya götürecek mi?";
			link.l1.go = "hayamee_5";
		break;
		
		case "hayamee_5":
			dialog.text = "Tagofa, savaşçılarını selva boyunca İspanyol köyüne götürmeyi kabul etti. Ama bazı şartları var...";
			link.l1 = "Hangileri?";
			link.l1.go = "hayamee_6";
		break;
		
		case "hayamee_6":
			dialog.text = "Sen Tagofa'yı Capong savaşçılarından koruyorsun. Tagofa ne İspanyollarla ne de Caponglarla savaşır. Tehlikeyle karşılaşırsa hemen kaçar, kimse onu bulamaz, o en iyi Locono avcısıdır.";
			link.l1 = "Anlıyorum. Adamın için endişeleniyorsun, bu gayet normal. Sana söz veriyorum, o Caponglarla kendimiz ilgileneceğiz.";
			link.l1.go = "hayamee_7";
		break;
		
		case "hayamee_7":
			dialog.text = "Oh-ey! Tagofa denizin oğlundan hediyeler istiyor: biri küçük, çok taş atan, diğeri büyük, bir taş atan, güzel olanlardan. Ayrıca, her silah için mermi istiyor: iki elin parmakları kadar, üç katı.";
			link.l1 = "Vay canına! Adamın silahlar konusunda bir şeyler biliyor, ha? Pekâlâ. Başka ne var?";
			link.l1.go = "hayamee_8";
		break;
		
		case "hayamee_8":
			dialog.text = "Ve Tagofa, soluk yüzlülerden güzel bir sihirli göz istiyor.";
			link.l1 = "Dürbün mü? Peki. Başka bir şey?";
			link.l1.go = "hayamee_9";
		break;
		
		case "hayamee_9":
			dialog.text = "Tagofa için artık yok. "+npchar.name+"Güzel şeyler istiyor. Büyük kırmızı taşlı bir altın yüzük ve çok, çok sayıda yeşil taştan yapılmış boncuklar. "+npchar.name+"Maracaibo'da White Mary'de gördüm.";
			link.l1 = "Yakut ve yeşim boncuklu altın bir yüzük mü?";
			link.l1.go = "hayamee_10";
		break;
		
		case "hayamee_10":
			dialog.text = "Yeşim değil. Parlak ve beyaz, beyaz adamlar buna değer verir.";
			link.l1 = "Zümrüt mü? Zümrüt boncuklar mı?";
			link.l1.go = "hayamee_11";
		break;
		
		case "hayamee_11":
			dialog.text = "Oh-ey!";
			link.l1 = "Heh, "+npchar.name+"Mücevherler hakkında bir şeyler biliyor! Pekâlâ, alacaksın.";
			link.l1.go = "hayamee_12";
		break;
		
		case "hayamee_12":
			dialog.text = "Her şeyi getir "+npchar.name+" birlikte, denizin oğlu. Sonra Tagofa seni ve savaşçılarını yönlendirecek. Zaman kaybetme, yarım ay sonra Tagofa ve ben komşu köye gideceğiz. Büyük bir gün için. Şimdi git, "+npchar.name+" uyumak istiyor.";
			link.l1 = "Seni fazla bekletmeyeceğim. Görüşürüz.";
			link.l1.go = "hayamee_13";
		break;
		
		case "hayamee_13":
			DialogExit();
			AddQuestRecord("Roger_5", "10");
			LAi_CharacterDisableDialog(npchar);
			SetFunctionTimerCondition("Mtraxx_MeridaHayameeLate", 0, 0, 15, false); // таймер
			// Тагофу в сидячее положение
			pchar.quest.mtraxx_merida_wait2.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.hour  = 9.0;
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.function = "Mtraxx_MeridaTagofaHide";
		break;
		
		case "hayamee_14":
			bOk = GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0;
			dialog.text = "Ne getirdin "+npchar.name+" ve Tagofa sordu mu?";
			if (bOk && GetCharacterFreeItem(pchar, "pistol3") > 0 && GetCharacterFreeItem(pchar, "pistol5") > 0 && GetCharacterItem(pchar, "bullet") >= 30 && GetCharacterItem(pchar, "grapeshot") >= 30 && GetCharacterItem(pchar, "gunpowder") >= 60 && CheckCharacterItem(pchar, "jewelry41") && CheckCharacterItem(pchar, "jewelry42"))
			{
				link.l1 = "Evet. Her şey listenizdeki gibi.";
				link.l1.go = "hayamee_15";
			}
			else
			{
				link.l1 = "Hayır, hâlâ üzerinde çalışıyorum.";
				link.l1.go = "hayamee_14x";
			}
		break;
		
		case "hayamee_14x":
			DialogExit();
			npchar.dialog.currentnode = "hayamee_14";
		break;
		
		case "hayamee_15":
			pchar.quest.Mtraxx_MeridaHayameeLate.over = "yes";
			Mtraxx_MeridaRemoveGifts();
			dialog.text = ""+npchar.name+" mutlusun, denizin oğlu. Artık sana koca diyorum. O seninle gidiyor. Ama ne söz verdiğini unutma "+npchar.name+"!";
			link.l1 = "Evet, evet, her şeyi hatırlıyorum. Onu güvende tutacağım, merak etme.";
			link.l1.go = "hayamee_16";
		break;
		
		case "hayamee_16":
			DialogExit();
			pchar.questTemp.Mtraxx = "merida_hayamee_peace";
			chrDisableReloadToLocation = true;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 7.0);
			DoQuestFunctionDelay("Mtraxx_MeridaTagofaEnter", 20.0);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
			
		case "CitizenNotBlade":
			dialog.text = "Silahını indir, solgun surat, yoksa biz indiririz!";
			link.l1 = LinkRandPhrase("Pekala.","Pekala.","Merak etme, kaldırıyorum...");
			link.l1.go = "exit";
		break;  

	}
}
