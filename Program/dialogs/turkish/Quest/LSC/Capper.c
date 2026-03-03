// Чад Каппер - боцман Акулы и тюремщик
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
			dialog.text = "Bir şey mi istiyorsun?";
			link.l1 = "Hayır, hiçbir şey.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// вариант R
		case "Chimiset":
			dialog.text = "Demek... gizemli hırsız sensin? Hmm... sıradan bir yankesiciye pek benzemiyorsun.";
			link.l1 = "Beyefendi, yanılıyorsunuz. Ben buraya yeni geldim, sizin adamlarınızın beni yakaladığı ambarın size ait olduğunu nasıl bilebilirdim ki?";
			link.l1.go = "Chimiset_1";
		break;
		
		case "Chimiset_1":
			dialog.text = "Gerçekten mi? Güzel deneme, dostum... O zaman buraya nereden geldin?";
			link.l1 = "İspanyol Ana Karası'ndan, bir Hint putu aracılığıyla... Nasıl açıklayacağımı tam olarak bilmiyorum...";
			link.l1.go = "Chimiset_2";
		break;
		
		case "Chimiset_2":
			dialog.text = "Heykel mi? Ha-ha! Sen de komik bir adamsın, değil mi...? Dur, bir tahmin edeyim: geminin gövdesindeki delikten yüzerek ambarımıza gizlice girdin. Ama yüzünü neden hatırlamıyorum? Tüm Rivados'u tanırım ben...";
			link.l1 = "Rivados mu? Neden bahsettiğin hakkında hiçbir fikrim yok! Bak, ben buraya yaklaşık bir saat önce geldim--";
			link.l1.go = "Chimiset_3";
		break;
		
		case "Chimiset_3":
			dialog.text = "Bağırma, sağır değilim. Hayır, ne kadar lanet komik olsan da, seni biraz burada bırakacağım. Belki fareler ayak parmaklarını kemirdikten sonra fikrini değiştirirsin.";
			link.l1 = "Bu Rivados hakkında hiçbir şey bilmiyorum! Benim adım Charles de Maure!";
			link.l1.go = "Chimiset_4";
		break;
		
		case "Chimiset_4":
			dialog.text = "Hm... belki de doğruyu söylüyorsun... Rivados beyaz adamlarla çalışmaya alışık değildir. Bana açıkça söyle... onlardan biri misin?";
			link.l1 = "Sana yemin ederim, bu ismi daha önce hiç duymadım! Kimseyle iş birliği yapmıyorum!";
			link.l1.go = "Chimiset_5";
		break;
		
		case "Chimiset_5":
			dialog.text = "Gerçekten mi? Peki. Kanıtla o zaman. Aşağı in, kafeste oturan bir Rivados var. Tehlikeli bir büyücü. Onu öldür, ikna olayım.\nAyrıca depomuza izinsiz girdiğini de unutacağım. Ne dersin? Korkma, büyücü silahsız ve güçsüz. Gerçi... belki bir büyüyle seni toza çevirebilir, ha-ha...";
			link.l1 = "Eğer benim gördüklerimi görseydin, şaka yapmazdın--";
			link.l1.go = "Chimiset_6";
		break;
		
		case "Chimiset_6":
			dialog.text = "Pekâlâ, yeter! Bunu yapacak mısın, yoksa yapmayacak mısın? Eğer yapacaksan, şu palayı al ve büyücüyü öldür. Yoksa Tartarus'un derinliklerinde can verirsin. Anlaşıldı mı?";
			link.l1 = "... pala mı ver.";
			link.l1.go = "Chimiset_7";
		break;
		
		case "Chimiset_7":
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "slave_02");
			EquipCharacterbyItem(pchar, "slave_02");
			dialog.text = "Aferin çocuk. Şimdi git ve Zenci büyücüyü öldür. Kafesi açık. Sakın aptalca bir şey deneme – kaçmayı aklından bile geçirirsen seni hiç tereddüt etmeden gebertiriz. Şimdi yürü!";
			link.l1 = "Sizleri bu paslı hurda parçasıyla doğrayacağımdan mı korkuyorsunuz?";
			link.l1.go = "Chimiset_8";
		break;
		
		case "Chimiset_8":
			dialog.text = "Sabrım tükeniyor, dostum. Ambar bölümüne git ve sana söyleneni yap!";
			link.l1 = "Pekala, pekala, gidiyorum...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Chimiset_9";
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//разлочим Ф2
		break;
		
		case "Chimiset_9":
			dialog.text = "Sabrımı zorluyorsun, eşek herif! Beni kızdırmak istemezsin...";
			link.l1 = "Ta, tamam, sakin ol.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Chimiset_9";
		break;
		
		case "Fightfail_Final":
			dialog.text = "Zenciyi öldürdün mü? Güzel... Sevindim. Rivados olmadığını kanıtladın.";
			link.l1 = "Sonunda şu lanet tekneden kurtulacak mıyım? Hemen Köpekbalığı Dodson'u görmem lazım.";
			link.l1.go = "Fightfail_Final_1";
		break;
		
		case "Fightfail_Final_1":
			dialog.text = "Onu göreceksin... cehenneme giden yolda.";
			link.l1 = "... siktir.";
			link.l1.go = "Fightfail_Final_2";
		break;
		
		case "Fightfail_Final_2":
			DialogExit();
			DoQuestCheckDelay("LSC_ChadGuardAttack_Fail", 0.1);
		break;
		
		// вариант N
		case "prisoner":
			dialog.text = "Ha! Şuna bak. Benim zindanımda ne işin var?";
			link.l1 = "Adın Chad Kapper, değil mi? Ben "+GetFullName(pchar)+", Köpekbalığı Dodson adına buradayım. Anahtarları bana o verdi.";
			link.l1.go = "prisoner_1";
		break;
		
		case "prisoner_1":
			dialog.text = "Amiral mi gönderdi seni? Hıh. Onun yeni ayak işlerini yapanı mısın?";
			link.l1 = "Diline dikkat et, efendi... yoksa onu kaybedersin. Ben kimsenin ayak işlerini yapanı değilim.";
			link.l1.go = "prisoner_2";
		break;
		
		case "prisoner_2":
			dialog.text = "Ha-ha! Senden hoşlandım dostum. Boşver, söylediklerimi unut... Peki, buraya geliş sebebin ne?";
			link.l1 = "Köpekbalığı, Chimiset'in serbest bırakılmasını emretti.";
			link.l1.go = "prisoner_3";
		break;
		
		case "prisoner_3":
			dialog.text = "Rivados'un vudu büyücüsü mü? Hm, bu garip... Bunu duyduğuma gerçekten şaşırdım...";
			link.l1 = "Köpekbalığı, Rivados ile barış yapmak istiyor.";
			link.l1.go = "prisoner_4";
		break;
		
		case "prisoner_4":
			dialog.text = "A-ah, I see... Fine. I'll send a man to Rivados; they can come and collect their wizard.";
			link.l1 = "Neden onu hemen serbest bırakmıyorsun?";
			link.l1.go = "prisoner_5";
		break;
		
		case "prisoner_5":
			dialog.text = "Elbette yapabilirdim... eğer onu öldürtmek isteseydim. Chimiset burada tanınan biri. Esmeralda'nın güvertesine adım attığı anda hayatı Narvaların - düşmanlarının - bölgesinde tehlikeye girer.\nTartarus'tan ayrılmanın başka yolu yok, yaşlı adamı adanın etrafında yüzdürecek halimiz de yok! Ona bir şey olursa Rivados bizi suçlar - özellikle de beni!\nBöyle bir belaya bulaşmak istemem, bu yüzden onu ancak kendi klanı güvenliğinden sorumlu olursa serbest bırakırım. Chimiset'le bizzat konuşmak ister misin? Renkli bir kişiliktir...";
			if (CheckAttribute(npchar, "quest.chimiset_talk")) link.l1 = "Onunla zaten konuştum. Gerçekten tuhaf biri... Neyse, gitmem gerek. Hoşça kal, Chad.";
			else link.l1 = "Öyle de yapacağım. Onunla şimdi görüşeceğim.";
			link.l1.go = "prisoner_6";
		break;
		
		case "prisoner_6":
			DialogExit();
			sld = characterFromId("Chimiset");
			sld.quest.capper_talk = "true"; // разговор с Каппером состоялся
			if (!CheckAttribute(npchar, "quest.chimiset_talk")) chrDisableReloadToLocation = true;//закрыть локацию
			else chrDisableReloadToLocation = false;//открыть локацию
			NextDiag.CurrentNode = "prisoner_7";
		break;
		
		case "prisoner_7":
			dialog.text = "Rivados'a bir ulak göndereceğim, gelip büyücülerini alacaklar. Merak etme dostum, gidebilirsin.";
			link.l1 = "Pekâlâ.";
			link.l1.go = "exit";
			NextDiag.TempNode = "prisoner_7";
		break;
		
		// вариант M
		case "Aeva_attack":
			dialog.text = "... fıçıyı çoktan açmıştır, eminim. En sevdiği viski: Bushmills. Yakında her şey bitecek, o fıçıya bir fili öldürecek kadar arsenik koydum...";
			link.l1 = "";
			link.l1.go = "Aeva_attack_1";
			CharacterTurnToLoc(npchar, "quest", "quest2");
		break;
		
		case "Aeva_attack_1":
			dialog.text = "Hmm? Kahretsin, burada ne işin var?! Defol git!";
			link.l1 = "Seni arıyordum, zehirci. Garip, Tek Göz'ü göremiyorum... Köpekbalığı'nın yerini almak istemiştin, değil mi?";
			link.l1.go = "Aeva_attack_2";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Aeva_attack_2":
			dialog.text = "Ha-ha, Köpekbalığı muhtemelen çoktan ölmüştür! Ve sen de yakında ona katılacaksın, casus!";
			link.l1 = "...";
			link.l1.go = "Aeva_attack_fight";
		break;
		
		case "Aeva_attack_fight":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("ChadNarval_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_CapperDieAeva");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Aeva_attack_2":
			dialog.text = "... this is going to be a hell of a drink. Shark's been dreaming of this whiskey so long, he'll down it in a single draught. Where's the arsenic? We'll use two bottles, just to be sure... then our friend Fazio can deliver this barrel to the Admiral as a present from tje Narwhals, ha-ha!\nAm I right, dear Giuseppe? Chin up, lad; you do this right, and you've got nothing to worry abou-- Ah! We have company, boys! What do you want, jackass? This is a private get-together.";
			link.l1 = "Planın işe yaramadı, Kapper. Senin ve arkadaşın Marcello'nun ne yapacağını biliyorum. At şu arseniği! Köpekbalığını zehirleyemezsin!";
			link.l1.go = "Aeva_attack_3";
		break;
		
		case "Aeva_attack_3":
			dialog.text = "Ah, kahretsin. Peki... önce sen ölüyorsun, sonra Köpekbalığı! Silah başına, çocuklar!";
			link.l1 = "...";
			link.l1.go = "Aeva_attack_fight";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
