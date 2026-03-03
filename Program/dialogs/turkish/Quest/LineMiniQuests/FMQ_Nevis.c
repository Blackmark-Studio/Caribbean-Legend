// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Açık bir hata. Geliştiricilere bildir.";
			link.l1 = "Ah, edeceğim.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "seafox":
			DelMapQuestMarkCity("Charles");
			LAi_SetImmortal(npchar, false);
			DelLandQuestMark(npchar);
			LAi_RemoveLoginTime(npchar);
			PlaySound("Voice\English\LE\SeaFox\SeaFox_01.wav");
			dialog.text = TimeGreeting()+", kaptan. (selam verir) Kendimi tanıtmama izin verin - Teğmen "+GetFullName(npchar)+", Antigua Deniz Alayı, St. John's'ta konuşlu. Sizden bir ricam olacak.";
			link.l1 = "Selamlar, Teğmen Gretton. Benim adım "+GetFullName(pchar)+". Ne tür bir iyilik?";
			link.l1.go = "seafox_1";
		break;
		
		case "seafox_1":
			dialog.text = "Durumu kısaca açıklayayım. Dört adamımla birlikte St. Johns'tan Sint Maarten'e gidiyorduk, bir fırtına gemimize çarptı. Kötü hava uzun sürmedi ama eski tekneye su aldırmaya yetti. Rotamızı değiştirmek ve burada tamir için durmak zorunda kaldık. Bu da bize zaman kaybettiriyor, oysa vaktimiz yok\nSint Maarten'e, özellikle de Grand Case Plajı'na acelemiz var. Bana yardım et kaptan, karşılığını fazlasıyla alacaksın. İki günlük yolculuk, cömert bir ödeme!";
			link.l1 = "Gerçekten de cömert bir ödeme olmalı, teğmen, eğer benden İngiliz denizcilerini gizlice bir Hollanda adasına sokmamı istiyorsanız.";
			link.l1.go = "seafox_2";
		break;
		
		case "seafox_2":
			dialog.text = ""+UpperFirst(GetAddress_Form(PChar))+", bu seni ilgilendirmez. Hiçbir tehlikede değilsin. Bizi koyda bırak, hepsi bu. Anlaştık mı?";
			link.l1 = "Peki, kabul ediyorum. Burası çok uzak sayılmaz. Şimdi şu ödemeden bahset bakalım.";
			link.l1.go = "seafox_3";
			link.l2 = "Üzgünüm, ama acil işlerim var ve başka bir yöne gitmem gerekiyor, Hollandalıları kızdırmak istemem.";
			link.l2.go = "seafox_exit";
		break;
		
		case "seafox_exit":
			dialog.text = "Dediğiniz gibi, kaptan. O zaman aramaya devam edeceğim. Hoşça kalın ve yolunuz açık olsun!";
			link.l1 = "Elveda, teğmen.";
			link.l1.go = "seafox_exit_1";
		break;
		
		case "seafox_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
		break;
		
		case "seafox_3":
			GiveItem2Character(pchar, "purse2"); 
			Log_Info("You have received a purse of doubloons");
			dialog.text = "On bin sekiz parça. İşte bir avans.";
			link.l1 = "İyi. Adamlarını gemiye al, vakit kaybetmeyelim.";
			link.l1.go = "seafox_4";
		break;
		
		case "seafox_4":
			dialog.text = "Baş üstüne, kaptan!";
			link.l1 = "...";
			link.l1.go = "seafox_5";
		break;
		
		case "seafox_5":
			DialogExit();
			AddQuestRecord("FMQ_Nevis", "1");
			pchar.questTemp.FMQN = "begin";
			
			chrDisableReloadToLocation = false;
			sld = CharacterFromID("FMQN_seafox_1");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload4_back", "", "", "", "", 10.0); // англичане на борт
			sld.location = "None";
			AddPassenger(pchar, sld, false);//добавить пассажира
			SetCharacterRemovable(sld, false);
			pchar.quest.FMQN_sailing.win_condition.l1 = "location";
			pchar.quest.FMQN_sailing.win_condition.l1.location = "Shore40";
			pchar.quest.FMQN_sailing.win_condition.l2 = "Ship_location";
			pchar.quest.FMQN_sailing.win_condition.l2.location = "Shore40";
			pchar.quest.FMQN_sailing.function = "FMQN_ArriveMaarten";
			if(bImCasual)
			{
				NewGameTip(StringFromKey("FMQ_69"));
			}
			else SetFunctionTimerCondition("FMQN_SailingLate", 0, 0, 10, false);
			for(i = 0; i < MAX_LOCATIONS; i++)
			{	
				sld = &Locations[i];
				if (CheckAttribute(sld, "islandId") && sld.islandId == "SentMartin")
				{
					sld.DisableEncounters = true;	
				}
			}
			sld = &Locations[FindLocation("Shore40")];
			sld.QuestlockWeather = "23 Hour";
			AddMapQuestMarkShore("Shore40", true);
		break;
		
		case "seafox_6":
			PlaySound("Voice\English\LE\SeaFox\SeaFox_02.wav");
			dialog.text = "Yolculuğun bu kadar sorunsuz geçtiği için teşekkürler, kaptan! Gerçekten çok üzgünüm ama şu anda sana ödeme yapamam... Bu bölgede bizim bir sandallarımızdan biri olmalıydı, ama gördüğün gibi burada yok. Bir kez daha yardımını istemek zorundayım. Bu körfezde iki ya da üç gün bekleyebilir misin? Etrafı kontrol etmemiz gerek. Döndüğümüzde, bizi Antigua'ya götür. Albay Fox seni cömertçe ödüllendirecek.";
			link.l1 = "Hmm... Bu tam olarak anlaştığımız gibi değil...";
			link.l1.go = "seafox_7";
		break;
		
		case "seafox_7":
			dialog.text = "Lütfen üzülmeyin kaptan. Nasıl hissettiğinizi anlıyorum ama ne yazık ki hiç param yok. Size söz veriyorum, hem iki seferinize hem de burada bizi beklediğiniz için size ödeme yapılacak ve ayrıca Albay Fox'un bizzat teşekkürünü alacaksınız!";
			link.l1 = "Seni tamamen kendi haline bırakamam... Peki öyle olsun, Teğmen Gretton. Üç gün bekleyeceğim, ama daha fazla değil.";
			link.l1.go = "seafox_8";
		break;
		
		case "seafox_8":
			dialog.text = "Teşekkür ederim, "+GetAddress_Form(NPChar)+"! Karaya doğru gidiyoruz. Yemin ederim, yetmiş iki saat içinde döneceğiz, bir dakika bile geç kalmayacağız.";
			link.l1 = "Yolun açık olsun, teğmen. Yakalanma sakın.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_EnglishmanGo");
		break;
		
		case "seafox_9":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\LE\SeaFox\SeaFox_02.wav");
			dialog.text = "Ne tesadüf bir karşılaşma! Grand Case Plajı'nda bizi bekliyor olacağını sanmıştım, Kaptan "+pchar.lastname+"!";
			link.l1 = "Merhaba, Teğmen, şaşkınlık karşılıklı. Sizi Hollandalı bir asker gibi giyinmiş görmek hiç aklıma gelmezdi.";
			link.l1.go = "seafox_10";
		break;
		
		case "seafox_10":
			dialog.text = "Bu bizim kılığımız... Neden buradasın, "+GetAddress_Form(NPChar)+"?";
			link.l1 = "Bu tehlikeli bir kılık, dostum. Casuslar genellikle yargılanmadan hemen idam edilir. Ve idamdan söz açılmışken, kendi sonunu görmek istemiyorsan beni iyi dinle.";
			link.l1.go = "seafox_11";
		break;
		
		case "seafox_11":
			dialog.text = "Tüm dikkatimi sana verdim.";
			link.l1 = "Philipsburg'a gittim ve sen karaya çıktıktan sonra yerlilerle konuştum. Hollandalılar peşindeler. Esir alınan üst düzey İngiliz subaylarını kurtarma görevin hakkında bilgi sahibiler.";
			link.l1.go = "seafox_12";
		break;
		
		case "seafox_12":
			dialog.text = "Kahretsin! Bunu nasıl öğrendiler, aklım almıyor!";
			link.l1 = "Yakalanan İngiliz subaylarından biri. Özgürlüğü karşılığında kurtarma operasyonu hakkında bildiği her şeyi Hollandalılara anlattı. Philipsburg’daki herkes, senin ve adamlarının şehre girmeye çalışmasını bekliyor. Üstüne üstlük, Sint Maarten çevresinde bir Hollanda korveti devriye geziyor. Bu bir tuzak, teğmen.";
			link.l1.go = "seafox_13";
		break;
		
		case "seafox_13":
			dialog.text = RandSwear()+"O namussuz hain! O alçağın kim olduğunu bulup onu Parlamento'nun önünde ifşa edeceğim!";
			link.l1 = "Bu beklemek zorunda, Bay Gretton. Bu gece Grand Case Plajı'na dön ve seni yakalamadan önce gemime geri gel.";
			link.l1.go = "seafox_14";
		break;
		
		case "seafox_14":
			dialog.text = "Ve İngiliz centilmenlerini bir Hollanda hapishanesinde bırakmak mı? Ölürüm daha iyi, efendim. Albay Fox'u asla yüzüstü bırakmam.";
			link.l1 = "Hm, sence Hollandalılar seni yakaladıklarında idam sehpası ile kurşuna dizilme arasında seçim yapmana izin verir mi?";
			link.l1.go = "seafox_15";
		break;
		
		case "seafox_15":
			dialog.text = "Buradan öylece yelken açıp gideceğini de sanma, Kaptan de Maure. İkimiz de bu işin tam ortasındayız.";
			link.l1 = "Lanet olsun, muhtemelen haklısın. Demir alır almaz o korvet üstümüze çullanacak...";
			link.l1.go = "seafox_16";
		break;
		
		case "seafox_16":
			dialog.text = "Hollandalılar geldiğimizi biliyor olabilir, ama *nasıl* geleceğimizi bilmiyorlar. Kılık değiştirme işini hallettik bile – şu üniformaya bir bak. Güzel değil mi? Planımız ortaya çıkmasaydı, doğrudan yerel hapishaneye gidip onları gafil avlar, içeridekilerin hepsini öldürürdük. Ama şimdi kesin pusuya yatmışlardır. O yüzden doğaçlama yapıyoruz. Kaptan, Philipsburg'un kilisesine git ve orada Filippe Jacobsen adında bir vaiz bul. Sabah altıdan ona kadar orada olur. Filippe içerideki adamlarımızdan biri. Ona şu parolayı söyle: 'Esir denizciler ne kadar önce günah çıkardı?'. Sonra durumu anlat ve Albay Fox'un adına yardımını iste. Sonra da cevabını bana getiriyorsun. Basit, hem de senin için hiçbir risk yok.";
			link.l1 = "Hollanda Calvinist kilisesinde günah çıkarmayı sormak epey tehlikeli bir iş, teğmen. Papist olduğum için papaz beni asmaya kalkardı. Peki, şu üniformaları anlat bakalım... Bunu bir Hollanda devriyesinden mi aldın?";
			link.l1.go = "seafox_17";
		break;
		
		case "seafox_17":
			dialog.text = "Evet, efendim.";
			link.l1 = "Ve şimdi neredeler?";
			link.l1.go = "seafox_18";
		break;
		
		case "seafox_18":
			dialog.text = "Bu mağaradan çok da uzakta olmayan çalılıkların arasında rehin tutuluyor.";
			link.l1 = "Anlaşıldı. Onları güvende tut, ben kasabaya gidiyorum. Burada bekle ve dikkatli ol – Hollandalılar hem ormanda hem de denizde seni arıyorlar.";
			link.l1.go = "seafox_19";
		break;
		
		case "seafox_19":
			dialog.text = "Kilisedeki fareler kadar sessiz olacağız, kaptan. Lütfen acele edin!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ToChurch");
		break;
		
		case "seafox_20":
			PlaySound("Voice\English\soldier_common_4.wav");
			DelLandQuestMark(npchar);
			dialog.text = "Geri mi döndün? Kaptan, burada ne işin var? Şehre git, saklandığımız yere dikkat çekiyorsun!";
			link.l1 = "Şehirden döndüm. Siz İngilizler ne tür oyunlar çeviriyorsunuz?";
			link.l1.go = "seafox_21";
		break;
		
		case "seafox_21":
			dialog.text = "Affedersiniz?";
			link.l1 = "Kilisenin yolunu tuttum. Büyük bir bina, sade ve gösterişli değil, tam Hollandalı ikonoklastların sevdiği gibi. Bil bakalım ne oldu, teğmen? Filippe Jacobsen adında bir vaiz yokmuş.";
			link.l1.go = "seafox_22";
		break;
		
		case "seafox_22":
			dialog.text = "Bu imkânsız, her sabah oraya gelir-";
			link.l1 = "Kapa çeneni ve beni dinle! O Jacobsen'in gerçekten var olup olmadığını bile bilmiyorum, ama kiliseye gitmiyor! Onu hiç görmemişler! Ne sabah ne akşam! Allah kahretsin! Ben bu lanet işi neden kabul ettim ki?! Aptal bir orospu çocuğu, toy bir çaylak, kulağı kesik bir teğmen tarafından yönetiliyorum-";
			link.l1.go = "seafox_23";
		break;
		
		case "seafox_23":
			dialog.text = "Efendim, bu hakaretin hesabını vermenizi istiyorum. Buradan çıkar çıkmaz, geleneklere uygun şekilde düello edeceğiz-";
			link.l1 = ""+RandSwear()+"";
			link.l1.go = "seafox_24";
		break;
		
		case "seafox_24":
			PlaySound("Ambient\Jail\chain.wav");
			PlaySound("Ambient\Land\door_001.wav");
			dialog.text = "Kesin sesinizi, hepiniz!!! ... Az önce bir şey duydum.";
			link.l1 = "";
			link.l1.go = "seafox_25";
		break;
		
		case "seafox_25":
			if (pchar.sex == "man") {PlaySound("VOICE\English\LE\SeaFox\SeaFox_04.wav");}
			dialog.text = "Vay canına, biri dışarıda! Sen! Sen Hollandalıları buraya geri getirdin, seni alçak!";
			link.l1 = ""+RandSwear()+"!!!";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattleFight");
		break;
		
		case "seafox_26":
			DelLandQuestMark(npchar);
			pchar.quest.FMQN_fail1.over = "yes";
			PlaySound("Voice\English\LE\SeaFox\SeaFox_02.wav");
			dialog.text = "Sizi görmek güzel, efendim. Ne haber?";
			link.l1 = "Adamınla görüştüm. Bu akşam hapishane muhafızlarına biraz 'aromalı' şarap götürecek. Bir çingeneden bir iksir aldı, öldürücü değil ama onları ölü gibi uyutacak. Bu gece oraya girip esir düşen adamlarını çıkarman gerekiyor. Bu arada, bu şarap teslimatı bana yirmi beş dublona mal oldu. Bunu raporda mutlaka belirt.";
			link.l1.go = "seafox_27";
		break;
		
		case "seafox_27":
			dialog.text = "Parayı dert etme. Kaptan, bu işte bize katılmanı ve hapishaneye giden yolu göstermeni istiyorum. Daha önce Philipsburg’a gittin, şehri bizden iyi biliyorsun. Hapishanenin içine bizimle girmen gerekmiyor, kaçışı biz hallederiz. Bizi sadece kapıya kadar götür.";
			link.l1 = "Gözlerim kör olsun, Bay Gretton, bu iş gittikçe daha da ilginçleşiyor. Umarım maaşımız da buna göre artıyordur.";
			link.l1.go = "seafox_28";
		break;
		
		case "seafox_28":
			dialog.text = "Kesinlikle öyle, kaptan. Bize yardım ettiğinize pişman olmayacaksınız. Geminiz Grand Case Plajı'nda mı?";
			if (pchar.location.from_sea == "Shore40")
			{
				link.l1 = "Aynen.";
				link.l1.go = "seafox_29";
			}
			else
			{
				link.l1 = "Hayır.";
				link.l1.go = "seafox_29x";
			}
		break;
		
		case "seafox_29":
			dialog.text = "Güzel. O zaman hazırlan ve akşam saat on birde şehir kapısında bizimle buluş.";
			link.l1 = "Orada görüşürüz.";
			link.l1.go = "seafox_30";
		break;
		
		case "seafox_29x":
			dialog.text = "Onu oraya mutlaka götür, çünkü adamlarımızı oradan çıkarmak için ormandan geçmemiz gerekiyor. Limandan ya da Simpson Körfezi'nden denize açılmak kale yüzünden imkânsız. Her şeyi hazırla ve akşam saat on birde kasaba kapısında buluşalım.";
			link.l1 = "Orada görüşürüz.";
			link.l1.go = "seafox_30";
		break;
		
		case "seafox_30":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddDialogExitQuestFunction("FMQN_EnglandPrepare");
		break;
		
		case "seafox_31":
			PlaySound("Voice\English\Gr_hovernor01.wav");
			dialog.text = "Hazır mısınız, kaptan?";
			link.l1 = "Evet.";
			link.l1.go = "seafox_32";
		break;
		
		case "seafox_32":
			dialog.text = "Hadi o zaman, devam edelim.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_EnglandReload");
		break;
		
		case "seafox_33":
			dialog.text = "Sessiz ol... Kaptan! İş bitti, hadi buradan defolup gidelim!..";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_EnglandRunToJungle");
		break;
		
		case "seafox_34":
			dialog.text = "Bunu nasıl başardık bilmiyorum ama başardık! Tüm bunlar sizin yardımınız olmadan mümkün olmazdı, efendim. Şimdi ise nispeten kolay bir iş kaldı - Sint Maarten'den sağ salim ve tek parça halinde çıkmamız gerek. Hadi Grand Case Plajı'na gidelim!";
			link.l1 = "Hadi gidelim!";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_EnglandRunToShore");
		break;
		
		case "seafox_35":
			PlaySound("Voice\English\LE\SeaFox\SeaFox_05.wav");
			dialog.text = "Kaptan "+pchar.lastname+"... "+GetAddress_Form(NPChar)+", thank you for your assistance! I beg you, please don't leave port immediately, but stay here for one more day while I report to Colonel Fox. Pay him a visit tomorrow; his office is in the governor's palace.";
			link.l1 = "Pekâlâ, Teğmen Gretton. Lütfen buna değsin. Senin maceran yüzünden Hollandalılarla itibarımı düzeltmem uzun sürecek.";
			link.l1.go = "seafox_36";
		break;
		
		case "seafox_35x":
			PlaySound("Voice\English\LE\SeaFox\SeaFox_05.wav");
			dialog.text = "Yardımınız için teşekkürler, kaptan! Siz "+GetSexPhrase("gerçek bir kahraman gibi davrandın","çok cesur bir genç hanımsınız")+", "+GetAddress_Form(NPChar)+"! Teğmen Gretton'ın hayatta kalamaması büyük bir talihsizlik. Gerçek bir centilmen ve İngiltere'nin evladı olarak öldü. Albay Fox'a rapor vermem için burada bir gün daha kalmak istiyorum. Yarın ona uğra, ofisi valinin sarayında.";
			link.l1 = "Pekala. Lütfen buna değsin. Senin maceran yüzünden Hollandalılarla itibarımı düzeltmem çok zaman alacak.";
			link.l1.go = "seafox_36";
		break;
		
		case "seafox_36":
			dialog.text = "Endişelenme, "+GetAddress_Form(NPChar)+". Raporumda sana mümkün olan en yüksek takdiri vereceğim. (selam verir) Bir zevkti, "+GetAddress_Form(NPChar)+"!";
			link.l1 = "...";
			link.l1.go = "seafox_37";
		break;
		
		case "seafox_37":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", -1);
			pchar.quest.FMQN_eng_reward.win_condition.l1 = "Timer";
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.hour  = 6.0;
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQN_eng_reward.function = "FMQN_EnglandReward";
			AddQuestRecord("FMQ_Nevis", "28");
		break;
		
		case "soldier":
			PlaySound("Voice\English\soldier_common_2.wav");
			dialog.text = "Kaptan "+GetFullName(pchar)+"?";
			link.l1 = "Hm... Evet, size nasıl yardımcı olabilirim?";
			link.l1.go = "soldier_1";
		break;
		
		case "soldier_1":
			dialog.text = "Liman ofisi, geminizin yakın zamanda varışını bize bildirdi. Philipsburg valisi Ekselansları Mynheer Martin Thomas, sizinle görüşmek istiyor.";
			link.l1 = "Ne için? Tutuklu muyum yoksa?";
			link.l1.go = "soldier_2";
		break;
		
		case "soldier_2":
			AddLandQuestMark(characterFromId("Marigo_Mayor"), "questmarkmain");
			dialog.text = "Ah hayır, hayır, "+GetAddress_Form(NPChar)+" kaptan, tutuklu değilsiniz. Vali, yeni gelen her kaptanın sarayına kahve ve tanışma için davet edilmesini emretti. Beni takip edin!";
			link.l1 = "Kaçırılmayacak bir teklif gibi geliyor. Yol göster.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ReloadToGovernor");
		break;
		
		case "hol_officer":
			PlaySound("Voice\English\hol_gov_complete.wav");
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+",   bize o İngiliz askerlerini nerede gördüğünü göster.";
			link.l1 = "Ormanda bir mağarada, sıradan haydutlar gibi saklanıyorlar.";
			link.l1.go = "hol_officer_1";
		break;
		
		case "hol_officer_1":
			dialog.text = "Önden git, seni takip ediyoruz!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattleMarch");
		break;
		
		case "hol_officer_2":
			PlaySound("Voice\English\hol_gov_quest.wav");
			dialog.text = "Bekle, kaptan! Casuslarla orada, mağaranın girişinde karşılaştığını mı söyledin?";
			link.l1 = "Evet. Benimle konuştuktan sonra içeri girdiklerini kısaca gördüm.";
			link.l1.go = "hol_officer_3";
		break;
		
		case "hol_officer_3":
			dialog.text = "Büyük ihtimalle hâlâ oradalar. Eğer hep birlikte içeri dalarsak, mağaraya çekilecekler. Oradan onları çıkarmak tam bir kabus olur... Akıllıca davranalım. Kaptan, sen tek başına git ve dikkatlerini dağıt. Adamlarımla ben köşedeki kuru kuyuya geçeceğiz. Orası doğrudan mağaranın içine açılıyor. O alçaklar arkamızdan geldiğimizi anlamayacaklar\nSen içeri gir ve casuslar hâlâ oradaysa, onlarla konuş, saçma sapan sorular sor, oyala onları. Tüm dikkatleri sende olduğunda - ağzına gelen en pis küfürleri et. Sonuçta denizcisin, bu senin için çocuk oyuncağı. Bu bizim işaretimiz olacak. Adamlarımdan ikisi ana girişi tutacak, oradan kaçmalarını engelleyecek. Onları yakalayacağız.";
			link.l1 = "Senin planın sağlığım için fazlasıyla tehlikeli geliyor. Bana kalırsa, önce beni öldürmeye çalışacaklar.";
			link.l1.go = "hol_officer_4";
		break;
		
		case "hol_officer_4":
			dialog.text = "Endişelenme, kaptan. Düşman baskın ekibini görür görmez olabildiğince yüksek sesle bağırman yeterli. Eğer sana saldırırlarsa hemen kaç ve bağırmaya devam et. Adamlarım iyi eğitimli, merak etme, seni yaralamadan önce o casusları hallederler.";
			link.l1 = "Daha iyi olur. Oraya gidiyorum.";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattlePosition");
		break;
		
		case "hol_officer_5":
			PlaySound("Voice\English\hol_gov_common.wav");
			dialog.text = "Zor adamlardı... Güzel iş çıkardınız kaptan, İngiliz köpekleri artık yok. Sabotajcılar ortadan kaldırıldı, komutan ve vali memnun kalacak.";
			link.l1 = "Vaktini bolca aldın, efendim...";
			link.l1.go = "hol_officer_6";
		break;
		
		case "hol_officer_6":
			dialog.text = "Suçu ipe at, ucunda kocaman bir kova vardı ve tam bir gürültüye sebep oldu. Dikkatli olmamız gerekiyordu.";
			link.l1 = "Evet... ip meselesi. Her neyse. Kayıp devriyelerinizden biri şurada çalılıkların arasında bağlı duruyor. Hâlâ hayatta olmalılar.";
			link.l1.go = "hol_officer_7";
		break;
		
		case "hol_officer_7":
			dialog.text = "Onlarla ben ilgilenirim. Sen kasabaya git, biraz dinlen. Yarın valimize uğra, o zamana kadar raporumda seni övgüyle anacağım.";
			link.l1 = "Bunu yapacağım. Yolun açık olsun, efendim.";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattleRest");
		break;
		
		case "monk":
			DelLandQuestMark(npchar);
			DelLandQuestMarkToPhantom();
			if (GetCharacterIndex("marigojailoff") != -1)
			{
				DelLandQuestMark(characterFromId("marigojailoff"));
			}
			pchar.questTemp.FMQN = "way_eng_2";
			dialog.text = "Senin için ne yapabilirim, oğlum?";
			link.l1 = "Merhaba papaz, sadece merakımdan soruyorum, esir denizciler ne kadar zaman önce günah çıkardı?";
			link.l1.go = "monk_1";
		break;
		
		case "monk_1":
			dialog.text = "Dün akşam, oğlum... (fısıldayarak) Planın ihanet edildiğini biliyorsun, değil mi?";
			link.l1 = "Yoksa burada olmazdım. Teğmen Casper Gratton ve adamları şu anda ormanda. Hepsi Hollandalı asker kılığında, ama fazladan yardıma ihtiyacımız var çünkü hapishane gardiyanları onları bekliyor.";
			link.l1.go = "monk_2";
		break;
		
		case "monk_2":
			dialog.text = "(yüksek sesle) Onun Anglikan ruhunu lanetten kurtarmak için her gün dua ettim! (fısıldayarak) Bir planım var, ama ihtiyacım olan her şeyi almak için iki düzine altın dublona ihtiyacım var.";
			link.l1 = "Pahalı bir plan. Para neye lazım?";
			link.l1.go = "monk_3";
		break;
		
		case "monk_3":
			dialog.text = "Being a prison guard is dull work. To keep up morale, the officer in charge orders wine every evening to go with their dinner. The wine is brought from a warehouse I have access to. There is a gypsy woman in town who owes me a favour; she will make us a sleeping potion. All I need is to buy a few bottles of good wine, add the potion, and swap the bottles in the warehouse. That's why I need the gold.";
			if (PCharDublonsTotal() >= 24)
			{
				link.l1 = "Altınlar bende. Al onları.";
				link.l1.go = "monk_4";
			}
			else
			{
				link.l1 = "Gemiye dönüp senin için biraz getireyim.";
				link.l1.go = "monk_wait";
			}
		break;
		
		case "monk_wait":
			DialogExit();
			npchar.dialog.currentnode = "monk_repeat";
		break;
		
		case "monk_repeat":
			dialog.text = "Ah, oğlum, konuştuğumuz 'bağışı' getirdin mi?";
			if (PCharDublonsTotal() >= 24)
			{
				link.l1 = "Evet, burada.";
				link.l1.go = "monk_4";
			}
			else
			{
				link.l1 = "Yakında alacağım...";
				link.l1.go = "monk_wait";
			}
		break;
		
		case "monk_4":
			RemoveDublonsFromPCharTotal(24);
			dialog.text = "Harika. Yarın aynı saatte yanıma gel - sonuçları sana anlatacağım.";
			link.l1 = "Pekala...";
			link.l1.go = "monk_5";
		break;
		
		case "monk_5":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("FMQ_Nevis", "18");
			pchar.quest.FMQN_monk.win_condition.l1 = "Timer";
			pchar.quest.FMQN_monk.win_condition.l1.date.hour  = 6.0;
			pchar.quest.FMQN_monk.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQN_monk.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQN_monk.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQN_monk.function = "FMQN_EnglandMonkPlan";
			pchar.quest.FMQN_fail.win_condition.l1 = "Timer";
			pchar.quest.FMQN_fail.win_condition.l1.date.hour  = 11.0;
			pchar.quest.FMQN_fail.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQN_fail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQN_fail.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQN_fail.function = "FMQN_EnglandFail";
			pchar.questTemp.FMQN = "way_eng_3";
		break;
		
		case "monk_6":
			DelLandQuestMark(npchar);
			pchar.quest.FMQN_fail.over = "yes";
			dialog.text = "Selam, oğlum.";
			link.l1 = "Sana da aynısı, papaz. Yeni bir haber var mı?";
			link.l1.go = "monk_6x";
		break;
		
		case "monk_6x":
			dialog.text = "Evet. İş tamam. Şarap 'baharatlandı' ve muhafızlar bu gece özel bir ikram alacaklar. Akşam yemeğini saat dokuzda yiyorlar, gece yarısına kadar hepsi uyumuş olacak. Bunu yapmak için tek şansın bu, ikinci bir fırsat olmayacak. Dikkatli ol, Hollandalı kılığına tamamen güvenemezsin.";
			link.l1 = "Anladım. Hiç vakit kaybetmeyelim. Hoşça kal.";
			link.l1.go = "monk_7";
		break;
		
		case "monk_7":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("FMQ_Nevis", "20");
			sld = CharacterFromID("FMQN_seafox_1");
			sld.dialog.currentnode = "seafox_26";
			LAi_CharacterEnableDialog(sld);
			sld.talker = 9;
			AddLandQuestMark(sld, "questmarkmain");
			pchar.quest.FMQN_fail1.win_condition.l1 = "Timer";
			pchar.quest.FMQN_fail1.win_condition.l1.date.hour  = 20.0;
			pchar.quest.FMQN_fail1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.FMQN_fail1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.FMQN_fail1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.FMQN_fail1.function = "FMQN_EnglandFail";
			pchar.questTemp.FMQN = "way_eng_4";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
