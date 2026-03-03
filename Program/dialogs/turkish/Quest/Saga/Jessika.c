// Джессика Роуз - нежить и супербосс
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;
	float locx, locy, locz;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Bir şey mi istiyorsun?";
			link.l1 = "Hayır, bir şey değil.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// бой на рифе
		case "reef":
			PlaySound("Voice\English\saga\Jessica Rose-06.wav");
			dialog.text = "Sen! Onu buraya sen getirdin! O, onun kanından! O, onun kanından! O fahişenin kızı annesinin mezarına geldi! Ölecek! Ve sen bunu durduramayacaksın! Jessica'nın yoluna çıkma! İntikam benim olacak!";
			link.l1 = "...";
			link.l1.go = "reef_1";
		break;
		
		case "reef_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "stage_1":
			PlaySound("Voice\English\saga\Jessica Rose-07.wav");
			dialog.text = "Ha! Bana zarar veremezsin!\n Hava, su, toprak, ateş - size emrediyorum, bana yardım edin!\n Ölüler kalksın, ateş yansın, su köprüyü korusun ve rüzgar seni kanatlarında yükseltip yere çarpsın!\nİyi eğlenceler!!!";
			link.l1 = "...";
			link.l1.go = "stage_1_exit";
		break;
		
		case "stage_1_exit":
			DialogExit();
			LAi_SetActorType(pchar);
			CreateLocationParticles("blast_inv", "quest", "top", 1.6, 0, 0, "");
			PlaySound("Sea Battles_01\Bomb_Explosion_03.wav");
			PlaySound("People Fight\Death_NPC_08.wav");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(pchar, "shore67", "goto", LAi_FindFarFreeLocator("goto", locx, locy, locz));
			LAi_ActorAnimation(Pchar, "Ground_sitting", "", 3.5);
			DoQuestCheckDelay("Saga_JessikaFirstKick_2", 3.5);
			SetCameraShake(4.0, 12.0, 0.1, 0.1, 0.05, true, false, -1);
		break;
		
		case "stage_2":
			PlaySound("Voice\English\saga\Jessica Rose-08.wav");
			dialog.text = "Ha! Bana zarar veremezsin!\nDaha fazla ölü kalkıp saldırsın, ateş taşı yakıp kül etsin, rüzgar seni havaya kaldırıp yere çalsın, toprak gücünü içine çeksin!\nKeyfini çıkar!!!";
			link.l1 = "...";
			link.l1.go = "stage_2_exit";
		break;
		
		case "stage_2_exit":
			DialogExit();
			LAi_SetActorType(pchar);
			CreateLocationParticles("blast_inv", "quest", "rock", 1.6, 0, 0, "");
			PlaySound("Sea Battles_01\Bomb_Explosion_03.wav");
			PlaySound("People Fight\Death_NPC_08.wav");
			pchar.GenQuest.BladePenalty = 30;
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(pchar, "shore67", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorAnimation(Pchar, "Ground_sitting", "", 3.5);
			DoQuestCheckDelay("Saga_JessikaSecondKick_2", 3.5);
			SetCameraShake(4.0, 12.0, 0.1, 0.1, 0.05, true, false, -1);
		break;
		
		case "stage_3":
			PlaySound("Voice\English\saga\Jessica Rose-07.wav");
			dialog.text = "Ha! Bana zarar veremezsin!\nBırak zehir alevli kılıcımı sarsın, rüzgar seni kucaklasın, su çevikliğini silip götürsün!\nÖl! Ha-ha-ha!";
			link.l1 = "...";
			link.l1.go = "stage_3_exit";
		break;
		
		case "stage_3_exit":
			DialogExit();
			npchar.viper = true;
			TakeNItems(npchar, "potion2", 3);
			LAi_SetActorType(pchar);
			PlaySound("Sea Battles_01\Bomb_Explosion_03.wav");
			PlaySound("People Fight\Death_NPC_08.wav");
			pchar.GenQuest.EnergyPenalty = 2;
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(pchar, "shore67", "quest", "bridge2");
			LAi_ActorTurnToLocator(pchar, "quest", "bridge1");
			LAi_ActorAnimation(Pchar, "Ground_sitting", "", 3.5);
			DoQuestCheckDelay("Saga_JessikaThirdKick_2", 3.5);
			SetCameraShake(4.0, 12.0, 0.1, 0.1, 0.05, true, false, -1);
		break;
		
		case "stage_4":
			PlayStereoOGG("music_shore");
			sld = characterFromId("Svenson");
			dialog.text = "Yeter... Yoruldum. Yenildim... Zavallı Jessica'nın kaderine acıyın!";
			link.l1 = "Elbette... Zavallı ruhunu bu cesedin yükünden kurtaracağım!";
			link.l1.go = "exit_battle";
			if (CheckAttribute(sld, "quest.jessika_peace")) // выслушал историю Джессики
			{
				link.l2 = "Hikayeni biliyorum, Jessica. Ve hayatının bu kadar hüzünlü geçip böyle sona erdiğine üzgünüm. Benimle konuşmak istiyorsun, değil mi? Peki, yakın zamanda beni öldürmeye çalıştığını unutmaya çalışacağım ve seni dinleyeceğim, ama bu benim için kolay olmayacak...";
				link.l2.go = "exit_talk";
			}
		break;
		
		case "exit_battle":
			DialogExit();
			SetMusic("music_teleport");
			DeleteAttribute(npchar, "viper");
			LAi_SetImmortal(npchar, false);
			npchar.chr_ai.hp = stf(npchar.chr_ai.hp)+100;
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_JessikaDie");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.JessSeekTreatment = 0;
			LAi_LocationDisableOfficersGen(pchar.location, false);//офицеров пускать
		break;
		
		case "exit_talk":
			dialog.text = "Teşekkür ederim... Beatrice Sharp ve Lawrence'ı zaten biliyorsun... benim Lawrence'ımı. Onu hiç tereddüt etmeden öldürdüm, ama Lawrence'ı öldüremedim. Yapamadım, ama o yapabildi. Jessica öldü...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("Video_Reef");
			NextDiag.TempNode = "exit_talk_0";
		break;
		
		case "exit_talk_0":
			dialog.text = "... ama korkunç bir yeminle mühürlenen kan yemini hâlâ yerine getirilmedi. Bu yemin gücünü Hint büyüsünden alıyor. Cesedi mezarından kaldırdı.\nNefret ruhumu bir çöle çevirdi. Bu resife gelen herkes elimde can verdi ve cesetleri kuklalarım oldu. Benden üstün gelen kişi dışında hiç kimseden yardım isteyemem...";
			link.l1 = "Sana ne yapabilirim ki? Yapabileceğim tek şey, seni acıdan kurtarmak...";
			link.l1.go = "exit_talk_1";
		break;
		
		case "exit_talk_1":
			PlaySound("Voice\English\saga\Jessica Rose-03.wav");
			dialog.text = "Bana yardım et... Beni ona götür.";
			link.l1 = "Lawrence Beltrope'a mı? Peki bunu nasıl yapmamı bekliyorsun? Mürettebatım seni görür görmez ya kaçacak ya da hiç düşünmeden seni yakacak. Bu arada, hâlâ adamlarımı doğrayıp 'kontrol' edebiliyorsun...";
			link.l1.go = "exit_talk_2";
		break;
		
		case "exit_talk_2":
			dialog.text = "They won't see me. But you will. You must have already realised that I possess powers unavailable to the living. But I cannot board your ship without your permission. Take me to him.\nI won't stay with you for long. And I won't harm your people. Land me at Portland Bay in Jamaica at midnight; the following night we'll meet again and you will receive what you came here to find.";
			link.l1 = "Burada neden olduğumu nereden biliyorsun?";
			link.l1.go = "exit_talk_3";
		break;
		
		case "exit_talk_3":
			PlaySound("Voice\English\saga\Jessica Rose-01.wav");
			dialog.text = "I know a lot. More than the living do. I saw her... You need a document for her, and you will get it. You will get even more; I will give you something extra. Take me to him...";
			link.l1 = "Hm. Helen'e karşı bu kanlı niyetlerinden hoşlanmıyorum. Sakın ona dokunmaya kalkma. Sonuçta, annesinin yaptıklarından o sorumlu değil.";
			link.l1.go = "exit_talk_4";
		break;
		
		case "exit_talk_4":
			dialog.text = "Beni yendin. Ona zarar vermeyeceğim... Söz veriyorum.";
			link.l1 = "Daha bitmedi. Üzerimdeki sayısız lanetini kaldıracak mısın? Kabul ediyorum, onlarla sonsuza dek yaşama fikri pek hoşuma gitmiyor...";
			link.l1.go = "exit_talk_5";
		break;
		
		case "exit_talk_5":
			dialog.text = "O kadar basit değil... Portland Cove'da buluştuğumuzda, ben... Sana nasıl iyileşeceğini anlatacağım.";
			link.l1 = "Senden sonra ne?.. Ne demek istiyorsun?";
			link.l1.go = "exit_talk_6";
		break;
		
		case "exit_talk_6":
			dialog.text = "Onunla görüştükten sonra.";
			link.l1 = "Ah, bundan hoşlanmayacak. Tahmin edebiliyorum. Peki, özetleyelim: birincisi, kimse seni görmeyecek, buna söz veriyorsun; ikincisi, mürettebatıma zarar vermeyeceksin; üçüncüsü, Helen hakkında düşünmeye bile kalkmayacaksın; dördüncüsü, aradığım şeyi bana vereceksin; ve beşincisi, üzerimdeki lanetlerini kaldıracaksın. Doğru mu anladım?";
			link.l1.go = "exit_talk_7";
		break;
		
		case "exit_talk_7":
			dialog.text = "Az kaldı. Seni iyileştirmeyeceğim, ama nasıl yapacağını anlatacağım. Bunu kendin yapmak zorundasın.";
			link.l1 = "Pekâlâ. Anlaştık o zaman. Gemime binmene izin veriyorum.";
			link.l1.go = "exit";
			AddDialogExitQuest("Video_Reef2");
			NextDiag.TempNode = "exit_talk_8";
		break;
		
		case "exit_talk_8":
			PlaySound("Ambient\Teno_inside\teleporter.wav");
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			dialog.text = "";
			link.l1 = "Hey! Neredesin? Bir anda ortadan kayboldun...";
			link.l1.go = "exit_talk_9";
		break;
		
		case "exit_talk_9":
			DialogExit();
			LAi_group_Delete("EnemyFight");
			pchar.quest.Saga_JessFire.over = "yes"; 
			pchar.quest.Saga_JessFire1.over = "yes"; 
			pchar.quest.Saga_JessFire2.over = "yes";
			ref chr = &Locations[FindLocation(pchar.location)];
			DeleteAttribute(chr, "hell_fire_1");
			DeleteAttribute(chr, "hell_fire_2");
			DeleteAttribute(chr, "hell_fire_3");
			chrDisableReloadToLocation = false;//открыть локацию
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			AddQuestRecord("Shadows", "9");
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.questTemp.Saga.JessOnShip = "true"; // атрибут на отрицательные последствия
			pchar.quest.Saga_Jessika_Travel.win_condition.l1 = "Hour";
			pchar.quest.Saga_Jessika_Travel.win_condition.l1.start.hour = 0.00;
			pchar.quest.Saga_Jessika_Travel.win_condition.l1.finish.hour = 2.00;
			pchar.quest.Saga_Jessika_Travel.win_condition.l2 = "location";
			pchar.quest.Saga_Jessika_Travel.win_condition.l2.location = "shore36";
			pchar.quest.Saga_Jessika_Travel.function = "Saga_JessikaOnJamaica";
			NextDiag.CurrentNode = "shore";
			npchar.greeting = "jessika_2";
			LAi_LocationDisableOfficersGen(pchar.location, false);//офицеров пускать
			LAi_LocationDisableOfficersGen("shore36", true);//офицеров не пускать в бухту Портленд
		break;
		
		case "shore":
			dialog.text = "Sözünü tuttun - Jamaika'dayız. Yarın gece buraya gel, ben de verdiğim sözü tutacağım. Hoşça kal.";
			link.l1 = "Elveda...";
			link.l1.go = "shore_1";
		break;
		
		case "shore_1":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Saga.JessOnShip");
			DeleteAttribute(npchar, "SaveItemsForDead");
			DeleteAttribute(npchar, "DontClearDead");
			LAi_SetActorType(npchar);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			AddQuestRecord("Shadows", "10");
			SetFunctionTimerCondition("Saga_JessikaShoreWait", 0, 0, 1, false);
			NextDiag.CurrentNode = "shore_2";
			npchar.greeting = "jessika_3";
		break;
		
		case "shore_2":
			dialog.text = "Bitti, "+pchar.name+"...";
			link.l1 = "Ne demek istiyorsun?";
			link.l1.go = "shore_3";
		break;
		
		case "shore_3":
			dialog.text = "Bitti... Al, işte aradığın şey bu. Bu, rakibimin mektubu, onunla birlikte gömülmüştü. Oldukça iyi korunmuş. Onu affettim, artık ruhumda nefret yok.";
			link.l1 = "Onunla... karşılaştın mı? Lawrence ile birlikte mi?";
			link.l1.go = "shore_4";
		break;
		
		case "shore_4":
			GiveItem2Character(pchar, "letter_beatriss"); // дать письмо
			AddQuestRecordInfo("Letter_beatriss", "1");
			dialog.text = "Evet. Hayatında hissettiği son şey dehşetti. Ona acımıyorum.";
			link.l1 = "Tanrı günahkâr ruhunu affetsin... Görünen o ki, onu asla göremeyeceğim.";
			link.l1.go = "shore_5";
		break;
		
		case "shore_5":
			dialog.text = "Değerli hiçbir şeyini kaybetmedin. O çok kötü bir adamdı. Şimdi, birbirimize veda etmeliyiz, burada yapacak başka bir işim kalmadı. Yeminimi yerine getirdim ve büyünün gücü tükendi. Sana bir hediye sözü vermiştim. Al. Bu benim Flamberge’im. Artık ihtiyacım yok. Bu kılıç eşsizdir, dünyada bundan daha iyisini bulamazsın.";
			link.l1 = "Teşekkürler...";
			link.l1.go = "shore_6";
		break;
		
		case "shore_6":
			RemoveAllCharacterItems(npchar, true);
			GiveItem2Character(pchar, "blade_25");
			PlaySound("interface\important_item.wav");
			dialog.text = "Şimdi, sana gelince. Bridgetown'a git, oradaki kiliseye uğra ve üzerimdeki lanetleri kaldırmak için yardım iste. Orada bir rahip bulacaksın. Beni şahsen tanır. Onunla konuş, sana ne yapman gerektiğini anlatacaktır. Yirmi mum hazırla, onlara ihtiyacın olacak.";
			link.l1 = "Emin misin, beni iyileştirecek mi?";
			link.l1.go = "shore_7";
		break;
		
		case "shore_7":
			dialog.text = "Bunu kendin yapacaksın. Tanrı sana yol gösterecek. Emin ol. Her şey yoluna girecek.";
			link.l1 = "Pekala, hemen Barbados'a yelken açacağım. Peki şimdi ne olacak?";
			link.l1.go = "shore_8";
		break;
		
		case "shore_8":
			PlaySound("Voice\English\saga\Jessica Rose-04.wav");
			dialog.text = "Ve şimdi son bir dileğim var. Bedenimi burada, bu koyda deniz kenarına gömmeni istiyorum. Bu benim arzum. Belki bir gün zavallı Jessica'nın mezarını ziyaret edersin. Elveda, "+pchar.name+", ve benim için dua et...";
			link.l1 = "Jess?..";
			link.l1.go = "shore_9";
		break;
		
		case "shore_9":
			DialogExit();
			LAi_KillCharacter(npchar);
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen("shore36", false);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddQuestRecord("Shadows", "11");
			pchar.questTemp.Saga.JessTreatment = "true";
			// вытираем Белтропа
			sld = characterFromId("Beltrop");
			sld.lifeday = 0;
			pchar.questTemp.Saga.Beltrop_die = "true"; // Белтроп убит
			sld = ItemsFromID("letter_jess");
			sld.price = 1; // страницу можно выкладывать 270912 
		break;
		
		case "soul":
			dialog.text = "Beni tanıyor musun, Kaptan?";
			link.l1 = "Bu... bu sen misin? Ama nasıl?";
			link.l1.go = "soul_1";
		break;
		
		case "soul_1":
			dialog.text = "Evet, "+pchar.name+", benim, Jessica'yım! En azından yirmi yıl önce böyle görünüyordum.";
			link.l1 = "Yani... öldüm mü? Ama ne zaman? Nasıl?";
			link.l1.go = "soul_2";
		break;
		
		case "soul_2":
			dialog.text = "Ölmemişsin, "+pchar.name+" . Şu anda Bridgetown'daki kilisedesin. Sadece... uyuyorsun.";
			link.l1 = "Bu sadece bir rüya mı? Her şey fazlasıyla gerçek görünüyor...";
			link.l1.go = "soul_3";
		break;
		
		case "soul_3":
			dialog.text = "Bazen olur, "+pchar.name+". Tanrı seni duydu. Duaların sadece seni iyileştirmekle kalmadı, ruhumu da arındırdı. Çok teşekkür ederim, "+pchar.name+"! Ve resifte olanlar için senden özür dilemek istiyorum. Bu... yani, lütfen beni affet. Affını istemeden ayrılamazdım.";
			link.l1 = "Seni affediyorum, Jessica. Gerçekten yaşıyor muyum?";
			link.l1.go = "soul_4";
		break;
		
		case "soul_4":
			dialog.text = "Sen... Endişelenme. Yakında uyanacaksın. Sadece veda etmek istedim.";
			link.l1 = "O kadar... güzelsin ki!";
			link.l1.go = "soul_5";
		break;
		
		case "soul_5":
			dialog.text = "Beni beğeniyor musun? Evet, bir zamanlar Küçük Antiller’in en seçkin talipleri bana kur yapardı ve Isla Tesoro’daki her üç korsandan biri benim için düelloya hazırdı.";
			link.l1 = "Ama senin her zaman tek bir şeye ihtiyacın oldu... Eh, şu kızıl tılsım! Söylesene, nasıl bu hale geldin?";
			link.l1.go = "soul_6";
		break;
		
		case "soul_6":
			dialog.text = "Öfkem yüzünden. Nefretim yüzünden. Anlayamamak, affedememek ve unutamamak yüzünden. Yeni bir hayata başlayabilirdim, ama onun yerine kendimi aptalca ve anlamsız bir intikama adadım. Beni özgür bıraktın. Teşekkür ederim, "+pchar.name+"...";
			link.l1 = "Gerçekten hayatına acıyorum...";
			link.l1.go = "soul_7";
		break;
		
		// здесь проверяем Мэри
		case "soul_7":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{ // Мэри-офицер
				dialog.text = "Yapma... Zencefilli muskan hâlâ yanında...";
				link.l1 = "Ne demek?";
				link.l1.go = "mary_1";
				break;
			}
			if (!CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && CheckAttribute(pchar, "questTemp.LSC.marywait"))
			{ // Мэри осталась на острове
				dialog.text = "Dur... Hâlâ zencefilli tılsımın yanında...";
				link.l1 = "Ne demek?";
				link.l1.go = "mary_3";
				break;
			}
			dialog.text = "Yapma... Benim acı tecrübemi düşün ve aynı hataları tekrarlama. Sevdiğin insanların da aynı hataları yapmasına izin verme.";
			link.l1 = "Bunu dikkate alacağım ve aynı hataları bir daha asla yapmayacağım...";
			link.l1.go = "soul_8";
		break;
		
		case "mary_1":
			dialog.text = "Bir düşün. O senin geminde.";
			link.l1 = "Mary?!";
			link.l1.go = "mary_2";
		break;
		
		case "mary_2":
			dialog.text = "Evet. O, hayatında sahip olacağın en iyi kadın. Bunu unutma. Sevgisi saf, bağlılığı sonsuzdur. Cesur, genç ama çaresiz ve deneyimsiz. Pek çok şeyi anlamıyor. Ona iyi bak, koru ve aranıza kimsenin girmesine izin verme. O senin tılsımın...";
			link.l1 = "Ben... Onu asla bırakmayacağım ve onu her türlü tehlikeden koruyacağım.";
			link.l1.go = "soul_8";
		break;
		
		case "mary_3":
			dialog.text = "O, ölü gemilerden oluşan o garip adada... Orada yalnız değil, ama kendini yalnız hissediyor. Her sabah seni düşünerek uyanıyor, her gün senin için dua ediyor, her gece kamarasında bir ışık yanıyor ve yastığı gözyaşlarıyla ıslanıyor...";
			link.l1 = "Mary...";
			link.l1.go = "mary_4";
		break;
		
		case "mary_4":
			dialog.text = "Aranızda bir kız var. Bir zamanlar Lawrence ile benim aramda duran kadının kızı. Tılsımının kaderi senin ellerinde. Onlar bir arada var olamaz, tıpkı Beatrice ile benim olamadığımız gibi.";
			link.l1 = "Bunu nereden biliyorsun?";
			link.l1.go = "mary_5";
		break;
		
		case "mary_5":
			dialog.text = "Diğer taraf... Çok şey ortaya koyuyor... Seçim senin, ama unutma: Mary hayatında sahip olacağın en iyi insan. Onun sevgisi saf, bağlılığı sınırsız. Cesur, genç ama çaresiz ve tecrübesiz. Pek çok şeyi anlamıyor. Senin korumana, ilgine ve sevgine ihtiyacı var. O senin tılsımın.";
			link.l1 = "Bunu düşüneceğim. Kesinlikle yapacağım...";
			link.l1.go = "soul_8";
		break;
		
		case "soul_8":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_friend")) sTemp = "";
			else sTemp = "And about the daughter of Beatrice, know that your noble actions on her behalf will be left unvalued. Soon you will see that for yourself. Be careful with her. Well...\n";
			dialog.text = ""+sTemp+"Gitmem lazım. Artık veda etme zamanı... Bu sefer gerçekten. Jessica'yı unutma, ara sıra mezarını ziyaret etmeye çalış... Yerini sadece sen biliyorsun.";
			link.l1 = "Elbette, Jess. Oraya gidip senin için dua edeceğim.";
			link.l1.go = "soul_9";
		break;
		
		case "soul_9":
			dialog.text = "Teşekkür ederim. Hoşça kal, "+pchar.name+"! Hoşça kal!";
			link.l1 = "Hoşça kal, Jessica...";
			link.l1.go = "soul_10";
		break;
		
		case "soul_10":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Saga_JessikaSoul_4", -1);
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
