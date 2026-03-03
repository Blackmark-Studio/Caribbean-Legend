// лидер клана ривадос - Чёрный Эдди
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Rivados'un topraklarında ne işin var, beyaz adam?";
			link.l1 = "Sadece buradaki insanları tanımaya çalışıyorum. Rahatsız ettiysem kusura bakmayın.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Friend":
			dialog.text = "Rivados'un bir dostunu ve aynı zamanda iyi bir adamı selamlamaktan memnuniyet duyuyorum! Chimiset senin onun için yaptıklarını anlattı. Tüm Rivados, ben de dahil, artık sana borçlu. Kendimi tanıtmama izin ver - Edward Black, namıdiğer Kara Eddie, Rivados çetesinin lideriyim.";
			link.l1 = ""+GetFullName(pchar)+" . Gerçi Chimiset’in sana benden bahsettiğine inanıyorum. Sana anlatacağına söz vermişti...";
			link.l1.go = "Friend_1";
		break;
		
		case "Friend_1":
			dialog.text = "Ve öyle de yaptı. Artık gemilerimizi özgürce ziyaret edebilirsin. Muhafızlar seni durdurmayacak ve seni görmekten memnun olacağız. Narvallara karşı dikkatli ol, muhtemelen Chimiset'i kurtardığını çoktan duymuşlardır ve bundan hoşlanmayacaklardır, çünkü biz düşmanız.";
			link.l1 = "Bunu düşüneceğim. Sıcak karşılaman için teşekkürler, Eddie! Şimdi lütfen, Chimiset ile konuşmama izin ver.";
			link.l1.go = "Friend_2";
		break;
		
		case "Friend_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto1", "LSC_EddyStay", -1);
			AddSimpleRumourCityTip("They say that you are a close friend of Black Eddie, the head of Rivados. How did you do this?", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("Rivados claim you as their friend. How'd you do it?", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("They say that the Narwhals have a price on your head. Are you scared?", "LostShipsCity", 10, 1, "LSC", "");
		break;
		
		// --> информационный блок
		case "Total_info": // стал другом
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Beyaz kardeş mi? Hayatta mısın? Sevindim! Demek ki Narvaller, herkese boğulduğunu söylediklerinde yalan söylemişler...";
				link.l1 = "Seni görmek de beni mutlu etti, Eddie. Ölümümle ilgili söylentiler fazlasıyla abartılmış.";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			dialog.text = "Seni gördüğüme sevindim, "+pchar.name+" . Bir haber var mı?";
			if (!CheckAttribute(npchar, "quest.natan"))
			{
				link.l1 = "Eddie, Nathaniel Hawk adında bir adamı tanıyor musun? Bildiğim kadarıyla burada olmalı.";
				link.l1.go = "natan";
			}
			if (!CheckAttribute(npchar, "quest.rivados"))
			{
				link.l2 = "Bana Rivados çetesi hakkında daha fazla anlat.";
				link.l2.go = "rivados";
			}
			link.l9 = "Öyle özel bir şey yok aslında. Sadece merhaba demek istedim.";
			link.l9.go = "exit";
		break;
		
		case "natan":
			dialog.text = "Nathaniel Hawk? No, I don't know this man. He is neither on the Rivados ships nor in neutral territory. I can't say the same about the Narwhal gang; we don't visit them.";
			link.l1 = "Anlıyorum...";
			link.l1.go = "exit";
			npchar.quest.natan = "true";
			NextDiag.TempNode = "Total_info";
		break;
		
		case "rivados":
			dialog.text = "The Rivados gang was founded many years ago. It was the very first clan in this City of Abandoned Ships. More than fifty years ago, Admiral Betancourt's expedition sailed here from West Africa with several large slave ships. The holds of the Tartarus were filled with hundreds of black slaves bound for the Caribbean plantations. There was a man among those slaves named Pedro Rivados; some Portuguese priests had taught him how to read and write.\nHe managed to free a few dozen slaves from their shackles and raised a mutiny. Alas, the rest of the slaves failed to join him. The revolt was quelled. The slavers tied Rivados hand and foot and left him in the ship's hold to perish from hunger and thirst. A few days later the weather turned bad and Betancourt's squadron was swept up by a powerful storm.\nDays later, after fighting the weather, the 'San Augustine' and the 'Tartarus', the only two ships still intact, were stuck in the middle of this Island. A lot of men died during those events, black and white, but many more managed to survive. The ex-slaves started a new life together and called themselves the Rivados in honour of Pedro Rivados, the liberator.";
			link.l1 = "Çok ilginç bir hikaye... Teşekkür ederim!";
			link.l1.go = "exit";
			npchar.quest.rivados = "true";
			NextDiag.TempNode = "Total_info";
		break;
		// <-- информационный блок
		
		case "capper":
			dialog.text = "Rivados'un topraklarında ne arıyorsun, beyaz adam?";
			link.l1 = "Benim adım "+GetFullName(pchar)+" ve ben buraya Amiral Dodson'ın emriyle geldim. Kara Eddie ile konuşmam gerek. Bildiğim kadarıyla, o da sensin.";
			link.l1.go = "capper_1";
		break;
		
		case "capper_1":
			dialog.text = "Evet, ben Edward Black, nam-ı diğer Kara Eddie. Söyle bakalım, amiral benden ne istiyor.";
			link.l1 = "'Tartarus'ta Chimiset adında bir adam var. Amiral onu serbest bırakmaya istekli.";
			link.l1.go = "capper_2";
		break;
		
		case "capper_2":
			dialog.text = "Bu gerçekten iyi bir haber. Chimiset bizim manevi liderimizdir ve tüm Rivados onu özlüyor. Ama anladığım kadarıyla amiral onun özgürlüğü karşılığında bir şey istiyor, doğru mu?";
			link.l1 = "Hiçbir şey. Sadece iyi niyet göstergesi olarak onu serbest bırakmak istiyor. Ama bir sorun var...";
			link.l1.go = "capper_3";
		break;
		
		case "capper_3":
			dialog.text = "Devam et, beyaz adam.";
			link.l1 = "Amiralin eski lostromosu, şimdi gardiyan olan Chad Kapper, Narvallara katıldı, yoldan çıktı ve artık amiralin kontrolünde değil. Chad’in Chimiset’i öldürmeyi planladığını biliyoruz. Amiralin böyle bir şey olmasını istemiyor. Hainin ortadan kaldırılması ve adamınızın kurtarılması için ortak bir operasyon öneriyoruz.";
			link.l1.go = "capper_4";
		break;
		
		case "capper_4":
			dialog.text = "Sözlerin biraz tuhaf geliyor, ama devam et. Chimiset bir sıkıntıda mı?";
			link.l1 = "Evet. Chad onu öldürmeyi planlıyor. Kapper, Narvalları kullanarak Şehir'in kontrolünü ele geçirecek. Chimiset'i kurtarmak istiyorsak, Chad henüz hiçbir şeyden şüphelenmediği için hızlı davranmalıyız. Amiral, 'Tartarus'tan tüm muhafızları çekti, geçit açık. İşte hapishanenin iç kapısını açan anahtar. Al.";
			link.l1.go = "capper_5";
		break;
		
		case "capper_5":
			RemoveItems(pchar, "key_capper", 1);
			dialog.text = "";
			link.l1 = "Adamlarını topla, Tartarus'a git ve Chimiset'i kurtar. Tüm kozlar artık senin elinde.";
			link.l1.go = "capper_6";
		break;
		
		case "capper_6":
			dialog.text = "Bu bir tuzak gibi kokuyor... Ya pusuya düşersek? Ya amiral Rivados'a saldırmaya karar verirse? Neden Kapper'la kendisi ilgilenmiyor?";
			link.l1 = "Dodson, Chimiset'in hayatını önemsediğini söyledi... O üzerine düşeni yaptı: işte anahtar ve gardiyanlar artık yok. Sadece içeri girmen, Chad'le hesaplaşman ve adamını kurtarman gerekiyor. Sana söz veriyorum, bir tuzak yok. Ha, bir de son bir şey: amiral, Chimiset'in hayatı ve özgürlüğü karşılığında Chad'in kafasını istiyor. Anlaştık mı?";
			link.l1.go = "capper_7";
		break;
		
		case "capper_7":
			dialog.text = "Chimiset'in hayatı Rivados için paha biçilemez. Hemen 'Tartarus'a geçeceğiz. Ama sen burada rehine olarak kalacaksın. Eğer bir pusu olursa, Rivados'un gazabıyla karşılaşırsın!\nZikomo! Kapının yanında dur ve misafirimizi gözle. Onu dışarı bırakma. 'Tartarus'a saldırıyı bizzat ben yöneteceğim!";
			link.l1 = "Bol şans, Eddie. Ve unutma: Chad Kapper'ın kafasını istiyorum!";
			link.l1.go = "capper_8";
		break;
		
		case "capper_8":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LSC_ZikomoNearDoor", 10.0);
			NextDiag.CurrentNode = "chimiset";
		break;
		
		case "chimiset":
			dialog.text = "Chimiset özgür bırakıldı! Yalan söylemiyormuşsun, beyaz adam, seni Rivados'un dostu olarak görmeye hazırım!";
			link.l1 = "Memnun oldum. Chad Kapper öldü mü?";
			link.l1.go = "chimiset_1";
		break;
		
		case "chimiset_1":
			dialog.text = "Senden af dilemeliyim, beyaz dostum: bizim için elinden geleni yaptın, ama biz sana karşı başarısız olduk... Ben sana karşı başarısız oldum! O lanet Kapper kaçtı. Yanında iki Narval vardı. Onları öldürdük, ama o pis gardiyan alt kapıdan Narval topraklarına yüzerek kaçtı.";
			link.l1 = "Siktir... 'Tartarus'tan iki çıkış olduğunu bilmiyor muydun?";
			link.l1.go = "chimiset_2";
		break;
		
		case "chimiset_2":
			dialog.text = "Bunu hiç düşünmedik. Ana girişten saldırdık...";
			link.l1 = "Yazık. Onun başına güveniyordum. Ne kötü. Şimdi bize karşı hareket etmeye devam edecek.";
			link.l1.go = "chimiset_3";
		break;
		
		case "chimiset_3":
			dialog.text = "I admit my guilt. But we couldn't follow him onto the hostile ships. You will have our friendship and respect instead of Chad's head. From now on, you are allowed to visit our territory freely. Chimiset's wisdom will serve you well too; talk to him if you need anything. Also, give the admiral my assurances that I appreciated his actions.";
			link.l1 = "Pekâlâ.";
			link.l1.go = "chimiset_4";
		break;
		
		case "chimiset_4":
			dialog.text = "Bekle! Chad'i kaybettik, ama masasında bizim geldiğimizde incelediği birkaç belge buldum. İşte burada. Belki işine yarar, beyaz kardeş.";
			link.l1 = "Ha! Belki de... Chad kâğıda çok güvenir...";
			link.l1.go = "chimiset_5";
		break;
		
		case "chimiset_5":
			dialog.text = "Sen burada her zaman hoş karşılanan bir dostsun, beyaz arkadaş. Bütün Rivados bundan haberdar olacak. Bol şans!";
			link.l1 = "Sana da, Eddie...";
			link.l1.go = "chimiset_6";
		break;
		
		case "chimiset_6":
			DialogExit();
			LAi_ActorGoToLocator(npchar, "goto", "goto1", "LSC_EddyStay", -1);
			sld = CharacterFromID("Zikomo");
            LAi_SetWarriorType(sld);
			LAi_warrior_SetStay(sld, true);
			LAi_warrior_DialogEnable(sld, true);
			GiveItem2Character(pchar, "letter_chad");
			ChangeItemDescribe("letter_chad", "itmdescr_letter_aeva");
			GiveItem2Character(pchar, "letter_chad_1");
			ChangeItemDescribe("letter_chad_1", "itmdescr_letter_axel");
			pchar.questTemp.LSC.rvd_friend = "true"; //флаг на проход по кораблям ривадос
			// // ривадосы не будут останавливать где просят пароль
			pchar.questTemp.Saga.SharkHunt = "dodson_whiskey"; // к Акуле
			sld = CharacterFromID("Dodson");
			sld.dialog.currentnode = "Chad_escape"; // ноду Акуле
			AddQuestRecord("SharkHunt", "33");
			LocatorReloadEnterDisable("LostShipsCity_town", "reload48", true); // закрыть вход к Дональду Гринспи
			for (i=7; i<=12; i++)
			{
				sld = CharacterFromID("RivadosSold_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			for (i=4; i<=8; i++)
			{
				sld = CharacterFromID("RivadosProt_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			AddSimpleRumourCityTip("Have you heard the latest news? The Rivados' insolence is out of control, they have attacked the admiral's prison and released their wizard!", "LostShipsCity", 3, 2, "LSC", "");
			AddSimpleRumourCityTip("Just think about it - those uppity Rivados dared to attack the 'Tartarus'! They say that the jailer, Chad Kapper, has escaped to the Narwhals...", "LostShipsCity", 3, 2, "LSC", "");
			AddSimpleRumourCityTip("This is the height of impudence, isn't it? Attacking a military facility of the admiral! Aye, looks like Black Eddie is getting stronger...", "LostShipsCity", 3, 2, "LSC", "");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
