// Санчо Карпентеро - бармен
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Defol! Sokaklarda masum insanlara saldıran alçaklara hizmet etmem!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = ""+pchar.name+" ! Seni gördüğüme çok sevindim! Biliyordum – biliyordum! – söylentiler doğru değildi! Kahretsin, gel benimle bir içki iç!";
				link.l1 = "Hadi içelim, Sancho! Seni gördüğüme ben de gerçekten çok sevindim!";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			// пей до дна
			if (CheckAttribute(npchar, "quest.drink") && npchar.quest.drink == "fail")
			{
				dialog.text = ""+pchar.name+", kaybettiğine üzüldüm. O şişman adamla içki yarışında çok az kişi galip gelebiliyor. Başın nasıl?";
				link.l1 = "Sen... sen bayağı sert bir rom veriyorsun, Sancho. İçkiler için sana borçlandım... ne kadar?";
				link.l1.go = "drunk_fail";
				break;
			}
			if (CheckAttribute(npchar, "quest.drink") && npchar.quest.drink == "win")
			{
				dialog.text = "Fazio'yu yendin, "+pchar.name+"! Şaşkına döndüm! Onu içkiyle alt eden bir ya da iki kişi olmuştur bugüne kadar. Al, işte iki yüz dublonun.";
				link.l1 = "Güzel sözlerin için teşekkür ederim, Sancho!";
				link.l1.go = "drunk_win";
				break;
			}
			// крабовый салат
			if (CheckAttribute(npchar, "quest.crab") && npchar.quest.crab == "begin")
			{
				dialog.text = ""+pchar.name+"? O Narval tamircisinin yaptığı bir dalış kıyafetiyle dibe daldığını söylüyorlar. Doğru mu?";
				link.l1 = "Doğru, dostum. Denizin dibini gördüm ben!";
				link.l1.go = "crab";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Selamlar! Meyhanemde yeni bir yüz görmek her zaman güzel! Hoş geldin! Burada her zaman iyi içki bulursun – Avrupa şarabıyla ağzına kadar doluyuz!\nAma yemek için aynı şeyi söyleyemem. Ha... şaka yapıyorum. Benim adım Sancho Carpentero, burası da bana ait.";
				link.l1 = TimeGreeting()+", Sancho. Benim adım "+GetFullName(pchar)+". Tanıştığımıza memnun oldum.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, dostum "+pchar.name+"! Sizi görmek ne güzel! Ne alırsınız?";
				// квестовые ветки
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_1" && !CheckAttribute(npchar, "quest.mushket"))
				{
					link.l6 = "Dinle Sancho, iyi bir tüfek nereden bulabilirim biliyor musun? Sıradan bir piyade tüfeği değil, daha isabetli ve uzun menzilli bir şey - belki av için.";
					link.l6.go = "mushket";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_2")
				{
					link.l6 = "Dinle Sancho, sana birkaç sorum olacak. Adolf Barbier adında bir adamı arıyorum. Onun sık sık burada içtiğini duydum...";
					link.l6.go = "adolf";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "barmen_whiskey")
				{
					link.l6 = "Dinle Sancho, Chad Kapper'ın senden biraz arsenik aldığı söyleniyor...";
					link.l6.go = "whiskey";
				}
				if (CheckCharacterItem(pchar, "talisman1") && CheckAttribute(npchar, "quest.rat"))
				{
					link.l7 = "Sancho, sana bir şey göstermek istiyorum. Bu, ele geçirmeye çalıştığın yarasa maskesi mi?";
					link.l7.go = "rat";
				}
				if (CheckCharacterItem(pchar, "talisman1") && CheckAttribute(npchar, "quest.ratmoney") && PCharDublonsTotal() >= 1)
				{
					if (PCharDublonsTotal() >= sti(npchar.quest.ratmoney))
					{
						if(!CheckAttribute(npchar, "quest.ratmoneyagain")) ChangeCharacterComplexReputation(pchar, "fame", 5);
						link.l7 = "Sancho, zırhımı almaya geldim. İşte paran.";
						link.l7.go = "rat_3";
					}
					else
					{
						npchar.quest.ratmoneyagain = true;
						link.l7 = "Sancho, zırhımı almaya geldim. İşte paran.";
						link.l7.go = "rat_take_money_not_all";
					}
				}
				if (makeint(pchar.money) >= 25)
				{
					link.l1 = "Bana biraz rom koy, Sancho.";
					link.l1.go = "drink";
				}
				if (makeint(pchar.money) >= 20)
				{
					link.l2 = "Bir oda kiralamak istiyorum.";
					link.l2.go = "room";
				}
				if (stf(environment.time) >= 6.0 && stf(environment.time) <= 18.0 && makeint(pchar.money) >= 300)
				{
					link.l9 = "Sıkıldım, Sancho. Akşam olana kadar burada bir şişe şarapla vakit geçirmek istiyorum...";
					link.l9.go = "drink_sit";
				}
				link.l3 = LinkRandPhrase("Bu günlerde insanlar ne konuşuyor, Sancho?","Son zamanlarda adada neler oluyor?","Dedikodu var mı?");
				link.l3.go = "rumours_LSC";
				if (CheckAttribute(npchar, "quest.crab") && npchar.quest.crab == "current" && CheckCharacterItem(pchar, "crab_pincers"))
				{
					link.l10 = "Sana satacak yengeç pençelerim var, Sancho.";
					link.l10.go = "crab_trade";
				}
				link.l4 = "Sancho, sana ada hakkında bir şey sormak istiyorum.";
				link.l4.go = "int_quests"; //информационный блок
				link.l5 = "Hayır dostum. Sadece nasıl olduğunu görmek istedim. Hoşça kal!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Ben de öyleyim. Umarım seni her akşam en az bir kez görürüm, ha-ha! Meyhanemde yeni bir misafirim olduğu için gerçekten çok mutluyum.";
			if (makeint(pchar.money) >= 25)
			{
				link.l1 = "Bana biraz rom koy, Sancho.";
				link.l1.go = "drink";
			}
			if (makeint(pchar.money) >= 20)
			{
				link.l2 = "Bir oda kiralamak istiyorum.";
				link.l2.go = "room";
			}
			link.l3 = "Sancho, sana ada hakkında bir şey sormak istiyorum.";
			link.l3.go = "int_quests"; //информационный блок
			link.l4 = "Görüşürüz, Sancho!";
			link.l4.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "mushket":
			dialog.text = "Hayır dostum, sana yardımcı olamam. Benim uzmanlık alanım bira ve şarap, tüfekler değil, ha-ha! Dükkâna git, Axel'in bazen ilginç silahlar sattığını duydum. Aradığını orada bulabilirsin.";
			link.l1 = " Tavsiyen için teşekkürler. ";
			link.l1.go = "exit";
			npchar.quest.mushket = "true";
		break;
		
		case "adolf":
			dialog.text = "Adolf? Evet, arada bir uğrar bana, ama birkaç gündür görmedim onu. O şişman adam Giuseppe ile konuştuktan beri ortalarda yok.";
			link.l1 = "Giuseppe... Giuseppe Fazio'yu mu kastediyorsun?";
			link.l1.go = "adolf_1";
		break;
		
		case "adolf_1":
			dialog.text = "Adada sadece bir Giuseppe var. Evet, o. Birkaç saat oturdular, bir şişe rom paylaştılar ve oldukça hararetli bir sohbet ettiler.";
			link.l1 = "Tartışıyorlar mıydı?";
			link.l1.go = "adolf_2";
		break;
		
		case "adolf_2":
			dialog.text = "Hayır. Eski dostlar gibi konuştular. Bak, Caroline'deki Fazio'ya uğra ve ona sor.";
			link.l1 = "Pekala, bunu yapacağım.";
			link.l1.go = "adolf_3";
		break;
		
		case "adolf_3":
			dialog.text = "Hepsi bu mu? Birkaç sorunuz olduğunu söylemiştiniz...";
			link.l1 = "Evet. Söylesene, kim bu Kızıl Mary ve Marcello Cyclops?";
			link.l1.go = "adolf_4";
		break;
		
		case "adolf_4":
			dialog.text = "Red Mary is one of the Narwhals. Beautiful young girl, but absolutely wild. She wields her blade and a handgun as good as any man. Used to be the girlfriend of Alan Milrow, a former leader of the Narwhal clan, before the Admiral killed him\nAlan's death hit her hard. She spends her days crying and cursing Shark in her cabin on the Ceres... But she will get over it; life goes on, after all.\nI don't know much about Marcello, only seen him a couple of times. Scary fellow. They say he used to be a royal hunter, lost an eye in a fight, and went sailing on a merchantman as a mercenary - spent his days at sea repelling hostile boarding actions.\nUnsurprisingly... he hates pirates.";
			link.l1 = "Anladım... Çok teşekkürler Sancho, bana gerçekten çok yardımcı oldun.";
			link.l1.go = "adolf_5";
		break;
		
		case "adolf_5":
			dialog.text = "Rica ederim, dostum. Yine uğra, birlikte biraz bira içeriz.";
			link.l1 = "Tabii!";
			link.l1.go = "adolf_6";
		break;
		
		case "adolf_6":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "search_mush_3"; //флаг на Джузеппе
			AddQuestRecord("SharkHunt", "13");
		break;
		
		// виски для Акулы
		case "whiskey":
			dialog.text = "Kapper mı? Hayır. Son zamanlarda meyhaneye uğramadı. Marcello Cyclops on beş dakika önce bir şişe arsenik aldı – demek ki onun da başı farelerle dertte. Çok iyi anlıyorum... şu lanet fareler.";
			link.l1 = " Kiklop buradaydı mı?! ";
			link.l1.go = "whiskey_1";
		break;
		
		case "whiskey_1":
			dialog.text = "Evet, öyle. Neden?";
			link.l1 = "Onu birkaç gündür arıyorum. Nereye gittiğini biliyor musun?";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "Adolf Barbier ile birlikteydi, o Santa Florentina'da yaşıyor. Belki de oraya gitmişlerdir?";
			link.l1 = "Teşekkürler!";
			link.l1.go = "whiskey_3";
		break;
		
		case "whiskey_3":
			dialog.text = "Eğer biraz arsenik istersen, bir şişesini yirmi dublona satabilirim--!";
			link.l1 = "Sonra konuşuruz Sancho, hoşça kal!";
			link.l1.go = "whiskey_4";
		break;
		
		case "whiskey_4":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "whiskey_poison"; // флаг - виски травят
			AddQuestRecord("SharkHunt", "37");
			sld = CharacterFromID("LSC_Adolf");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "SantaFlorentinaShipInside4", "goto", "goto2");
			sld = CharacterFromID("Dodson");
			sld.dialog.currentnode = "whiskey"; // ноду Акуле
			// важный момент! От дальнейшего поведения геймера зависит результат
			pchar.quest.LSC_Whiskeypoison_SF.win_condition.l1 = "location";
			pchar.quest.LSC_Whiskeypoison_SF.win_condition.l1.location = "SantaFlorentinaShipInside4";
			pchar.quest.LSC_Whiskeypoison_SF.function = "LSC_WhiskeyPoison_SF"; // прерывание на Санта-Флорентину
			pchar.quest.LSC_Whiskeypoison_AE.win_condition.l1 = "location";
			pchar.quest.LSC_Whiskeypoison_AE.win_condition.l1.location = "AvaShipInside3";
			pchar.quest.LSC_Whiskeypoison_AE.function = "LSC_WhiskeyPoison_AE"; // прерывание на Эву
			pchar.quest.LSC_Whiskeypoison_exit.win_condition.l1 = "location";
			pchar.quest.LSC_Whiskeypoison_exit.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_Whiskeypoison_exit.function = "LSC_Whiskeypoison_exit"; // прерывание на выход из таверны
			// закрываем вход к Фацио
			LocatorReloadEnterDisable("LostShipsCity_town", "reload20", true);
			LocatorReloadEnterDisable("LostShipsCity_town", "reload24", true);
		break;
		
		// пей до дна
		case "drunk_fail":
			dialog.text = "Hadi ama dostum, bana hiçbir borcun yok.  Zaten yüz dublon kaybettin. Fazio'yla içki yarışına kalkışırsan olacağı bu...";
			if (sti(pchar.money) >= 500)
			{
				link.l1 = "Hayır, hayır, Sancho, lütfen! Al şu beş yüz peso. Bildiğim kadarıyla bu içkilerin parasını karşılar. Sana borçlu kalmak istemiyorum.";
				AddMoneyToCharacter(pchar, -500);
			}
			else link.l1 = "Eh.. sağ ol, Sancho. Haklısın.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.drink");
		break;
		
		case "drunk_win":
			DialogExit();
			TakeNItems(pchar, "gold_dublon", 200);
			Log_Info("You have received 200 doubloons");
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "quest.drink");
		break;
		
		// крабовый салат
		case "crab":
			dialog.text = "Hm... o zaman sana bir teklifim var. Aşağıda dev yengeçler gördün mü?";
			link.l1 = "Şaka mı yapıyorsun? Onlardan sürüler vardı! Ne düşünüyordun?";
			link.l1.go = "crab_1";
		break;
		
		case "crab_1":
			dialog.text = "Eğer onlardan herhangi birini öldürürsen, pençelerini mutlaka bana getir. Sana iyi bir ödeme yaparım: her biri için beş dublon! Axel Yost bu kadar ödeme yapmaz, emin olabilirsin.\nSana özellikle avlanmanı söylemiyorum... ama olur da bir iki tanesini öldürürsen, teklifimi unutma lütfen...";
			link.l1 = "Neden pençeler? Yengecin diğer kısımları ne olacak?";
			link.l1.go = "crab_2";
		break;
		
		case "crab_2":
			dialog.text = "Çünkü etin çoğu kıskaçlarında olur. Yengeçlerin bacaklarında fazla et yoktur ve gövdeleri sert bir kabukla kaplıdır. Yengeç eti burada bir lezzet sayılır. Nefis bir tadı vardır ve çok besleyicidir!\nBunun için özel bir tarifim var, bu yüzden her kıskaç için sana beş dublon ödeyeceğim.";
			link.l1 = "Pekâlâ, bunu aklımda tutacağım...";
			link.l1.go = "crab_3";
		break;
		
		case "crab_3":
			DialogExit();
			npchar.quest.crab = "current";
		break;
		
		case "crab_trade":
			iTotalTemp = GetCharacterItem(pchar, "crab_pincers")
			dialog.text = "Harika! Kaç tane var?";
			link.l1 = ""+FindRussianQtyString(iTotalTemp)+".";
			link.l1.go = "crab_trade_1";
			link.l2 = "Fikrimi değiştirdim.";
			link.l2.go = "exit";
		break;
		
		case "crab_trade_1":
			dialog.text = "Pekala. Al, işte doblonların - "+FindRussianQtyString(iTotalTemp*5)+"Sağ ol dostum, eğer daha bulursan bana getir.";
			link.l1 = "Tabii, dostum.";
			link.l1.go = "crab_trade_2";
		break;
		
		case "crab_trade_2":
			DialogExit();
			RemoveItems(pchar, "crab_pincers", iTotalTemp);
			TakeNItems(pchar, "gold_dublon", iTotalTemp*5);
			PlaySound("interface\important_item.wav");
			Log_Info("You have received "+iTotalTemp*5+" doubloons");
		break;
		
		// крыс
		case "rat":
			dialog.text = "Ne?! Göster bana! Bakayım şuna!";
			link.l1 = "Pekala, pekala, ha-ha!";
			link.l1.go = "rat_1";
		break;
		
		case "rat_1":
			PlaySound("interface\important_item.wav");
			dialog.text = "Bu... bu işte! Denizcinin bana çizdiği resimdekinin aynısı!\nDostum... bunu bana satar mısın?";
			link.l1 = "Bu duruma bağlı. Bildiğim kadarıyla, bunun için bir servet vaat etmiştin.";
			link.l1.go = "rat_2";
			link.l2 = "Üzgünüm dostum, bu satılık değil. Gemim için lazım. Sadece gerçekten bahsettiğin tılsımın bu olup olmadığını doğrulamanı istedim.";
			link.l2.go = "rat_exit";
		break;
		
		case "rat_exit":
			PlaySound("interface\important_item.wav");
			dialog.text = "Eh, ne yazık... Evet dostum, işte o tılsım bu. Şanslı adam! Artık fareler için asla endişelenmene gerek yok! Ben ise onları zehirle öldürmeye devam edeceğim...";
			link.l1 = "Üzgünüm, Sancho, sana umut verdim. Bu şeyin nasıl göründüğünden emin değildim, o yüzden emin olmam gerekiyordu. Kusura bakma.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.rat");
		break;
		
		case "rat_2":
			dialog.text = "Bunun için,"+pchar.name+",   sana...  sana sahip olduğum en değerli ve en kaliteli eşyayı satın alma fırsatı sunacağım! Hemen getiriyorum...\nBak bakalım. İşte karşında eşsiz, göz alıcı bir Milano Göğüslüğü, ustalıkla işlenmiş! Savaşta olağanüstü koruma sağlar, hareket kabiliyetini kısıtlamaz, hafif ve rahattır. Bu kalitede bir zırh hem Karayipler'de hem de Avrupa'da son derece nadirdir.\nBu göğüslüğü birkaç yıl önce bir İspanyol savaş gemisinin kaptan kamarasında tesadüfen buldum ve tam da böyle bir fırsat için sakladım. Sana iki bin altın sikke ve Sıçan Tanrısı karşılığında satmaya hazırım!";
			link.l1 = "Hmm... Bu gerçekten de usta işi bir zırh! Bu takas bana gayet uygun. Farelerle baş etmenin birçok yolu var, ama böyle bir zırhı bir daha bulmak neredeyse imkânsız olurdu. Daha önce hiç böylesini görmemiştim. Gerçekten de eşsiz bir parça.";
			link.l1.go = "rat_yes";
			link.l2 = "Ne kadar mı dedin?! Sancho, senin farelerin bu sabah seni birkaç kez ısırdı mı yoksa? İki bin mi dedin? Bu putu bulmak için neler çektiğimi biliyor musun sen?! Şu fiyatı hemen indir!";
			link.l2.go = "rat_torg";
			link.l3 = "Ne kadar?! Sen tam bir fırsatçı balıksın, biliyor musun Sancho? 'Satın alma fırsatı sunmak' ha! Bu parayla anakarada kendime kurşun geçirmez, suda yürüyebileceğim bir zırh yaptırırım! Peki sen bu kadar altını ne yapacaksın, Jurgen’e kendinin heykelini döktürüp San Agustine’in güvertesine mi koyduracaksın?";
			link.l3.go = "rat_no";
		break;
		
		case "rat_yes":
			dialog.text = "Sana katıldığın için memnunum, dostum. Sorunumu unutmadığın için teşekkürler! O halde, doblonlarımı bekliyor olacağım. Zırhın seni bekliyor olacak!";
			link.l1 = "Kısa süre içinde onları getireceğim!";
			link.l1.go = "rat_yes_1";
		break;
		
		case "rat_yes_1":
			DialogExit();
			DeleteAttribute(npchar, "quest.rat");
			npchar.quest.ratmoney = 2000;
		break;
		
		case "rat_torg":
			if(GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 60)
			{
				Notification_Skill(false, 60, SKILL_COMMERCE);
				dialog.text = ""+pchar.name+", under different circumstances, I would demand five thousand. The Admiral himself has shown interest - and he is not the only one, believe me. But take your time deciding; the armor will be waiting for you for as long as you need. I'll only sell it to you.";
				link.l1 = "Düşüneceğim, Sancho.";
				link.l1.go = "rat_yes_1";
				AddCharacterExpToSkill(pchar, "Commerce", 400);
			}
			else
			{
				Notification_Skill(true, 60, SKILL_COMMERCE);
				dialog.text = ""+pchar.name+"Farklı koşullarda, beş bin isterdim. Amiral'in kendisi bile ilgi gösterdi – ve inanın, o tek değil.\nPekâlâ, siz beni ve derdimi unutmadığınız için beş yüz düşeyim. Kolay bir macera olmamış olmalı.";
				link.l1 = "Bu daha iyi... ama hâlâ neden bu kadar eşsiz eşyaları takas ederken fazladan ödemem gerektiğini anlamıyorum. Belki de bana ödeme yapması gereken sensin, ha Sancho, he-he?";
				link.l1.go = "rat_yes_1500";
				AddCharacterExpToSkill(pchar, "Commerce", 100);
			}
		break;
		
		case "rat_yes_1500":
			if(GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 90)
			{
				Notification_Skill(false, 90, SKILL_COMMERCE);
				dialog.text = "Hayır, "+pchar.name+", hiç şansın yok. Farelerle arsenik kullanarak başa çıkabilirim, ama bu zırh bir gün hayatını kurtarabilir. Üstelik bunu giyince bir İtalyan dükü gibi görüneceksin! Bin beş yüz, son fiyatım bu. Düşünmek için vaktin var, bana haber verirsin. Zırh seni bekliyor olacak, ne kadar istersen beklerim, sadece sana satacağım.";
				link.l1 = "Sancho, eğer bu kasvetli mezarlıkta başka bir meyhaneci olsaydı... Teklifini düşüneceğim.";
				link.l1.go = "rat_yes_1500exit";
				AddCharacterExpToSkill(pchar, "Commerce", 600);
			}
			else
			{
				Notification_Skill(true, 60, SKILL_COMMERCE);
				dialog.text = "Bir askeri kaptan ve korsan olarak, pazarlık yapmayı gerçekten iyi biliyorsun! Jost'u hatırlıyor musun? Bir keresinde, fareler beni zaten mahvediyorken, tüm arseniklerimi indirimli almayı başarmıştı.\nPekâlâ, "+pchar.name+", kazandın. Senin için beş yüz daha indireceğim! Ama bu son teklifim!";
				link.l1 = "Bu hâlâ biraz kazık gibi geliyor, ama en azından artık ormanda yardıma muhtaç biri gibi hissetmeyeceğim. Bekle beni, parayı yakında getireceğim.";
				link.l1.go = "rat_yes_1000exit";
				AddCharacterExpToSkill(pchar, "Commerce", 200);
			}
		break;
		
		case "rat_no":
			dialog.text = "Sakin ol, "+pchar.name+" . Başkasından olsaydı, beş bin isterdim! Amiralin kendisi bile ilgi gösterdi – ve inanın bana, o tek değil.\nZırhınız sizi bekliyor olacak – bu arada kimseye satmam.";
			link.l1 = "Ne büyük bir onur! Yakında dönerim. İki bin!";
			link.l1.go = "rat_yes_1";
		break;
		
		case "rat_yes_1500exit":
			DialogExit();
			DeleteAttribute(npchar, "quest.rat");
			npchar.quest.ratmoney = 1500;
		break;
		
		case "rat_yes_1000exit":
			Achievment_SetStat(106, 1);
			DialogExit();
			DeleteAttribute(npchar, "quest.rat");
			npchar.quest.ratmoney = 1000;
		break;
		case "rat_3":
			dialog.text = "Bitti! Anlaştığımıza sevindim dostum. Sorunumu unutmadığın için sağ ol! Zırhı al, savaşta sana iyi hizmet etsin.";
			link.l1 = "Al, muskanı yanında tut — anlaşılan, meyhanendeki fareler için kara günler yaklaşıyor, ha-ha!";
			link.l1.go = "rat_4";
		break;
		
		case "rat_4":
			DialogExit();
			GiveItem2Character(pchar, "cirass4");
			RemoveItems(pchar, "talisman1", 1);
			RemoveDublonsFromPCharTotal(sti(npchar.quest.ratmoney));
			Log_Info("You have given away the talisman 'God of rats'");
			Log_Info("You have received a Milanese armor");
			Log_Info("You gave "+FindRussianDublonString(sti(npchar.quest.ratmoney))+"");
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "quest.ratmoney");
			if(CheckAttribute(npchar, "quest.ratmoneyagain"))
				DeleteAttribute(npchar, "quest.ratmoneyagain");
		break;
		
		case "rat_take_money_not_all":
			npchar.quest.ratmoney = sti(npchar.quest.ratmoney) - PCharDublonsTotal();
			Log_Info("You gave "+FindRussianDublonString(PCharDublonsTotal())+"");
			RemoveDublonsFromPCharTotal(PCharDublonsTotal());
			PlaySound("interface\important_item.wav");
			dialog.text = "Hâlâ beni hayran bırakıyorsun "+FindRussianDublonString(sti(npchar.quest.ratmoney))+", "+pchar.name+".";
			link.l1 = "Bana bunu hatırlatma!";
			link.l1.go = "exit";
		break;
		
		//--> информационный блок
		case "int_quests":
			dialog.text = "Dinliyorum, dostum.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Bu ada nedir? Bana biraz daha anlatır mısın?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Adadan nasıl ayrılabilirim?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Adada bilmem gerekenler neler?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = " Peki burada nasıl gidiyor? Meyhanen nasıl? ";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Hiçbir sorum yok, boşver...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "This island? Well, they call it Justice Island, the Island of Justice, or the City of Abandoned Ships - but we just call it the island. It's formed out of shipswrecks, which are stuck on a shoal at the centre of the reefs.\nThis central part of the island is our living space; the outer ring of wrecks is uninhabited. There's been no connection with the outside world for ten years.";
			link.l1 = "İnanılmaz!";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Uzun bir tekne ya da sal yapabilirsin - ama sonun iyi olmaz. Fırtınalar ve güçlü akıntılar adayı çepeçevre sarar, dış halkayı geçersen hayatını riske atarsın.\nHayatta kalmak için en iyi denizcilerden oluşan bir ekibe ihtiyacın olurdu ve buradaki yerlilerin çok azı bu adadan ayrılmak ister. Dış halkayı aşmaya cesaret edenler ise daha da azdır.\nİnsanlar burada yaşamaktan memnun. Bana inanmıyorsan etrafa sor.";
			link.l1 = "Anlıyorum...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Öncelikle, adada birkaç yasak bölge olduğunu unutma. İki klan, Narvaller ve Rivadoslar, burada uzun zamandır yaşıyor; birbirleriyle durmaksızın savaşıyor ve kendi bölgelerini koruyorlar. Davetsiz gidersen, ölüsün demektir.\nOnların topraklarına girmek istiyorsan, güncel parolayı bilmelisin. Yanlışlıkla sınırı geçmekten endişelenme, nöbetçiler ateş açmadan önce sana birkaç kez uyarıda bulunacaklar.";
			link.l1 = "Bunu aklımda tutacağım...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "You know, my friend, it's fine. I'm used to working with food and drink. I served as a cook lots of places in Europe - garrisons, grog houses, ships - so the first thing I did here was establish a tavern.\nI like my job and my life is satisfying. Everybody needs food and drink, and I enjoy serving them. Folks are friendly, here, and mostly peaceful. I can't remember the last time I had to clean up after a drunken brawl. And the clans don't bother me.\nAll in all, this the best place I've had in my life. I'm free here, and no one tells me what to do.\nThe only thing driving me mad is the rats. They torture me; eating my provisions and ruining my tableware. And they're impossible to get rid of.";
			link.l1 = "Ah evet, o küçük veletlerin ne kadar baş belası olduklarını bizzat biliyorum...";
			link.l1.go = "ansewer_4_1";
		break;
		
		case "ansewer_4_1":
			dialog.text = "Seems I'm the most unfortunate person in the city when it comes up to rats. Other ships are not terrorized nearly as badly as my Fleuron. Axel Yost somehow managed to get rid of his rats once and for all, but me, I've got armies of the furry bastards crawling around.\nYou know, I once heard tell of a special amulet called the Rat God. It looks like a bat's face. Supposedly this amulet scares rats away completely.\nMust be how Axel dealt with his rats; he buys and re-sells every piece of garbage people bring him from the outer ring.\nIf someone offered me that amulet, I'd pay a king's ransom for it!";
			link.l1 = "Bunu unutmayacağım...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
			npchar.quest.rat = "true";
		break;
		//<-- информационный блок
		
		//--> выпивка
		case "drink":
			if (CheckAttribute(pchar, "questTemp.Rum") && sti(pchar.questTemp.Rum) > 4)
			{
				dialog.text = ""+pchar.name+", Bence artık yeterince içtin dostum. Allah korusun, soyulursun ya da denize düşüp yengeçlere yem olursun. Burada fazla içmek hiç akıllıca değil, başına iş açabilir.";
				link.l1 = "Hm... Sanırım haklısın, Sancho - hık! - Yeterince içtim. Endişelendiğin için sağ ol.";			
				link.l1.go = "exit";
			}
			else
			{
				AddMoneyToCharacter(pchar, -25);
				if(!IsEquipCharacterByArtefact(pchar, "totem_01"))
				{
					if (CheckAttribute(pchar, "questTemp.Rum"))
					{
						pchar.questTemp.Rum = sti(pchar.questTemp.Rum) + 1;
					}
					else pchar.questTemp.Rum = 1;
				}
				else 
				{
					if(CheckAttribute(pchar, "questTemp.Rum")) DeleteAttribute(pchar, "questTemp.Rum");
				}				
				WaitDate("",0,0,0, 0, 30);
				
				dialog.text = "Rica ederim dostum. En iyi romumdan bir pint sadece yirmi beş peso!";
				link.l1 = RandPhraseSimple(LinkRandPhrase("Sağlığına ve meyhanenin bereketine, dostum!","Tüm deniz insanlarına, nerede olurlarsa olsunlar!","Adalet Adası'nın insanlarına!"),LinkRandPhrase("Adaya, ve umarım sonsuza dek burada kalır!","Rüzgar, hangi rotayı seçersek seçelim, her zaman lehimize essin!","Şansa, mutluluğa... ve kadınlara!"));		
				link.l1.go = "drink_1";
			}
		break;
		
		case "drink_1":
			DialogExit();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.Rum"))
			{
				if (sti(pchar.questTemp.Rum) < 3) LAi_AlcoholSetDrunk(pchar, 51, 5600);
				else LAi_AlcoholSetDrunk(pchar, 71, sti(pchar.questTemp.Rum)*2800);
			}
		break;
		
		case "drink_sit":
			if (chrDisableReloadToLocation || pchar.questTemp.Saga.SharkHunt == "barmen_whiskey" || pchar.questTemp.Saga.SharkHunt == "whiskey_poison") //идёт квест
			{
				dialog.text = "Şu anda içki içmemelisin bence. Bana güven...";
				link.l1 = "Pekala...";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye") || CheckAttribute(pchar, "questTemp.LSC.MaryWait")) // подружился с Мэри
			{
				dialog.text = "Heh, tuhaf bir adamsın... Burada, adada vakit geçirecek birini bulamadın mı? Seni burada yalnız bırakıp içmene izin verirsem Mary beni öldürür. Akşam birlikte gelin, sabaha kadar eğlenin, isterseniz.";
				link.l1 = "İyi fikir!";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = " Sorun değil dostum. Sadece üç yüz peso karşılığında sana güzel bir şişe vereceğim "+LinkRandPhrase("Spanish","Italian","Fransız")+" şarap - ve istediğiniz kadar bir masa.";
				link.l1 = "Teşekkürler!";
				link.l1.go = "drink_sit_1";
			}
		break;
		
		case "drink_sit_1":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = true;
			sld.startLocation = "FleuronTavern";
			sld.startLocator = "bottle";
			DoQuestReloadToLocation("FleuronTavern", "quest", "sit2", "LSC_DrinkSit");
		break;
		//<-- выпивка
		
		//--> сон в таверне
		case "room":
   			if (chrDisableReloadToLocation || pchar.questTemp.Saga.SharkHunt == "barmen_whiskey" || pchar.questTemp.Saga.SharkHunt == "whiskey_poison") //идёт квест
			{
				dialog.text = "Şu anda uyumaman gerektiğini düşünüyorum. Bana güven...";
				link.l1 = "Pekâlâ.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye") || CheckAttribute(pchar, "questTemp.LSC.MaryWait")) // подружился с Мэри
			{
				if(!isDay())
				{
					dialog.text = "Seni anlamıyorum dostum. Ceres'te seni bekleyen güzel bir kız var, ama sen geceyi tek başına meyhanede geçirmek istiyorsun? Buna izin veremem, Mary beni öldürür.";
					link.l1 = "Muhtemelen haklısın...";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "You can rest upstairs until the evening, but I won't let you spend the night here; Mary would kill me. Sorry...";
					link.l1 = "Pekala, akşama kadar burada kalacağım...";
					link.l1.go = "hall_night_wait";
					link.l2 = "Pekâlâ... Uyumadan da idare ederim.";
					link.l2.go = "exit";
				}
				break;
			}
			dialog.text = "Yirmi peso karşılığında, yukarıdaki yatakta uyuyabilirsin. Ne zaman uyandırmamı istersin?";
			if(!isDay())
			{
				link.l1 = "Sabahleyin.";
				link.l1.go = "hall_day_wait";
			}
			else
			{
				link.l1 = "Gece olmadan.";
				link.l1.go = "hall_night_wait";
				link.l2 = "Ertesi sabah.";
				link.l2.go = "hall_day_wait";
			}
			link.l3 = "Fikrimi değiştirdim. Uyumak istemiyorum.";
			link.l3.go = "exit";
		break;
		
		case "hall_night_wait":
			AddMoneyToCharacter(pchar, -20);
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			TavernWaitDate_LSC("wait_night");
		break;
		
		case "hall_day_wait":
			AddMoneyToCharacter(pchar, -20);
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			TavernWaitDate_LSC("wait_day");
		break;
		//<-- сон в таверне
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
