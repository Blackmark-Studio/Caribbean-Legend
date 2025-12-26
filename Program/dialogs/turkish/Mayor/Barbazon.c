// Жак Барбазон в Ле Франсуа
int iBarbazonTotalTemp;
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc, sTemp;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

//--> -----------------------------------------------блок angry-------------------------------------------------
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
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
					if (npchar.angry.name == "pirate_threat")
                    {
                        if (Dialog.CurrentNode == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                        else Dialog.CurrentNode = "AngryRepeat_1";
                    }
                break;
            }
        }
    }
//<-- -------------------------------------------блок angry------------------------------------------------------

	switch(Dialog.CurrentNode)
	{
	// ----------------------------------- Диалог первый - первая встреча---------------------------------------
		case "First time":
            if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Sen deli misin? Kasap mı olmak istedin? Bütün korsanlar sana öfkeli, oğlum, buradan gitmen en iyisi...","Sen kafayı yemişsin galiba, oğlan. Biraz kolunu kanadını açmak mı istedin? Alınma ama burada işin yok. Kaybol!");
				link.l1 = RandPhraseSimple("Dinle, durumu düzeltmek istiyorum...","Bu sorunu çözmeme yardım et...");
				link.l1.go = "pirate_town";
				break;
			}
			
			link.l0 = ""+npchar.name+", denizdeki güvenliğim hakkında" + GetSexPhrase("", " konuşmak istiyorum") + ". Sahil Kardeşliği tayfası benim mütevazı varlığıma fazla ilgi gösteriyor. Onları biraz dizginleyebilir misin?";
			link.l0.go = "pirate_threat";
			
			dialog.text = NPCStringReactionRepeat("Bana söyleyecek bir şeyin var mı? Yok mu? O zaman defol buradan!",
						"Bence kendimi açıkça ifade ettim, beni rahatsız etmeyi bırak.",
						"Ne kadar açık konuşsam da, hâlâ sinirimi bozuyorsun!","Doğrusu, bu kabalıktan bıktım artık.","repeat",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Zaten gidiyorum.",
						"Tabii, "+npchar.name+"...",
						"Üzgünüm, "+npchar.name+"...",
						"Ah...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			
		//----------------------------------Сага - искушение Барбазона---------------------------------------
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "begin")
			{
				link.l1 = "Seninle konuşmam lazım, Jacques... Baş başa.";
				link.l1.go = "Temptation";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "give_silk" && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 60)
			{
				link.l1 = "Ben Saint Martin'den geliyorum, Jacques...";
				link.l1.go = "Temptation_6";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "terrax")
			{
				link.l1 = "Ve ne zaman havlamayı bırakıp adam gibi konuşacaksın, Jacques? Beni görmeyi beklemiyordun, değil mi?";
				link.l1.go = "terrax";
			}
			
			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
				{
					link.l1 = "Tutsak hakkında konuşmaya geldim.";
					link.l1.go = "CapComission1";
					DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
				}
             	
				if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway") // лесник. новая проверка. искл. возможность сразу сдать задание,минуя 15 дней.
				{
					link.l1 = "Merhaba Jacques, görevin için buradayım.";
					link.l1.go = "CapComission3";
				}
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak") && !CheckAttribute(pchar,"GenQuest.CaptainComission.vikupzaplatil")) 
				{ // лесник . второй диалог с проверкой ,если ГГ ещё не принес деньги за выкуп.
					link.l1 = "Tutsak hakkında konuşmaya geldim.";
					link.l1.go = "CapComission6";
				}
			}	
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin")
			{
				link.l1 = "Tutsaklarla ilgili işlere bulaştığını duydum...";
				link.l1.go = "Marginpassenger";
			}
		break;
			

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Sen deli misin? Kasapçılık mı oynamak istedin? Bütün korsanlar sana öfkeli, oğlum, buradan gitmen en iyisi...","Aklını kaçırmışsın, çocuk. Biraz kaslarını mı göstermek istedin? Alınma ama burada işin yok. Kaybol!");
				link.l1 = RandPhraseSimple("Dinle, durumu düzeltmek istiyorum...","Bu sorunu çözmeme yardım et...");
				link.l1.go = "pirate_town";
				break;
			}
			
			link.l0 = ""+npchar.name+", denizdeki güvenliğim hakkında" + GetSexPhrase("", " konuşmak istiyorum") + ". Sahil Kardeşliği tayfası benim mütevazı varlığıma fazla ilgi gösteriyor. Onları biraz dizginleyebilir misin?";
			link.l0.go = "pirate_threat";
			
			dialog.text = NPCStringReactionRepeat(GetFullName(pchar)+"! Bu sefer ne istiyorsun?",
						"Bana söylemeyi unuttuğun bir şey mi var? Dinliyorum.",
						"Bu daha ne kadar sürecek... Yapacak bir işin yoksa, başkalarını rahatsız etme!","Benden kibar olmamı istedin. Ama ben de senden aynısını bekliyorum!","repeat",10,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Önemli bir şey değil. Sadece bir ziyaret.",
						"Hiçbir şey...",
						"Pekala...",
						"Haklısın. Özür dilerim.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";

			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
			{
				link.l1 = "Tutsak hakkında konuşmaya geldim.";
				link.l1.go = "CapComission1";
				DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
			}	
			if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway")//  правка лесник,новая проверка ,исключающая тут же сдачу задания
			{
				link.l1 = "Merhaba Jacques, görevin hakkında konuşmamız lazım.";
				link.l1.go = "CapComission3";
			}
		/*	if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak")) //лишний диалог лесник
			{
				link.l1 = "Tutsak hakkında konuşmaya geldim.";
				link.l1.go = "CapComission6";
			}*/
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin")
			{
				link.l1 = "Tutsaklarla ilgili işlerde parmağının olduğunu duydum...";
				link.l1.go = "Marginpassenger";
			}
		break;

//--> -----------------------------------Сага - Искушение Барбазона---------------------------------------------
		case "Temptation":
			dialog.text = "Beni rahatsız etmenin tehlikeli olduğunu biliyor musun? Peki, dinliyorum.";
			link.l1 = "Bir borcum var. Hem de büyük bir borç. Ödeme zamanı yaklaşıyor ve elimde beş kuruş yok. İyi kalpli insanlar, senin iş bitirici biri olduğunu ve büyük ganimetlerin yerini her zaman bildiğini fısıldadı...";
			link.l1.go = "Temptation_1";
		break;
		
		case "Temptation_1":
			dialog.text = "Dinle, oğlum! Bana sadık olanlara Jacques the Kindman’ım. Diğerlerine Barbazon’um, bazen de bizzat Lucifer olurum. Sana güvenebileceğimi nereden bileyim?";
			link.l1 = "Beni dene. Sana yemin ederim, pişman olmayacaksın!";
			link.l1.go = "Temptation_2";
		break;
		
		case "Temptation_2":
			dialog.text = "Hm... Sanırım Jacques the Kindman'ın kendisini dolandıranlara ne yaptığını biliyorsun, değil mi? Neyse, seni korkunç ayrıntılarla sıkmayacağım. Küçük bir işim var. Başarırsan, tüm maddi sıkıntıların sona erecek.";
			link.l1 = "Benden şüphe etme, çok kavgaya girdim ve...";
			link.l1.go = "Temptation_3";
		break;
		
		case "Temptation_3":
			dialog.text = "Shut up and listen to me! A few weeks ago, a Dutch patrol caught one of my employees not far from Saint Martin. He was delivering Dutch silk to me. It's very rare; the Dutch bring only small batches here for the needs of the Company's navy.\nSo, I managed to buy six bales of silk, and Simon Morel was supposed to bring them to me on his brigantine, 'Salt Dog', but he ran into a Dutch patrol by accident. Or perhaps not by accident. That's what Morel's navigator said—he told me he was the only one who survived the fight.\nHe also gave me Morel's log, which confirms the story. According to the log, Morel threw the silk overboard during an escape attempt. It's strange, isn't it? Silk is light. They should have thrown their cannons overboard; they didn't stand a chance against the patrol anyway.";
			link.l1 = "Burada gerçekten bir terslik var.";
			link.l1.go = "Temptation_4";
		break;
		
		case "Temptation_4":
			dialog.text = "Her şey mümkün. Benim için çalışan çok cesur adam var, ama akıllı olanlar çok daha az. Alınma, heh. Morel’in yükü attığı yeri mutlaka kontrol etmelisin. Kaptanın günlüğüne göre, 21 derece 10' Kuzey ve 61 derece 30' Batı.\nHollandalılar ipeği mantar çubuklara sarar, bu yüzden balyalar hâlâ suyun üstünde olmalı. Altı balya olmalı. Hemen yelken aç, zaman çok önemli.";
			link.l1 = "Yoldayım!";
			link.l1.go = "Temptation_5";
		break;
		
		case "Temptation_5":
			DialogExit();
			SetFunctionTimerCondition("Saga_BarbTemptationOver", 0, 0, 10, false); // таймер
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			pchar.quest.BarbTemptation.win_condition.l1 = "location";
			pchar.quest.BarbTemptation.win_condition.l1.location = "SentMartin";
			pchar.quest.BarbTemptation.function = "Saga_BarbTemptationBarkas";
			pchar.questTemp.Saga.BarbTemptation = "silk";
			AddQuestRecord("BarbTemptation", "2");
		break;
		
		case "Temptation_6":
			dialog.text = "Harika! İpeğimi buldun mu?";
			link.l1 = "Evet, altı tane, dediğin gibi.";
			link.l1.go = "temptation_wrong";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 90)
			{
				link.l2 = "Yes. But there were more than you said, nine of them, not six. I brought them all here; your part is to figure out how this could happen.";
				link.l2.go = "temptation_right";
			}
		break;
		
		case "temptation_wrong":
			dialog.text = "Yanlış cevap. Dokuz balya olmalıydı. Ve eğer altı tanesini bulduysan, geri kalanını da bulmuş olmalısın. Yani ya bir faresin ya da tembelin tekisin. Bana üç balya ipek borçlusun, üstüne üç tane daha... 'ahlaki tazminat' olarak, beni kandırmaya kalkıştığın için.";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 120)
			{
				link.l1 = "Ne akıllısın sen! Bunu unutmayacağım. Al ipeğini, ve benim hatamı da unutalım.";
				link.l1.go = "temptation_wrong_1";
			}
			link.l2 = "Bana altı balya olduğu söylendi, bir tane bile fazla yoktu. Bulduğum her şeyi sana verdim ve senin ne düşündüğün umurumda değil. Daha fazla ipeğim yok.";
			link.l2.go = "temptation_wrong_2";
		break;
		
		case "temptation_wrong_1":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 120);
			dialog.text = "Pekala. Umarım bir daha olmaz, çünkü sana önemli bir görev vermek istiyorum. Ne kadar para kazanmak istiyorsun?";
			link.l1 = "Para her zaman makbuldür, şimdilik elli bin peso gayet iyi olur.";
			link.l1.go = "junior";
		break;
		
		case "temptation_wrong_2":
			dialog.text = "Ha, demek şimdi böyle konuşuyorsun! Bununla paçayı sıyıramazsın. Seni uyardım – sakın ha bana kazık atmaya kalkışma! Muhafızlar! Malikânede lanet bir fare var!";
			link.l1 = "Kahretsin!";
			link.l1.go = "temptation_wrong_fight";
		break;
		
		case "temptation_wrong_fight":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetWarriorType(npchar);
			ChangeCharacterAddressGroup(npchar, "LeFransua_townhall", "goto", "goto1");
			LAi_SetImmortal(npchar, true);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i = 1; i <= 3; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("BarbGuard_"+i, "citiz_4"+(i+6), "man", "man", 80, PIRATE, 1, true, "quest"));
				FantomMakeCoolFighter(sld, 80, 100, 100, "blade_21", "pistol4", "bullet", 3000);
				ChangeCharacterAddressGroup(sld, "LeFransua_townhall", "reload", "reload1");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "temptation_right":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 80);
			dialog.text = "İyi iş çıkardın. Seni açgözlülük konusunda test ediyordum ve sınavımı geçtin. Orada dokuz balya olmalıydı. Bir tanesi senin. Şimdi ciddi şekilde konuşabiliriz. Ne kadar paraya ihtiyacın var?";
			link.l1 = "Para her zaman makbuldür, şimdilik elli bin peso yeter.";
			link.l1.go = "junior";
		break;
		
		case "junior":
			dialog.text = "Daha fazlasını kazanmak için bir fırsatın var. Belli bir beyefendi, hassas ve tehlikeli bir görev için senin gibi güvenilir birini bulmamı istedi. Bu adam oldukça zengin ve onu hayal kırıklığına uğratmazsan seni buna göre ödüllendirecek.";
			link.l1 = "Hazırım.";
			link.l1.go = "junior_1";
		break;
		
		case "junior_1":
			dialog.text = "Pekâlâ. Şimdi iyi dinle. Onun 'Knave' adında bir adamını bulmalısın. O, 'Marlin' adlı polacrenin kaptanı, hakkında bildiğim tek şey bu. Onu Kapsterville'de bulacaksın. Parola: 'av başladı'. Ne yapacağını o sana söyleyecek. Bana hiçbir borcun yok. Sadece sana yardım etmek istiyorum. Şansın yaver giderse, tekrar karşılaşırız.";
			link.l1 = "Yardımın için teşekkürler. Yoluma devam ediyorum!";
			link.l1.go = "junior_2";
		break;
		
		case "junior_2":
			DialogExit();
			AddQuestRecord("BarbTemptation", "7");
			Saga_SetJuniorInCharles(); // ставим Валета
			pchar.questTemp.Saga.BarbTemptation = "valet";
		break;
		
		case "terrax":
			dialog.text = "Ne?! Senin ... parçalarım...";
			link.l1 = "You won't, Barbazon. Let's see our cards! I work for Jan Svenson. I have exposed your conspiracy with Jackman. I know everything—what you were planning and what role you played as well. Jackman and his brother are dead; the first killed Blaze Sharp, sealing his own fate, and the second wasn't talkative enough, I'm afraid...";
			link.l1.go = "terrax_1";
		break;
		
		case "terrax_1":
			dialog.text = "Lanet olsun! Tyrex bunu asla affetmeyecek, ama ben hâlâ..";
			link.l1 = "Aptalca bir şey yapma, Jacques. Bu konuşmanın kolay geçmeyeceğini biliyordum, bu yüzden önlemimi aldım. Pencereye bir bak... kulübün etrafı musketerlerimle çevrili. Adamlarım köyünün her yanında, kapının hemen dışında da bir saldırı birliği var. Katliam başlatmak mı istiyorsun? Çok kolay!";
			link.l1.go = "terrax_2";
		break;
		
		case "terrax_2":
			dialog.text = "Lanet olsun sana! Ne istiyorsun?";
			link.l1 = "Bana inanmayacaksın Barbazon, ama tek istediğim... huzur! Huzur istiyorum. Bu yüzden Tyrex'e ona karşı kurduğun bu komplodaki rolünü anlatmayacağım. Ama sadece istediğimi yaparsan...";
			link.l1.go = "terrax_3";
		break;
		
		case "terrax_3":
			dialog.text = "Benden ne istiyorsun? Para mı? Ne kadar?";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) // Акула жив
			{
				link.l1 = "Ah, hayır, onu o beyni olmayan adamlarına bırak. Ben başka bir şey istiyorum. Steven Dodson için oyunu istiyorum.";
			}
			else
			{
				link.l1 = "Ah, hayır, onu senin akılsız adamlarına bırak. Ben başka bir şey istiyorum. Marcus Tyrex için oyuna ihtiyacım var.";
			}
			link.l1.go = "terrax_4";
		break;
		
		case "terrax_4":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "And Steven Dodson is on our side.";
			else sTemp = "";
			dialog.text = "Cidden mi? Bir düşüneyim... ya hayır dersem?";
			link.l1 = "O zaman tek başına kalırsın. Tamamen yalnız. Svenson, Tyrex ve Hawk sana karşı olacaklar."+sTemp+"Onlara sadece Knave'in mektubunu, Jackman'ın kardeşini göstereceğim, bir de benim sözüme güvenilecek. Peki, sence bundan sonra ne kadar rahat oturabileceksin?";
			link.l1.go = "terrax_5";
		break;
		
		case "terrax_5":
			dialog.text = "Hawk mı? O hayatta mı?!";
			link.l1 = "O öyle. Onu Jackman'ın kurduğu tuzaktan kurtardım. Yani Jacob'un en yakın dostu artık onun ezeli düşmanı olacak. Ve ben de onlara katılacağım, bunu unutma, Barbazon.";
			link.l1.go = "terrax_6";
		break;
		
		case "terrax_6":
			dialog.text = "Jackman benim dostum değil! Kahretsin seni! Beni köşeye sıkıştırdın!";
			link.l1 = "Saçmalık. Sana söylediğim adama oyunu ver, senin için hiçbir şey değişmeyecek. Zaten söyledim Jacques, ben barış istiyorum. Tüm baronları sana düşman edebilirim ama etmeyeceğim... henüz.";
			link.l1.go = "terrax_7";
		break;
		
		case "terrax_7":
			GiveItem2Character(pchar, "splinter_jb"); // дать осколок
			dialog.text = "Pekala. Anlaştık. Sözüm söz. Al, taş parçamı da veriyorum, sana lazım, değil mi?";
			link.l1 = "Aynen öyle. Anlaştığımıza sevindim, Jacques. Ve 'Knave'in mektubunu tatlı bir hatıra olarak al. Ya da daha iyisi, yak onu — kimsenin eline geçmesini istemezsin. Ha, bir de son bir şey...";
			link.l1.go = "terrax_8";
		break;
		
		case "terrax_8":
			RemoveItems(pchar, "letter_chad", 1);
			dialog.text = "Bir de bu mu?! Daha ne istiyorsun benden?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Barbazon"))
			{
				link.l1 = "Sana bir şeyi hatırlatayım. Çok değil, kısa bir süre önce köpeğin Ignacio Marco'yu beni öldürmesi için gönderdin. Onu öldüren bendim. İspanyol altın gemisini yağmalama planını toprağa gömen de bendim. Arkadaşlarını Saint Martin yakınlarında İspanyol pususuna gönderen de bendim. Benim adım Charlie Prince! Artık işimiz bitti, Jacques, bir dahaki karşılaşmamızda bana daha kibar davran. Bana inan, 'velet', tekrar karşılaşacağız, hem de bir kereden fazla, eminim.";
				link.l1.go = "terrax_8_1";
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Barbazon") && CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
				{
					link.l1 = "Sana bir şeyi hatırlatayım. Çok da uzun zaman önce değil, köpeğin Ignacio Marco'yu beni öldürmesi için gönderdin. Onu öldüren bendim. İspanyol altın gemisini yağmalama planını toprağa gömen de bendim. Benim adım Charlie Prince! Artık işimiz bitti, Jacques, bir dahaki karşılaşmamızda bana daha kibar davran. İnan bana, 'çocuk', tekrar karşılaşacağız, hem de bir kereden fazla, öyle tahmin ediyorum. Unutma, tüm korsan baronları benim tarafımda. Elveda, Barbazon...";
					link.l1.go = "terrax_9";
				}
				else
				{
					link.l1 = "Bir dahaki karşılaşmamızda bana daha kibar davran. İnan bana, 'velet', tekrar görüşeceğiz, hem de bir kereden fazla, sanırım. Unutma, Karayip'teki bütün korsan baronları benim tarafımda. Hoşça kal, Barbazon...";
					link.l1.go = "terrax_9";
				}
			}
		break;
		
		case "terrax_8_1":
			dialog.text = "";
			link.l1 = "Unutma, tüm korsan baronları benim tarafımda. Elveda, Barbazon...";
			link.l1.go = "terrax_9";
		break;
		
		case "terrax_9":
			DialogExit();
			NextDiag.CurrentNode = "I_know_you_good";
			AddQuestRecord("BarbTemptation", "26");
			if (CheckCharacterItem(pchar, "splinter_mt") && CheckCharacterItem(pchar, "splinter_jb") && CheckCharacterItem(pchar, "splinter_zm")) Saga_GiveCalendar();
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Saga_SGM_"+i);
				LAi_SetCitizenType(sld);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
				sld.lifeday = 0;
			}
			ChangeCharacterComplexReputation(pchar, "fame", 1);
			bDisableFastReload = false;
			LAi_LocationFightDisable(&Locations[FindLocation("LeFransua_town")], false);
		break;

//-----------------------------------Поручение капитана - Выкуп-------------------------------------------------
		case "CapComission1":
			dialog.text = "Ha-ha. Burada sadece bir mahkumum olduğunu mu sanıyorsun? Adını söyle.";
			link.l1 = pchar.GenQuest.CaptainComission.SlaveName+" . O burada mı?";
			link.l1.go = "CapComission2";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
		break;

		case "CapComission2":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.DaysLeft"))
			{
				dialog.text = "O öyleydi. Onu bir hafta önce buradayken Barbadoslu o plantasyon sahibine - Albay Bishop'a sattım.";
				link.l1 = "Lanet olsun...";
				link.l1.go = "CapComission2_1";
			}
			else
			{
				dialog.text = "Ah, sonunda. Onu Barbados'tan şu plantasyon sahibine satmayı düşünüyordum, bir iki haftaya burada olacak... Fidyen var mı?";
				link.l1 = "Bak, ufak bir sorun var... Aslında o kadar param yok. Ama çalışmaya hazırım.";
				link.l1.go = "CapComission2_2";
				if(makeint(pchar.money) > 150000)
				{
					link.l2 = "Onu satmamış olman iyi. Al, paraların – 150.000 peso. Onu nerede bulabilirim?";
					link.l2.go = "CapComission2_3";
				}	
			}
		break;
		
		case "CapComission2_1":
			dialog.text = "Çok yavaştın... Hem, sana ne ondan? Ben sadece akrabalarıyla pazarlık ettim.";
			link.l1 = "Beni buraya gelmem için çağırdılar.";
			link.l1.go = "CapComission2_11";
		break;
		
		case "CapComission2_11":
			dialog.text = "Pekâlâ, geç kaldın. Yapabileceğim bir şey yok.";
			link.l1 = "Dinle, ona kaça sattın, sır değilse?"; 
			link.l1.go = "CapComission2_12";
		break;
		
		case "CapComission2_12":
			dialog.text = "Eh, değil. Ama sana söylemem... Söylesem de sadece güleceksin. Ha-ha-ha-ha! Hoşça kal.";
			link.l1 = "Görüşürüz.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", "Jacques Barbazon");//правка лесник.  в СЖ запись ниже не работает																																				  
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			CaptainComission_GenerateManager();
		break;
		
		case "CapComission2_2":
			if(rand(3) == 1)
			{

				dialog.text = "Pekala, "+pchar.name+", biliyorsun, işler öyle yürümüyor. Parayı getir, o zavallıyı alırsın, ha-ha.";
				link.l1 = "Pekala. Görüşürüz.";
				link.l1.go = "CapComission2_4";
			}
			else
			{
				dialog.text = "Pekala, pekala... Bir işim var... Nereden başlayacağımı bile bilmiyorum. Haddini aşan bir korsanı batırmam gerek.";
				link.l1 = "Onu ormanda öldürmek daha kolay olmaz mı?";
				link.l1.go = "CapComission2_2_1";
			}
		break;

		case "CapComission2_2_1":
			dialog.text = "İşler böyle yürümez, biliyorsun... Onun ölmesini istemiyorum, sadece bazılarına ganimetten payımı almamayı öğretmem gerek. Ama sonunda köpekbalıklarına yem olursa, hiç üzülmem.";
			link.l1 = "Neden kendi adamlarını onun peşinden göndermiyorsun?";
			link.l1.go = "CapComission2_2_2";
		break;
		
		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			sLoc = XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Dat"); // belamour gen
			dialog.text = "Hm... Pekala, "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.UnknownPirateName,NAME_NOM)+" bazı korsanları ganimet paylarının bizim gizli depomuzda, şuracıkta saklandığına inandırmış "+XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore+"Gen")+". İki gemileri '"+pchar.GenQuest.CaptainComission.ShipName1+"' ve '"+pchar.GenQuest.CaptainComission.ShipName2+"' demir aldıktan kısa bir süre sonra yelken açtı ve "+sLoc+". Şimdi bu işi adamlarıma neden emanet edemeyeceğimi anlıyorsun, değil mi?";
			link.l1 = "Evet, biliyorum. Ne kadar vaktim var?";
			link.l1.go = "CapComission2_2_3";
		break;
		
		case "CapComission2_2_3":
			dialog.text = "12 ila 15 gün, daha fazla değil. Onların gizli yere ulaşmaması benim için önemli, yoksa değerli yükle birlikte onları batırmanın bir anlamı kalmaz. O durumda, buraya getirmeleri daha iyi olurdu...";
			link.l1 = "Pekala, varım. Onları yakalamaya çalışacağım.";
			link.l1.go = "CapComission2_2_4";
		break;
		
		case "CapComission2_2_4":
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", "Jacques Barbazon");//правка
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));// в СЖ не работает имя . лесник
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Dat")); // belamour gen
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Voc")); // belamour gen
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips"; 
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);
			
			DialogExit();
		break;
		
		case "CapComission2_3":
			dialog.text = "Merak etme. Adamlarım onu gemine götürecek. Hem, sana ne onun derdinden?";
			link.l1 = "Hayır, getirmemi akrabaları istedi.";
			link.l1.go = "CapComission2_31";
		break;
		
		case "CapComission2_31":
			dialog.text = "Ah, bu iyi. Adamın için bu kadar düşük bir fiyat teklif ettiğime neredeyse üzülecektim. Ha-ha-ha-ha! Hoşça kal.";
			link.l1 = "Görüşürüz.";
			link.l1.go = "CapComission2_32";
		break;
		
		case "CapComission2_32":
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc")); // belamour gen
			addMoneyToCharacter(pchar, -150000);
			pchar.GenQuest.CaptainComission.vikupzaplatil = true; // новая проверка ,если шарль заплатил выкуп за пленника. лесник																																								
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission2_4":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
			{
				AddQuestRecord("CaptainComission1", "31");
				AddQuestUserData("CaptainComission1", "sName", "Jacques Barbazon");		// лесник																												  
				//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM)); в СЖ не работает
			}	
			pchar.GenQuest.CaptainComission.RepeatSpeak = true;		
			DialogExit();
		break;
		
		case "CapComission3":
			dialog.text = "So, , "+GetFullName(pchar)+", adamlarımı mı batırdın? He-he-he...";
			if(pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = "Hayır. Onları yakalayamadım. Ve dönüş yolunda da karşılaşmadım.";
				link.l1.go = "CapComission4";
			}
			if(pchar.GenQuest.CaptainComission.PirateShips == "died")	
			{
				link.l1 = "Yaptım. Onları köpekbalıklarına yem ettim.";
				link.l1.go = "CapComission5";
			}
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
		break;
		
		case "CapComission4":
			dialog.text = "Lanet olsun! Onlarla karşılaşmış olsam da olmasam da, artık fark etmez! Peki, sıradaki önerin ne olacak?";
			link.l1 = "Belki bana daha kolay bir işin vardır?";
			link.l1.go = "CapComission4_1";
			link.l2 = "Dinle, "+NPChar.name+", esiri için fiyatı düşür...";
			link.l2.go = "CapComission4_2";
		break;
		
		case "CapComission4_1":
			dialog.text = "Hayır.";
			link.l1 = "Öyleyse hoşça kal...";
			link.l1.go = "CapComission4_3";
		break;
		
		case "CapComission4_2":
			dialog.text = "Fiyatı düşürmek mi?! Senin beceriksizliğin yüzünden malımı kaybettim! Şimdi ise fiyatı yükseltebilirim! İstersen onu 200.000 pesoya alırsın, istemiyorsan defolup gidersin.";
			link.l1 = "Çok pahalı... Hoşça kal...";
			link.l1.go = "CapComission4_4";
			if(sti(pchar.money) >= 200000)
			{
				link.l2 = "Lanet olsun, al şu paralarını.";
				link.l2.go = "CapComission4_5";
			}	
		break;
		
		case "CapComission4_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", "Barbazon"); // лесник																			  
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));// в СЖ не работает
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();
		break;
		
		case "CapComission4_4":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "28");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", "Barbazon"); // правка	// лесник																	  
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM)); в сж не работает
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
		break;
		
		case "CapComission4_5":
			dialog.text = "Bu zavallıyı alabilirsin...";
			link.l1 = "Elveda.";
			link.l1.go = "CapComission4_6";
		break;
		
		case "CapComission4_6":
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", "Barbazon"); // правки имени в сж лесник
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));//в СЖ не работает // belamour gen : это хорошо, но закомментить нужно было)))
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			DialogExit();	
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission5":
			dialog.text = "Ho-ho! Aferin! Al şu zavallını ve bol şans.";
			link.l1 = "Teşekkürler. Hoşça kal.";
			link.l1.go = "CapComission5_1";
		break;
		
		case "CapComission5_1":
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
	   	/*case "CapComission6":    // ЕСЛИ В ПЕРВЫЙ РАЗ ОТКАЗАЛ В ЗАДАНИИ ,ТО ПУСТЬ БАБКИ ИЩЕТ
		     ИНАЧЕ ПОВТОРНАЯ ДАЧА ЗАДАНИЯ ПРЕВРАЩАЕТ КВЕСТ В КАШУ.. лесник
			dialog.text = "Fidyeyi getirdin mi "+GetSexPhrase("","ла")+"? Onu plantasyon sahiplerine satacağımı söylerken şaka yapmıyordum.";			
			link.l1 = "Dinle, "+NPChar.name+", bak şimdi... O kadar param yok. Ama istekliyim"+GetSexPhrase("","а")+" çalışmak.";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "Onu satmamış olman iyi. Al bakalım, 150.000 peso. Nerede bulabilirim onu?"link.l2.go ="CapComission2_3";
			}			
		break;*/
		  case "CapComission6":                        // лесник . пусть шарль бабло ищет,или забить на пленника.
			dialog.text = "Parayı getirdin mi? O adamı plantasyona satmak konusunda şaka yapmıyordum.";			
			link.l1 = "Param yok, "+NPChar.name+", ama üzerinde çalışıyorum.";
			link.l1.go = "exit";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "Onu satmamış olman iyi. Al, paraların burada – 150.000 peso. Onu nerede bulabilirim?"link.l2.go ="CapComission2_3";
			}			
		break;
																																					 																																													  																																															
//--------------------------------------------Похититель------------------------------------------------------
		case "Marginpassenger":
			dialog.text = "Ve benim ne yaptığımla neden ilgileniyorsun? Biliyor musun, en iyisi sen buradan git...";
			link.l1 = "Tshh, sakin ol. Seninle bir işim var. Esirinle ilgili.";
			link.l1.go = "Marginpassenger_1";
		break;
		
		case "Marginpassenger_1":
			dialog.text = "Ah, peki. Kimi fidyeyle serbest bırakmamı istiyorsun?";
			link.l1 = "Bekle.   Kimseyi satın almaya gelmedim, sana bir esiri satın alma fırsatı sunmaya geldim.   Ve, şey, onun için fidye alman için de bir fırsatın olacak.";
			link.l1.go = "Marginpassenger_2";
		break;
		
		case "Marginpassenger_2":
			dialog.text = "Hm. Peki neden benim yardımımı istiyorsun? Parayı doğrudan kendin almak istemiyor musun?";
			link.l1 = "Bu benim için oldukça riskli. Yetkililerle başım belaya girebilir.";
			link.l1.go = "Marginpassenger_3";
		break;
		
		case "Marginpassenger_3":
			dialog.text = "Ha-h... peki o zaman. Göster bakalım. Kim bu esirin?";
			link.l1 = "Bu "+pchar.GenQuest.Marginpassenger.Text+" "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City+"Gen")+".";
			link.l1.go = "Marginpassenger_4";
		break;
		
		case "Marginpassenger_4":
			int iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "Anladım... yalan söylemiyorsan bu adil bir takas olurdu. Sanırım bu adam için sana ödeme yapabilirim "+iTemp+" pesos, ya da istersen sana ilginç bir bilgi verebilirim. Seçim senin.";
			link.l1 = "En iyisi peso alayım. Bu işten bıktım artık...";
			link.l1.go = "Marginpassenger_money";
			link.l2 = "Ha! Devam et, anlat bakalım. Eminim bana ilginç bir şeyin vardır.";
			link.l2.go = "Marginpassenger_offer";
		break;
		
		case "Marginpassenger_money":
			dialog.text = "Para işte. Al onları. Artık senin sorunun değil. Eşyayı buraya satmaya getir.";
			link.l1 = "Şu anda kasaba kapılarının yakınında olmalı. Teşekkür ederim! Gerçekten bana çok yardımcı oldun.";
			link.l1.go = "Marginpassenger_money_1";
		break;
		
		case "Marginpassenger_money_1":
			iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "Rica ederim, bana daha fazlasını getir... Görüşürüz!";
			link.l1 = "İyi şanslar...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, iTemp);
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			AddQuestRecord("Marginpassenger", "12");
			AddQuestUserData("Marginpassenger", "sSum", iTemp);
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
		break;
		
		case "Marginpassenger_offer":
			pchar.GenQuest.Marginpassenger.Goods = GetRandomGood(FLAG_GOODS_TYPE_EXPORT, FLAG_GOODS_VALUABLE_WOOD);
			pchar.GenQuest.Marginpassenger.GoodsQty = 200+rand(10)*10;
			switch (hrand(1))
			{
				case 0: //бухта на южном мейне
					SelectSouthshore();
					while (!isLocationFreeForQuests(pchar.GenQuest.Marginpassenger.Shore)) SelectSouthshore();
					dialog.text = "Akıllı bir adamla iş yapmak güzeldir. Şimdi dinle: birkaç gün içinde "+XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat")+" Anakaradan yüklü değerli mallarla bir İspanyol seferi gelecek. Yükü alacak bir gemiyi bekliyor olacaklar. Bir hafta içinde oraya varırsan, yükü kendin alabilirsin.\nBen olsam, şimdiye çoktan gemime gidiyor olurdum. Ve mahkumu buraya getir.";
					link.l1 = "Teşekkürler! Bu mallar, yaşadığım sıkıntılar için iyi bir karşılık olacak. Yolcum da muhtemelen kasaba kapılarının yakınında. Onu sana getirecekler.";
					link.l1.go = "Marginpassenger_offer_1";
				break;
				
				case 1: //просто кораблик
					SelectSouthcity();
					pchar.GenQuest.Marginpassenger.ShipName1 = GenerateRandomNameToShip(SPAIN);
					dialog.text = "Akıllı bir adamla iş yapmak güzeldir. Şimdi dinle: yaklaşık bir hafta sonra, bir İspanyol brigantini '"+pchar.GenQuest.Marginpassenger.ShipName1+" değerli mallarla yüklü olan  bir gemi  yola çıkacak "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen")+" to "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Gen")+". Acele edersen kolayca yakalarsın.\nHâlâ burada mısın? Ben olsam çoktan gemime gidiyordum. Ve mahkumu buraya getir.";
					link.l1 = "Teşekkürler! Mallar, yaşadığım sıkıntılar için iyi bir karşılık olacak. Ve yolcum muhtemelen şehir kapılarının yakınında olmalı. Onu sana getirecekler.";
					link.l1.go = "Marginpassenger_offer_2";
				break;
			}
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			pchar.GenQuest.Marginpassenger = "final";
		break;
		
		case "Marginpassenger_offer_1":
			DialogExit();
			AddQuestRecord("Marginpassenger", "13");
			AddQuestUserData("Marginpassenger", "sShore", XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat"));//лесник - окончание в СЖ // belamour gen
			AddQuestUserData("Marginpassenger", "sName", "Jacques the Kindman"));
			SetFunctionTimerCondition("Marginpassenger_SouthshoreOver", 0, 0, 7, false);
			pchar.quest.Marginpassenger.win_condition.l1 = "location";
			pchar.quest.Marginpassenger.win_condition.l1.location = pchar.GenQuest.Marginpassenger.Shore;
			pchar.quest.Marginpassenger.function = "Marginpassenger_Southshore";
		break;
		
		case "Marginpassenger_offer_2":
			DialogExit();
			AddQuestRecord("Marginpassenger", "16");
			AddQuestUserData("Marginpassenger", "sName", "Jacques the Kindman"));
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen"));
			AddQuestUserData("Marginpassenger", "sCity1", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Acc")); // лесник - окончание в СЖ
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName1);
			SetFunctionTimerCondition("Marginpassenger_SouthshipInWorld", 0, 0, 5+rand(2), false);
		break;
		
//---------------------------------------попытка залезть в сундуки --------------------------------------------
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Soygun!!! Bu kabul edilemez! Hazır ol, "+GetSexPhrase("oğlan","kız")+"...","Hey, orada ne halt ediyorsun?! Beni soyabileceğini mi sandın? İşin bitti... ","Ne oluyor lan? Ellerini çek! Demek ki hırsızmışsın! Yolun sonu, alçak...");
			link.l1 = LinkRandPhrase("Kahretsin!","Caramba!!","Lanet olsun!!");
			link.l1.go = "PL_Q3_fight";
		break;
					
// ----------------------------------------------блок нод angry--------------------------------------------------
		case "AngryRepeat_1":
            dialog.text = "Defol buradan!";
			link.l1 = "Hay aksi...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Beni ucuz laflarınla oyalama. Bir dahaki sefere, sonucu hiç beğenmeyeceksin...";
        			link.l1 = "Anladım.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = RandPhraseSimple("Bitti, konuşmak yok.","Seninle artık konuşmak istemiyorum, o yüzden beni rahatsız etmesen iyi olur.");
			link.l1 = RandPhraseSimple("Dediğin gibi olsun...","Hm, peki o zaman...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Umarım daha fazla saygı gösterir ve kaba davranmayı bırakırsın?";
        			link.l1 = "Emin olabilirsin, Jacques, yapacağım.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("LeFransua_town","reload","reload6");
		break;
		
		case "pirate_town":
            dialog.text = " Sorunu çözmek mi? Ne yaptığının farkında mısın? Neyse, bana bir milyon peso getir, adamlara senin 'marifetlerini' unutturmaya çalışırım. Bu fikir hoşuna gitmediyse, defol git cehenneme.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "Pekala, ödemeye hazırım.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "Anladım. Gidiyorum.";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//закрыть переход
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "Güzel! Kendini tekrar temiz say. Ama umarım bir daha böyle iğrenç şeyler yapmazsın.";
			link.l1 = "Yapmam. Benim için fazlasıyla pahalı. Hoşça kal...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
		
		case "pirate_threat":
			if (GetNpcQuestPastDayWOInit(NPChar, "ThreatTalk") == 0)
			{
				dialog.text = NPCStringReactionRepeat("Bugün bu konuyu zaten konuştuk.",
				                                      "Yeterince açık konuşmadım mı?",
				                                      "Israrcılığın can sıkmaya başladı.",
				                                      "Artık sabrım taştı. Defol buradan!",
				                                      "repeat", 3, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Başka zaman konuşuruz...",
				                                   "Elbette, "+npchar.name+"...",
				                                   "Üzgünüm, "+npchar.name+"...",
				                                   "Ah...", npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
				break;
			}
			if (iGPThreat != 0)
			{
				iBarbazonTotalTemp = 10 * iGPThreatRate;
				dialog.text = "Ha! Kardeşlik tayfası seni fena hırpalıyor ha, " + GetSexPhrase("dostum", "dostum") + "? Onları bir süreliğine dizginleyebilirim. Ama bunun bir bedeli var. " + FindRussianDublonString(iBarbazonTotalTemp) + " ver, işi halledelim.";
				if (PCharDublonsTotal() > iBarbazonTotalTemp)
				{
					if (iGPThreat < 5) link.l0 = "Elbette, işte paran.";
					else link.l0 = "Başka çarem yok gibi görünüyor. Al paranı.";
					link.l0.go = "pirate_threat_pay";
				}
				link.l1 = "Sonra tekrar gelirim...";
				link.l1.go = "exit";
			}
			else
			{
				SaveCurrentNpcQuestDateParam(NPChar, "ThreatTalk");
				if (NextDiag.TempNode != "I_know_you_good")
					dialog.text = "Aklını mı kaçırdın" + GetSexPhrase("", "") + "? Bizim tayfa seni vebalı gibi kaçıyor. Hadi git, kafamı ütüleme.";
				else
					dialog.text = "Neden bahsediyorsun, " + GetSexPhrase("dostum", "dostum") + "? Sen baş belasının tekisin — köpekler bile bunu hissediyor. Kimse seninle uğraşmak istemiyor.";
				link.l1 = "Anladım...";
				link.l1.go = "exit";
			}
		break;

		case "pirate_threat_pay":
			iGPThreatRate = 0;
			iGPThreat = 0;
			SaveCurrentNpcQuestDateParam(NPChar, "ThreatTalk");
			RemoveDublonsFromPCharTotal(iBarbazonTotalTemp);
			DialogExit();
			PiratesDecreaseNotif("");
		break;
	}
}

void SelectSouthshore()
{
	switch (rand(6))
	{
		case 0: pchar.GenQuest.Marginpassenger.Shore = "shore37"; break;
		case 1: pchar.GenQuest.Marginpassenger.Shore = "shore47"; break;
		case 2: pchar.GenQuest.Marginpassenger.Shore = "shore48"; break;
		case 3: pchar.GenQuest.Marginpassenger.Shore = "shore25"; break;
		case 4: pchar.GenQuest.Marginpassenger.Shore = "shore21"; break;
		case 5: pchar.GenQuest.Marginpassenger.Shore = "shore20"; break;
		case 6: pchar.GenQuest.Marginpassenger.Shore = "shore19"; break;
	}
}

void SelectSouthcity()
{
	switch (hrand(2))
	{
		case 0: 
			pchar.GenQuest.Marginpassenger.Southcity = "Maracaibo";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Havana"; 
		break;
		
		case 1:
			pchar.GenQuest.Marginpassenger.Southcity = "Cartahena";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santiago"; 
		break;
		
		case 2:
			pchar.GenQuest.Marginpassenger.Southcity = "Portobello";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santodomingo"; 
		break;
	}
}
