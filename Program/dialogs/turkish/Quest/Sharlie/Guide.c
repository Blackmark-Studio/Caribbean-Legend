// гид
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

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
		
		case "guide_0":
			PlaySound("Voice\English\LE\Greguar\Greguar_01.wav");
			dialog.text = "Sizi kolonilerde ağırlamak büyük bir zevk, efendim! Kendimi tanıtmama izin verin: "+GetFullName(npchar)+" . Eski güzel yuvadan mı geliyorsun?";
			link.l1 = "İyi günler, monsieur. Benim adım "+GetFullName(pchar)+" . Evet, az önce gemiden indim.";
			link.l1.go = "guide_1";
		break;
		
		case "guide_1":
			DelLandQuestMark(npchar);
			dialog.text = "Bir centilmeni görünce yardım etmek istedim. Yeni Dünya'nın kendine has kuralları var, onları bilmemek pahalıya patlayabilir. Mevki sahibi insanlar birbirine destek olmalı. Burada bir avuç para için sizi satacak serseri çok.\n"+"Sana etrafı gezdireyim ve temel bilgileri anlatayım mı?";
			link.l1 = "Çok naziksiniz, monsieur! Memnuniyetle.";
			link.l1.go = "guide_2";
			link.l2 = "Teşekkür ederim, monsieur, ama kendi yolumu bulurum.";
			link.l2.go = "guide_exit";
		break;
		
		case "guide_exit":
			dialog.text = "Nasıl isterseniz, Mösyö. Her neyse, sizinle tanışmak güzeldi. Saygın beyefendiler burada nadiren misafir olur. Size bol şans diliyorum!";
			link.l1 = "Sana da, "+GetFullName(npchar)+"!";
			link.l1.go = "guide_exit_1";			
		break;
		
		case "guide_exit_1":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DoQuestCheckDelay("NgtF3", 1.0);
			QuestPointerToLoc("FortFrance_town", "reload", "reload3_back");
		break;
		
		case "guide_2":
			dialog.text = "Mükemmel! Karayip kasabalarının yerleşimi hep aynıdır. Saint-Pierre'i öğrenirsen, diğer limanlar da anlamlı gelecektir.";
			link.l1 = "";
			link.l1.go = "guide_tavern";		
		break;
		
		case "guide_tavern":
			dialog.text = "Meyhane—limanın kalbi. Yatak bul, rom iç, dedikodu dinle, denizci ya da subay tut. İstersen iskambil oyna, iş ara ya da kaçakçılar ve hazine haritası satanlarla uğraş.";
			link.l1 = "";
			link.l1.go = "guide_market";
			locCameraFromToPos(-2.08, 5.32, 68.88, true, -15.00, 0.90, 55.00);
		break;
		
		case "guide_market":
			dialog.text = "Market. Need supplies? The smith has blades, armor, and shot; the herb-woman sells tonics. Gypsies and monks trade charms, and the junk-dealer offers odds and ends for those who can craft.";
			link.l1 = "";
			link.l1.go = "guide_brothel";
			locCameraFromToPos(-13.58, 4.11, 69.06, true, -45.00, -6.00, 52.00);
		break;
		
		case "guide_brothel":
			dialog.text = "Genelev. Usta bir hanımefendiyle geçirilen zaman kadar ruhu canlandıran bir şey yoktur. Eğer kendini yorgun hissediyorsan, uğra ve bambaşka biri olarak çık.";
			link.l1 = "";
			link.l1.go = "guide_bank";
			locCameraFromToPos(-2.75, 7.07, 61.10, true, 60.00, -6.60, 42.65);
		break;
		
		case "guide_bank":
			dialog.text = "Banka. Para ödünç alabilir veya yatırım yapabilir, peso karşılığında dublon alabilir, ayrıca mücevher satmak için en iyi yerdir.";
			link.l1 = "";
			link.l1.go = "guide_prison";
			locCameraFromToPos(3.07, 7.64, 51.99, true, 45.00, -8.30, 4.50);
		break;
		
		case "guide_prison":
			dialog.text = "Prison. Few real villains inside—mostly drifters. Want a job from them? Talk to the commandant; a small bribe opens the cells.";
			link.l1 = "";
			link.l1.go = "guide_townhall";
			locCameraFromToPos(-50.52, 5.79, 38.60, true, -47.65, 3.95, 33.52);
		break;
		
		case "guide_townhall":
			dialog.text = "Vali Sarayı. Tüccarlar ve kaptanlar önemli işler için buraya gelir. Valinin dostluğunu kazanmaya bak—onun sözü, ülkesinin sana nasıl davranacağını belirler.";
			link.l1 = "";
			link.l1.go = "guide_12";
			locCameraFromToPos(3.14, 7.39, 37.55, true, 1.06, 8.45, 14.14);
		break;
		
		case "guide_12":
			dialog.text = "Seni oyalıyor muyum, dostum?";
			link.l1 = "Monsieur, kardeşimi bulmak için buradayım. Onun Saint-Pierre'de olduğunu söylüyorlar. Biraz önemli bir adam—Vali mutlaka onu tanıyordur...";
			link.l1.go = "guide_13";
			SetCameraDialogMode(npchar);
		break;
		
		case "guide_13":
			dialog.text = "Anladım. Valimiz Jacques Dyel du Parquet. Eminim sizi hemen kabul edecektir.";
			link.l1 = "Başka kimi sorabilirim? Doğrudan Ekselanslarını rahatsız etmek istemem.";
			link.l1.go = "guide_14";
		break;
		
		case "guide_14":
			dialog.text = "Eğer kardeşiniz Martinique'te tanınıyorsa, kasaba halkına sorun—birisi mutlaka bilir. Peki, adı ne?";
			link.l1 = "Michel de Monper.";
			link.l1.go = "guide_15";
		break;
		
		case "guide_15":
			dialog.text = "Adını duydum, ama hiç tanışmadık. Etrafta sorabilirsin—ya da doğrudan Valinin yanına git. İyi şanslar, monsieur. Yine görüşürüz!";
			link.l1 = "Teşekkür ederim, "+GetFullName(npchar)+"!";
			link.l1.go = "guide_16";
		break;
		
		case "guide_16":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			LAi_group_MoveCharacter(npchar, "FRANCE_CITIZENS"); // пока идем заниматься Мишелем
			chrDisableReloadToLocation = false;//открыть локацию
			DoQuestCheckDelay("NgtF3", 1.0);
			QuestPointerToLoc("FortFrance_town", "reload", "reload3_back");
		break;
		
		case "guide_21":
			dialog.text = "Ah, yine sen! Şövalyelerin kalesine adım attığını duydum. Belli ki yüksek çevrelerde dolaşıyorsun. Kardeşini bulabildin mi?";
			link.l1 = "Onu buldum... bir bakıma.";
			link.l1.go = "guide_22";
		break;
		
		case "guide_22":
			dialog.text = "Beni affedin, ama bu cevabınızda pek bir sevinç duymuyorum...";
			link.l1 = "Doğru. Bir sonraki gemiyle eve dönerim diye ummuştum ama kader bana gülüyor. Burada kaldım—kim bilir ne kadar süreyle—ve üstüne üstlük, bir de denizci olmayı öğrenmem gerekiyor.";
			link.l1.go = "guide_23";
		break;
		
		case "guide_23":
			dialog.text = "Şaşırmadım. Ulysses'teki yolculuğun dilden dile dolaşıyor. Moralin bozulmasın—bir gemiye sahip olmak ve kaptan unvanı taşımak küçümsenecek şeyler değil. Bir gemi satın almayı düşünüyorsun, öyle mi?";
			link.l1 = "Evet—kahretsin—zorundayım. Ama tersanenin nerede olduğunu, nasıl yelken açacağımı ya da parayı nasıl bulacağımı bilmiyorum. Hiçbir şey!";
			link.l1.go = "guide_24";
		break;
		
		case "guide_24":
			dialog.text = "Param yok, ama diğer her konuda hizmetinizdeyim. Gezmeye devam edelim mi?";
			link.l1 = "Haklısın—bilgi güçtür.";
			link.l1.go = "guide_25";
			link.l2 = "Teşekkür ederim, monsieur, ama buradan sonrası bende.";
			link.l2.go = "guide_exit_11";
		break;
		
		case "guide_exit_11":
			dialog.text = "Memnun oldum. Para için kasabanın ileri gelenleriyle konuş—belki dükkân sahibiyle\n"+"İyi şanslar, "+pchar.name+"—cesur ol, üstesinden gelirsin.";
			link.l1 = "";
			link.l1.go = "guide_exit_12";			
		break;
		
		case "guide_exit_12":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		case "guide_25":
			dialog.text = "O zaman beni takip et! Öncelikle—gemiler.";
			link.l1 = "";
			link.l1.go = "guide_shipyard";
		break;
		
		case "guide_shipyard":
			dialog.text = "Tersane. Buradan gemi satın alabilir veya tamir ettirebilirsin. Genellikle küçük tekneler var, ama arada iyi bir tane de çıkar. Toplar ve süslü yelkenler de mevcut.";
			link.l1 = "";
			link.l1.go = "guide_port";
			locCameraFromToPos(-23.25, 7.74, 77.79, true, -27.85, 5.36, 73.65);
		break;
		
		case "guide_port":
			dialog.text = "İskele—denize açılan kapın. Bir gemin olduğunda, teknen burada seni bekleyecek. Şimdilik bir dümenci, bir kambiyo memuru ve bir topçu tut—denizde hayatın daha kolay olur.";
			link.l1 = "";
			link.l1.go = "guide_portoffice";
			locCameraFromToPos(-8.55, 4.06, 91.31, true, 40.00, -8.00, 0.00);
		break;
		
		case "guide_portoffice":
			dialog.text = "Liman Ofisi. Geminizi buraya bağlayın ya da dürüst bir iş bulun—yük taşıma, eskortluk, posta seferleri. Ne kadar çok iş tamamlarsanız, ödemeniz o kadar iyi olur.";
			link.l1 = "";
			link.l1.go = "guide_store";
			locCameraFromToPos(48.38, 9.48, 43.95, true, 43.69, 5.47, 48.13);
		break;
		
		case "guide_store":
			dialog.text = "Mağaza. Kaptanlar buraya yiyecek, rom, ilaç, barut ve cephane almak için gelir. Bir şey eksikse, meyhanedeki kaçakçıları bul. İyi bir kambiyeci olmadan ticaret zaman ve para kaybıdır.";
			link.l1 = "";
			link.l1.go = "guide_gate";
			locCameraFromToPos(-21.10, 6.60, 45.21, true, -30.00, 3.70, 45.00);
		break;
		
		case "guide_gate":
			dialog.text = "Vahşi bölgelere açılan kapılar. Tehlikeli ama kalelere ulaşmak, hazine avlamak ya da başka bir yerleşime geçmek için işe yarar.";
			link.l1 = "";
			link.l1.go = "guide_45";
			locCameraFromToPos(50.58, 5.74, 23.21, true, 100.00, 0.00, 20.00);
			//AddQuestRecordInfo("Guide_OnLand", "1");
		break;
		
		case "guide_45":
			dialog.text = "Her koloni yabancıları hoş karşılamaz. Geceyi beklemek istemiyorsan, denizde başka bir bayrak çek, sonra gizliliğe güven—ya da ticaret ruhsatı satın al.";
			link.l1 = "";
			link.l1.go = "guide_46";
		break;
		
		case "guide_46":
			dialog.text = "İyi dinle, dostum. Biraz eğlence ister misin? Kapıların dışında bir idman düellosu.";
			link.l1 = "Elbette! Harika olur.";
			link.l1.go = "guide_47";
			link.l2 = "Teşekkür ederim, monsieur, ama bundan sonrasını ben hallederim.";
			link.l2.go = "guide_exit_11";
		break;
		
		case "guide_47": // телепортируем за городские ворота
			DialogExit();
			LAi_SetActorType(npchar);
			DoQuestReloadToLocation("FortFrance_ExitTown", "goto", "goto19", "Guide_ExitTown");
		break;
		
		case "guide_49":
			dialog.text = "Dostum, anladığım kadarıyla eskrim sana yabancı değil?";
			link.l1 = "Ha! Bir kere gemi baskını atlattım bile, hatta—";
			link.l1.go = "guide_50";
			if (GetCharacterEquipByGroup(pchar, BLADE_ITEM_TYPE) == "unarmed")
			{
				GiveItem2Character(pchar, "blade_05");
				EquipCharacterByItem(Pchar, "blade_05");
			}
		break;
		
		case "guide_50":
			dialog.text = "Mükemmel. Başlayalım mı?";
			link.l1 = "Hadi dans edelim!";
			link.l1.go = "guide_56";
			npchar.quest.guide_win = 0;
		break;
		
		case "guide_56": // махач
			LAi_SetPlayerType(pchar);
			LAi_SetCurHPMax(pchar); 
			LAi_GetCharacterMaxEnergy(pchar);
			LAi_SetCurHPMax(npchar); 
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_group_Delete("EnemyFight");
			if (MOD_SKILL_ENEMY_RATE <= 6)	// На первых трёх сложностях Валинье будет ослаблен
			{
				LAi_SetHP(npchar, LAi_GetCharacterMaxHP(npchar) * 0.7, LAi_GetCharacterMaxHP(npchar) * 0.7);
				npchar.rank = 1;
				SetSelfSkill(npchar, 1, 1, 1, 1, 1);
			}
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			// ставим проверяльщики
			LAi_SetCheckMinHP(pchar, 1, true, "Guide_HeroFail");
			LAi_SetCheckMinHP(npchar, 1, true, "Guide_HeroWin");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			//DoQuestCheckDelay("GuideFight_tutorial", 1.0);
		break;
		
		case "guide_57": // побил гида с первого раза
			dialog.text = "Sen... sen kılıcını nasıl kullanacağını bilen bir adamsın. Aferin, Mösyö. Daha fazla antrenmana ihtiyacın var, ama gerçek bir kılıç ustası olma potansiyelin var.";
			link.l1 = "Çok teşekkür ederim. Peki şimdi ne yapacağız?";
			link.l1.go = "guide_62"; // нода на выход
			if (MOD_SKILL_ENEMY_RATE >= 6)
			{
				link.l2 = "Daha fazla pratik mi diyorsun? Ciddi misin? Bu berbat yere adım attığımdan beri şu küçümseyici tavrından bıktım artık!";				//Пасхалка Корсары 2 для сложности СФ и выше
				link.l2.go = "guide_64";
			}
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 80);
		break;
		
		case "guide_58": // побил гида со второго или третьего раза
			dialog.text = "Much better! See, all you need is to concentrate. You need more practice; one day you will become a decent fencer.";
			link.l1 = "Çok teşekkürler. Peki şimdi ne olacak?";
			link.l1.go = "guide_62"; // нода на выход
			AddComplexSelfExpToScill(20, 20, 20, 20);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
		break;
		
		case "guide_59": // побили первый раз
			dialog.text = "Ben kazandım, Mösyö. Daha hızlı hareket et, hamlelerimi savuştur, geri sıçra. Bir rövanş ister misin?";
			link.l1 = "Evet! Merhamet yok, Mösyö!";
			link.l1.go = "guide_56";
			link.l2 = "Hayır, artık yeter. Dersi bitirelim. Şimdi ne olacak?";
			link.l2.go = "guide_62"; // нода на выход
		break;
		
		case "guide_60": // побили второй раз
			dialog.text = "Yine kazandım, "+pchar.name+"! İnisiyatifini kaybetme. Saldırılarımı yakala, onları şaşırt. Sert vuracak gibi görünüyorum, hemen geri çekil ya da savuştur, sadece savunmada kalma. Tekrar!";
			link.l1 = "Gelin, Mösyö, bu sefer sizi fena halde pataklayacağım!";
			link.l1.go = "guide_56";
			link.l2 = "Hayır, yeter artık. Dersi bitirelim. Şimdi ne olacak?";
			link.l2.go = "guide_62"; // нода на выход
		break;
		
		case "guide_61": // побили третий раз
			dialog.text = "Öğrenecek çok şeyin var, "+pchar.name+". Merak etme, hala eskrim ustası olmak için bolca vaktin var. Ama dikkatli ol, bir silahı nasıl tutacağını öğrenene kadar riske girme.";
			link.l1 = "Bunu düşüneceğim, Mösyö, ama şunu söylemeliyim ki gerçekten çok şanslıydın! Bu lanet sıcak... Seni pataklamamış olmamın tek sebebi bu. Merde, hadi eskrim dersimizi bitirelim. Şimdi ne yapacağız?";
			link.l1.go = "guide_62"; // нода на выход
		break;
		
		case "guide_62":
			dialog.text = "Artık veda etme vakti geldi, Mösyö. Tanıştığımıza memnun oldum. Umarım sunumum ve eğitimim size faydalı olmuştur ve ileride de işinize yarar. Belki bir gün tekrar karşılaşırız.\nVe ihtiyacınız olan para konusunda - şehrimizin önemli insanlarıyla konuşun. Bugün size gösterdiğim tüm yerlere gidin ve sahipleriyle sohbet edin. Etrafınıza sorun. Ormana ve kaleye de bir uğrayın. Bir iş bulun ya da... şey, ben ne rahip ne de yargıcım, insanların evlerine göz atın, açık sandıklarında neler bulabileceğinize bakın. Yalnız bunu onların arkası dönükken yapın, yoksa muhafızlar sizi yakalar.\nBol şans, "+pchar.name+", içimde güçlü bir his var ki, sende gerçek bir büyüklüğün kıvılcımı var. Elinden geleni yap ve onu alev alev bir ateşe dönüştür!";
			link.l1 = "Teşekkürler, Mösyö. Zevk bana aitti. Yolunuz açık olsun!";
			link.l1.go = "guide_63";
		break;
		
		case "guide_63":
			LAi_SetCurHPMax(pchar); 
			LAi_GetCharacterMaxEnergy(pchar);
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.lifeday = 0;
			DoQuestReloadToLocation("FortFrance_Town", "quest", "quest2", "");
		break;
		
		case "guide_64": // решили убить Валинье
			dialog.text = "Dilini tut, Mösyö! Bu kadar küstahlığı daha fazla tolere etmeyeceğim. Yine de, yeni bir ortama verdiğin tepkiyi anlıyorum, bu yüzden bu seferki patlamanı affediyorum. Ama bundan sonra sözlerine dikkat et. Hoşça kal, Mösyö de Maure.";
			link.l1 = "Alınmayın, Monsieur Valinnie. Şu anda Louvre'da olsaydık, ses tonunuza dikkat ederdiniz! Bir taşralıya son dersini verme vakti geldi. Kendinizi savunun!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Guide_DlgExit_64");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
