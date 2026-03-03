// Addon-2016 Jason, французские миниквесты (ФМК) Последний урок
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
			dialog.text = "Açık bir hata. Bunu geliştiricilere bildir.";
			link.l1 = "Ah, yapacağım.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "greguar":
			PlaySound("Voice\English\LE\Greguar\Greguar_04.wav");
			pchar.quest.FMQL_delete_guide.over = "yes";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Fortfrance");
			if (CheckAttribute(pchar, "questTemp.HWIC") || pchar.Ship.Type == SHIP_NOTUSED)
			{
				dialog.text = "Oh, "+GetFullName(pchar)+"! Farklı görünüyorsun dostum, hem de başarılısın! Hakkında konuşmaya başladılar, biliyor musun? Hızlı öğreniyorsun, monsieur, seninle gerçekten gurur duyuyorum. Gelecekte daha fazla şans ve bolluk diliyorum! Seni tekrar görmek büyük bir zevk!";
				link.l1 = "Monseigneur Gregoire Valinnie, ne karşılaşma ama! Mütevazı başarılarım için size çok şey borçluyum. Sizi tanımak da büyük bir zevk! Bol şanslar!";
				link.l1.go = "greguar_exit_1";
			}
			else
			{
				dialog.text = "Oh, "+GetFullName(pchar)+"! Farklı görünüyorsun dostum, hem de başarılısın! Hakkında konuşmaya başladılar, biliyor musun? Hızlı öğreniyorsun, monsieur, söylemeliyim ki seninle gurur duydum.";
				link.l1 = "Monsieur Gregoire Valinnie, ne güzel bir karşılaşma! Mütevazı başarılarımda size çok şey borçluyum. Sizi görmek büyük bir zevk! Tahmin edeyim, bana bir iş teklifiniz var?";
				link.l1.go = "greguar_1";
			}
		break;
		
		case "greguar_1":
			dialog.text = "Evet! Elbette biliyorum. Kısa keseceğim, zaman para. Şöyle ki, Brezilya’dan Curaçao’ya stratejik değeri yüksek bir yük taşıyan Hollanda taç filosu, Trinidad ile ana kara arasında İngilizler tarafından pusuya düşürüldü. Şirketin bir fluytu kaçmayı başarıp Boca de la Serpienta kıyısına demir attı. Yükün bir kısmını kurtardılar ama uzun sürmedi – yerli bir Kızılderili kabilesinin saldırısına uğradılar\nAldığım bilgilere göre, o kıyıdaki tüm Hollandalıları öldürüp yükü köylerine götürmüşler. Kızılderililer ayrıca Hollandalıların ateşli silahlarını da ele geçirmiş ama ağır kayıplar vermişler. İşte bu bizim fırsatımız! İngilizler ve Hollandalılar hâlâ o bölgede savaşıyor, kayıp fluytla ilgilenecek halleri yok. Şimdilik... Senin bir gemin ve mürettebatın var. Oraya gidip karaya çıkar, Kızılderilileri tamamen temizleriz. Yük son derece değerli ve orada bol miktarda var\nBen zaten keşif için küçük bir ekip gönderdim – elimden gelen buydu, para sıkıntısı malum. Güvenilir bir alıcım var, kılıcıma ve paralı askerlerime güvenebilirsin. Yüzde elli-yüzde elli paylaşırız, oraya varmak için bir haftamız var. Ne dersin dostum, var mısın?";
			link.l1 = "Beni affedin, monsieur, ama ben almayacağım. Zorlu bir yolculuktan yeni çıktım, tamir ve mürettebat toplamak için yeterli vaktimiz yok. Tanrı'nın unuttuğu bu yerde bile, insan her istediğine sahip olamıyor.";
			link.l1.go = "greguar_exit";
			link.l2 = "Tehlikeli ama kârlı ve macera dolu bir iş gibi görünüyor. Elbette varım! Hadi hiç vakit kaybetmeyelim!";
			link.l2.go = "greguar_2";
		break;
		
		case "greguar_exit":
			dialog.text = "Yazık. Karar senin o zaman. Yolun açık olsun, monsieur, ben yine de oraya gideceğim. İnsan denemeli, değil mi?";
			link.l1 = "Yolun açık olsun, Mösyö Valinnie!";
			link.l1.go = "greguar_exit_1";
		break;
		
		case "greguar_exit_1":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload5_back", "none", "", "", "", 20.0);
		break;
		
		case "greguar_2":
			dialog.text = "Doğru seçim, dostum! Biraz fazladan paraya ihtiyacın vardır, değil mi? Bu arada kardeşin nasıl?";
			link.l1 = "Her zaman fazladan paraya ihtiyacım olur. Michel mi? Kardeşim sağlığı yerinde ve canı sıkılıyor. Bazen ona imreniyorum... Yelken açma vakti!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQL_Begin");
		break;
		
		case "greguar_3":
			PlaySound("Voice\English\QuestMan02.wav");
			dialog.text = "Çok kolay! Bunlar, Hollandalılarla çatışmadan sağ çıkan acemilerdi. Anakaraya daha derine gitmeliyiz, keşif grubum orada olmalı!";
			link.l1 = "Çok kolay gibi geldi... ama kutlamak için henüz erken, monsieur Valinnie. Şuraya bir bakın...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQL_SecondCoastBattle");
		break;
		
		case "greguar_4":
			PlaySound("Voice\English\LE\Greguar\Greguar_05.wav");
			dialog.text = "Kahrolası Kızılderililer! Az kalsın bizi yakalıyorlardı! Şimdi köyde sadece kadınlar ve çocuklar kaldığına eminim. Hadi, ilerleyin!";
			link.l1 = "Tüfeklerden bahsettiğinden pek emin değilim, onları görmedim... Neyse. Hadi gidelim!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQL_GoToJungle");
		break;
		
		case "greguar_5":
			PlaySound("Voice\English\LE\Greguar\Greguar_06.wav");
			dialog.text = "Ne demek istiyorsun? Hollandalılar ve biz hepsini öldürmüş olmalıyız!";
			link.l1 = "";
			link.l1.go = "greguar_6";
		break;
		
		case "greguar_6":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Prosper_fmql")) sld = CharacterFromID("FMQL_Prosper");
			else sld = CharacterFromID("FMQL_mercen");
			sld.dialog.currentnode = "prosper_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "greguar_7":
			dialog.text = "Kaçmak mı? Aklını mı kaçırdın? Az kaldı! Bir avuç boyalı vahşiden mi korkuyorsun?";
			link.l1 = "";
			link.l1.go = "greguar_8";
		break;
		
		case "greguar_8":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Prosper_fmql")) sld = CharacterFromID("FMQL_Prosper");
			else sld = CharacterFromID("FMQL_mercen");
			sld.dialog.currentnode = "prosper_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "greguar_9":
			dialog.text = "En aşağıların en aşağısı, kaptan. Avrupa'ya geri dönüyorum. Hayal kırıklığına uğradım! Senden, bu korkaklardan ve şu lanet bölgeden!";
			link.l1 = "...";
			link.l1.go = "greguar_10";
		break;
		
		case "greguar_10":
			DialogExit();
			DoQuestReloadToLocation("shore18", "goto", "goto8", "FMQL_JungleExit");
		break;
		
		case "greguar_11":
			dialog.text = "Oh! Başardık!";
			link.l1 = "Ama ne pahasına! Bak! Neredeyse tüm ekibimiz öldü. Geri çekilmeliyiz Gregoire, bizi bekleyen başka savaşçılar olmadığına dair hiçbir garanti yok. Ayrıca, ganimeti taşımak için yeterli adamımız da yok.";
			link.l1.go = "greguar_12";
		break;
		
		case "greguar_12":
			dialog.text = "Kahretsin! Üzücü ama haklısın, "+pchar.name+": vahşiler tamamen ölmüş olsa bile, Hollandalılar ya da İngilizler buraya çıkmadan yükü götüremeyeceğiz. Şimdi gitmeliyiz! Kahrolası sahil de cehenneme gitsin!";
			link.l1 = "...";
			link.l1.go = "greguar_10";
		break;
		
		case "greguar_13":
			dialog.text = "Oh! Başardık! Güzel iş çıkardın, "+pchar.name+" ! Şimdi ödülümüz için vahşilerin inine geçelim! Artık bizi hiçbir şey durduramaz!";
			link.l1 = "Britler ve Hollandalılar hâlâ birbirleriyle uğraşırken acele etmeliyiz. Hadi gidelim!";
			link.l1.go = "greguar_14";
		break;
		
		case "greguar_14":
			DialogExit();
			DoQuestCheckDelay("FMQL_RunToGrabbing", 1.0);
		break;
		
		case "greguar_15":
			dialog.text = "İyi iş çıkardık, "+pchar.name+". Şimdi tek yapmamız gereken, yükü kimseye fark ettirmeden satmak. Güvenilir bir alıcım var, gece yarısı Lamentin Körfezi'nde bizi bekliyor olacak. Yanına subay alma ve buluşmadan önce oraya uğrama, müşteri oldukça tedirgin biri.";
			link.l1 = "İş iştir. Yük satılmalı ve bu güvenli bir şekilde yapılmalı, yoksa Poincy'ye olan borcum daha da artacak. Peki, gece yarısında orada olacağım.";
			link.l1.go = "greguar_16";
		break;
		
		case "greguar_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.quest.FMQL_goods_timer.win_condition.l1 = "Timer";
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.hour  = 0.0;
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQL_goods_timer.function = "FMQL_MeetingOnLamanten";
			AddQuestRecord("FMQ_Lesson", "7");
			LAi_LocationDisableOfficersGen("Shore38", true); // may-16
			LAi_LocationFightDisable(&Locations[FindLocation("Shore38")], true);
			locations[FindLocation("Shore38")].DisableEncounters = true;
			Pchar.GenQuest.Hunter2Pause = true;
		break;
		
		case "greguar_17":
			PlaySound("Voice\English\Master_01.wav");
			pchar.quest.FMQL_goods_over.over = "yes";// лесник снято прерывание на встречу.
			dialog.text = "İş tamam. Yük indirildi, müşteri burada. Konuşmayı bana bırak.";
			link.l1 = "...";
			link.l1.go = "greguar_18";
		break;
		
		case "greguar_18":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("FMQL_contra_"+i);
				if (i == 2) 
				{
					LAi_CharacterEnableDialog(sld);
					AddLandQuestMark(sld, "questmarkmain");
				}
			}
		break;
		
		case "greguar_19":
			dialog.text = "Sürpriz, pislikler!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQL_LookOnGuards");
		break;
		
		case "greguar_20":
			PlaySound("Voice\English\OliverTrast01.wav");
			dialog.text = "Ah, Johnny, ne adam ama! Harika! Söylemek istediğin bir şey var mı, "+pchar.name+"?";
			link.l1 = "Hayır. Aslında, evet! Ne oluyor be?!";
			link.l1.go = "greguar_21";
		break;
		
		case "greguar_21":
			dialog.text = "Ölüyle alay etme, monsieur. Nerede senin görgün?.. Para burada, yükle de ben ve arkadaşlarım ilgileniyoruz. Onları kıyıya göndermedim, israf olurdu. Özellikle Johnny'i oraya göndermek... Şu elinde culverin olan Kızılderiliyi görüyor musun? Biliyor musun, Johnny kendi kabilesini hiç sevmezdi zaten.";
			link.l1 = "Anladım... Şimdi ne olacak? Beni de mi öldüreceksin?";
			link.l1.go = "greguar_22";
		break;
		
		case "greguar_22":
			dialog.text = "Aslında yapmalıydım. Ama duygusalım. Git ve paranın dörtte birini al. Yük ve kalan para burada benimle kalacak. Kahramanlık yapmaya kalkma, burası ana karanın ormanları değil. Hiç şansın yok.";
			link.l1 = "Ve senin asaletin ve görgün nerede, Gregoire? Bunu senden beklemezdim. Gidiyorum, ama bunu unutmayacağım.";
			link.l1.go = "greguar_23";
			link.l2 = "Kahramanlık taslamıyorum, hiç taslamadım. Sizi öldüreceğim, hepinizi! Önce bu hanımları, sonra el bombası atan maymunu, sonra da seni!";
			link.l2.go = "greguar_25";
		break;
		
		case "greguar_23":
			dialog.text = "Bu sahilde ne asilzadeler ne de serseriler var, monsieur. Burada sadece beş adam, büyük bir silah ve bir kurban var. Bu burada sık sık olur, ama sen tek doğru seçimi yaptın. Aferin. Biliyor musun, senin yerinde şu an burada, tam bu noktada, iki başkası da olabilirdi? Onlar neredeyse senin gibiler. Ama burada olan sensin, onlar değil, ve bence bunun yüzünden yok olacaklar.";
			link.l1 = "Anlamadım...";
			link.l1.go = "greguar_24";
		break;
		
		case "greguar_24":
			dialog.text = "Bir gün sen de öğreneceksin. Onlar son derslerini almadılar. Sen aldın. Rica ederim. Elveda, monsieur. Karayiplere hoş geldin!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQL_PeaceFinal");
		break;
		
		case "greguar_25":
			dialog.text = "Ahh... Şimdiye kadar gördüğüm en parlak öğrenci değilsin. Peki... herkesin yolu kendine!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQL_BattleOnBeach");
		break;
		
		case "mercen":
			PlaySound("Voice\English\pirat_guard_4.wav");
			dialog.text = "Tam zamanında geldin! Cariblerin saldırısından zor kurtulduk, senin tarafına doğru gidiyorlardı ve haline bakılırsa, onlarla çoktan karşılaşmışsın. Köyleri yakında, ama asıl dertlerimiz şimdi başlıyor.";
			link.l1 = "";
			link.l1.go = "prosper_2";
		break;
		
		case "prosper":
			dialog.text = ""+GetFullName(pchar)+"! Buradasın! Ve neden hiç şaşırmadım! Tam zamanında geldin, dostum. Az daha Kariplerin sürüsünden zor kurtuluyorduk, senin tarafa gidiyorlardı ve haline bakılırsa, onlarla zaten karşılaşmışsın.";
			link.l1 = "Prosper! Ve şaşırdım doğrusu! Yine yerlilere bela mı oluyorsun? Selina iyidir umarım?";
			link.l1.go = "prosper_1";
		break;
		
		case "prosper_1":
			dialog.text = "Bu sefere katılmak benim için aptallıktı. Kızım beni bir daha görebilecek mi, merak ediyorum. Selina mı? O evde oturup seni hayal ediyor! Martinique'in gençleri artık tüm umutlarını kaybetti... Biliyor musun, bu tüfeği aldığıma artık pişman değilim. Sağlam bir silah. Güvenilir. Ayrıca, başka bir intihar görevine katılmak için fazladan bir sebep, gerçi sen ortaya çıkınca bu iş biraz daha az intihar gibi oldu. Köyleri yakınlarda, ama asıl sorunlarımız şimdi başlıyor.";
			link.l1 = "";
			link.l1.go = "prosper_2";
		break;
		
		case "prosper_2":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "prosper_3":
			dialog.text = "Hepsi değil. İzci vuruldu ama yine de onların inine ulaşmayı başardı. Şef bizzat muhafızlarıyla buraya geliyor. Ellerinde Hollanda tüfekleri var. Sayıca üstünler ve öfkeden delirmiş durumdalar. Şef, kabilesinin en iyi savaşçısı, adamları ise adeta şeytan gibi. Hemen, burada bir karar vermeliyiz. Ya onlarla savaşırız ya da kaçarız. Açıkçası, ben ikinciyi tercih ederim...";
			link.l1 = "";
			link.l1.go = "prosper_4";
		break;
		
		case "prosper_4":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_7";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "prosper_5":
			dialog.text = "Onları görmedin, dostum! Bu 'vahşiler'in ellerinde tüfekler var ve onları şaşırtıcı derecede iyi kullanıyorlar. Belli ki birisi onlara eğitim vermiş, bu kesin! O yüzden bana bir daha korkak deme!";
			link.l1 = "Sakin olalım ve ne yapacağımıza karar verelim. Hâlâ zamanımız var.";
			link.l1.go = "prosper_6";
		break;
		
		case "prosper_6":
			int n = 0;
			for (i=1; i<=5; i++)
			{
				if (GetCharacterIndex("FMQL_sailor_"+i) != -1) n++;
			}
			dialog.text = "Dinliyorum, "+pchar.name+".";
			if (n > 2 && GetSummonSkillFromName(pchar, SKILL_SNEAK) > 30)
			{
				Notification_Skill(true, 31, SKILL_SNEAK);
				link.l1 = "Onlara iyi bir mücadele vereceğiz, çocuklar! Şu tepenin ardında mallar ve para var! Buraya onlar için geldik ve asla vazgeçmeyeceğiz. Bir avuç Kızılderili, ellerinde tüfek olsa bile, bizi durduramaz! Şunları toprağa gömelim ve işi bitirelim! Yeterince adamımız var, pusu kurma şansımız da var. Dört adamımız yandan ateşle karşılayacak, geri kalanımız burada mevzi alacak. Sayılarını azaltıp işlerini bitireceğiz!";
				link.l1.go = "prosper_8";
			}
			else
			{
				if (GetCharacterSkill(pchar, SKILL_SNEAK) < 31) Notification_Skill(false, 31, SKILL_SNEAK);
				if (n < 3) notification("Not enough people", "X");
				if (n > 0)
				{
					link.l1 = "Onlara iyi bir ders vereceğiz, çocuklar! Şu tepenin ardında mallar ve para var! Biz buradayız ve gitmeye niyetimiz yok. Birkaç Kızılderili, ellerinde tüfek olsa bile, bizi durduramaz! Şunları haklayalım ve işi bitirelim!";
					link.l1.go = "prosper_7";
				}
				else
				{
					link.l1 = "Her açıdan şans bizden yana değil. Arkamızdaki Hollandalıları da unutma.";
					link.l1.go = "prosper_9";
				}
			}
		break;
		
		case "prosper_9":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "prosper_7":
			DialogExit();
			pchar.questTemp.FMQL = "battle";
			AddDialogExitQuestFunction("FMQL_PrepareAttack");
		break;
		
		case "prosper_8":
			DialogExit();
			pchar.questTemp.FMQL = "sneak";
			AddDialogExitQuestFunction("FMQL_PrepareSneakAttack");
		break;
		
		case "prosper_9x":
			dialog.text = "Hayattayız ve evimizdeyiz! Yemin ederim, önümüzdeki birkaç ay için macera bana yeter... ha-ha! Kızıma gitmeliyim, lütfen bizi ziyarete gel, "+pchar.name+". Ve lütfen, dikkatli ol.";
			link.l1 = "Hiçbir söz veremem, Prosper. Yolun açık olsun!";
			link.l1.go = "prosper_10";
		break;
		
		case "prosper_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 10.0);
		break;
		
		case "prosper_11":
			pchar.quest.FMQL_prosper_dead.over = "yes";
			LAi_RemoveCheckMinHP(npchar);
			PlaySound("Voice\English\pirat_guard_4.wav");
			dialog.text = "Sana dikkatli olmanı söylemiştim, kaptan! Bu herif hakkında şüphelerim vardı.";
			link.l1 = "Zengin ol! Teşekkür ederim! Ama nasıl?";
			link.l1.go = "prosper_12";
		break;
		
		case "prosper_12":
			sTemp = "";
			if (CheckAttribute(pchar, "questTemp.FMQL.PirateDead")) sTemp = "Poor lad, even though he was a pirate.";
			dialog.text = "Johnny çok konuşkan oldu. Kumda duran Kızılderili adam. Bir geneleve geldi ve bir kızla birlikte olmaya çalıştı. Ona hizmet etmeyi reddettiler, Johnny öfkelendi, yakında zengin olacağını, o ve arkadaşları ormanda bir kaptanı öldürdüklerinde bunu başaracaklarını bağırmaya başladı. Neler olacağını anladım ve kasabada biraz ün kazanmış olan subayınıza koştum."+sTemp+" Sana çok şey borçluyum, "+pchar.name+", bu yüzden bana fazla teşekkür etmene gerek yok.";
			link.l1 = "Yine de çok teşekkür ederim, Prosper! Burada işler zordu... fazlasıyla zordu. Mürettebatıma katılmak ister misin? Senin gibi bir subaya ihtiyacım var. Bu devirde sadık adam bulmak zor, hele de iyi nişancıları.";
			link.l1.go = "prosper_13";
		break;
		
		case "prosper_13":
			dialog.text = "Hayır, dostum. Kızıma karşı sorumluluklarım var. Bana maceralarımı geride bırakacağıma dair yemin ettirdi. O, benim son maceramdı. Kahretsin, ne yazık, ama kızımı dünyadaki her şeyden çok seviyorum. Elveda, "+pchar.name+". Ve... Selina sürekli senden bahsediyor. Belki bir gün bize uğrarsın?";
			link.l1 = "Kim bilir, belki de yaparım... Elveda, Prosper! Umarım kızın iyi bir koca bulur... (kendi kendine) Ders alındı, monsieur Gregoire, ders alındı... Herkes kendi yolunda, dedi... Bunu unutmayacağım.";
			link.l1.go = "prosper_14";
		break;
		
		case "prosper_14":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 15.0);
			chrDisableReloadToLocation = false;
			InterfaceStates.Buttons.Save.enable = true; // разрешим сохраняться
			AddQuestRecord("FMQ_Lesson", "15");
			CloseQuestHeader("FMQ_Lesson");
			pchar.questTemp.FMQL = "end";
		break;
		
		case "contra":
			DelLandQuestMark(npchar);
			dialog.text = "Sen de kimsin be?";
			link.l1 = "Yük elimizde. İlgilenir misin?";
			link.l1.go = "contra_1";
		break;
		
		case "contra_1":
			dialog.text = "Ha. Oldukça ilgilendim. Özellikle de müvekkilimin. Ne kadar kazanacağız?";
			link.l1 = ""+FindRussianQtyString(sti(pchar.questTemp.FMQL.Sanl))+" demir ağacından, "+FindRussianQtyString(sti(pchar.questTemp.FMQL.Silk))+" gemi ipeği, "+FindRussianQtyString(sti(pchar.questTemp.FMQL.Rope))+"   halat ve   "+FindRussianQtyString(sti(pchar.questTemp.FMQL.Oil))+" reçine.";
			link.l1.go = "contra_2";
		break;
		
		case "contra_2":// Addon 2016-1 Jason пиратская линейка
			iTotalTemp = 2200*sti(pchar.questTemp.FMQL.Sanl)+1600*sti(pchar.questTemp.FMQL.Silk)+1000*sti(pchar.questTemp.FMQL.Rope)+900*sti(pchar.questTemp.FMQL.Oil);
			dialog.text = "Pekâlâ. Her bir demir ağaç parçası için 2200 peso, reçine için 900 peso, gemi ipeği için 1600 peso ve halatlar için 1000 peso. Bakalım burada ne varmış... Hımm, hımm. "+iTotalTemp+" peso. Anlaştık mı?";
			link.l1 = "Anlaştık!";
			link.l1.go = "contra_3";
		break;
		
		case "contra_3":
			LAi_Fade("", "");
			FMQL_CreateGuidesWarriors();
			dialog.text = "Harika! Daha fazlasını getir. Hollandalılar, Kızılderililere cömertlikte sınır tanımıyor... Peki ya şu misafirler kim? Ne oluyor burada?!";
			link.l1 = "";
			link.l1.go = "contra_4";
		break;
		
		case "contra_4":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_19";
			AddMoneyToCharacter(sld, iTotalTemp);
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "FMQL_beach":
			pchar.quest.FMQL_pirate_dead.over = "yes";
			LAi_RemoveCheckMinHP(npchar);
			dialog.text = "Evet, kaptan. Yola çıkmadan önce fazla içtim, bir sebebi vardı.";
			link.l1 = "Sen mi? Nasıl?!";
			link.l1.go = "FMQL_beach_1";
		break;
		
		case "FMQL_beach_1":
			dialog.text = "Üzgünüm, kaptan. O Kızılderililerle yaşanan karmaşadan sonra bir iki kadeh içmem gerekti. Bir kız vardı, yüz peso verip bir oda tuttum ve o... o...";
			link.l1 = "Ne? Soydular mı seni?";
			link.l1.go = "FMQL_beach_2";
		break;
		
		case "FMQL_beach_2":
			sld = CharacterFromID("FMQL_Prosper");
			dialog.text = "Hayır! Aşık oldu! Kahretsin, oradan kaçmalıydım! Ama sonra arkadaşın çıkageldi, bana bu pislikten, senin eski yoldaşından bahsederek, seni hem kandırmak hem de öldürmek istediğini bağırıp durdu.";
			if (LAi_GetCharacterHP(sld) > 0)
			{
				link.l1 = "Aferin, Prosper...";
				link.l1.go = "FMQL_beach_3";
			}
			else
			{
				link.l1 = "Prosper... Çok üzgünüm. Kızına göz kulak olacağım. Dersimi aldım, Mösyö Gregoire... Ne demiştin? Herkes kendi yolunda mı? Bunu aklımda tutmalıyım.";
				link.l1.go = "FMQL_beach_3";
			}
		break;
		
		case "FMQL_beach_3":
			dialog.text = "Gidelim mi, kaptan?";
			link.l1 = "Evet. Hizmetin için teşekkürler. Kupadan uzak dur, biz de seni o güzellikten kurtarırız. Hadi gidelim.";
			if (CheckAttribute(pchar, "questTemp.FMQL.ProsperDead")) link.l1.go = "FMQL_beach_5";
			else link.l1.go = "FMQL_beach_4";
		break;
		
		case "FMQL_beach_4": // Проспер жив
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload_sea", "none", "", "", "FMQL_PirateNormal", 10.0);
			sld = CharacterFromID("FMQL_Prosper");
			sld.Dialog.currentnode = "prosper_11";
			sld.MusketerDistance = 20;
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0); 
		break;
		
		case "FMQL_beach_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "FMQL_PirateNormal", 10.0);
			if (sti(pchar.money) >= 20000) DoQuestFunctionDelay("FMQL_MoneyForSelina", 0.5);
			else
			{
				pchar.quest.FMQL_money_20k.win_condition.l1 = "Money";
				pchar.quest.FMQL_money_20k.win_condition.l1.value = 20000;
				pchar.quest.FMQL_money_20k.win_condition.l1.operation = ">=";
				pchar.quest.FMQL_money_20k.function = "FMQL_MoneyForSelina";
			}
			chrDisableReloadToLocation = false;
			InterfaceStates.Buttons.Save.enable = true; // разрешим сохраняться
			AddQuestRecord("FMQ_Lesson", "10");
			CloseQuestHeader("FMQ_Lesson");
			pchar.questTemp.FMQL = "end";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
