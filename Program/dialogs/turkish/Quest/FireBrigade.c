
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
    string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
// ГРИФФОНДОР -->
		case "FireBrigade_fra":
			dialog.text = GetSexPhrase("","Bir kadın... hem de bir kaptan! Artık her şeyi gördüm. Mademoiselle, gerçekten büyüleyicisiniz. Ne yazık ki güzelliğiniz Fransa Tacı'na bu kadar acı getirdi\n")+"Poincy'nin emirleri hep böyle biter. Biri hapiste. Diğeri ise ya ona katılacak ya da bugün savaşta ölecek.";
			link.l1 = "Senin burada işin yok gibi görünüyor. Neden böylesine zeki bir subayı ve böylesine güzel bir gemiyi bir ödül avcısının pis işine gönderiyorlar?";
			link.l1.go = "FraOff_1";
		break;

        case "FraOff_1":
			dialog.text = "Emirler tartışılmaz, yerine getirilir. Her kaptan hangi emrin değerli olduğuna kendi karar verseydi—donanmamız olmazdı.";
			link.l1 = "Bunu adamlarına söyle.";
			link.l1.go = "FraOff_2";
        break;

        case "FraOff_2":
			dialog.text = "Beni köşeye sıkıştırdın ve sadakatimi, yeminimi sarsmaya çalışıyorsun. Bu şartlar altında bu, bayağı bir darbe. Bunu kelimelerle değil, kılıçların çarpışmasıyla çözelim!";
			link.l1 = "(Liderlik) Üçüncü bir yol daha var. Bir subaya yakışmayan kirli işlerle uğraşmayı bırak. Bana katıl—ve sana bambaşka bir dünya göstereceğim.";
			link.l1.go = "FraOff_HireCheck";
            link.l2 = "Silaha sarılalım, o halde!";
			link.l2.go = "FraOff_ExitFight";
        break;

        case "FraOff_HireCheck":
            if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 80)
            {
                notification("Skill Check Failed (80)", SKILL_LEADERSHIP);
                dialog.text = "Hainlere her yerde aynı muamele yapılır. Ve ben onlardan biri olmayacağım. Silahını çek!";
                link.l1 = "Şansını denedin, ama kaçırdın. Silahını çek!";
                link.l1.go = "FraOff_ExitFight";
                break;
            }
            notification("Skill Check Passed", SKILL_LEADERSHIP);
            dialog.text = "Ben tahta sadakat yemini ettim, kendi hatalarını örtbas etmek için bizi ölüme gönderen kibirli, burnu havada bürokratlara değil. Ama sen—sen benim kralımın düşmanısın ve bunu görmezden gelemem.";
			link.l1 = "Yarın ülkenize karşı işlediğim günahların bedelini ödeyebilirim—yeter ki doğru aracıyı bulup parasını vereyim. Bu, sizin üstleriniz hakkında benim hakkımda söylediğinden daha fazlasını anlatıyor.";
			link.l1.go = "FraOff_Sucess";
        break;

        case "FraOff_Sucess":
			dialog.text = "Doğru. Ve artık buna katlanmaktan yoruldum. Eğer Fransızlara dokunmayacağına söz verirsen, senin emrinde hizmet etmeye hazırım.";
			link.l1 = "Kiminle yollarımız kesişecek bilmiyorum, hiçbir şeyin garantisini veremem. Ama mantıklı davranacağıma söz veriyorum. Mürettebata hoş geldin, Subay "+NPChar.name+"!"; // своего имени он вообще-то не называл
			link.l1.go = "FraOff_Hired";
        break;

        case "FraOff_ExitFight":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle(""); 
            AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();	
        break;

        case "FraOff_Hired":
            AddBrigadierOfficer(sld, NPChar);
            DialogExit();
        break;

// ЭЛЬ КАСАДОР -->
		case "FireBrigade_spa":
            // to_do: чек нуля?
			dialog.text = "Demek kamu düşmanı böyle biri oluyormuş. Umarım bu unvanla gurur duyuyorsundur, korsan. Bunu hak etmek için epey uğraşmış olmalısın\nCasa de Contratación'a göre, sen şunları alt etmişsin "+(Statistic_AddValue(PChar,"spa_AbordShip",0)+Statistic_AddValue(PChar,"spa_KillShip",0))+" İspanyol Kraliyetinin bayrağını taşıyan gemiler. Ve bugün, güzel gemim o listeye katılacak"+GetSexPhrase(".","\nİspanyol filosunun vay haline! Hastalık, kayırmacılık, ihanet çektik... Ama bir kadına yenilmek mi?");
			link.l1 = " Ayakta kalan son kişi sensin, mürettebatın öldü. Sen de öldün, sadece henüz farkında değilsin.";
			link.l1.go = "Alonso_1";
			if(Statistic_AddValue(PChar, "spa_AbordShip", 0) + Statistic_AddValue(PChar, "spa_KillShip", 0) < 1)
			{
				Achievment_Set("ach_CL_159")
			}
		break;

		case "Alonso_1":
            dialog.text = "Keşke bu görevi de Alba alsaydı. O benden daha iyi yapardı. Ama yine de işi bitirmeye çalışacağım.";
            link.l1 = "Sen vatanının gerçek bir evladısın. Kahramanlarıyla tanışmaya hazırlan, señor.";
            link.l1.go = "Alonso_2";
            link.l2 = "Avcı av oldu. Bütün o lafların boşa gitti—bu, dünyanın en eski hikâyesi.";
            link.l2.go = "Alonso_3";
        break;

        case "Alonso_2":
            ChangeCharacterComplexReputation(PChar, "nobility", 5);
            dialog.text = "Biraz nefes almamı sağladığın için sağ ol, ama şimdi söz sırası kılıcımda.";
            link.l1 = "Silaha sarılın!";
            link.l1.go = "Alonso_ExitFight";
        break;

        case "Alonso_3":
            ChangeCharacterComplexReputation(PChar, "nobility", -5);
            dialog.text = "Biraz soluklanmamı sağladığın için sağ ol, ama şimdi söz sırası kılıcımda.";
            link.l1 = "Ölmeye hazırlan!";
            link.l1.go = "Alonso_ExitFight";
        break;

        case "Alonso_ExitFight":
        	SetCharacterPerk(NPChar, "Rush");
            ActivateCharacterPerk(NPChar, "Rush");
            PlaySound("Ambient\Tavern\glotok_001.wav");
            PlaySound("Types\" + LanguageGetLanguage() + "\warrior03.wav");
            SendMessage(NPChar, "lfffsfff", MSG_CHARACTER_VIEWSTRPOS, 0.0, 0.0, 0.1, XI_ConvertString("Rampage"), 255.0, 30.0, 30.0);
            MakeUnpushable(NPChar, true);
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle(""); 
            AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
		break;

// ХИМЕРА -->
        case "FireBrigade_eng":
            // to_do: ты-вы у элен
            dialog.text = GetSexPhrase(PChar.Name+"! Adınız raporlarda o kadar sık geçiyor ki, sanki yıllardır birbirimizi tanıyormuşuz gibi hissediyorum","Miss McArthur! Himayenizin neyle uğraştığınızı biliyor mu? Ah, boşverin. Zaten bir sonraki işim o olacak, eminim.")+"\nŞanslısın: patronlarım acil emirler göndermeye bayılır, hem de öncekilerle çelişenlerden. Antigua'daki eski tayfayı temizlemekle uğraşmasam... Neyse, boşver. Yeter. Gerçek işimden alıkoyuyorsun beni.";
			link.l1 = "Sen de beni oyalıyorsun.";
			link.l1.go = "Cortny_ExitFight";
		break;

        case "Cortny_ExitFight":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle("KnippelAppearance");
            AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();	
		break;

        case "Kneepel":
            dialog.text = "Kıçımı zincirli gülleyle sıyırdı, az kalsın fark etmeyecektim! Eski kemiklerim biraz daha hızlı olsaydı, o alçağı kendi ellerimle deniz şeytanına yollardım. Sağ ol, Kaptan. Merhum efendim de sana minnettar!";
			link.l1 = "Sen kimsin? Bir mahkum musun? Mürettebatım mı seni serbest bıraktı?";
			link.l1.go = "Kneepel_1";	
		break;

        case "Kneepel_1":
            dialog.text = "Karşınızda Charlie Knippel. İngiliz Donanması'nın en iyi topçusu!";
			link.l1 = "Courtney'nin seni bulmak için uzun süre uğraştığını söyledi. Bunun hikayesi nedir?";
			link.l1.go = "Kneepel_2";	
		break;

        case "Kneepel_2":
            dialog.text = "Uzun yıllar boyunca cesur bir İngiliz kaptan olan Richard Fleetwood'un yanında hizmet ettim. Birçok savaşa birlikte girdik, gerçek tutkumuz olan İngiliz Donanması'na hizmet ettik. Ama bir gün her şey değişti.\nLondra'daki üst düzeyler bizi piyon gibi kullandı. Kendi insanımıza saldırttılar. Başkalarının pisliğini temizlerken üniformalarımızı kirlettik. Ve şimdi sıra bize geldi...";
			link.l1 = "Burada kimse seni yargılamaz. Hayat karmaşık, hele ki kendi hayatının efendisi değilsen.";
			link.l1.go = "Kneepel_2_good";
            link.l2 = "Yani, eski günahlarının gölgeleri sonunda seni yakaladı diyebilir miyiz?";
			link.l2.go = "Kneepel_2_bad";
		break;

        case "Kneepel_2_good":
            dialog.text = "Ülkeme hizmet ettiğim için pişman değilim. Sadece... canımı yakıyor, Kaptan. Özellikle de koruyucum ve zavallı karısı için.";
			link.l1 = "Şimdi ne olacak?";
			link.l1.go = "Kneepel_3";	
		break;

        case "Kneepel_2_bad":
            TEV.NoKneepel = "";
            dialog.text = "İğnelemelere gerek yok... Günahlarımızın bedelini fazlasıyla ödedik zaten!";
			link.l1 = "Şimdi ne olacak?";
			link.l1.go = "Kneepel_3";	
		break;

        case "Kneepel_3":
            dialog.text = "Artık ne adım var, ne de yurdum. Her yere gidebilirim, ama şimdilik gidecek bir yer yok. Ve birlikte gidecek kimse de yok. Topçular her yerde aranır, ama her gemide top yok.";
			link.l1 = "Bana katıl. İngiliz filosuyla en iyi ilişkilere sahip olduğumu söyleyemem, ama en iyilerine saygı duyarım.";
            if(!CheckAttribute(&TEV, "NoKneepel"))
                link.l1.go = "Kneepel_3_good";
            else
                link.l1.go = "Kneepel_3_bad";
            link.l2 = "Toplarım var. Eğer gerçekten o kadar iyisen, ekibimde gerçek bir profesyonele her zaman yer vardır.";
			link.l2.go = "Kneepel_3_bad";
		break;

        case "Kneepel_3_good":
            dialog.text = "Evde beni bekleyen bir ilmek var, İspanyollar ve Hollandalılar için de aynı, Fransızlardan ise hiç hoşlanmam. Ama senin iyi bir topçuya ihtiyacın var gibi görünüyor. Varım, Kaptan. İlk fırsatta kamaraya geçerim. Uğrarsan, biraz rom eşliğinde sohbet ederiz.";
			link.l1 = "Hoş geldiniz.";
			link.l1.go = "Kneepel_Hired";	
		break;

        case "Kneepel_3_bad":
            dialog.text = "Hiçbir şekilde olmaz. Bir tekneyi ele geçirip takımadaların en kuytu köşesine kaybolmayı tercih ederim. Kurtardığın için sağ ol, Kaptan, ve hoşça kal.";
			link.l1 = "...";
			link.l1.go = "Kneepel_Escape";	
		break;

        case "Kneepel_Escape":
            DeleteAttribute(&TEV, "NoKneepel");
            DeleteAttribute(&TEV, "boardingReloadFreeze");
            NPChar.lifeday = 0;
            LAi_SetActorTypeNoGroup(NPChar);
            LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1.0);
            PostEvent("LAi_event_boarding_EnableReload", 5000);
            DialogExit();
		break;

        case "Kneepel_Hired":
            DeleteAttribute(&TEV, "NoKneepel");
            DeleteAttribute(&TEV, "boardingReloadFreeze");
            NPChar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
            NPChar.Dialog.CurrentNode = "Knippel_officer";
            NPChar.quest.OfficerPrice = sti(PChar.rank)*200; // Артефакт
            NPChar.quest.meeting = true;
            NPChar.OfficerImmortal = true;
            NPChar.Health.HP    = 60.0;
            NPChar.Health.maxHP = 60.0;
            NPChar.OfficerWantToGo.DontGo = true;
            NPChar.loyality = MAX_LOYALITY;
            NPChar.Payment = true;
            NPChar.DontClearDead = true; 
            SaveCurrentNpcQuestDateParam(NPChar, "HiredDate");
            AddPassenger(pchar, NPChar, false);
            SetCharacterRemovable(NPChar, true);
            LAi_SetActorTypeNoGroup(NPChar);
            LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1.0);
            PostEvent("LAi_event_boarding_EnableReload", 5000);
            DialogExit();
		break;

// МЕЙФЕНГ -->
        case "FireBrigade_hol":
			dialog.text = "Buraya kadar gelmesi gereken kişi sen değildin. Meifeng, Şirket’in dişi. Filom ise intikam kılıcı. İkisini de kırdın. Bu... olmaz.";
			link.l1 = "Beni bir canavar gibi peşine taktılar. Ve ben de köşeye sıkışmış bir hayvan gibi savaştım. Ya savaşacaksın ya da öleceksin; işte o zaman zihnin berraklaşır. Sonunda ise tek bir soru kalır: Efsanevi xebec’in kamarasına ulaşabilecek miyim—yoksa ulaşamayacak mıyım.";
			link.l1.go = "Longway_1";
		break;

		case "Longway_1":
			dialog.text = GetSexPhrase("","Garip—bir kadının komuta ettiğini görmek. Bu pek sık rastlanan bir şey değil. ")+"Beni mi bekliyordun?";
			link.l1 = "Evet. Meifeng geçmişi olan bir gemidir. Hollandalıları kandırdığımda, er ya da geç seni peşime göndereceklerini biliyordum. Bu onurlu bir son olurdu... ama bak işler nasıl gelişti.";
			link.l1.go = "Longway_2";
		break;

		case "Longway_2":
			dialog.text = "Düşmanını ve kendini bilmek zaferin anahtarıdır. Yani, seçimini yaptın. Filomla kendi şartlarında yüzleşmeyi seçtin. Ölmeye hazırdın. Ama kazandın. Şimdi hayatım senin ellerinde. Neden beni bitirmiyorsun?";
			link.l1 = "(Liderlik) Çünkü Şirket'in hırsları uğruna efsanevi bir kaptanı batırmanın hiçbir anlamı yok. Senin yerinde bulundum—bir piyon. Başkalarının çıkarlarına hizmet ettim, başkalarının emirlerini uyguladım. Sana bir zamanlar kendim seçtiğim şeyi sunuyorum: özgürlük.";
            if (GetSummonSkillFromName(PChar, SKILL_LEADERSHIP) >= 50)
                link.l1.go = "Longway_Success";
            else
                link.l1.go = "Longway_Failed";
            link.l2 = "Çünkü her kaptan son sözü söylemeyi hak eder. Silahını hazırla!";
			link.l2.go = "Longway_ExitFight";
		break;

		case "Longway_ExitFight":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle(""); 
            AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
		break;

		case "Longway_Failed":
            notification("Skill Check Failed (50)", SKILL_LEADERSHIP);
			dialog.text = "Özgürlük kimse tarafından verilmez. Onu almak gerekir. Ve seçimden bahseden herkes sana gerçekten bir seçenek sunamaz. Kaçamayacağın yollar vardır. Yarım bırakamayacağın emirler vardır. Benim yolum burada. Benim emrim ise sonuna kadar ayakta kalmak.";
			link.l1 = "Demek ölümü seçiyorsun?";
			link.l1.go = "Longway_Failed_over";
		break;

		case "Longway_Failed_over":
			dialog.text = "Hayır. Kendim olarak kalmayı seçiyorum.";
			link.l1 = "O zaman dövüşelim!";
			link.l1.go = "Longway_ExitFight";
		break;

		case "Longway_Success":
            notification("Skill Check Passed", SKILL_LEADERSHIP);
			dialog.text = "Sen Rodenburg gibi değilsin. O beni bir araç olarak gördü. Sen ise bir eşit olarak. Kendini feda etmek bir erdem değil. Şartlarını duymaya hazırım.";
			link.l1 = "Basit. Amiral gemimde rotacı ol. Ya da istersen, kendi geminle benim bayrağım altında yol alabilirsin. Artık Şirket'in pisliğini temizlemek ya da onların sırlarını saklamak zorunda kalmayacaksın. Ben özgürüm—ve sana da bu özgürlüğü sunuyorum.";
			link.l1.go = "Longway_Success_over";
		break;

		case "Longway_Success_over":
			dialog.text = "Çok şey gördüm: kan, altın, ihanet. Şirket öder—ama saygı duymaz. Gemi verir—ama zincirler. Sen... bir seçenek sunuyorsun. Sözünü tutarsan—Longway artık başkasının iradesi için avcı olmayacak. Bir adam olacak. Bir kaptan. Ya da—nereye yelken açacağını bilen bir kaptanın yanında duracak.";
			link.l1 = "Ekibe hoş geldin, Dümenci Longway.";
			link.l1.go = "Longway_Hired";
		break;

		case "Longway_Hired":
			sld = InitLongwayFP("Longway_FP", NPChar);
			NPChar.lifeday = 0;
			LAi_group_MoveCharacter(NPChar, LAI_GROUP_PLAYER);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);

			AddDialogExitQuest("pchar_back_to_player");
			PostEvent("LAi_event_boarding_EnableReload", 5000);
			DialogExit();
		break;
	}
}

// TO_DO
void AddBrigadierOfficer(ref sld, ref NPChar)
{
    string sTemp = NationShortName(NPChar.nation);
    sld = GetCharacter(NPC_GenerateCharacter("FraBrigadier", NPChar.model, "man", NPChar.model.animation, 30, FRANCE, -1, false, "quest"));
    float num = 1.0;
    switch (MOD_SKILL_ENEMY_RATE)
	{
		case  1: num = 0.5;  break;
		case  2: num = 0.6;  break;
		case  3: num = 0.7;  break;
		case  4: num = 0.8;  break;
		case  5: num = 0.9;  break;
		case  6: num = 1.0;  break;
		case  7: num = 1.1;  break;
		case  8: num = 1.2;  break;
		case  9: num = 1.3;  break;
		case 10: num = 1.5;  break;
	}
    num = stf(NPChar.Rank) / num;
    FantomMakeCoolFighter(sld, MakeInt(num+2), 70, 70, BLADE_LONG, "", "", 100);
    RemoveAllCharacterItems(sld, true);
    GiveItem2Character(sld, NPChar.equip.blade);
    EquipCharacterbyItem(sld, NPChar.equip.blade);
    sTemp = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
    if(sTemp != "")
    {
        GiveItem2Character(sld,   sTemp);
        EquipCharacterbyItem(sld, sTemp);
        sTemp = LAi_GetCharacterBulletType(NPChar, GUN_ITEM_TYPE);
        LAi_SetCharacterBulletType(sld, sTemp);
        LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, sTemp);
        sTemp = LAi_GetCharacterGunpowderType(NPChar, GUN_ITEM_TYPE);
        if(sTemp != "") AddItems(sld, sTemp, 30 + rand(20));
    }
    sld.name = NPChar.name;
    sld.lastname = NPChar.lastname;
    sld.greeting = "officer_hire";
    sld.Dialog.Filename = "Enc_Officer_dialog.c";
    sld.quest.meeting = true;
    sld.quest.OfficerPrice = sti(PChar.rank)*200; // Артефакт
    Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
    sld.OfficerImmortal = true;
    sld.Health.HP    = 60.0;
    sld.Health.maxHP = 60.0;
    sld.OfficerWantToGo.DontGo = true;
    sld.loyality = MAX_LOYALITY;
    AddDialogExitQuest("pchar_back_to_player");
    AddDialogExitQuestFunction("LandEnc_OfficerHired");
    NPChar.lifeday = 0;
    LAi_SetActorType(NPChar);
    LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);
    PostEvent("LAi_event_boarding_EnableReload", 5000);
}
