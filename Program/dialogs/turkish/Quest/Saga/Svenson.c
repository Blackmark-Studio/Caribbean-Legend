// Ян Свенсон - пиратский барон Западного Мэйна
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp, sStr;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Svenson")) {
				if (pchar.questTemp.HelenDrinking.Result == "won") {
					dialog.text = "Ah, Charles. Geldiğin için teşekkürler. Sadece Helen'le vakit geçirdiğin için sana teşekkür etmek istedim. Kızın yaralarını sarması gerekiyordu, ve senin de iyi vakit geçirdiğini duydum, ha-ha! Kahretsin, neredeyse kıskandım!";
					link.l1 = "Hiç üzülmedin mi? Fıçı yüzünden ve... diğer her şey için?";
					link.l1.go = "after_drinking";
				} else {
					dialog.text = "Ah, Charles. Geldiğin için teşekkürler. Sadece Helen'le vakit geçirdiğin için sana teşekkür etmek istedim. Kızın yaralarını sarması gerekiyordu, senin de iyi vakit geçirdiğini duydum, ha-ha! Cartagena'da sana bol şans!";
					link.l1 = "Evet, dün her şeyin yolunda gitmesine ben de sevindim. Tekrar görüşene dek, Jan.";
					link.l1.go = "exit";
				}
				
				DeleteAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Svenson");
				break;
			}
		
			if(CheckAttribute(pchar, "questTemp.Saga"))
			{
				if (CheckAttribute(pchar, "questTemp.Saga_Late")) // отсекание при провале по времени
				{
					dialog.text = "Ah, dostum "+pchar.name+"Sizi görmek ne güzel! Size nasıl yardımcı olabilirim?";
					link.l1 = "Sadece nasıl olduğunu görmek için uğradım.";
					link.l1.go = "exit";
					if(CheckAttribute(npchar, "quest.trade_bakaut")) // торговля бакаутом
					{
						if (GetDataDay() == 14 || GetDataDay() == 28)
						{
							link.l2 = "Jan, demir ağacı satın almak istiyorum.";
							link.l2.go = "trade_bakaut";
						}
					}
					break;
				}
				if(pchar.questTemp.Saga == "svenson")
				{
					dialog.text = "Size nasıl yardımcı olabilirim, efendim?";
					link.l1 = "Senden yardım istemek istiyorum, Orman Şeytanı.";
					link.l1.go = "saga";
					break;
				}
				if(pchar.questTemp.Saga == "svenson1")
				{
					dialog.text = "Aha, dostum "+pchar.name+"! Ne haber?";
					link.l1 = "Cellattan pek çok ilginç şey öğrenmeyi başardım.";
					link.l1.go = "saga_11";
					break;
				}
				if(pchar.questTemp.Saga == "svenson2")
				{
					dialog.text = "Yani, "+pchar.name+", Gladys ile konuştun mu?";
					link.l1 = "Evet, yaptım. Jan, buraya bir bak... Şu parşömen parçası hakkında bana bir şey söyleyebilir misin?";
					link.l1.go = "saga_17";
					break;
				}
				if(pchar.questTemp.Saga == "helena1" || pchar.questTemp.Saga == "helena2" || pchar.questTemp.Saga == "svenson_wait")
				{
					dialog.text = "Sana henüz anlatacak yeni bir şeyim yok, "+pchar.name+". Ama sorunumuzun çözümü üzerinde çalışıyorum. Sonra tekrar gel.";
					link.l1 = "Pekala, Jan. Sonra görüşürüz.";
					link.l1.go = "exit";
					break;
				}
				if(pchar.questTemp.Saga == "baronsquests") // старт трех квестов баронов
				{
					// первая проверка времени. Свенсон очень недоволен растяпством ГГ. Счищаем Элен, к Свенсону доступ закроем
					if (CheckAttribute(pchar, "questTemp.Saga.Late"))
					{
						dialog.text = ""+pchar.name+", beni tam anlamıyla hayal kırıklığına uğrattın. Senden ciddi bir adam olmanı bekliyordum, ama görüyorum ki sadece aptal bir çocuksun. Bunca zamandır neredeydin, ha? Sen kim bilir neyle uğraşırken İngilizler Isla Tesoro'yu ele geçirdi!\nBütün planlarım mahvoldu! Açıkçası, neredeyse varlığını unutmuştum ve hatırlamak da istemiyorum. Defol git!";
						link.l1 = "İnanamıyorum!";
						link.l1.go = "saga_l1";
					}
					else
					{
						dialog.text = "İşte buradasın, "+pchar.name+"Durumumuzu biraz düşündüm. Buna tam olarak bir plan diyemem, ama...";
						link.l1 = "Tamamen seni dinliyorum, Jan.";
						link.l1.go = "saga_25";
					}
					break;
				}
				if(pchar.questTemp.Saga == "baronsquests_1") // идут три квеста баронов
				{
					dialog.text = "İşler nasıl gidiyor? Yardım edebileceğim bir şey var mı?";
					if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "after_marlow")
					{
						link.l3 = "Siyah Papaz'la konuştum. Ne yazık ki, sohbetimizin sonucu beni doğrudan sana danışmaya geri getirdi, ne yapacağımı bilemiyorum.";
						link.l3.go = "shark_hunt_2";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "LSC" && !CheckAttribute(pchar, "questTemp.Saga.BaronReturn"))
					{
						link.l3 = "Dios'u buldum ve keyifli bir sohbet ettik. Bana birçok ilginç şey anlattı, ama ne yazık ki işin özüne inemedik.";
						link.l3.go = "shark_hunt_7";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.BaronReturn") && pchar.questTemp.Saga.BaronReturn == "third_teleport")
					{
						link.l3 = "Ah, Jan. Sana anlatacak o kadar çok şeyim var ki, hepsini anlatmam bütün gece sürerdi, bu yüzden kısa keseceğim.";
						link.l3.go = "return_LSC";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.BaronReturn") && pchar.questTemp.Saga.BaronReturn == "shamane" && !CheckAttribute(npchar, "quest.shamane"))
					{
						link.l3 = "Nathaniel Hawk'u Justice Adası'ndan aldım. Şu anda gemimde.";
						link.l3.go = "nathaniel";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.BaronReturn") && pchar.questTemp.Saga.BaronReturn == "treatment")
					{
						link.l3 = "Nathaniel Hawk'ı tedavi için Miskito köyüne, Yılan Göz adında bir şamana bıraktım. Nathan'ın sağlığını geri kazandıracağına söz verdi.";
						link.l3.go = "nathaniel_2";
					}
					link.l4 = "Şu anda anlatacak pek bir şeyim yok. Sadece nasıl olduğunu görmek için uğradım.";
					link.l4.go = "exit";
					break;
				}
				if(pchar.questTemp.Saga == "fail_centurion") // провал - потоплен Центурион
				{
					dialog.text = "Ne haber, "+pchar.name+"? Nasılsın, işler nasıl gidiyor?";
					link.l1 = "Ah, daha kötüsü olamazdı. O kadar çok uğraştım ki... Jackman'ın izini sürdüm, kılıfları fırlattık, onu da en büyük aptal gibi boğdum, kamarasında ne varsa hepsiyle birlikte. Şimdi Shark'ın adını temize çıkarmaya ya da suçu Barbazon'a atmaya yarayacak hiçbir şeyim yok. Korkarım bu iş kaybedildi, Jan.";
					link.l1.go = "saga_f_1";
					break;
				}
				if(pchar.questTemp.Saga == "calendar") // квесты баронов завершены
				{
					// вторая проверка времени. Отбираем Элен, со Свенсоном нейтральные отношения - ну не выщло и не вышло, хоть попытались. Данни и Натана - в Марун-Таун
					if (CheckAttribute(pchar, "questTemp.Saga.Late"))
					{
						dialog.text = "Kahramanlıklarını duydum! Dannie bana kısaca anlattı. Bu arada, artık arkadaşız. Nathan da tamamen değişti! 'Centurion'unu görünce bütün o depresyonu yok oldu.\nAma sana kötü bir haberim var, "+pchar.name+". O kadar çok zaman kaybettik ki, Sharp'ın vasiyetindeki miras hakları çoktan gitti ve Isla Tesoro artık bir İngiliz askeri üssü oldu. Levasseur konusunda sana daha fazla yardımcı olamam."link.l1 ="Gerçekten nutkum tutuldu... Bunca sıkıntıyı boşuna çekmişiz. Hiç mi yapabileceğimiz bir şey yok?";
						link.l1.go = "saga_l2";
					}
					else
					{
						dialog.text = "Tüm kahramanlıklarını duydum! Dannie bana her şeyi anlattı. Bu arada, barıştık. Nathan'ı tanıyamazsın bile. 'Centurion'unu' görür görmez, bütün homurdanmalarını kötü bir rüya gibi geride bıraktı...";
						link.l1 = "Nathan yine iyi mi? Bunu duyduğuma sevindim!";
						link.l1.go = "saga_26";
					}
					break;
				}
				if(pchar.questTemp.Saga == "mine") // рудник взят
				{
					dialog.text = "İşte buradasın, "+pchar.name+" ! Şimdi sana anlatacak bir şeyim var.";
					link.l1 = "Merhaba, Jan. Çok mutluyum! Ne haber? Umarım güzel bir şeydir?";
					link.l1.go = "saga_32";
					break;
				}
				if(pchar.questTemp.Saga == "mine_1") // рудник взят совместно
				{
					dialog.text = "Buyurun, "+pchar.name+" ! Biraz dinlendin mi? Ve yine büyük maceralara hazır olduğunu söyleyebilir miyim?";
					link.l1 = "Merhaba, Jan. Evet, hazırım.";
					link.l1.go = "saga_32a";
					break;
				}
				if(pchar.questTemp.Saga == "late_l3") // провал по времени у адвоката
				{
					dialog.text = "Ne haber, "+pchar.name+"? Nasılsın, işler nasıl gidiyor?";
					link.l1 = "Ah. Her şey gerçekten berbat.  Sonuna kadar direndim, ama yine de kaybettim. Hatırlarsan, Sharp'ın vasiyetinde bir süre sınırı vardı. O süre doldu ve Isla Tesoro artık bir İngiliz askeri üssü oldu. Artık yapacak bir şey yok, Jan.";
					link.l1.go = "saga_l3";
					break;
				}
				if(pchar.questTemp.Saga == "bakaut") // пришёл от адвоката за деньгами
				{
					dialog.text = "Selamlar, "+pchar.name+"! Güzel haber: Konsey toplantısı yapıldı ve Kıyı Kardeşliği yeni bir lider buldu.";
					link.l1 = "İyi günler, Jan. Senin adına sevindim.";
					link.l1.go = "saga_44";
					break;
				}
				if(pchar.questTemp.Saga == "sellbakaut" && GetSquadronGoods(pchar, GOOD_SANDAL) >= 1) // отдает бакаут
				{
					dialog.text = "Peki, "+pchar.name+"? Mulligan'a yetişebildin mi?";
					link.l1 = "Ben yaptım. Demir ağacını çalan oydu.";
					link.l1.go = "saga_55";
					break;
				}
				if(CheckAttribute(npchar, "quest.bakaut") && GetNpcQuestPastDayParam(npchar, "bakaut_date") >= 1) // за деньгами за бакаут
				{
					dialog.text = "Her zamanki gibi tam vaktinde, "+pchar.name+". Getirdiğin demir ağacını sattım.";
					link.l1 = "Mükemmel. Ne kadar para kazandın?";
					link.l1.go = "saga_57";
					break;
				}
				if(CheckAttribute(npchar, "quest.bakaut_sum")) // сам продал бакаут
				{
					dialog.text = "Pekâlâ, "+pchar.name+"? Molligan'a yetişebildin mi?";
					link.l1 = "Yaptım. Demir ağacını çalan oydu. Tesadüfen alıcısıyla da karşılaştım. Hollandalı bir askeri komutandı. Malları ona sattım.";
					link.l1.go = "saga_59";
					link.l2 = "Yaptım. Bana ambarını göstermesi için zorladım... aramızda bir arbede çıktı ve... artık Molligan diye biri yok. Ama ambarında abanoz ve maun dışında görebileceğin hiçbir şey yok.";
					link.l2.go = "saga_59_1";
					break;
				}
				if(CheckAttribute(npchar, "quest.jessika")) // информация о Джессике
				{
					dialog.text = TimeGreeting()+", "+pchar.name+". Ne var ne yok?";
					link.l1 = "Jan, seninle bir konuda konuşmak istiyorum. Helen’in annesi Beatrice’in geçmişini araştırırken, senin de çok iyi tanıdığın birine rastladım. Bildiğim kadarıyla...";
					link.l1.go = "saga_62";
					break;
				}
				if(pchar.questTemp.Saga == "lastpages") 
				{
					dialog.text = TimeGreeting()+", "+pchar.name+" . İşler nasıl gidiyor? Yüzüne bakılırsa, tebrik edebilir miyim? ";
					link.l1 = "Evet. Sonunda bu karmaşayı çözmeyi başardım. Helen, Isla Tesoro üzerindeki tüm haklarını aldı. Artık hiç kimse Kıyı Kardeşliği'nin sığınağına el uzatamayacak!";
					link.l1.go = "saga_82";
					break;
				}
				if (pchar.questTemp.Saga == "end") sTemp = "Oh, my friend "+pchar.name+"! Pleased to see you! What brings you here?";
				else sTemp = "Anything else, "+pchar.name+"?";
				dialog.text = sTemp;
				link.l1 = "Hayır, Jan. Şu anda hiçbir şey yok.";
				link.l1.go = "exit";
				if(CheckAttribute(npchar, "quest.trade_bakaut")) // торговля бакаутом
				{
					if (GetDataDay() == 14 || GetDataDay() == 28)
					{
						link.l2 = "Jan, biraz demir ağacından almak istiyorum.";
						link.l2.go = "trade_bakaut";
					}
				}
				NextDiag.TempNode = "First time";
			}
			else
			{
				// заглушка Элен
				if(startHeroType == 4)
				{
					dialog.text = "Helen, merhaba, canım. Ne haber? Bana söylemek istediğin bir şey mi var?";
					link.l1 = "Merhaba, Jan! Sadece seni görmek için uğradım, hepsi bu.";
					link.l1.go = "exit";
					NextDiag.TempNode = "First time";
					break;
				}
				dialog.text = "Sana bir konuda yardımcı olabilir miyim?";
				link.l1 = "Hayır, iyiyim.";
				link.l1.go = "exit";
				NextDiag.TempNode = "First time";
			}
		break;
		
		case "saga":
			dialog.text = "Seni tanıyorum, kahretsin! Sen, Rumba'yı kurtaran ve İngiliz korvetinin toplarının önüne dimdik çıkan cesur kaptansın! Seni görmek ne büyük mutluluk! Helen benim için bir kız evlat gibidir. Bugünden itibaren sana sonsuza dek minnettarım. Bana Jan ya da istersen Svenson diyebilirsin. Senin için ne yapabilirim?";
			link.l1 = "Levasseur'u, Tortuga valisini ortadan kaldırmam gerekiyor. Onun adasına ulaşmanın kolay olmayacağını biliyorum, bu yüzden tavsiye almak için sana geldim.";
			link.l1.go = "saga_1";
		break;
		
		case "saga_1":
			dialog.text = "Aman Tanrım, keşke birkaç yıl önce burada olsaydın! Aynı macerayı ben de planlıyordum. O adam Fransızlarla bütün oyunumuzu bozdu. Ama o zamanlar her şey başkaydı. Blaze hayattaydı, Shark'ın sözü geçiyordu, Nathan ise Maroon Town'da her şeye hükmediyordu... Şimdi ise her şey değişti ve Tanrı bilir, hiç de iyiye gitmedi. Bizim hakkımızda, Kardeşlik hakkında bir şey biliyor musun?";
			link.l1 = "Buraya daha yeni geldim, bu yüzden neredeyse hiçbir şey bilmiyorum. Sadece senin ve Jackman'ın Konsey üyesi olduğunuzu biliyorum.";
			link.l1.go = "saga_2";
		break;
		
		case "saga_2":
			dialog.text = "Ah, şu Jackman'a dayanamıyorum! O geldiğinden beri bütün dertlerimiz başladı. İsteğini düşüneceğim. Şu anda aklıma bir şey gelmiyor.";
			link.l1 = "Jackman hakkında ilginç bir şey öğrendim.";
			link.l1.go = "saga_3";
		break;
		
		case "saga_3":
			dialog.text = "Hm. Bu da ne?";
			link.l1 = "Jackman, Gladys Chandler ve kızını arıyor. Higgins ile konuştuktan sonra, aradığı kişinin Rumba olduğunu düşünmeye başladım. Görünüşe göre Gladys, Helen'in öz annesi değilmiş ve Sean McArthur ile evlenmeden önce soyadı Chandler'mış.";
			link.l1.go = "saga_4";
		break;
		
		case "saga_4":
			dialog.text = "Lanet olsun! Bu kötü haber. Jackman şimdi her zamankinden daha güçlü. Üstelik, yalnız çalışmadığına dair kötü bir his var içimde. Arkasında oldukça uğursuz bir gölge var. Eğer gerçekten Helen'e ihtiyacı varsa, o kızın acilen bir koruyucuya ihtiyacı var demektir. Korkarım, bunu artık kendim yapacak kadar genç değilim...";
			link.l1 = "Hepsi bu değil. Jackman ayrıca, Kaptan Butcher'ın tayfasından 'Neptune'un eski başçavuşu Henry the Hangman adında birini de arıyor.";
			link.l1.go = "saga_5";
		break;
		
		case "saga_5":
			dialog.text = "Caramba! En kötü şüphelerim doğru çıktı! Bu Kasap ve onun 'Neptune'u tüm takımadayı korku içinde tutardı. O zamanlar Kardeşlik yoktu, herkes kendi başının çaresine bakıyordu. O adam çok kötülük yaptı ve bana çok yakın biri onun yüzünden öldü.\nOnunla hiç tanışma fırsatım olmadı. 'Neptune' bir İngiliz fırkateyni tarafından batırıldı ve Kasap St. John's'ta idam edildi. Kurtulduk ondan! Ama şansına ve gözü pekliğine hayran olan çok kişi vardı.\nJackman'ın kendisi onun sağ kolu ve 'Neptune'daki baş yardımcısıydı. Şaşırdın mı? Eski suçlular şimdi Milletin kahramanları oldu, hepsi Cromwell sayesinde! O eski güzel İngiltere nerede şimdi?\nJackman'ın adamlarından önce Henry the Hangman'ı bulmalıyız. Belki de bu gizemin anahtarı onda, eğer hâlâ hayattaysa.";
			link.l1 = "Bir samanlıkta iğne bulmak daha kolay olurdu herhalde. Hiçbir ipucu bulabildin mi, bari?";
			link.l1.go = "saga_6";
		break;
		
		case "saga_6":
			dialog.text = "Henry'i çocukken tanırdım. Cartagena'lı bir fahişenin oğlu, yarı İspanyoldu ama bunu hep gizli tutardı. Annesi tam bir ateş parçasıydı! Güzel olduğunu söyleyemem ama onun gibi flamenko dansçısı çok azdı. Bütün genelev çıplak Chica Gonzales ve kastanyetlerinin gösterisini izlerdi. Zavallı kız. Korkunç bir hastalığa yakalandı ve mum gibi eriyip gitti. O zaman Henry'i Providence'a gitmeye ikna ettim, orada hızla adını duyurdu ve Nicolas Sharp'ın yakın dostu Thomas Beltrope'un tayfasına katıldı. O ikisi Kraliçe Elizabeth'in son köpekleriydi ve hep birlikte çalışırlardı. Ne güzel günlerdi! Ortağı ölünce Thomas İngiltere'ye döndü. Tayfasını da yanında götürdü ama Henry Karayipler'de kaldı. Farklı kaptanların altında çalıştı, ta ki Kasap ortaya çıkana kadar. Bu arada, lakabını hep yanında taşıdığı pala yüzünden aldı.";
			link.l1 = "Bu bilgi bize ne anlatıyor?";
			link.l1.go = "saga_7";
		break;
		
		case "saga_7":
			dialog.text = "Eğer Cellat korsanlardan saklanmaya karar verdiyse, onun için en güvenli yer bir İspanyol şehri olurdu. Özellikle de Cartagena’daki evinde, çünkü orada arkadaşları ve akrabaları var. Henry oldukça dindar biriydi, bu yüzden başka bir azizin kilisesine gitmesi pek olası değil. Muhtemelen hâlâ çocukluğundan beri kullandığı ismi taşıyordur, Enrique.";
			link.l1 = "Evet... Seçenekler az, ama hiç yoktan iyidir.";
			link.l1.go = "saga_8";
		break;
		
		case "saga_8":
			dialog.text = "Onu bulmaya çalış, Charles! Henry'nin İspanyol kökenlerini pek az kişi biliyor, bu yüzden burada ufak bir avantajımız var. Rumba'yı mürettebatına katılmaya ikna etmenin bir yolunu düşüneceğim. O kızda cesaret var, babasından başka kimsenin emrinde hiç çalışmamış.\nAma ne gemisi var ne de mürettebatı, geçimini sağlamak zorunda. Tabii ki Gladys'e her zamanki gibi yardım etmeye devam edeceğim, ama Helen'i Blueweld'de uzun süre tutamam. Böyle bir subay sana çok faydalı olur. Sean ona bildiği her şeyi öğretti ve onu bir erkek gibi yetiştirdi.\nSenin gibi bir kaptanın emrinde olursa içim daha rahat eder.";
			link.l1 = "Rumba kendini fazlasıyla kanıtladı. Mürettebatımda onun gibi daha fazla insana ihtiyacım var. Yani, eğer onu ikna edebilirsen, onu subay yaparım. Ama önce kim olduğunu ve Jackman'ın ona neden ihtiyacı olduğunu anlamak istiyorum. Korkarım ki, Donovan'ın aksine, Jackman onun cazibesine ilgi duymuyor. Bu yüzden Cellat'ı bulmaya çalışacağım, ama hiçbir şey vaat edemem.";
			link.l1.go = "saga_9";
		break;
		
		case "saga_9":
			dialog.text = "Well, splendid. Take this licence from the Dutch West India Company for three months. Write your name there; it may very well come in handy in your search. In the meantime, I'll think about what you have said concerning Levasseur and Tortuga.";
			link.l1 = "Çok teşekkürler! Bu belge benim için çok işe yarayacak. O halde, ben Cartagena'ya gidiyorum.";
			link.l1.go = "saga_10";
		break;
		
		case "saga_10":
			DialogExit();
			GiveNationLicence(HOLLAND, 90);
			AddQuestRecord("Saga", "14");
			pchar.questTemp.Saga = "cartahena";//идем в Картахену
			pchar.quest.Saga_Gonsales.win_condition.l1 = "location";
			pchar.quest.Saga_Gonsales.win_condition.l1.location = "Cartahena_town";
			pchar.quest.Saga_Gonsales.function = "Saga_CreateGonsalesB";
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", false);//открыть спальню Элен
			LocatorReloadEnterDisable("FortOrange_town", "reload6", true); // закрыть резиденцию Джекмана
			npchar.greeting = "svenson_3";
			
			AddQuestRecord("HelenDrinking", "1");
			pchar.questTemp.HelenDrinking.CanDrink = true;
			SetFunctionTimerConditionParam("HelenDrinking_NoVisit", 0, 0, 1, 24 - GetHour(), false);
			
			pchar.questTemp.Saga.HelenRelation = 0;
		break;
		
		case "saga_11":
			dialog.text = "Henry öldü mü?  Bekle, onu sen mi öldürdün?";
			link.l1 = "Bana öyle iri gözlerle bakma! Bununla hiçbir alakam yok. Kendi vicdanının çürümüşlüğü ve Jackman'dan duyduğu korku yüzünden kendi elleriyle canına kıydı. Yaşlı korsanın kalbinde sorunlar vardı ve fazla ömrü kalmamıştı. İşte öğrenebildiklerim...";
			link.l1.go = "saga_12";
		break;
		
		case "saga_12":
			dialog.text = "Lütfen, söyle bana!";
			link.l1 = "Yirmi yıl önce, Henry, Kaptan Butcher adına öz kızının koruyucu annesine bir sandık altın teslim etmekle görevlendirilmişti. Bu koruyucu annenin Bayan McArthur olduğundan hiç şüphe yok. O zamanlar soyadı Chandler’dı ve Belize’de yaşıyordu. Fakat şartlar nedeniyle Cellat, St John’s’ta tam bir ay daha kalmak zorunda kaldı ve nihayet Belize’ye vardığında, şehir İspanyolların baskını sonrası harabeye dönmüştü, Gladys Teyze ve Sean ise senin koruman altında çoktan ayrılmışlardı.";
			link.l1.go = "saga_13";
		break;
		
		case "saga_13":
			dialog.text = "";
			link.l1 = "Helen'i öz kızları gibi gösterip kendi çocukları olarak büyüttüler. Henry ise izlerini kaybettirdi ve yirmi yıldır Jackman'ın intikamından korkarak sessizce yaşadı. Meğerse Jackman kaptanının kızını arıyormuş. Ama neden, bilmiyorum.";
			link.l1.go = "saga_14";
		break;
		
		case "saga_14":
			dialog.text = "Belki de birinin emirlerini yerine getiriyordur...";
			link.l1 = "Sanmam. Ona kim emir verebilir ki? Kasap öldü. Ölümü resmi belgelerle doğrulandı. Onlarca, hatta belki yüzlerce kişi onun ölümüne tanık oldu.";
			link.l1.go = "saga_15";
		break;
		
		case "saga_15":
			dialog.text = "Belki de mesele Helen’in babasının kim olduğu değil. Belki de her şey onun öz annesiyle ilgili. Kim olduğunu tahmin edebiliyorum ama itiraf etmeye korkuyorum. Ama Gladys! Bunu yıllarca, kocasına bile söylemeden nasıl sakladı! Sean McArthur kesinlikle bana bundan bahsederdi. Aramızda hiç paylaşmadığımız bir sır olmamıştı.";
			link.l1 = "Gladys ile ciddi bir konuşma yapacağım. Onu konuşturacak bir yolum var gibi görünüyor. Bir dahaki sefere kadar, Jan!";
			link.l1.go = "saga_16";
		break;
		
		case "saga_16":
			DialogExit();
			pchar.questTemp.Saga = "gladis1";
			sld = characterFromId("Gladis");
			sld.dialog.currentnode = "Gladis_history";
			AddQuestRecord("Saga", "21");
		break;
		
		case "saga_17":
			dialog.text = "Bunu nereden buldun!?";
			link.l1 = "Gladys bunu bana verdi. Bunun 'Helen'in annesinin mirası' olduğunu söyledi. Adını bilmiyor. İçimden bir ses bunun sıradan bir kağıt parçası olmadığını söylüyor.";
			link.l1.go = "saga_18";
		break;
		
		case "saga_18":
			dialog.text = "Hatırlıyor musun, sana Helen’in gerçek annesinin kim olduğuna dair bir tahminim olduğunu söylemiştim? Artık bundan eminim. Adı Beatrice Sharp’tı. O, öğretmenim ve dostum Nicholas Sharp’ın öz kızı, Kardeşliğimizin kurucusu Blaze Sharp’ın kabul edilmiş kız kardeşi ve Isla Tesoro’nun ortak sahiplerinden biriydi. Jackman’ın peşinde olduğu şey de bu harita parçası.";
			link.l1 = "Vay canına! Ama neden bir adanın haritasının yarısına ihtiyacı olsun ki?";
			link.l1.go = "saga_19";
		break;
		
		case "saga_19":
			dialog.text = " Ada Nicolas Sharp tarafından keşfedildi. Ona Isla Tesoro adını verdi, haritasını çıkardı ve iyi bağlantıları olduğu Providence Island Company aracılığıyla adanın mülkiyetini üstlendi.\nNicolas ifadesinde, adanın yalnızca haritanın iki parçasını da sunabilenlere miras kalabileceğini yazdı. Bunu, herhangi bir anlaşmazlığı önlemek için yaptı. Parçaları Beatrice'e ve üvey oğlu Blaze'e verdi, ardından trajik bir şekilde İspanyolların elinde hayatını kaybetti. ";
			link.l1 = "Vay canına! Ne tuhaf.";
			link.l1.go = "saga_20";
		break;
		
		case "saga_20":
			dialog.text = "Haklısın. En iyi fikir değildi. Üstelik kurnaz bir noter, varisler öldükten sonra bir yıl içinde haritanın iki parçası da bulunamazsa, adanın İngiliz tacına geçeceğini ekledi.\nO zamanlar kimse böyle olacağını öngöremedi. Şimdi ise aptallığımızın bedelini ödüyoruz. Beatrice yirmi yıl önce öldü. Onca yıl geçti, hâlâ onun mezarının ve haritanın parçasının nerede olduğunu bilmiyoruz. Blaze Sharp ise kısa süre önce öldürüldü. Onun parçası da kayboldu.\nEğer kimse Isla Tesoro’nun haritasının tamamını bir yıl içinde yetkililere sunamazsa, Sharptown İngiltere’ye geçecek. Oraya bir valiyle birlikte bir garnizon gönderecekler ve Kardeşlik’in sonu olacak.";
			link.l1 = "Ne yapmamızı öneriyorsun?";
			link.l1.go = "saga_21";
		break;
		
		case "saga_21":
			dialog.text = "Buna izin veremeyiz. Sana ihtiyacım var Charles, böyle bir şeyin olmasını engellemeni istiyorum. Levasseur'u ancak Isla Tesoro'nun kontrolünü ele geçirip Shark Dodson'ı Kardeşliğin yeni lideri olarak seçtikten sonra ortadan kaldırmana yardımcı olabilirim. Aramızda en layık olan o. Sana bir ittifak teklif ediyorum.\nBu arada, Helen'le konuştum. Mürettebatına katılmayı kabul etti.";
			link.l1 = "Bana başka bir seçenek bırakmıyorsun, Jan. Ailemin onurunu geri kazanmadan Fransa'ya dönemem. Bunu yapmak için de Levasseur'u senin yardımınla ya da yardımsız devirmem gerekiyor. Gereksiz ölümler istemiyorum ve umarım Tortuga'yı fazla kan dökmeden ele geçirmenin bir yolunu bulabilirsin. Yine de, Sharps'ın mirasıyla ilgili sisli geçmişi kendi gözlerimle anlamak istediğimi de itiraf etmeliyim.";
			link.l1.go = "saga_22";
		break;
		
		case "saga_22":
			dialog.text = "Akıllıca konuştuğunu duymak güzel! Tortuga'yı ele geçirmenin doğru yolunu bulacağız. Bunu sana söz veriyorum. O halde, başlayalım mı?";
			link.l1 = "Hadi gidelim! Birazdan tekrar uğrarım. Şimdilik, bu işi nereden ele alacağına bir düşün.";
			link.l1.go = "saga_23";
		break;
		
		case "saga_23":
			dialog.text = "İki ya da üç gün sonra tekrar uğra. O zamana kadar planımın meyvesini vereceğini düşünüyorum. Ve Helen'i de yanında gemine almayı unutma. Zavallı kız denizsiz solup gidiyor. Sana sadık bir yardımcı olur, ona güvenmekte asla tereddüt etmezsin.";
			link.l1 = "Pekâlâ, Jan. Hemen gidip onu getireceğim.";
			link.l1.go = "saga_24";
		break;
		
		case "saga_24":
			DialogExit();
			pchar.questTemp.Saga = "helena1";
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", true);//закрыть выходы из города
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", true);//закрыть спальню Элен
			AddQuestRecord("Saga", "23");
		break;
		
		case "saga_25":
			dialog.text = "First, you need to find the Shark. He wanted to get rid of Levasseur himself, and I assure you he has some bright ideas. Of course, we could also persuade Marcus to accept the leadership. He is the keeper of the Codex, after all. But I doubt he would be of any help; he has intentionally limited any contact with Levasseur and Tortuga. A man of principles.   I have no idea where Steven and his men are hiding, but his frigate, 'Fortune', was seen at Puerto Principe. Perhaps Zachary Marlow, also known as the Black Pastor, can point us to where we should look for the Shark. Second, we have to gain the support of the other barons to elect Dodson. And in order to do that, we need to collect their Indian shards – the votes. The new leader must have all five of them. That is what the Code tells us to do in the case that the previous leader has died.   Ridiculous! It is time to change the laws, but only the new leader can do that. We already have my vote. I believe that the Black Pastor doesn't give a damn whose arse is planted in Sharptown. I hope Jackman didn't talk to him first. We also have to persuade both Tyrex and Jacques Barbazon, who hate each other. But it is all irrelevant until we find out what has happened to the Shark. Third, one day we will have to kill Jackman and replace him with someone else. He won't negotiate with us.   Too bad Hawk is dead! People trusted him, and we could use his word. We won't find a better baron for Maroon Town. It is possible that Jackman has something to do with Blaze's murder, so he is also the clue to finding the second part of the map. Jacob trusts no one and most likely keeps the part of the map in his cabin on the 'Centurion'.   Hawk's family used to own the frigate, but Jackman claimed it, just like Hawk's barony. If we find the second part of the map in Jackman's possession, it would be a great argument for Steven's election. Especially for Marcus Tyrex, the Code keeper, and his over-scrupulousness in terms of honour. We will return to Helen her rights over Isla Tesoro as soon as we acquire both parts of the map.   We must be careful, though; Jackman won't stay idle and just watch you searching.";
			link.l1 = "Pekala... Kara Papaz'a bir ziyaret yapacağım. Bana ondan bahset.";
			link.l1.go = "shark_hunt";
			pchar.questTemp.Saga = "baronsquests_1";
		break;
		
		case "shark_hunt":
			dialog.text = "Hell if I know what's on his mind. Sometimes he looks like a complete freak, but nevertheless, I believe it's just clever acting. Besides, his men are ready to fight the devil himself in honour of their beloved Pastor.\nThey've established some sort of Protestant sect, not far from the Spanish Inquisition, on Cuba. So don't even start talking about theological matters there; they won't approve of them.";
			link.l1 = "Bunu dikkate alacağım...";
			link.l1.go = "shark_hunt_0";
		break;
		
		case "shark_hunt_0":
			dialog.text = "Ve, "+pchar.name+": zamanını bir dakika bile boşa harcama. Ciddiyim. Vasiyetteki o maddeyi hatırlıyorsun, değil mi? Eğer mirasçılar bir yıl içinde adayı sahiplenmezse, Isla Tesoro İngiliz tacına geçiyor. Şu anda zaman bizim lehimize değil. Seninle en son görüştüğümüzde, sürenin dolmasına sadece on bir ay kadar kalmıştı.";
			link.l1 = "Hatırlıyorum, Jan.  Haklısın, zaman para. Hallediyorum!";
			link.l1.go = "shark_hunt_1";
		break;
		
		case "shark_hunt_1":
			DialogExit();
			AddQuestRecord("SharkHunt", "1");
			pchar.questTemp.Saga.SharkHunt = "begin";
			pchar.GenQuest.LigaAttack = "true"; // киллеры Лиги активированы
		break;
		
		case "shark_hunt_2":
			dialog.text = "Hm... Zachary sana ne söyledi?";
			link.l1 = "Kaybolmadan önce, Shark onu ziyarete geldi ve Zachary'ye biraz erzak karşılığında bir brig almak için fırkateynini rehin bıraktı, sonra da kuzeybatıya, Küba'ya doğru yelken açtı.";
			link.l1.go = "shark_hunt_3";
		break;
		
		case "shark_hunt_3":
			dialog.text = "Bu gerçekten tuhaf. Devam et.";
			link.l1 = "Bir ay sonra Dodson geri dönmedi ve anlaşmanın şartlarına göre Papaz fırkateyni kendine aldı, sonra da iyi bir fiyata Paterson adında birine sattı. Bizim işlerimize gelince, Zachary, Shark'ın Küba'nın kuzeybatısında bir yerde olduğu söylenen efsanevi Adalet Adası'na gitmiş olabileceğinden bahsetti.";
			link.l1.go = "shark_hunt_4";
		break;
		
		case "shark_hunt_4":
			dialog.text = "Adalet Adası'nı duydum. Beyazlarla siyahların eşit olarak huzur içinde yaşadığı bir ada olduğu söylenir. Her çeşit hayalperestin yaydığı saçmalıklar bunlar. Ama kuzeybatıda bir kaçakçı üssü olma ihtimali var. Onların barkaları on yıl önce açık denizde sık sık görülürdü. Küba'ya yiyecek karşılığında her türlü mal getirirlerdi.";
			link.l1 = "Hazineden yiyecek mi olur? Papaz bana sığır ticareti yapan korsanlardan da bahsetti. Bu başlı başına bir çelişki gibi.";
			link.l1.go = "shark_hunt_5";
		break;
		
		case "shark_hunt_5":
			dialog.text = "These rumours must have a source; those smugglers' or buccaneers' barques were sailing to that region for some reason. I remember the Shark told me stories about his youth—he was some sort of slave at a strange structure made of shipwrecks in the middle of the sea.   Perhaps that is our place? No clue. Anyway, the Pastor has a point—something is out there, either a secret base or an island where the Shark could have gone. Listen, sail to Santo Domingo and find a scientist named Jose Dios.   He is a Spanish cartographer. I once saved him from some filthy scoundrels; I respect educated people. He will help you, just tell him my name. Go to Hispaniola, find Dios and speak to him.   He knows our region's geography perfectly, and if he cannot help you—no one will.";
			link.l1 = "Pekâlâ, Jan. Kulağa mantıklı geliyor. Hadi gidiyorum!";
			link.l1.go = "shark_hunt_6";
		break;
		
		case "shark_hunt_6":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "dios";
			AddQuestRecord("SharkHunt", "3");
		break;
		
		case "shark_hunt_7":
			dialog.text = "Ne yazık. Jose'nin bize yardım edeceğini ummuştum.";
			link.l1 = "Ben de buna güveniyordum, ama ne yazık ki olmadı. Neyse, kendimize acımakla vakit kaybetmeyelim. Bu meseleyi biraz daha düşüneceğim. Evet Jan, söyle bakalım, Hawk nasıl öldü?";
			link.l1.go = "baron_return";
		break;
		
		case "baron_return":
			dialog.text = "Onun ölümüne kimse tanık olmadı, tıpkı cesedini kimsenin görmemesi gibi. Sadece birkaç ay önce ortadan kayboldu. O zamandan beri, Shark'ta olduğu gibi, ne izi var ne haberi. Ama Steven'ın aksine, Nathan'ın saklanmak için bir nedeni yoktu. Bu yüzden herkes onun ormanda öldüğünü düşündü. Eğer bu olmasaydı, yerine Jackman'ı seçmeye razı olmazlardı.";
			link.l1 = "Şahin o ormanda ne halt ediyordu?";
			link.l1.go = "baron_return_1";
		break;
		
		case "baron_return_1":
			dialog.text = "Bu benim hatamdı, yaşlı bir aptalım! Onu yeni gelen haydutlarla ilgilenmeye ben ikna ettim. Kim oldukları ya da liderlerinin kim olduğu hakkında hiçbir fikrim yok. Normalde umursamazdım, ama dost Miskitoları kaçırmaya başladılar. Savaş şefi Kumvana, Savaş Yolu ilan etmekle tehdit etti ve yardımımı istedi. Müdahale etmekten başka çarem kalmadı.\nHawk, küçük bir birlikle Miskito Sahili'ne çıktı, ustaca hazırlanmış bir pusuya düştü ve yenildi. Sanki Hawk ve adamlarının oraya ineceği önceden biliniyordu. Hawk'ın cesedi ormanda bulunan diğerlerinin arasında yoktu.";
			link.l1 = "Burnunun dibinde neler dönüyor, haberin yok! Hawk'ın adamlarından hiçbiri haydutlarla uğraşmaya kalkmadı mı?";
			link.l1.go = "baron_return_2";
		break;
		
		case "baron_return_2":
			dialog.text = "Jackman herkesten önce davrandı. Kardeşler Meclisi'nde sorunu çözmeyi gönüllü olarak üstlendi ve kararı verdi. Miskitolar kaybolmayı bıraktı, ama haydutlar orada kalmaya devam etti, fazla göze batmadan.\nJackman, saldırganlarından hiçbirini rehin tutmadıklarını, bu yüzden Kardeşlerin onlara savaş ilan etmesi için bir sebep olmadığını söyledi. İlk saldıran Hawk'tı, bu yüzden yasalarımıza göre haydutların kendilerini savunmaya hakkı vardı. Herkes kabul etti. Herkes, bir kişi hariç...";
			link.l1 = "Herkes ama kim hariç?";
			link.l1.go = "baron_return_3";
		break;
		
		case "baron_return_3":
			dialog.text = "Nathan'ın bir karısı vardı. Adı Danielle Hawk'tu ve gerçekten güçlü bir kadındı! Kaptanını kaybetmenin acısını hiçbir zaman atlatamadığını sanıyorum, üstelik en başından beri bir şeylerden şüphelenmiş ve Hawk'ı vazgeçirmeye çalışmıştı. Bu konuda aralarında büyük bir tartışma çıktığını hatırlıyorum, ama bu onlar için alışılmadık bir şey değildi.";
			link.l1 = "Ve şimdi Danielle nerede?";
			link.l1.go = "baron_return_4";
		break;
		
		case "baron_return_4":
			dialog.text = "Kim bilir! Jackman onun Maroon Kasabası'ndan ayrıldığından emin oldu. Bana hiç uğramaz. Birbirimizi hiç sevmedik, yıllar geçtikçe daha da kinci oldu, şimdi ise muhtemelen beni başına gelenlerin sebebi sanıyor ve benden nefret ediyordur. Belki Hawk'ı kendi başına arıyordur, ama bir kadın ne yapabilir ki, pantolon giyip kılıç taşısa bile! Bu arada, kılıç kullanmada ustalaştı. Onunla karşılaşırsan yeteneklerini sınamayı hiç tavsiye etmem. Haydutlarla konuşmanın da anlamı yok. Orada oldukça etkileyici bir kamp kurmuşlar ve tepeden tırnağa silahlılar. Eski asker oldukları belli, işlerini iyi biliyorlar. Topraklarına kimseyi sokmuyorlar. Eskiden orada İspanyolların altın çıkardığı söyleniyor. Ama altın tükenince madeni terk etmişler. O heriflerin orada ne iş çevirdiği hakkında hiçbir fikrim yok.";
			link.l1 = "Şey, kimse Hawk'ın cesedini görmediğine göre, onu sağ bulma umudu hâlâ var. Tanrı bilir, belki onu tekrar baronluğa bile döndürebiliriz.";
			link.l1.go = "baron_return_5";
		break;
		
		case "baron_return_5":
			dialog.text = "Evet, ne dersin. Al, bu mektubu al. Steve Dodson'la karşılaştığında hemen ona ver. Bu mektubun içeriği güvenliğini garanti edecek. Yani, ne olur ne olmaz.";
			link.l1 = "Teşekkürler, Jan. Bunu mutlaka yapacağım!";
			link.l1.go = "baron_return_6";
		break;
		
		case "baron_return_6":
			DialogExit();
			GiveItem2Character(pchar, "letter_svenson");
			AddQuestRecord("BaronReturn", "1");
			pchar.questTemp.Saga.BaronReturn = "begin";
			pchar.quest.Saga_DannyMeeting.win_condition.l1 = "location";
			pchar.quest.Saga_DannyMeeting.win_condition.l1.location = "SantaCatalina_town";
			pchar.quest.Saga_DannyMeeting.function = "Saga_DannyMeeting";
		break;
		
		case "return_LSC":
			dialog.text = "Peki, neden böyle surat astın? Yoruldun mu? Belki bir kadeh rom iyi gelir?";
			link.l1 = "İtirazım yok...";
			link.l1.go = "return_LSC_1";
		break;
		
		case "return_LSC_1":
			LAi_AlcoholSetDrunk(pchar, 51, 5600);
			dialog.text = "Al bakalım, bir bardak. Şimdi konuş.";
			link.l1 = "(içki içerken) Ah, şimdi çok daha iyi... Jan, sen de Kara Papaz da haklıymışsınız. Adalet Adası gerçekten var. Oradaydım.";
			link.l1.go = "return_LSC_2";
		break;
		
		case "return_LSC_2":
			dialog.text = "Sana orada bir kaçakçılık üssü olması gerektiğini söylemiştim!";
			link.l1 = "Aslında orada hiçbir üs yok. Ve Karayipler'deki söylentiler doğruymuş. Siyahlar ve beyazlar gerçekten de orada birlikte yaşıyor, illa ki huzur içinde değil, daha çok kediyle köpek gibi. Ve adanın kendisi de sayısız gemi enkazından oluşuyor.";
			link.l1.go = "return_LSC_3";
		break;
		
		case "return_LSC_3":
			dialog.text = "İnanamıyorum! Eminim José Dios hikayeni duymaktan büyük ilgi duyacaktır. Bu arada, bir gün mutlaka onu ziyaret et.";
			link.l1 = "Daha sonra ona uğrarım. Şu an bunun için en uygun zaman değil. Şimdilik daha acil işlerim var. Nathaniel Hawk'u adada buldum.";
			link.l1.go = "return_LSC_4";
		break;
		
		case "return_LSC_4":
			dialog.text = "Nathan'ı buldun mu? Bu harika! Nasıl, iyi mi?";
			link.l1 = "Şey... Hasta, sürekli sarhoş ve derin bir depresyonda.";
			link.l1.go = "return_LSC_5";
		break;
		
		case "return_LSC_5":
			dialog.text = "Lanet olsun, bu moral bozucu. Nerede o? Geminde mi?";
			link.l1 = "Hayır, kendi gemisinde. Adada.";
			link.l1.go = "return_LSC_6";
		break;
		
		case "return_LSC_6":
			dialog.text = "Ne, onu buraya getirmedin mi? Neden?";
			link.l1 = "Çünkü onu durduracak hiçbir şey yoktu. Adaya bir gemim olmadan ulaştım.";
			link.l1.go = "return_LSC_7";
		break;
		
		case "return_LSC_7":
			dialog.text = "Kahretsin, "+pchar.name+", daha bir kadeh rom içmeden saçmalamaya başladın, sanki kendini içkiye vurmuşsun gibi. Ne oldu, Karayipleri yüzerek mi geçtin? Yoksa ayaklarına kaplumbağa mı bağladın?";
			link.l1 = "Hayır, yüzmedim. Jan, adaya Anakaradan ormanın içinden geldim, tıpkı Nathan gibi, sihirli bir Kızılderili idolü sayesinde. Bu hikayeyi o kadar çok kişiye anlattım ki, artık deli olmadığımı kanıtlamaktan yoruldum, bu yüzden tek söyleyeceğim şu: bana inan, olur mu!?";
			link.l1.go = "return_LSC_8";
		break;
		
		case "return_LSC_8":
			dialog.text = "Hindistan putu?";
			link.l1 = "Karayipler'de en az üç tane Kukulcan heykeli olarak bilinen put var: biri West Main'deki Miskito köyünün yakınında, biri Justice Adası'nın sığ sularının dibinde, bir diğeri ise Dominika'daki Karib köyünde. Bu putlar, yerli büyüsünün yardımıyla, insanları anında zaman ve mekân içinde taşıyabiliyor.";
			link.l1.go = "return_LSC_9";
		break;
		
		case "return_LSC_9":
			dialog.text = "";
			link.l1 = "Üç heykelin etrafında bir daire çizerek geçtim ve sonunda Miskito köyünde yolculuğuma başladığım yere tam olarak geri döndüm. Bana inanmıyorsan, Danielle'i çağırabilirim. Her şeyi kendi gözleriyle gördü!";
			link.l1.go = "return_LSC_10";
		break;
		
		case "return_LSC_10":
			dialog.text = "Danielle mi? Hawk'ın karısı mı? O seninle miydi?";
			link.l1 = "Kısmen, evet. Beni Blueweld'de kendi buldu ve Miskito köyüne, beni büyülü heykele gönderen bir şamana götürdü. Şimdi ise, tabii ki geçici olarak, subaylarımdan biri olarak görev yapıyor.";
			link.l1.go = "return_LSC_11";
		break;
		
		case "return_LSC_11":
			dialog.text = "Gerçekten de şaşkına döndüm, "+pchar.name+"! İngilizlerin dediği gibi. Ağzında gümüş kaşıkla doğmuşsun. Şanslı herifin tekisin! Peki, sana inanacağım, gerçi inanmak zor. Ama Nathan'ın meselesi değişmiyor, onun hâlâ yardıma ihtiyacı var.";
			link.l1 = "Bunu yapacağım. Justice Adası'na bir sefer hazırlıyorum. Şimdi ihtiyacım olan her şeye sahibim: adanın koordinatları ve seyir talimatları.";
			link.l1.go = "return_LSC_12";
		break;
		
		case "return_LSC_12":
			dialog.text = "Harika. Sana yardımcı olabileceğim bir şey var mı?";
			link.l1 = "Hayır, teşekkür ederim. Ama küçük bir detayı atladım. Nathan dışında, adada Shark Dodson'ı da buldum.";
			link.l1.go = "return_LSC_13";
		break;
		
		case "return_LSC_13":
			dialog.text = "Demek gerçekten oraya gitmiş! Peki, "+pchar.name+", harika bir iş çıkardın. Dodson orada nasıl, iyi mi? Onunla konuştun tabii, değil mi?";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie"))
			{
				link.l1 = "Onunla sadece konuşmakla kalmadım, aynı zamanda arkadaş da olduk. Adaya geri dönebilmem için gerekli deniz rotalarını bana o verdi. Steven, savaş gemisinin kamarasını Sharptown'daki konutla takas etmeyi kabul etti.";
				link.l1.go = "return_LSC_14";
			}
			else
			{
				link.l1 = "Konuştuk, evet, ama sonunda bunun hiçbir anlamı kalmadı. Ben adadayken, Steven onun lostromosu Chad Kapper tarafından düzenlenen bir komplo sonucu öldürüldü.";
				link.l1.go = "return_LSC_17";
			}
		break;
		
		case "return_LSC_14":
			dialog.text = "Hah! Köpekbalığı nasıl oldu da bir savaş gemisinin kaptanı olabildi?";
			link.l1 = "Gemi yarım asırdan fazladır bitmek bilmeyen bir 'sükûnet'te. Mürettebatıyla birlikte Ada'da mahsur kaldı. Bu yüzden Karayiplerde uzun zamandır ortalarda yok. Neyse, onu yakında buraya getireceğim, maceralarını sana kendisi anlatır.";
			link.l1.go = "return_LSC_15";
		break;
		
		case "return_LSC_15":
			dialog.text = "Bunu dört gözle bekliyorum! Şimdi işler yoluna girmeye başladı. Artık daha da güçlendik, "+pchar.name+" . Adaya ne zaman dönmeyi düşünüyorsun?";
			link.l1 = "Şu anda. Sadece bir dakikalığına buraya uğrayıp sana haber vermek istedim, Danielle ise sefer için hazırlık yapıyor. Nathan’ını görmek için can atıyor. Ve biliyor musun Jan, o aslında o kadar da kötü biri değil.";
			link.l1.go = "return_LSC_16";
		break;
		
		case "return_LSC_16":
			dialog.text = "Evet mi?  Belki de onun hakkında tamamen haklı değildim. Peki, "+pchar.name+", seni artık daha fazla tutmayacağım. Git, şansın yanında olsun! Dönüşünü dört gözle bekleyeceğim.";
			link.l1 = "Görüşürüz, Jan.";
			link.l1.go = "return_LSC_19";
		break;
		
		case "return_LSC_17":
			dialog.text = "Chad Kapper mı? Kahretsin, o adamı tanıyordum. Steven'ı mı öldürdü? O alçak...";
			link.l1 = "Kapper öldü. Ama Steven'ı geri getiremeyiz, bu yüzden siyasetimizi nasıl sürdüreceğimizi düşünmeliyiz.";
			link.l1.go = "return_LSC_18";
		break;
		
		case "return_LSC_18":
			dialog.text = "Hah! Ne yazık... Düşünecek ne var ki? Tyrex'i Kardeşliğin başına geçmeye ikna etmemiz gerekecek. Ayrıca, Blaze'den sonra, Tyrex, Yasa'nın koruyucusu olarak, en saygıdeğer ismimiz. Ama önce Hawk'ı geri getirmeliyiz ki en azından elimizde bir koz olsun. Adaya ne zaman yola çıkıyorsun?";
			link.l1 = "Şu anda. Sadece bir dakikalığına sana haber vermek için geldim, Danielle sefer için hazırlık yaparken. Nathan'ını görmek için can atıyor. Ve biliyor musun Jan, o aslında o kadar da kötü biri değil.";
			link.l1.go = "return_LSC_16";
		break;
		
		case "return_LSC_19":
			DialogExit();
			pchar.questTemp.Saga.BaronReturn = "return_LSC";
			// LSC ждёт своего героя!
			i = FindIsland("LostShipsCity");
			Islands[i].visible = true;
			Islands[i].reload_enable = true;
			pchar.quest.return_LSC.win_condition.l1 = "location";
			pchar.quest.return_LSC.win_condition.l1.location = "LostShipsCity";
			pchar.quest.return_LSC.function = "LSC_ReturnCheckShips"; // проверка типов кораблей
			pchar.quest.return_LSC_attack.win_condition.l1 = "location";
			pchar.quest.return_LSC_attack.win_condition.l1.location = "Beliz";
			pchar.quest.return_LSC_attack.function = "LSC_ReturnJackmanAttack"; // атака наймитов Джекмана
			pchar.quest.return_LSC_main.win_condition.l1 = "Ship_location";
			pchar.quest.return_LSC_main.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.return_LSC_main.function = "LSC_ReturnMain"; // основная функция возвращения
		break;
		
		case "nathaniel":
			dialog.text = "Nasıl? İyi değil demiştin.";
			link.l1 = "Evet, tam olarak doğru. Onu yanıma alıp Miskito köyüne, şaman Yılan Göz'e tedavi ettirmeye götüreceğim.";
			link.l1.go = "nathaniel_1";
		break;
		
		case "nathaniel_1":
			dialog.text = "O halde vakit kaybetmeye gerek yok! Acele et, "+pchar.name+"! Nathan'ı şamanına teslim eder etmez, hemen bana geri dön.";
			link.l1 = "Pekala, Jan. Kulağa mantıklı geliyor.";
			link.l1.go = "exit";
			npchar.quest.shamane = "true";
		break;
		
		case "nathaniel_2":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) // Акула жив
			{
				if (CheckAttribute(npchar, "quest.shark")) //и на месте
				{
					dialog.text = "Pekala. Steven zaten beni görmeye uğradı. Artık nihayet planlarımızı konuşmaya devam edebiliriz.";
					link.l1 = "Seni dinliyorum, Jan.";
					link.l1.go = "barbazon";
				}
				else
				{
					dialog.text = "Tabii ki bu güzel, ama Dodson neden hâlâ beni görmeye gelmedi? Ne oldu, onu adada mı bıraktınız?";
					link.l1 = "Hm... Nathan'ı Snake Eye'a götürmek için acele ediyordum...";
					link.l1.go = "nathaniel_wait";
				}
			}
			else
			{
				dialog.text = "Pekâlâ. Shark için içim yanıyor. Ama hayat böyle, bu yüzden yerine Tyrex geçecek. Şimdi nihayet planlarımızı konuşmaya devam edebiliriz.";
				link.l1 = "Seni dinliyorum, Jan.";
				link.l1.go = "barbazon";
			}
		break;
		
		case "nathaniel_wait":
			dialog.text = "... ve Köpekbalığı'nı almayı unuttun mu? İnanamıyorum."+pchar.name+"! Steven'ı hemen Blueweld'e götür! Duydun mu beni? Hadi, git!";
			link.l1 = "Sakin ol, Jan. Her şeyle ben ilgileneceğim.";
			link.l1.go = "exit";
			NextDiag.TempNode = "nathaniel_wait_1";
		break;
		
		case "nathaniel_wait_1":
			if (CheckAttribute(npchar, "quest.shark"))
			{
				dialog.text = "Steven uğradı, beni gördü. Artık nihayet planlarımızı konuşmaya devam edebiliriz.";
				link.l1 = "Dinliyorum seni, Jan.";
				link.l1.go = "barbazon";
			}
			else
			{
				dialog.text = "Oh, "+pchar.name+"... Son zamanlarda fazla rom içiyorsun gibi geliyor bana. Bak, bunun sonu hiç iyi olmaz. Önce ellerin titremeye başlar, sonra hafızanı kaybedersin, en sonunda da kara lekeyi yersin...";
				link.l1 = "Anladım, Jan. Hemen Steven'ı bulmaya gidiyorum!";
				link.l1.go = "exit";
				NextDiag.TempNode = "nathaniel_wait_1";
			}
		break;
		
		case "barbazon":
			dialog.text = "The Black Pastor has been very clear, he is only interested in that theological book. I've sent my men to search for it; perhaps someone will find it. Marcus Tyrex is not an issue, we'll have no problems persuading him. Jackman left Maroon Town soon after you paid him a visit. He sailed somewhere on the 'Centurion', the Hawks' frigate.\nThere is only Barbazon left - he is also known as Jacques the Kindman. We must find a way to make him cooperate with us. I am not sure how to accomplish that so far. But one thing is obvious - you should visit him.";
			link.l1 = "Bana Barbazon'u anlat."; // Addon 2016-1 Jason пиратская линейка патч 17/1
			link.l1.go = "barbazon_1";
		break;
		
		case "barbazon_1":
			dialog.text = "Gizli kapaklı biri. Fakir rolü yapıyor ama muhtemelen Karayipler’in en zengin adamı. Doğudaki tüm kaçakçılık işlerini o yönetiyor. Marcus ona karşı durmasa, Rüzgarlı Adalar’daki tüm kaçakçılık onun elinde olurdu. Tyrex onun için boğazında bir kemik gibi.\nKonseyde sürekli didişiyorlar, ama Barbazon açıkça savaş ilan edecek cesarete sahip değil. Belki gerçekten bir zamanlar Dunkirk korsanıydı, dediği gibi, ama şimdi bana daha çok bir tefeci gibi geliyor.";
			link.l1 = "Nasıl oldu da o adam baron seçildi, aklım almıyor?";
			link.l1.go = "barbazon_2";
		break;
		
		case "barbazon_2":
			dialog.text = "Gold, my friend, rules everything and everywhere; whoever has the gold makes the rules. Besides, Barbazon is really good at coming up with all kinds of profitable and illegal operations. He doesn't take part in them himself, but he always takes a share. So he is constantly surrounded by a lot of brave thugs, who are mostly weak in the head. They would all just die of hunger or end up on the scaffold without him.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
			{
				link.l1 = "Bana Marcus'u hatırlatıyor... Jan, mesele şu ki... Barbazon'a nasıl yaklaşacağımı hiç bilmiyorum. Senin bilmediğin bir sorun var.";
				link.l1.go = "barbazon_5";
			}
			else
			{
				link.l1 = "Barbazon'a nasıl gidebilirim?";
				link.l1.go = "barbazon_3";
			}
		break;
		
		case "barbazon_3":
			dialog.text = "Sadece iyi bir iş için tüyoya muhtaç o ahmaklardan biriymiş gibi davran. Sakın onun payını elinden almaya kalkışma. Merhametli Barbazon affetmez.";
			link.l1 = "Bunu söylemeye gerek yok. Onunla kendi çıkarım için iş birliği yapmıyorum. Neyse, artık onu ziyaret etmenin vakti geldi.";
			link.l1.go = "barbazon_4";
		break;
		
		case "barbazon_4":
			DialogExit();
			AddQuestRecord("BarbTemptation", "1");
			pchar.questTemp.Saga.BarbTemptation = "begin";
			pchar.questTemp.Saga.BaronReturn = "barbazon";
			NextDiag.CurrentNode = "First time";
			// тут вычищаем квестовый мусор от LSC
			if (CheckCharacterItem(pchar, "letter_chad")) RemoveItems(pchar, "letter_chad", 1);
			if (CheckCharacterItem(pchar, "letter_chad_1")) RemoveItems(pchar, "letter_chad_1", 1);
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "barbazon_5":
			dialog.text = "Gerçekten mi? Devam et.";
			link.l1 = "Charlie Prince'i duydun mu hiç?"; 
			link.l1.go = "barbazon_6";
		break;
		
		case "barbazon_6":
			dialog.text = "Evet, söylentileri duydum. Bu adam kısa süre önce Marcus Tyrex için çalışıyordu. Çok kısa sürede epey iş başardı, Cartagena'yı yağmalayarak adını duyurdu. Ee?";
			link.l1 = "Bu adam benim. Ben Charlie Prince'im. Öyleydim. Şimdi anladın mı?"; 
			link.l1.go = "barbazon_7";
		break;
		
		case "barbazon_7":
			dialog.text = "Lanet olsun! Sen Charlie Prince misin? Ne sürpriz! "+pchar.name+", etkilendim! Şimdi kavrayışının nereden geldiğini anlıyorum... Ama Barbazon'un bununla ne ilgisi var?";
			link.l1 = "Prens Barbazon'u ziyaret etse nasıl olur, Jan?.."; 
			link.l1.go = "barbazon_8";
		break;
		
		case "barbazon_8":
			dialog.text = "Hm... Anladım. Daha önce onunla karşılaştın mı?";
			link.l1 = "Tam olarak değil. Barbazon'un doğrudan emriyle adamlarından biri, Ignacio Marco adında bir herif, bana bulaşmaya kalktı. Bu, onların küçük savaşının bir parçasıydı."; 
			link.l1.go = "barbazon_9";
		break;
		
		case "barbazon_9":
			dialog.text = "Yüzünü gördü mü? Ona kendini tanıttın mı?";
			link.l1 = "Hayır."; 
			link.l1.go = "barbazon_10";
		break;
		
		case "barbazon_10":
			dialog.text = "Burada bir sorun görmüyorum o zaman. Korsan Charlie Prince'i de duymuştum ama bana söyleyene kadar sen olduğunu bilmiyordum.";
			link.l1 = "Barbazon'un beni hemen anlamayacağını mı sanıyorsun?"; 
			link.l1.go = "barbazon_11";
		break;
		
		case "barbazon_11":
			dialog.text = "Yüzünü hiç görmemiş biri bunu nasıl yapabilir ki? Tek yaptığı, Marcus'un çalışanlarından birinden kurtulmaları için emir vermekti.";
			link.l1 = "Hm... Bu konuda haklı olabilirsin."; 
			link.l1.go = "barbazon_12";
		break;
		
		case "barbazon_12":
			dialog.text = "No way we are getting through this without Barbazon. Go see him, but be careful. Run if he recognises you; we will think of another way to approach him in that case.";
			link.l1 = "Pekâlâ. Artık gitmeliyim. O herifle tanışmayı dört gözle bekliyordum."; 
			link.l1.go = "barbazon_13";
		break;
		
		case "barbazon_13":
			dialog.text = "Aptal numarası yapma ve Jacques’la uğraşmaya kalkışma. O asla affetmez. Kolay para kazanmak isteyen bir enayi gibi davran.";
			link.l1 = "En sevdiğim rol buymuş demek ki... Elveda, Jan!"; 
			link.l1.go = "barbazon_4";
		break;
		
		case "saga_26":
			dialog.text = "Evet. Hintli şaman elinden geleni yaptı, Hawk eskisi gibi sapasağlam. Şimdi Dannie ile birlikte Maroon Town'da olması gerekiyor, istersen gidip selam verebilirsin. Sizi gördüklerine çok sevineceklerdir.";
			link.l1 = "Kesinlikle uğrayıp nasıl olduklarına bakacağım... Jan, Sharp'ın haritasının ikinci parçasını bulmayı başardım! Jackman'ın kamarasında çıktı. Artık Helen'in Isla Tesoro üzerindeki haklarını kanıtlamakta hiçbir sıkıntımız olmayacak.";
			link.l1.go = "saga_27";
		break;
		
		case "saga_27":
			dialog.text = "Harika, göster bana onu.\nHaklıymışız, Blaze'i öldüren Jacob'mış. Artık Shark'ın adındaki leke tamamen silinmeli. Kanıt meselesine gelince, bu daha hassas bir konu. Ve ancak çok iyi düşünülüp taşındıktan sonra ele alınmalı.";
			link.l1 = "Bir de şu var, Jan. Şu notu bir incele. O da Jackman'ın eşyaları arasındaydı.";
			link.l1.go = "saga_28";
		break;
		
		case "saga_28":
			RemoveItems(pchar, "letter_parol", 1); // удалить записку
			dialog.text = "Pekala, bir bakalım... Ha, demek bu yüzden haydutlar Jackman'ı dinleyip Miskitoları kaçırmayı bıraktı! Başka türlü olamazdı zaten! O alçak her şeyi önceden planlamış, birkaç adım öndeymiş.";
			link.l1 = "Evet, Hawk'ın adamlarının neden katledildiğini de anlıyorum. Ama iki şeyi anlamıyorum: birincisi, Jackman'ın suç ortakları madende ne yapıyor, ikincisi ise, bütün bu karmaşanın senin topraklarında yaşanmasına neden bu kadar sakin tepki veriyorsun?";
			link.l1.go = "saga_29";
		break;
		
		case "saga_29":
			dialog.text = "Utanıyorum... Haklısın. Jackman gerçekten kontrolden çıktı. Adamlarının da benim bölgemde işi yok. Görünen o ki, Karayipler'e kiminle uğraştıklarını hatırlatmanın zamanı geldi.";
			link.l1 = "Aklında ne var, Jan?";
			link.l1.go = "saga_30";
		break;
		
		case "saga_30":
			dialog.text = "Geçmişi yeniden canlandırmak... Cezalandırıcı bir sefer düzenleyip madenlerdeki tüm haydutları ortadan kaldırmayı düşünüyorum. Artık onların Jackman'ın adamları olduğuna dair elimizde kanıt var ve topraklarımı bu pisliklerden temizlemek zorundayım.\n"+pchar.name+", harika bir iş çıkardın. Artık benim gitme zamanım geldi. Sen biraz dinlen. Şahinleri ziyaret et. On gün sonra geri gel!";
			link.l1 = "Pekala, Jan.  Yapacağım. Tam söylediğin zamanda döneceğim!";
			link.l1.go = "saga_31";
			link.l2 = "Ha! Ben de bu mücadelede yer almak istiyorum. Neden beni dinlenmeye ayırdın?";
			link.l2.go = "saga_31_1";
		break;
		
		case "saga_31_1":
			dialog.text = "Beni affet, dostum. Sadece artık biraz da benim çalışmamın ve senin dinlenmenin zamanı geldi diye düşündüm. Ama eğer sen böyle istiyorsan, memnuniyetle kabul ederim! Haydi fırtınaya birlikte göğüs gerelim! Madende bulduğumuz her şeyi de, Kardeşlik yasalarında yazdığı gibi, tayfalarımız arasında eşitçe paylaşırız.";
			link.l1 = "Anlaştık, Jan! Ne zaman yelken açıyoruz?";
			link.l1.go = "saga_31_2";
		break;
		
		case "saga_31_2":
			dialog.text = "Üç gün içinde adamlarınla birlikte Miskito Sahili'ne gel. O zamana kadar kendi grubumu toplamış olacağım ve seni orada bekliyor olacağım. Sakın geç kalma!";
			link.l1 = "Pekala, Orman Şeytanı. Seninle sırt sırta savaşa girmek için sabırsızlanıyorum! Yakında görüşürüz!";
			link.l1.go = "saga_31";
			npchar.quest.mine_tw = "true";
		break;
		
		case "saga_31": 
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto1");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			if (CheckAttribute(npchar, "quest.mine_tw"))
			{
				pchar.quest.Saga_MinePrepareAttack.win_condition.l1 = "location";
				pchar.quest.Saga_MinePrepareAttack.win_condition.l1.location = "Shore53";
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2 = "Timer";
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.hour  = sti(GetTime());
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.day   = GetAddingDataDay(0, 0, 3);
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.month = GetAddingDataMonth(0, 0, 3);
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.year  = GetAddingDataYear(0, 0, 3);
				pchar.quest.Saga_MinePrepareAttack.function = "Saga_MineBanditsPrepareAttack";
				SetFunctionTimerCondition("Saga_MineBanditsAttackOver", 0, 0, 4, false); // таймер
			}
			else SetFunctionTimerCondition("Saga_MineBanditsDestroyed", 0, 0, 10, false); // таймер
			sld = characterFromId("Nathaniel");
			sld.model = "Hawk_2";
			Characters_RefreshModel(sld); // наверно не нужно
			sld.greeting = "nathaniel_2";
			sld.dialog.currentnode = "marun_town";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "sit", "sit1");
			LAi_SetHuberType(sld);
			LocatorReloadEnterDisable("FortOrange_town", "reload6", false); // открыть резиденцию Хоука
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "marun_town";
			sld.greeting = "danny_2";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "goto", "goto1");
			LAi_SetStayType(sld);
		break;
		
		case "saga_32a":
			dialog.text = "Mükemmel. Madenin gizemli sahibi Lawrence Beltrope hakkında bir şeyler öğrendim.";
			link.l1 = "Peki, bu kuş da kim?";
			link.l1.go = "saga_35";
		break;
		
		case "saga_32":
			dialog.text = "Jackman'ın adamlarından madende zorla öğrendim. Kolay lokma değillerdi ama benim adamlarım da yabana atılmaz. Üstelik, senin bulduğun nottaki parolayı söyleyince gardlarını indirmelerini sağladık. Madene daldık ve onlara unutulmaz bir veda yaşattık.";
			link.l1 = "Madenini aldın mı? Harika!";
			link.l1.go = "saga_33";
		break;
		
		case "saga_33":
			dialog.text = "Bu, Orman Şeytanı'nın paslandığını düşünen herkese ders olsun. Son yıllarda gerçekten fazlasıyla tembellik ettim, bak ne oldu? Jackman, kötü planını burnumun dibinde uygulamaya koymuş!";
			link.l1 = "O madende ne gördün? Anlat bana!";
			link.l1.go = "saga_34";
		break;
		
		case "saga_34":
			dialog.text = "İspanyollar madeni gerçekten terk etmişti, fakat Port Royal'den Lawrence Beltrope onu yok pahasına satın alıp gizlice işletmeye devam etmiş. Görünüşe bakılırsa, İspanyollar galeriyi fazla erken bırakmış; çünkü biz altın bulamasak da, çok yakın zamana kadar orada altın olduğunu söyleyen birkaç köleyle karşılaştık.";
			link.l1 = "Lawrence Beltrope? Hiç duymadım. Kim o?";
			link.l1.go = "saga_35";
		break;
		
		case "saga_35":
			dialog.text = "O, buranın yerlisi, Thomas Beltrope'un oğlu; Thomas bir zamanlar Nicholas Sharp'ın yeminli kardeşi ve Providence Adası Şirketi'nin korsan kaptanıydı. Thomas'ı ben de çok iyi tanırdım. Bir yıl önce Lawrence tekrar Karayiplere geldi. Görünen o ki Jackman onun için çalışıyormuş. Bunu aklında tut ve gözünü dört aç!";
			link.l1 = "Demek Jackman'ın o mektupta bahsettiği gizemli 'patronu' Lawrence Beltrope'muş... Peki, bu ismi aklımda tutacağım.";
			link.l1.go = "saga_36";
		break;
		
		case "saga_36":
			dialog.text = "Bir şey daha var. Aklıma tuhaf bir şey geliyor. Blaze bir keresinde terk edilmiş bir İspanyol altın madeninden bahsetmişti ve oradaki altını Sharptown'a yatıracağını söylemişti. Ama madene ait harita, kız kardeşi Kaptan Butcher'la kaçtıktan sonra kayboldu. Belki de bizim madenden söz ediyordu?\nNeyse, bu çok eskide kaldı ve artık pek bir şeyi değiştirmez... Seninle benim Konsey'le ilgilenmemiz gerek. Beş parçanın hepsi sende mi?";
			link.l1 = "Evet. Şu dördü: Nathaniel, Tyrex, Marlow ve Barbazon. Hepsi de onaylarını verdiler.";
			link.l1.go = "saga_37";
		break;
		
		case "saga_37":
			RemoveItems(pchar, "splinter_nh", 1);
			RemoveItems(pchar, "splinter_mt", 1);
			RemoveItems(pchar, "splinter_jb", 1);
			RemoveItems(pchar, "splinter_zm", 1);
			sTemp = "Shark";
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Tyrex";
			dialog.text = "Harika. Eminim seçimde hiçbir sorun çıkmayacak "+sTemp+" Kıyı Kardeşliği'nin başı olarak. Hemen bir Konsey toplantısı ayarlamaya başlayacağım.";
			link.l1 = "Yani Jan, şimdilik tüm sorunların kontrol altında olduğunu söyleyebilir miyiz? Nathaniel Maroon Town’da, Jackman öldü, ve Kardeşliğin artık yeni bir lideri var... Belki de başladığımız yere, yani Tortuga’yı almaya geri dönmenin zamanı gelmiştir?";
			link.l1.go = "saga_38";
		break;
		
		case "saga_38":
			dialog.text = "Hatırlıyorum, "+pchar.name+", ama biraz daha beklememiz gerekiyor. Üstelik, Sharp'ın mirasını çözmek için zaman daralıyor ve biliyorsun, bu mesele gerçekten acilen halledilmeli.";
			link.l1 = "Mirasla ilgili sorun ne? Haritanın iki parçası da bende. Aslında yapmamız gereken tek şey onları sunmak, hepsi bu...";
			link.l1.go = "saga_39";
		break;
		
		case "saga_39":
			dialog.text = ""+pchar.name+", Emin ol ki, bu devirde kimseye öyle kolay kolay ada vermiyorlar. Vasiyetin her maddesi yerine getirilmiş olsa bile, yasal mirasçılara bile. İngiliz yetkililerin bu adayı ne kadar istediğini çok iyi biliyorum.\nAlbay Doyle'un, adayı çoktan İngiliz toprağı saydığı halde bizim elimizden alıp götürmemizi öylece izleyeceğini sanmıyorum. Ayrıca, seninle benim gölgede kalmamızda fayda var.";
			link.l1 = "Ve sen ne öneriyorsun?";
			link.l1.go = "saga_40";
		break;
		
		case "saga_40":
			dialog.text = "Port Royal'a git ve orada Albert Loxley adında bir adamı bul. Tüm Karayipler'deki en iyi avukattır. Her türlü karanlık işte ustalaşmıştır, ona yüklü bir ücret teklif edilirse her işi kabul eder. İştahı da pek büyüktür ama kesinlikle değer.";
			link.l1 = "Sence Sharp'ın vasiyetinde bazı tuzaklar olabilir mi?";
			link.l1.go = "saga_41";
		break;
		
		case "saga_41":
			dialog.text = "Bunu sadece düşündüğüm için söylemiyorum, bundan eminim. Hiç resmi makamlarla iş yapmak zorunda kaldın mı? Bil ki senden bir şey istediklerinde, ruhunu çekerler, yanlış yere konmuş bir virgülü bile burnuna dayarlar, her şeyi kendi işlerine geldiği gibi yorumlarlar ve seni kör bir kedi yavrusu gibi ortada bırakırlar.  İşte bu yüzden avukatlar var. Memurlarla onların silahlarıyla savaşırlar: laf kalabalığı, dökülen mürekkep ve kurnazlık. Bu yüzden Loxley'i ziyaret edip onu tutmalısın, bizim çıkarlarımızı korusun, ben de seçimlerle ilgileneyim.";
			link.l1 = "Pekala. Port Royal'a gidiyorum. Konseyin toplanıp seçim yapması ne kadar sürecek?";
			link.l1.go = "saga_42";
		break;
		
		case "saga_42":
			dialog.text = "On gün. Yani beni Blueweld'de daha erken aramaya kalkma.";
			link.l1 = "Anladım. O zaman Jan, birazdan görüşürüz!";
			link.l1.go = "saga_43";
		break;
		
		case "saga_43":
			DialogExit();
			AddQuestRecord("Testament", "1");
			pchar.questTemp.Saga = "loxly"; // обновляем флаг
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", true); // закрыть кабинет Свенсона
			SetFunctionTimerCondition("Saga_GoldForLoxly", 0, 0, 10, false); // таймер
		break;
		
		case "saga_44":
			sTemp = "Steven Dodson";
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus Tyrex";
			dialog.text = ""+sTemp+" en içten selamlarını gönderiyor. Isla Tesoro’daki konutunda sizi her zaman görmekten memnuniyet duyacaktır. Fırsatınız olursa mutlaka uğrayın.";
			link.l1 = "Emin olmak için "+sTemp+" yeni evinden ayrılmayacak, seninle benim, Jan, önümüzde biraz işimiz var.";
			link.l1.go = "saga_45";
		break;
		
		case "saga_45":
			sTemp = "four hundred and fifty";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) sTemp = "one thousand";
			dialog.text = "Loxley'yi zaten ziyaret ettiğini varsayıyorum...";
			link.l1 = "Evet, konuya el attı. Ama hizmetleri için yığınla altın istedi. "+sTemp+" önceden doblon. Peşin! Ayrıca Helen'in hak iddiası ne kadar iyi giderse, ona daha da fazla ödememiz gerekecek. Dediğine göre, tutar ikiye ya da üçe katlanacak.";
			link.l1.go = "saga_46";
		break;
		
		case "saga_46":
			dialog.text = "Ha! Doğrusu, ondan daha azını beklemezdim zaten. O yaşlı tilki, avı kilometrelerce öteden koklar, tıpkı bir sırtlan gibi. Tabii, burada koca bir adadan bahsediyoruz. Albert’in birkaç yüz altın istememesi saçma olurdu. Yani, toplamda bin beş yüz altın civarı bir şey çıkabilir...";
			link.l1 = "Jan, bu bir servet!";
			link.l1.go = "saga_47";
		break;
		
		case "saga_47":
			dialog.text = "Ne demek istediğini anlıyorum. Senin kendi cebinden bütün bu parayı ödeyen bir enayi olmadığını kabul ediyorum. Ama ne yazık ki, şu anda elimde o kadar altın yok. Böyle masrafları düşünmüştüm aslında, fakat bir alçağın müdahalesi her şeyi mahvetti.";
			link.l1 = "Ne diyorsun?";
			link.l1.go = "saga_48";
		break;
		
		case "saga_48":
			dialog.text = "Dinle. Belki de zaten biliyorsundur, yerleşimimiz yarı yasal bir durumda. İngilizler burada bir garnizon bulunduruyor ve biz de onlara iyi bir fiyata maun sağlıyoruz. Ama çok ağır ve dayanıklı bir ağaç türü var - Lignum Vitae, senin de bildiğin adıyla demir ağacı.\nNadir bulunur ve sertleştirilmiş çelikle bile işlenmesi zordur. Derler ki, çok eskiden Maya-Itza halkı korkunç sopalarını bundan yaparmış. Demir ağacını açık pazarda bulamazsın, kaçak olarak ise neredeyse gümüş ağırlığınca satılır.\nDoyle'un adamları ara sıra gelir, işlediğimiz tüm demir ağacını ucuza alıp götürür. Ama ben her zaman kendi ihtiyaçlarım için birazını ayırmayı başarırım.";
			link.l1 = "Bu ağacı duymuştum. Söylenene göre, tüfek mermileri yağlı gövdesine katran gibi gömülüyormuş! Sağlamlığı sayesinde çelik mekanizmalar için dişliler bile yapılabiliyor.";
			link.l1.go = "saga_49";
		break;
		
		case "saga_49":
			dialog.text = "Dişli konusunda biraz abartıyorlar, ama geri kalanı tamamen doğru. Masrafları önceden tahmin ederek bolca demir ağacı hazırlamıştım, ama birkaç gün önce bir alçak depomu boşaltmış. İçimizden biri olduğuna eminim. Bir şüphem var, ama kesin konuşamam.";
			link.l1 = "Fareleri ezmek gerek! Kimi şüpheleniyorsun?";
			link.l1.go = "saga_50";
		break;
		
		case "saga_50":
			dialog.text = "Paul Molligan. His East Indian 'Oyster' sailed to Barbados yesterday. I didn't have the chance to check her holds. But he wouldn't bring the ironwood to Bridgetown anyway; Lord Willoughby has serious customs officers there, and ironwood is a raw material of strategic importance for the English navy.\nIf he really has my ironwood, then he will sell it before arriving at Bridgetown. If only you could intercept Molligan and inspect his holds!..";
			link.l1 = "Dün Bridgetown'a gittiğini mi söylediniz? Henüz her şey bitmiş değil. Onu yakalamaya çalışacağım.";
			link.l1.go = "saga_51";
		break;
		
		case "saga_51":
			dialog.text = " Molligan'ın hain olduğunu anlarsan ne yapacağını biliyorsun. Ama önce müşterisinin adını öğrenmeye çalış. Sonra ya yükü doğrudan müşteriye teslim edersin, ya da bana geri getirirsin.\n'Oyster'ı da Blueweld'e getir, o harika bir gemi, onu kendim için alıp ihtiyaçlarıma göre donatmak isterim. Sen de istediğin ganimeti alabilirsin... Ve eğer Molligan suçlu değilse... yok, eminim demir ağacımı çalan hain odur.";
			link.l1 = "Zamanımı iyi değerlendireceğim!";
			link.l1.go = "saga_52";
		break;
		
		case "saga_52":
			dialog.text = "Eğer demir ağacı kendin satarsan, Loxley için bin beş yüz altın doblon ayır ve kalanını eşit paylaşırız. Buna güvenebilirim, değil mi?";
			link.l1 = "Elbette. Ben bir hain değilim.";
			link.l1.go = "saga_53";
		break;
		
		case "saga_53":
			dialog.text = "Hiç şüphem yok. Bol şans, "+pchar.name+"! Umarım bu sefer şans senden yana olur.";
			link.l1 = "Teşekkür ederim. Görüşürüz!";
			link.l1.go = "saga_54";
		break;
		
		case "saga_54":
			DialogExit();
			pchar.questTemp.Saga = "molligan"; // обновляем флаг
			AddQuestRecord("Testament", "3");
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			Saga_CreateMolliganInWorld(); // ставим корабль Моллигана на карту
		break;
		
		case "saga_55":
			npchar.quest.bakaut = GetSquadronGoods(pchar, GOOD_SANDAL);
			dialog.text = "Biliyordum. Ambarında ne kadar vardı?";
			link.l1 = "Bulduğum şey "+FindRussianQtyString(sti(npchar.quest.bakaut))+" 'Oyster'da. ";
			link.l1.go = "saga_56";
		break;
		
		case "saga_56":
			iTemp = sti(npchar.quest.bakaut);
			if (iTemp > 100)
			{
				dialog.text = "Vay canına! Depomda hiç bu kadarını görmemiştim. Kimler servetini kendi elleriyle bulmuş bak hele. Teşekkür ederim, "+pchar.name+", beni asla hayal kırıklığına uğratmıyorsun. Malları hemen satacağım, alıcımız hazır. Paranı yarın vereceğim.";
				link.l1 = "Pekala. O zaman seni daha fazla oyalamayayım. Yarın görüşürüz.";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 90 && iTemp < 101)
			{
				dialog.text = "Evet, artık yeterince sabrettim. Küçük fare! Teşekkür ederim, "+pchar.name+", beni hiç hayal kırıklığına uğratmıyorsun. Malları hemen satacağım, alıcımız hazır. Paranı yarın sana vereceğim.";
				link.l1 = "Pekala. O halde seni daha fazla oyalamayayım. Yarın görüşürüz.";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 70 && iTemp < 90)
			{
				dialog.text = "Muhtemelen yükün bir kısmını çoktan birine satmayı başarmıştır, çünkü daha fazla olmalıydı. Ama sorun değil, çoğunu geri aldık. Teşekkür ederim, "+pchar.name+", malları hemen satacağım, alıcımız hazır. Paranı yarın vereceğim.";
				link.l1 = "Pekala. O zaman seni daha fazla oyalamayayım. Yarın görüşürüz.";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 50 && iTemp < 70)
			{
				dialog.text = "Kahretsin, o alçak yükün iyi bir kısmını çoktan satmayı başarmış... Ah, ne yazık. Neyse. Elimde ne varsa satarım, zaten bir alıcım var. Parayı yarın alırım.";
				link.l1 = "Pekâlâ. O halde seni daha fazla oyalamayayım. Yarın görüşürüz.";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 20 && iTemp < 50)
			{
				dialog.text = "Kahretsin, bu gerçekten rezalet! O herif yükün yarısından fazlasını çoktan satmış bile... Ah, ne yazık. Neyse. Elimde kalanları satarım, alıcıyı da buldum zaten. Yarın param hazır olur.";
				link.l1 = "Pekala. O halde seni daha fazla oyalamayayım. Yarın görüşürüz.";
				link.l1.go = "saga_oust";
				break;
			}
			dialog.text = "Adamım, şansım hiç yaver gitmiyor. Neredeyse her şeyi satmış... Al, şu demir ağacını kendine sakla, "+pchar.name+", istediğini yap. Artık para kazanmak için tek umudum sensin.";
			link.l1 = "Anladım. Peki, kendim bakarım. Bu benim ilk seferim değil... Hoşça kal, Jan.";
			link.l1.go = "saga_oust";
		break;
		
		case "saga_oust":
			if (CheckAttribute(npchar, "quest.bakaut"))
			{
				if (sti(npchar.quest.bakaut) < 20) DeleteAttribute(npchar, "quest.bakaut");
				else 
				{
					SaveCurrentNpcQuestDateParam(npchar, "bakaut_date");
					RemoveCharacterGoods(pchar, GOOD_SANDAL, sti(npchar.quest.bakaut));
				}
				pchar.questTemp.Saga = "removebakaut";
			}
			int iUst = 0;
			for(i = 0; i < COMPANION_MAX; i++)
			{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
					sld = GetCharacter(iTemp);
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_EASTINDIAMAN && sld.ship.name == "Oyster") iUst = 1;
				}
			} // есть ли у нас Устрица
			dialog.text = "Bekle! 'Oyster'ı ele mi geçirdin?";
			if (iUst == 1)
			{
				link.l1 = "Evet. Şu anda limanda. Onu senin için demirledim, tam istediğin gibi.";
				link.l1.go = "saga_oust_yes";
			}
			else
			{	
				link.l1 = "Hayır. Gemi savaş sırasında o kadar ağır hasar aldı ki, batırmak zorunda kaldım.";
				link.l1.go = "saga_oust_no";
			}
		break;
		
		case "saga_oust_no":
			dialog.text = "Ne yazık. Ama olan oldu. Sonra görüşürüz, "+pchar.name+"!";
			link.l1 = "Hoşça kal, Jan.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "saga_oust_yes":
			dialog.text = "Harika! Bu güzelliği hak ettiği gibi donatacağım. Sonra da, anlaştığımız gibi, arada onu ödünç alabilirsin. Sanırım yaklaşık iki aya hazır olur.";
			link.l1 = "Pekala. Böyle bir gemi bazen gerçekten çok işe yarayabilir... Sonra görüşürüz, Jan!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Saga_RemoveOuster");
			npchar.quest.ouster = "true";
			SaveCurrentNpcQuestDateParam(npchar, "ouster_date"); // через 2 месяца
			NextDiag.TempNode = "First time";
		break;
		
		case "saga_57":
			int idlt;
			iTemp = sti(npchar.quest.bakaut)*30; // Ян за 1 шт бакаута даёт 30 дублонов
			if (iTemp > 1600)
			{
				idlt = makeint(iTemp-1500)/2; // доля Бонса :)
				dialog.text = "Aldım "+iTemp+" bunun için para. Bin beş yüzü avukata, üstüne bir de altınlardan sana düşen pay - "+idlt+". Buyurun.";
				link.l1 = "Takdire şayan! Artık Loxley'e kolayca yelken açabilirim.";
				link.l1.go = "saga_58";
				TakeNItems(pchar, "gold_dublon", 1500+idlt);
				break;
			}
			if (iTemp > 1450 && iTemp <= 1600)
			{
				dialog.text = "Bunun için bin beş yüz dublon aldım. Avukat için ancak yeter. Al bakalım.";
				link.l1 = "Harika. Artık Loxley'e gidebilirim.";
				link.l1.go = "saga_58";
				TakeNItems(pchar, "gold_dublon", 1500);
				break;
			}
			dialog.text = "Aldım "+iTemp+" dublon karşılığında. Al bakalım. Geri kalanını kendin kazman gerekecek.";
			link.l1 = "Pekala, kendi başıma olacaksa, kendi başıma olsun. Tamam, Loxley'i görmeye gidiyorum.";
			link.l1.go = "saga_58";
			TakeNItems(pchar, "gold_dublon", iTemp);
		break;
		
		case "saga_58":
			DialogExit();
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "quest.bakaut");
		break;
		
		case "saga_59":
			dialog.text = "Ne dersin? İlginçmiş. Peki, Hollandalı bu iş için ne kadar ödemeye razı?";
			link.l1 = "Kişi başı kırk dublon.";
			link.l1.go = "saga_60";
		break;
		
		case "saga_60":
			dialog.text = "Vay canına! Benim alıcılarım daha az ödüyor...";
			link.l1 = "Genel olarak, Loxley için iki bin altınım var ve "+sti(npchar.quest.bakaut_sum)*2+" üstüne doubloon da cabası.";
			link.l1.go = "saga_61";
		break;
		
		case "saga_61":
			dialog.text = "Pekala. O zaman ortadan ikiye böleceğiz.";
			if (PCharDublonsTotal() > 0)
			{
				npchar.quest.bakaut_pay = func_min(sti(npchar.quest.bakaut_sum), PCharDublonsTotal()); // дублоны в кармане
				link.l1 = "Buyur. Aldım işte "+FindRussianQtyString(sti(npchar.quest.bakaut_pay))+".";
				link.l1.go = "bakaut_pay";
			}
			else
			{
				link.l1 = "Altınları gemide bıraktım. Hemen gidip alıp döneceğim.";
				link.l1.go = "exit";
				NextDiag.TempNode = "bakaut_pay_wait";
			}
		break;
		
		case "saga_61_1":
			dialog.text = "Harika. Ne kadar getirdin?";
			if (PCharDublonsTotal() > 0)
			{
				npchar.quest.bakaut_pay = func_min(sti(npchar.quest.bakaut_sum), PCharDublonsTotal()); // дублоны в кармане
				link.l1 = "Al bakalım. Bende var "+FindRussianQtyString(sti(npchar.quest.bakaut_pay))+".";
				link.l1.go = "bakaut_pay";
			}
			else
			{
				link.l1 = "Şu hafızam ne halde! Artık bu romla oyalanmayı bırakmam lazım. Yine altınları sandığımda unuttum. Hemen gidip alıp getireceğim.";
				link.l1.go = "exit";
				NextDiag.TempNode = "bakaut_pay_wait";
			}
		break;
		
		case "bakaut_pay": // оплата
			if (sti(npchar.quest.bakaut_sum) < sti(npchar.quest.bakaut_pay)) // полная сумма
			{
				npchar.quest.bakaut_pay = sti(npchar.quest.bakaut_sum);
				iTemp = 0;
			}
			else iTemp = sti(npchar.quest.bakaut_sum)-sti(npchar.quest.bakaut_pay);
			npchar.quest.bakaut_sum = iTemp; // запоминаем остаток
			RemoveDublonsFromPCharTotal(sti(npchar.quest.bakaut_pay));
			Log_Info("You have given "+sti(npchar.quest.bakaut_pay)+" doubloons");
			PlaySound("interface\important_item.wav");
			if (iTemp == 0)
			{
				dialog.text = "İyi iş çıkardın, "+pchar.name+"! Bir kez daha seninle birlikte olmanın ne kadar iyi bir şey olduğunu hatırladım.";
				link.l1 = "Deniyorum, Jan...";
				link.l1.go = "bakaut_done";
			}
			else
			{
				dialog.text = "Harika. Geri kalanını da getirecek misin "+FindRussianQtyString(sti(npchar.quest.bakaut_sum))+" doubloon sonra?";
				link.l1 = "Evet. Bu kadar büyük bir altın yığınını tek seferde taşıyamazdım.";
				link.l1.go = "exit";
				NextDiag.TempNode = "bakaut_pay_wait";
			}
		break;
		
		case "bakaut_pay_wait":
			dialog.text = "Yani, "+pchar.name+", dublonlarım nasıl gidiyor?";
			link.l1 = "Sana biraz daha altın vermeye hazırım.";
			link.l1.go = "saga_61_1";
		break;
		
		case "bakaut_done": // рассчитались
			dialog.text = "Sana bir teklifim var. Madem kârlı bir alıcı bulabildin, sana biraz demir ağacı satabilirim. Eskiden tanesine otuz dublon alıyordum. İstersen, o fiyata sana satabilirim. Başkasına satmaktansa sana satmayı tercih ederim.";
			link.l1 = "Ne kadar demir ağacı satabilirsin?";
			link.l1.go = "bakaut_done_1";
		break;
		
		case "bakaut_done_1":
			dialog.text = "Büyük partiler biriktirmekten kaçınırım. Molligan'ınki istisnaydı. Yetkililer, burada bir kara pazar olduğunu duymaktan hoşlanmayacak. Şöyle yapalım: Her ayın 14'ünde ve 24'ünde senin için 25 parça demir ağacı ayıracağım.\nEğer almak istersen, yedi yüz elli dublon getir ve hepsini al. O gün gelmezsen, malı başka bir müşteriye satarım. Böylece ayda 50 parça almış olursun. Anlaştık mı?";
			link.l1 = "Anlaştık Jan! Hadi yapalım. Şimdi gitme vakti benim için...";
			link.l1.go = "saga_oust";
			DeleteAttribute(npchar, "quest.bakaut_sum");
			npchar.quest.trade_bakaut = "true"; // генератор купли-продажи бакаута
			AddQuestRecordInfo("Unique_Goods", "1");
		break;
		
		case "saga_59_1": // укрысил у Яна - нет генератора на бакаут, потерял больше
			dialog.text = "Ah, demek ya o değildi ya da demir ağacını daha önce satmış... Ne yazık. Neyse, şimdi avukat için parayı bulmak konusunda tek umudum sensin.";
			link.l1 = "Bu sorumluluğu üstlenmeye hazırım. Bu benim ilk seferim değil.";
			link.l1.go = "exit";
			// Ян расстроен и забыл про Устрицу - так что и Устрицы тоже не будет
			DeleteAttribute(npchar, "quest.bakaut_sum");
		break;
		
		case "saga_62":
			dialog.text = "Öyle mi? Bu ilginç. Devam et, sor. Kimin hakkında konuşmak istiyorsun?";
			link.l1 = "Bir kız hakkında. Adı... Jessica Rose'du.";
			link.l1.go = "saga_63";
		break;
		
		case "saga_63":
			dialog.text = "Hm. Kardeşliğimizin yeni lideri sana ondan bahsetti mi?";
			link.l1 = "O da öyle yaptı. Ama ben onun hakkında St. John's'un eski celladı Baker'dan öğrendim. Kaptan Butcher'ı idam eden adamın ta kendisi.";
			link.l1.go = "saga_64";
		break;
		
		case "saga_64":
			dialog.text = "Pekâlâ. Hm. Şey, Jessica'yı en son gördüğümden bu yana yirmi yıldan fazla geçti. Onun hakkında ne biliyorsun?";
			link.l1 = "Şey, onun Kaptan Butcher’la nasıl bir araya geldiğini ve birlikte korsanlık yaptıklarını biliyorum. Onun Beatrice için onu terk ettiğini de biliyorum. Sonra, o da intikamını almak için Joshua Leadbeater adında, Maske olarak da bilinen biriyle iş birliği yaptı...";
			link.l1.go = "saga_65";
		break;
		
		case "saga_65":
			dialog.text = "";
			link.l1 = "Jan, açık sözlülüğümü mazur gör, ama Jessica'yla ilgilendiğini de biliyorum. İşte bu yüzden sana geldim. Jessica, arayışımda önemli bir isim. Bildiğim kadarıyla, Beatrice Sharp'ı kıskançlıktan öldüren de oydu.";
			link.l1.go = "saga_66";
		break;
		
		case "saga_66":
			dialog.text = "Well, you know a great deal. Yes, I really had been courting Jess, but it was no surprise; all pirates of Isla Tesoro were divided into two different groups back then: those who wanted to fuck Beatrice and those who wanted Jessica.\nI remember her well... She was beautiful, very beautiful!..";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("Video_Jess");
			NextDiag.TempNode = "saga_66a";
		break;
		
		case "saga_66a":
			dialog.text = "O çok özeldi... Büyük ihtimalle Jess, Beatrice'i öldürdü. Kasap onu 'Neptune'den attıktan sonra, muhtemelen aklında sadece ondan ve Beatrice'ten intikam almak vardı. Bu arada, Kasap'ın Jessica'dan nasıl kurtulduğunu biliyor musun?";
			link.l1 = "Hayır. Ya onu Barbados'ta bıraktı ya da fidye için rehin tuttu.";
			link.l1.go = "saga_67";
		break;
		
		case "saga_67":
			dialog.text = "İkincisi. Ona inanılmaz derecede kötü davrandı. Onu kamaraya kilitledi, Barbados’a götürdü, babası Oliver Rose’la pazarlık yapmaya başladı ve sonunda onu bir yığın dublon karşılığında sattı... Oysa o kız onun için neler yapmıştı.";
			link.l1 = "Hm. Korsanlar 'Neptune'u Joshua Leadbeater'dan aldığında, Kasap onun onurunu savundu sanıyordum...";
			link.l1.go = "saga_68";
		break;
		
		case "saga_68":
			dialog.text = "Bu da doğru. Ama ona bunun karşılığında cömertçe ödeme de yaptı. Jessica, o alçağın zavallı hayatını defalarca kurtardı; kendi hovardalığı ve öfkesiyle başına açtığı belalardan hep o çekip çıkardı. Aslında, onun başarılı bir korsan olarak ün kazanmasını tamamen Jessica'ya borçluydu.";
			link.l1 = "Evet, evet, onun 'kırmızı tılsımı'. Bunu duydum. Derler ki, Kasap Jess'i devirdiği anda, şansı da onu terk etmiş...";
			link.l1.go = "saga_69";
		break;
		
		case "saga_69":
			dialog.text = "But of course. Without Jessica, he had become just another common sea raider, even though a recklessly brave one. But Jessica wasn't there for him; she was the one who helped him plan all his risky operations, and he could always count on her blade.\nSure, Beatrice wasn't a good girl either, but she couldn't match Jess. Bea's charms were completely different... She made the mistake of crossing Butcher.";
			link.l1 = "Bunu daha önce bir yerde duymuştum...";
			link.l1.go = "saga_70";
		break;
		
		case "saga_70":
			dialog.text = "All pirates thought so, including Blaze Sharp, her brother. He couldn't stand Butcher... But let's get back to Jessica. I didn't even dare think of her while she was on the 'Neptune'; she would never have left her beloved captain. But when Butcher got rid of her in such a mean way...\nI arrived in Barbados and became friends with her. It wasn't easy for her; she loved the sea and dangerous adventures. That dull colonial life was killing her. Besides, she had become a very infamous person in the Caribbean while serving on the 'Neptune', and the folk of Bridgetown had reasons to consider her Butcher's partner in crime...";
			link.l1 = "Ama hiçbir şeyi kanıtlayamadılar...";
			link.l1.go = "saga_71";
		break;
		
		case "saga_71":
			dialog.text = "No. But no one wanted to have anything to do with her either. She was considered cursed, despite her status in Bridgetown. I suppose I was the only man who spent more than half an hour with Jessica there.\nI offered her the chance to come with me to the West Main and start a new life there. The life she had always wanted - the sea, ships, voyages, adventures. I had already set up a large operation in Blueweld by then and I was able to offer her a hundred times more than that scoundrel Butcher. But Jess was badly hurt. She hadn't forgiven Butcher for his betrayal and the way he treated her afterwards. And I believe she still had feelings for him even then... Despite all my efforts, I could not make her forget the past; she was obsessed with thoughts of revenge.";
			link.l1 = "Evet, ona hiç imrenmiyorum. Zavallı kız...";
			link.l1.go = "saga_72";
		break;
		
		case "saga_72":
			dialog.text = "Ben de onun hakkında aynı şekilde hissediyordum. Sonraları, eski Hint kültleri ve ritüellerine ilgi duymaya başladı. Bu, bir Hint büyücüsünün Yucatan ormanlarının derinliklerinden yakalanıp buradaki plantasyona getirilmesinden sonra oldu. Jessica onu satın aldı ve malikanesinde ona bir ev verdi.   Büyücüyle çok vakit geçiriyordu, bunun tamamen Hint büyü ritüellerine olan tarihsel ilgisinden kaynaklandığını söylüyordu. Bridgetown halkı, özellikle de yerel papaz, endişelenmeye başladı. Aslında, papaz Jessica'ya iyi davranan az sayıdaki insandan biriydi.   Papaz sık sık onunla konuşup büyücüyü göndermesini, tehlikeler ve engizisyon konusunda onu uyarıyordu, ama Jessica'yı korkutmaya çalışmak boşunaydı. Bir gece, bazı yabancılar büyücünün evine girip onu öldürdüler.   Aynı gece, iki adam Jessica'ya kendi yatak odasında saldırdı, ama işler onlar için hiç iyi gitmedi—Bridgetown'da kimse Jess'in alevli kılıcıyla ne kadar usta olduğunu bilmiyordu. Kelimenin tam anlamıyla onları parçalara ayırdı.";
			link.l1 = "Evet, tabii... o pervasız cadı!";
			link.l1.go = "saga_73";
		break;
		
		case "saga_73":
			dialog.text = "Bundan sonra, bütün kasaba ondan korkar oldu. Sonra Maske ortaya çıktı. Birbirlerini pek de geç olmadan buldular.";
			link.l1 = "Yazılara göre, Maske 'Neptune'un eski kaptanı Joshua Leadbeater...";
			link.l1.go = "saga_74";
		break;
		
		case "saga_74":
			dialog.text = "Bunu çok daha sonra öğrendim. Maskenin gelişinden bir hafta sonra, Jess eşyalarını topladı, bana veda etti ve bir askeri fırkateynle bilinmez sulara açıldı. Bir daha asla dönmedi... tıpkı Beatrice'in Isla Tesoro'ya asla dönmediği gibi.\nButcher'ı St. John's'ta astıktan kısa bir süre sonra, Maskenin kendisi onu oraya teslim etti. Ama Butcher'dan yalnızca bir gün fazla yaşadı.";
			link.l1 = "Evet... Bizim Steven Dodson gerçekten kendini gösterdi...";
			link.l1.go = "saga_75";
		break;
		
		case "saga_75":
			dialog.text = "Yes, that's what I was told. He avenged Beatrice... And that's how Jessica's story ends; she passed away somewhere on an uninhabited island in a skirmish with Butcher's pirates. Nobody knows where this place is. Butcher is dead, and so are Jackman and Hangman.";
			link.l1 = "İşte orada yanılıyorsun, Jan. Kasap hayatta.";
			link.l1.go = "saga_76";
		break;
		
		case "saga_76":
			dialog.text = " Ne!? Bu olamaz! Onu asmışlardı!";
			link.l1 = "Raymond Baker'ın ifadesini oku. Herhangi bir hikayeden daha iyidir.";
			link.l1.go = "saga_77";
		break;
		
		case "saga_77":
			PlaySound("interface\important_item.wav");
			dialog.text = "Bana göster ki...(okuyor) Hm. İnanılmaz! Demek ki idamı sahnelenmiş!";
			link.l1 = "Akıllıca, değil mi? Ama hepsi bu kadar değil. Kasabı tanıyorsun. Sadece artık kim olduğunu bilmiyorsun.";
			link.l1.go = "saga_78";
		break;
		
		case "saga_78":
			dialog.text = "Öyle mi? Peki, kimmiş o?";
			link.l1 = "Port Royal'dan Lawrence Beltrope. Madenin sahibi, Jackman'ın arkasında duran o gizemli gölge. Bunu Baker sayesinde öğrendim, Baker ise Mask'tan duymuş.";
			link.l1.go = "saga_79";
		break;
		
		case "saga_79":
			dialog.text = "Lanet olsun! Demek her şeyin arkasında o varmış? Peki... Biz de Butcher'a gideceğiz. Bu baş belasını nasıl alt edeceğimi düşüneceğim. Kolay olmayacak tabii, sürekli İngiliz makamlarının koruması altında.";
			link.l1 = "Onun zamanı gelecek, Jan. Yakında lostromosu ve çavuşuyla buluşacak. Peki, hikaye için teşekkürler. Artık gitme vakti benim için.";
			link.l1.go = "saga_80";
		break;
		
		case "saga_80":
			dialog.text = "Şu anda nereye gidiyorsun?";
			link.l1 = "Bir adaya. Sanırım Jess ve Beatrice’in öldüğü, Mask’ın Butcher-Beltrope’a saldırdığı yerle aynı. Helen’in Sharp ailesine ait olduğuna dair bir kanıta ihtiyacım var ve umarım onu orada bulabilirim.";
			link.l1.go = "saga_81";
		break;
		
		case "saga_81":
			dialog.text = "Pekala. Yani, "+pchar.name+" , sana bol şans. Dönünce bana her şeyi anlat.";
			link.l1 = "Tabii. Sonra görüşürüz, Jan!";
			link.l1.go = "saga_81a";
		break;
		
		case "saga_81a":
			DialogExit();
			LAi_SetHuberType(npchar);
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(npchar, "quest.jessika");
			npchar.quest.jessika_peace = "true"; // атрибут на мирное разрешение после боя
		break;
		
		case "saga_82":
			dialog.text = "Harika iş çıkardın, "+pchar.name+". Sen imkansızı başardın. Biz Kıyı Kardeşliği'nin tüm baronları sana minnettarız.";
			link.l1 = "Evet, zafere giden yol dardı. Keşke önceden bu kadarına katlanmam gerekeceğini bilseydim...";
			link.l1.go = "saga_83";
		break;
		
		case "saga_83":
			dialog.text = "Helen nasıl? Ne yapmayı düşünüyor?";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				link.l1 = "Artık benimle birlikte gemimde kalıyor. O artık sıradan bir subay değil. Adanın kontrolü Kardeşliğin liderine verilecek, ona ise sadece kira düşecek. Bunu Helen kendi kararıyla kabul etti.";
				link.l1.go = "saga_84";
			}
			else
			{
				link.l1 = "Baronluğu kendi ellerine almak için Isla Tesoro'ya doğru yola çıktı.";
				link.l1.go = "saga_85";
			}
		break;
		
		case "saga_84":
			dialog.text = "Pekala, "+pchar.name+"... Tebrikler! Senin yerinde olmayı birçok erkek hayal etti. Helen'in kendisine layık birini seçmiş olmasına sevindim. Onun hayat arkadaşı olmak için senden daha iyi bir aday olamazdı.";
			link.l1 = "Teşekkür ederim, Jan! Şimdi Tortuga ve Levasseur hakkındaki sohbetimize dönmek istiyorum.";
			link.l1.go = "saga_86";
			if (CheckAttribute(pchar, "questTemp.PZ_DialogSvensonBlock"))
			{
				link.l1 = "Teşekkür ederim, Jan!";
				link.l1.go = "saga_87";
			}
		break;
		
		case "saga_85":
			dialog.text = "Harika. Bunu hak ediyor. Kardeşliğin yeni liderinin ona işlerinde yardımcı olacağına inanıyorum. O yetenekli ve zeki bir genç kız, her şeyi çabucak kavrayıp öğrenebilir. Teşekkür ederim, "+pchar.name+"! Helen benim için bir kız evlat gibi ve onun için böylesine harika bir geleceğin açılmış olmasından büyük mutluluk duyuyorum.";
			link.l1 = "Rica ederim, Jan... Neyse, Tortuga ve Levasseur hakkındaki sohbetimize dönmek isterim.";
			link.l1.go = "saga_86";
			if (CheckAttribute(pchar, "questTemp.PZ_DialogSvensonBlock"))
			{
				link.l1 = "Rica ederim, Jan.";
				link.l1.go = "saga_87";
			}
		break;
		
		case "saga_86":
			sTemp = "Shark Dodson";
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus Tyrex";
			dialog.text = "Sen yokken, "+sTemp+" ve ben bu konuyu zaten konuştuk ve Levasseur'un ortadan kaldırılması konusunda ortak bir karara vardık. Isla Tesoro'ya git ve yeni liderimizle konuş, sana planımızın ayrıntılarını anlatacak ve elinden gelen tüm yardımı sağlayacak.";
			link.l1 = "Sonunda barutun kokusunu alabiliyorum! Kaybedecek vakit yok, Isla Tesoro'ya gidiyorum!";
			link.l1.go = "saga_87";
		break;
		
		case "saga_87":
			dialog.text = ""+pchar.name+"Bir dakika bekle. Helen ve Kardeşlik konusunda bana yardım ettiğin için sana birkaç hediye getirdim. İlki, Uzak Doğu'dan gelen büyülü Sarazen muskası. Büyüsü gemideki disiplini güçlendiriyor, bizzat test ettim. Al bakalım.";
			link.l1 = "Teşekkür ederim!";
			link.l1.go = "saga_88";
		break;
		
		case "saga_88":
			GiveItem2Character(pchar, "talisman4");
			Log_Info("You've received the 'Janissary' amulet.");
			PlaySound("interface\important_item.wav");
			dialog.text = "İkincisi ise sadece geçmiş maceralardan bir hatıra. Konseyi, bu saçma taş parçalarını rüzgara savurma geleneğinden vazgeçmeye ikna ettim. Artık onlara ihtiyaç yok. Sana vereceğim. Belki bir işe yarar.";
			link.l1 = "Parçalar için bir kullanım mı? Hm. Bilmiyorum... ama hatıra olarak, minnettarım!";
			link.l1.go = "saga_89";
		break;
		
		case "saga_89":
			GiveItem2Character(pchar, "splinter_js"); 
			GiveItem2Character(pchar, "splinter_nh"); 
			GiveItem2Character(pchar, "splinter_mt"); 
			GiveItem2Character(pchar, "splinter_zm"); 
			GiveItem2Character(pchar, "splinter_jb"); 
			Log_Info("You've received five ornamental pattern fragments");
			dialog.text = "Pekâlâ, arkadaşını unutma, "+pchar.name+" . Blueweld'e demir attığında yanıma uğra. Oturur, biraz rom içeriz. Seni görmek her zaman beni mutlu eder.";
			link.l1 = "Kesinlikle, Jan. Artık hatırlayacak bir şeyimiz var, değil mi? Ha-ha! Neyse, ben artık gitmeliyim.";
			link.l1.go = "saga_90";
		break;
		
		case "saga_90":
			dialog.text = "Bol şans, "+pchar.name+"!";
			link.l1 = "Görüşürüz...";
			link.l1.go = "saga_91";
		break;
		
		case "saga_91":
			DialogExit();
			pchar.questTemp.Saga = "end";
			if (CheckAttribute(pchar, "questTemp.PZ_DialogSvensonBlock")) AddQuestRecord("Saga", "26_1");
			else 
			{
				AddQuestRecord("Saga", "26");
				pchar.questTemp.Terrapin = "islatesoro";
			}
			CloseQuestHeader("Saga");
			ChangeCharacterComplexReputation(pchar, "fame", 5);
		break;
		
	// --> провалы Саги
		case "saga_f_1":
			dialog.text = "Evet... Görünen o ki planımız tamamen suya düştü. Artık istediğimiz kişiyi Kardeşliğin başına getiremeyeceğiz. Jackman öldü, bu iyi bir şey. Ama ne yazık ki, planım artık işe yaramayacak. Kardeşliğin başkanını her zamanki gibi seçmek zorunda kalacağız ve Tanrı bilir bu iş nasıl bir hal alacak...";
			link.l1 = "Bu talihsiz bir durum. Hem de çok talihsiz. Görünen o ki, Helen de mirasından mahrum kalacak.";
			link.l1.go = "saga_f_2";
		break;
		
		case "saga_f_2":
			dialog.text = "Evet, "+pchar.name+". Ve Tortuga'yı ele geçirmen için sana yardım etmek isterdim, gerçekten isterdim, ama şu anda nasıl yapabileceğimi bile bilmiyorum. Muhtemelen sana yardımcı olabileceğim hiçbir şey yok. Görünen o ki, sadece kendi gücüne ve savaşma yeteneğine güvenmek zorunda kalacaksın.";
			link.l1 = "Görünüşe göre başka bir seçenek kalmadı... Peki Jan, gidip bundan sonra ne yapacağımı düşüneceğim. Sonra görüşürüz...";
			link.l1.go = "saga_f_3";
		break;
		
		case "saga_f_3":
			dialog.text = "Uğra, "+pchar.name+". Seni gördüğüme her zaman seviniyorum.";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.Saga = "end";
			CloseQuestHeader("Saga");
			CloseQuestHeader("Testament");
		break;
		
		case "saga_l1": // проход первый - отбираем Элен и закрываем вход к Свенсону
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", true); // закрыть кабинет Свенсона
			pchar.questTemp.Saga = "end";
			CloseQuestHeader("Saga");
			// Элен - к разговору
			sld = characterFromId("Helena");
			sld.quest.talk = "late_l1";
			pchar.quest.Saga_Late_1.win_condition.l1 = "Location_Type";
			pchar.quest.Saga_Late_1.win_condition.l1.location_type = "town";
			pchar.quest.Saga_Late_1.function = "Saga_HelenaTalk";
			pchar.questTemp.Saga.Jackman = "true";
			Saga_ChangesIslatesoro(); // вызов перестановки на Исла-Тесоро
		break;
		
		case "saga_l2": // проход второй - отбираем Элен, Натана и Данни в Марун-Таун, чистим квестовый лут
			dialog.text = "Ne yazık ki, artık yapacak bir şey yok. Isla Tesoro resmen İngiliz tacının yetkisine geçti. Şimdi orada bir garnizon var. Bu, Kardeşler için çok ağır bir darbe; korkarım, bundan toparlanamayacağız.";
			link.l1 = "Ne korkunç... Ah, daha hızlı davranmalıydım. O zaman, bak, her şey yolunda giderdi. Peki Jan, şimdi gidip ne yapacağımı düşüneceğim. Sonra görüşürüz...";
			link.l1.go = "saga_l2_1";
		break;
		
		case "saga_l2_1":
			dialog.text = "Uğra, "+pchar.name+".   Seni gördüğüme her zaman seviniyorum.";
			link.l1 = "...";
			link.l1.go = "saga_l2_2";
		break;
		
		case "saga_l2_2":
			DialogExit();
			pchar.questTemp.Saga = "end";
			CloseQuestHeader("Saga");
			RemoveItems(pchar, "splinter_nh", 1);
			RemoveItems(pchar, "splinter_mt", 1);
			RemoveItems(pchar, "splinter_jb", 1);
			RemoveItems(pchar, "splinter_zm", 1);
			RemoveItems(pchar, "letter_parol", 1);
			RemoveItems(pchar, "map_sharp_full", 1);
			sld = characterFromId("Nathaniel");
			sld.model = "Hawk_2";
			Characters_RefreshModel(sld); // наверно не нужно
			sld.greeting = "nathaniel_2";
			sld.dialog.currentnode = "marun_town";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "sit", "sit1");
			LAi_SetHuberType(sld);
			LocatorReloadEnterDisable("FortOrange_town", "reload6", false); // открыть резиденцию Хоука
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "marun_town";
			sld.greeting = "danny_2";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "goto", "goto1");
			LAi_SetStayType(sld);
			// Элен - к разговору
			sld = characterFromId("Helena");
			sld.quest.talk = "late_l2";
			pchar.quest.Saga_Late_2.win_condition.l1 = "Location_Type";
			pchar.quest.Saga_Late_2.win_condition.l1.location_type = "town";
			pchar.quest.Saga_Late_2.function = "Saga_HelenaTalk";
			Saga_ChangesIslatesoro(); // вызов перестановки на Исла-Тесоро
			pchar.questTemp.Saga_Late = true; // второй атрибут, отсекающий диалоги, на всякий пожарный
		break;
		
		case "saga_l3":
			dialog.text = "Evet... Gerçekten ağır bir yenilgi aldık. En kötüsü de, zaferden sadece bir adım uzaktaydık. Caramba! Bu nasıl oldu, ha, "+pchar.name+"? O kadar çok uğraştın, elinden geleni yaptın ve... ne kötü bir talih!";
			link.l1 = "Bu işten sorumlu aptal benim. Daha hızlı olmalıydım. Ve benim yüzümden Helen mirasını kaybedecek. Ayrıca Tortuga planı da asla gerçekleşmeyecek.";
			link.l1.go = "saga_f_2";
			pchar.questTemp.Saga_Late = true; // второй атрибут, отсекающий диалоги, на всякий пожарный
		break;
	// <-- провалы Саги
		
	//-----------------------------------генератор торговли бакаутом--------------------------------------------
		case "trade_bakaut":
			if (CheckAttribute(pchar, "questTemp.UpgradeBakaut"))
			{
				dialog.text = "Pekâlâ, benim için sorun yok. Depomda 125 birim var. Fiyatı, hatırlarsan, tanesi 3.150.";
				if (PCharDublonsTotal() >= 3150)
				{
					link.l1 = "Pekala, anlaştık. Al bakalım. İşte 3150 dublon.";
					link.l1.go = "trade_bakaut_1";
				}
				else
				{
					link.l1 = "Ne kötü şans. Paramı gemide unuttum. Hemen alıp döneceğim.";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Pekâlâ, benim için sorun değil. Depomda yirmi beş birim var. Fiyatı da hatırlarsan, tanesi otuz doblondur.";
				if (PCharDublonsTotal() >= 750)
				{
					link.l1 = "Pekala, anlaştık. Al bakalım. İşte yedi yüz elli doblon.";
					link.l1.go = "trade_bakaut_1";
				}
				else
				{
					link.l1 = "Ne kötü şans. Paramı gemide unuttum. Hemen getirip döneceğim.";
					link.l1.go = "exit";
				}
			}
			if(sti(pchar.questTemp.SvensonBakaut) >= 1 && !CheckAttribute(pchar, "questTemp.SvensonBakautBlock")) // увеличить объём поставок бакаута
			{
				link.l4 = "Jan, demir ağacı sevkiyatlarının miktarını artırmak mümkün mü?";
				link.l4.go = "UpgradeBakaut";
			}
			if(sti(pchar.questTemp.SvensonBakaut) >= 1 && CheckAttribute(pchar, "questTemp.SvensonBakautPotom") && PCharDublonsTotal() >= 3000) // увеличить объём поставок бакаута, если в первый раз не принесли
			{
				link.l4 = "Jan, üç bin altın topladım. Al, bu hediyeyi asalaklarımıza sunabilirsin. Sanırım bugün keyifleri yerinde olacak.";
				link.l4.go = "UpgradeBakaut_Agreed";
			}
		break;
		
		case "trade_bakaut_1":
			RemoveDublonsFromPCharTotal(750);
			Log_Info("You have given 750 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Takdire şayan. Adamlarıma demir ağacını geminize taşımalarını emredeceğim.";
			link.l1 = "Teşekkür ederim!";
			link.l1.go = "trade_bakaut_2";
		break;
		
		case "trade_bakaut_2":
			dialog.text = "Daha fazla almak istersen, iki hafta sonra tekrar gel. O zamana kadar yeni bir parti hazırlamış olurum.";
			link.l1 = "Pekala, Jan. Bir dahaki sefere görüşürüz!";
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_SANDAL, 25);
			DeleteAttribute(npchar, "quest.trade_bakaut");
			SetFunctionTimerCondition("Bakaut_SvensonAttrReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 100);
		break;
		
		case "UpgradeBakaut": //
			if (startHeroType == 1) sStr = "old friend";
			if (startHeroType == 2) sStr = "old friend";
			if (startHeroType == 3) sStr = "old friend";
			if (startHeroType == 4) sStr = "Helen";
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 80)
			{
				dialog.text = "Demir ağacını beğenmene sevindim, "+sStr+". Sevkiyatları artırmak sorun değil, ama bir pürüz var, sen de anlıyorsun. Hacim büyüdükçe izimiz de büyür, bu da istemediğimiz dikkatleri, özellikle İngiliz makamlarını çekebilir. Ama güvenilir eller, sadık kulaklar ve konakta bize göz kulak olacak insanlar eklersek, her şeyi yoluna koyabiliriz. Tabii bunun bir bedeli var – şehir hazinesini ve İngiltere'nin taleplerini atlatmak için üç bin doblon isterim. O zaman sana beş katı mal sağlayabilirim. Ne dersin?";
				link.l1 = "Üç bin doblon mu? Jan, bu resmen soygun! Masrafları biraz daha azaltamaz mıyız? Belki de bu işi bu kadar uçuk meblağlar olmadan halletmenin bir yolu vardır?";
				link.l1.go = "UpgradeBakaut_1";
				Notification_Skill(true, 80, SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "İyi fikir, ama söylemeliyim ki, bu kadar büyük ticaret hacimleri için biraz daha tecrübe ve beceri gerekir. Acele edersen, faydadan çok risk alırsın. Şöyle yapalım: biraz daha tecrübe kazan, büyük partilere hazır olduğunda tekrar gel. O zaman her şeyi düzgünce konuşuruz.";
				link.l1 = "Hmm... Peki. Bu konuşmaya sonra dönelim.";
				link.l1.go = "exit";
				Notification_Skill(false, 80, SKILL_COMMERCE);
			}
		break;
		
		case "UpgradeBakaut_1":
			dialog.text = "Ne yazık ki, "+pchar.name+" , işte günümüzde barışın bedeli böyle - o peruklu ve üniformalı beyefendilerin iştahı her geçen gün artıyor. Sandıklarındaki altınların şıngırtısından daha çok onları hiçbir şey cezbetmiyor. Eğer içinizi rahatlatırsa, sonraki tüm sevkiyatlarda size yüzde on beş indirim garanti ediyorum.";
			link.l1 = "Kahretsin onlara! Böyle paralar istemek de ne! Bu açgözlülükle kralların hazinelerini satın almalılar, sessizlik için pazarlık etmiyor olmalılar! Jan, belki de... onlara takımadadaki gerçek gücün kim olduğunu göstermeliyiz, ha?";
			link.l1.go = "UpgradeBakaut_2";
		break;
		
		case "UpgradeBakaut_2":
			if (startHeroType == 1) sStr = "my friend";
			if (startHeroType == 2) sStr = "my friend";
			if (startHeroType == 3) sStr = "my friend";
			if (startHeroType == 4) sStr = "Helen";
			dialog.text = "Ha! Ne güzel bir ruhun var, "+sStr+"! Ama şu anda bütün İngiltere'yi karşıma almak istemem, hem eskisi kadar genç de değilim. Şu kan emicilere parasını verip sessizce oturmalarını sağlayalım - bizim de kendi işlerimiz var. Gerekli parayı topla, yolumuz açılır, gereksiz sorular da olmaz!";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "Pekâlâ, Jan, beni ikna ettin. Öyle olsun, başka çare yok zaten. Al, üç bin doblonun burada. Ama unutma: Bu açgözlüleri sonsuza dek beslemeye niyetim yok.";
				link.l1.go = "UpgradeBakaut_Agreed";
			}
			link.l2 = "Şeytan alsın onları, Jan! Gerçekten başka bir çıkış yolu olmadığını mı düşünüyorsun? Peki. Bu doblonları bulacağım. Ama şu anda o kadar param yok.";
			link.l2.go = "UpgradeBakaut_4";
			link.l3 = "Lanet olsun Jan, gerçekten bu memurları ve onların şımarık hanımlarını beslememi mi istiyorsun? Oturdukları yerden hiçbir şey yapmıyorlar, sadece para istiyorlar! Hayır, bu iş hoşuma gitmiyor! Alın terimle, kanımla onların ceplerini doldurmayacağım! Eski şartlara dönelim. Bana o yeter.";
			link.l3.go = "UpgradeBakaut_3";
		break;
		
		case "UpgradeBakaut_Agreed":
			dialog.text = "İşte şimdi oldu! Senin katkınla işlerimiz yolunda gidecek, o cimriler de hak ettiklerini bulacaklar – artık demir ağaca bakmaya bile cesaret edemeyecekler. Emin ol, yatırımlarımızı kısa sürede katbekat geri alacağız.";
			link.l1 = "Umarım öyle olur, Jan, umarım öyle olur.";
			link.l1.go = "UpgradeBakaut_Agreed_1";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecordInfo("Unique_Goods", "1_1");
			pchar.questTemp.UpgradeBakaut = true;
			pchar.questTemp.SvensonBakautBlock = true;
			DeleteAttribute(pchar, "questTemp.SvensonBakautPotom");
		break;
		
		case "UpgradeBakaut_Agreed_1":
			dialog.text = "İşler olması gerektiği gibi yürüyecek, endişelenmenize gerek yok. Şimdi ise gelecekteki anlaşmalarımıza gelince: Daha önce olduğu gibi, her ayın 14’ü ve 28’inde sizin için 125 kereste demir ağacı hazır tutacağım. Tüm partiyi 3.150 dublona alabilirsiniz.";
			link.l1 = "Bu konuşmaları çok daha fazla beğendim! Yüz yirmi beş kütük, öyle mi? Harika, Jan. Peki, yakında görüşürüz, gönderiyi bekliyor olacağım!";
			link.l1.go = "exit";
		break;
		
		case "UpgradeBakaut_3":
			if (startHeroType == 1) sStr = "old friend";
			if (startHeroType == 2) sStr = "old friend";
			if (startHeroType == 3) sStr = "old friend";
			if (startHeroType == 4) sStr = "Helen";
			dialog.text = "Dediğiniz gibi, "+sStr+". Ve bu kadar sinirlenme. Dünya böyle bir yer işte.";
			link.l1 = "Evet, Jan, bu dünyanın nasıl işlediğini biliyorum. Ama bu, buna katlanmam gerektiği anlamına gelmiyor. Peki, gitmeliyim.";
			link.l1.go = "exit";
			pchar.questTemp.SvensonBakautBlock = true;
		break;
		
		case "UpgradeBakaut_4":
			dialog.text = "Parayı toplamanı bekleyeceğim. Bir yolunu bulacağına inanıyorum. Hazır olduğunda, parayla seni bekliyor olacağım ve devam edeceğiz.";
			link.l1 = "Pekala.";
			link.l1.go = "exit";
			pchar.questTemp.SvensonBakautBlock = true;
			pchar.questTemp.SvensonBakautPotom = true;
		break;
		// <-- генератор бакаута
		
	//----------------------------------- штурм рудника --------------------------------------------
		case "mine_attack":
			dialog.text = "Seni gördüğüme sevindim, "+pchar.name+". Adamlarım hazır. Ormana gidelim mi?";
			link.l1 = "Evet, Jan. Ekibim savaşa hazır.";
			link.l1.go = "mine_attack_1";
		break;
		
		case "mine_attack_1":
			dialog.text = "O zaman yola çıkalım. Maden ormanın derinliklerinde, tam bu patika boyunca. Çatala gelince sağdan devam edin. İleri!";
			link.l1 = "İleri!";
			link.l1.go = "mine_attack_2";
		break;
		
		case "mine_attack_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Svensons_off_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("Svensons_sold_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("shore53", "boat", true);
			LocatorReloadEnterDisable("mine_03", "reload3_back", true);
			LocatorReloadEnterDisable("mine_02", "reload3_back", true);
			pchar.quest.Saga_MineAttack_01.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_01.win_condition.l1.location = "Mine_02";
			pchar.quest.Saga_MineAttack_01.function = "Saga_PrepareMineAttackTail";
		break;
		
		case "mine_attack_3":
			dialog.text = "Yani, "+pchar.name+", bu operasyonu nasıl yürüteceğimizi konuşmanın zamanı geldi. Bölgede keşif yapmaları için birkaç Miskito yerlisini önceden gönderdim ve onların gözlemlerine dayanarak bir hareket planı hazırladım.";
			link.l1 = "Beni bilgilendir!";
			link.l1.go = "mine_attack_4";
		break;
		
		case "mine_attack_4":
			dialog.text = "Çukur, ormandaki dağların altındaki madeni temsil ediyor. Madenin girişine yakın bir kamp var. Birkaç ev ve bir palisad. Palisada giden bir patika var. Bak, bu patika ormanda buradan çok uzakta olmayan küçük, temizlenmiş bir alana çıkıyor. İşte çukurun ana girişi orada bulunuyor\nBu, iki dik tepe arasında yükselen taş bir duvarı temsil ediyor, kimsenin gizlice içeri sızmasını engelliyor. Kapıları altı adam koruyor. Büyük bir mesele değil, ama oraya iki top da yerleştirmişler. Asıl sorun bu.\nİki üzüm taneli top atışı timimizin yarısını yere serebilir, bu da tam bir felaket olurdu, bu yüzden doğrudan saldırmak bir seçenek değil...";
			link.l1 = "Ha! Ama bizim kozumuz var — içeri girmemizi sağlayacak şifreyi biliyoruz...";
			link.l1.go = "mine_attack_5";
		break;
		
		case "mine_attack_5":
			dialog.text = "Doğru. Bunu kendi lehimize kullanacağız, ama şimdilik sana planımın tamamını, sonuna kadar anlatayım.";
			link.l1 = "Tabii, Jan. Seni dinliyorum.";
			link.l1.go = "mine_attack_6";
		break;
		
		case "mine_attack_6":
			dialog.text = "Çukura başka bir giriş daha var - ormandaki o patikadan. Bu yol, madeni koruyan tepelerin etrafından dolanıyor ve içeri girmek için kullanılabilecek küçük, dar bir oyukla sona eriyor. Ama haydutlar oraya yüksek bir çit çekmiş ve nöbetçiler yerleştirmiş. Çitte küçük kapılar var, ama onlar da içeriden barikatlanmış.\nŞimdi ne yapacağımızı dinle. Madene giden ikinci girişteki nöbetçileri etkisiz hale getireceğiz. Ekibimizin bir kısmı orada kalıp koçbaşı olarak kullanmak için bir kütük bulacak.\nBiz ana girişe döneceğiz ve topçu ekibini öldüreceğiz. Elimizdeki parola bize iki kez yardımcı olacak. Sonrasında madene iki taraftan saldıracağız. İlk saldırı birliğine ben komuta edeceğim, ikinciye ise sen.";
			link.l1 = "Pekâlâ, mantıklı. Onları iki cephede bizimle savaşmaya zorlayacağız. İleri!";
			link.l1.go = "mine_attack_7";
		break;
		
		case "mine_attack_7":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.quest.mine01 = "true";
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationDisableOfficersGen("mine_01", true);//офицеров не пускать
			pchar.quest.Saga_MineAttack_02.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_02.win_condition.l1.location = "Mine_04";
			pchar.quest.Saga_MineAttack_02.function = "Saga_PrepareMineAttackTail";
		break;
		
		case "mine_attack_8":
			dialog.text = "Right, here we are... This is the path to the bandits' fence. Now we need to decide how to deal with them. If we send the whole squad, it will be too suspicious and they'll raise the alarm.\nWe should send a small group of three, no more; this group will be able to get close enough without arousing suspicion and attack by surprise. I can't lead the group, my face is too well known around here.\nSo it's up to you, "+pchar.name+", because you are the only one I can trust to command without risking the whole operation. I will give you Gregory and a musketeer to assist...";
			link.l1 = "Çit nöbetinde kaç muhafız var?";
			link.l1.go = "mine_attack_9";
		break;
		
		case "mine_attack_9":
			dialog.text = "Dört. İki musketeer ve iki asker.";
			link.l1 = "Onları alacağız...";
			link.l1.go = "mine_attack_10";
		break;
		
		case "mine_attack_10":
			dialog.text = "Seni tanıdığım için, buna hiç şüphem yok. Yanlarına git ve Jackman'ın seni gönderdiğini söyle. Parolayı ver. Sonra, herkes rahatlayınca... duruma göre hareket et.";
			link.l1 = "Pekâlâ. Onları tetikte tutacağız.";
			link.l1.go = "mine_attack_11";
		break;
		
		case "mine_attack_11":
			dialog.text = "İyi şanslar, "+pchar.name+"!";
			link.l1 = "...";
			link.l1.go = "mine_attack_12";
		break;
		
		case "mine_attack_12":
			DialogExit();
			LAi_SetStayTypeNoGroup(npchar);
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Svensons_off_"+i);
				LAi_SetStayTypeNoGroup(sld);
				if (i == 2)
				{
					LAi_SetActorType(sld);
					LAi_ActorFollowEverywhere(sld, "", -1);
				}
			}
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("Svensons_sold_"+i);
				LAi_SetStayTypeNoGroup(sld);
				if (i == 12)
				{
					LAi_SetActorType(sld);
					LAi_ActorFollowEverywhere(sld, "", -1);
				}
			}
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("Ourmine_sold_"+i);
				LAi_SetStayTypeNoGroup(sld);
				LAi_CharacterDisableDialog(sld);//запрет диалога
			}
			chrDisableReloadToLocation = false;//открыть локацию
			DeleteAttribute(npchar, "quest.mine01");
			npchar.quest.mine02 = "true";
			pchar.questTemp.Saga.MineAttack = "true";
			pchar.quest.Saga_MineAttack_03.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_03.win_condition.l1.location = "Mine_01";
			pchar.quest.Saga_MineAttack_03.function = "Saga_MineAttackTail";
		break;
		
		case "mine_attack_13":
			dialog.text = "Harika iş çıkardın, "+pchar.name+"! Yine her zamanki gibi galip geldin. Şimdi adamlarım bu taraftan madene fırtına gibi dalmaya hazırlanacak ve ana girişi temizleyeceğiz.";
			link.l1 = "Yine gardiyanların yanına ben mi gideceğim?";
			if (GetCharacterIndex("Svensons_off_2") != -1 && GetCharacterIndex("Svensons_sold_12") != -1) link.l1.go = "mine_attack_14";
			else link.l1.go = "mine_attack_14a";
		break;
		
		case "mine_attack_14a":
			dialog.text = "Evet, "+pchar.name+", bir kez daha. Kendim gitmeyi isterdim ama beni kesinlikle tanırlar ve bütün operasyon altüst olurdu. Düşman sayısı arttığı için daha tehlikeli olacak, silahları da unutma.";
			link.l1 = "Subaylarımı yanıma alacağım.";
			link.l1.go = "mine_attack_14_1";
		break;
		
		case "mine_attack_14":
			dialog.text = "Evet, "+pchar.name+", bir kez daha. Aslında kendim gitmek isterdim, ama kesinlikle beni tanırlar ve bütün plan altüst olurdu. Bu sefer daha fazla düşman var, ayrıca silahları da unutma, yani daha tehlikeli olacak. Yanına kimi alacaksın? Subaylarını mı, yoksa geçen seferki gibi Gregory ve tüfekçiyi mi?";
			link.l1 = "Subaylarımı alacağım.";
			link.l1.go = "mine_attack_14_1";
			link.l2 = "Gregory ve tüfekçiyi alacağım.";
			link.l2.go = "mine_attack_14_2";
		break;
		
		case "mine_attack_14_1":
			dialog.text = "Pekâlâ. Kendi adamların en iyi desteğindir. Şimdi ana girişe doğru geri dönelim. Yolu hatırlıyor musun?";
			link.l1 = "Elbette. Geldiğimiz yolu geri dön, sonra sola sap ve tepenin etrafındaki patikayı takip et.";
			link.l1.go = "mine_attack_15";
			pchar.questTemp.Saga.MineAttack = "officer";
		break;
		
		case "mine_attack_14_2":
			dialog.text = "Pekâlâ. Bir kez başardın, o yüzden ikinci kez yapmak çocuk oyuncağı olmalı. Şimdi ana girişe geri döneceğiz. Yolu hatırlıyor musun?";
			link.l1 = "Elbette. Geldiğimiz yolu geri dön, sonra sola sap ve tepenin etrafındaki patikayı takip et.";
			link.l1.go = "mine_attack_15";
			pchar.questTemp.Saga.MineAttack = "soldiers";
		break;
		
		case "mine_attack_15":
			dialog.text = "Vakit kaybetmeyelim. Hadi ilerleyelim!";
			link.l1 = "İleri!";
			link.l1.go = "mine_attack_16";
		break;
		
		case "mine_attack_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			for (i=1; i<=2; i++)
			{
				if (GetCharacterIndex("Svensons_off_"+i) != -1)
				{
					sld = characterFromId("Svensons_off_"+i);
					LAi_SetActorType(sld);
					LAi_ActorFollowEverywhere(sld, "", -1);
				}
			}
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("Svensons_sold_"+i);
				LAi_SetActorType(sld);
				if (pchar.questTemp.Saga.MineAttack == "soldiers" && i == 12) LAi_ActorFollowEverywhere(sld, "", -1);
				else LAi_ActorRunToLocation(sld, "reload", "reload3_back", "mine_01", "goto", "goto"+i, "", 5);
			}
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("Ourmine_sold_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationDisableOfficersGen("mine_01", false);//офицеров пускать
			if (pchar.questTemp.Saga.MineAttack == "soldiers") LAi_LocationDisableOfficersGen("mine_exit", true);//офицеров не пускать
			LocatorReloadEnterDisable("mine_03", "reload3_back", false);
			LocatorReloadEnterDisable("mine_02", "reload3_back", false);
			DeleteAttribute(npchar, "quest.mine02");
			npchar.quest.mine03 = "true";
			pchar.quest.Saga_MineAttack_05.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_05.win_condition.l1.location = "Mine_02";
			pchar.quest.Saga_MineAttack_05.function = "Saga_PrepareMineAttackTail";
		break;
		
		case "mine_attack_17":
			dialog.text = "Doğru, "+pchar.name+", son talimatları dikkatlice dinle. Kapıları koruyan iblisler çok zorlu, bu yüzden işin kolay olmayacak. Ana hedefin, kapıların yanında duran topçuları öldürmek, çünkü onlar hayattayken sana yardıma gelemeyiz.\nİkisi de öldüğünde ve toplu ateş riski kalmadığında, hepimiz birlikte saldırıp onları saniyeler içinde gebertiriz. Anladın mı, "+pchar.name+"? Kahramanlık yapma, topçuları öldür ve gerisini bize bırak.";
			link.l1 = "Pekala, Jan. Her şeyi planladığımız gibi yapmaya çalışacağım. Bir şeyler ters giderse, duruma göre hareket ederim.";
			link.l1.go = "mine_attack_18";
		break;
		
		case "mine_attack_18":
			dialog.text = "Kulağa hoş geliyor. Tanrı yardımcın olsun!";
			link.l1 = "Teşekkürler...";
			link.l1.go = "mine_attack_19";
		break;
		
		case "mine_attack_19":
			DialogExit();
			LAi_SetStayTypeNoGroup(npchar);
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			for (i=1; i<=2; i++)
			{
				if (GetCharacterIndex("Svensons_off_"+i) != -1)
				{
					sld = characterFromId("Svensons_off_"+i);
					if (pchar.questTemp.Saga.MineAttack == "soldiers" && i == 2)
					{
						LAi_SetActorType(sld);
						LAi_ActorFollowEverywhere(sld, "", -1);
					}
					else LAi_SetStayTypeNoGroup(sld);
				}
			}
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("Ourmine_sold_"+i);
				LAi_SetStayTypeNoGroup(sld);
			}
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationDisableOfficersGen("mine_01", false);//офицеров пускать
			DeleteAttribute(npchar, "quest.mine03");
			pchar.quest.Saga_MineAttack_06.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_06.win_condition.l1.location = "Mine_exit";
			pchar.quest.Saga_MineAttack_06.function = "Saga_MineAttackTail";
		break;
		
		case "mine_attack_20":
			dialog.text = "Vay canına! Şu alçakları biçtik resmen... Ne hırçın veletlermiş. Bu paralı askerlerin eskiden düzenli orduda görev yaptıkları belli. Burada epey gürültü çıkardık, sanırım duyan olmuştur. Bir dakika bile kaybetmeyelim! "+pchar.name+", maden ocağına saldırma zamanı geldi.\nBen ikinci girişteki grubuma döneceğim - muhtemelen çoktan bir kütük bulup çiti kırmaya hazırlamışlardır. Sen ve adamların ise ana kapıdan geçeceksiniz. Bizi yarım saat bekleyin, hemen saldırmayın...";
			link.l1 = "Jan, eğer madendeki silah sesini duydularsa, yarım saatimiz bile yok. O haydutlar ya savunma hattı kurar ya da doğrudan ana kapılara gelir ve ellerindeki her şeyle grubuma saldırırlar...";
			link.l1.go = "mine_attack_21";
		break;
		
		case "mine_attack_21":
			dialog.text = "Siktir! Bu gayet mümkün. Ne yapmamızı öneriyorsun?";
			link.l1 = "Hm... Ha! Bir fikrim var! Toplar! Etrafa bak. Sadece saçma değil, bombalar da var! Şimdi bu haydutlar bitti! Bunu daha önce neden düşünmedim?!";
			link.l1.go = "mine_attack_22";
		break;
		
		case "mine_attack_22":
			dialog.text = "Sence ne yapmalıyız?";
			link.l1 = "Bir top alacağız. Sadece bir tane olursa, çok daha hızlı ve verimli hareket edebiliriz. Onu içeri, kapıların ötesine, madene kadar yuvarlayıp yerine yerleştireceğiz. Eğer saldırıya geçerlerse, büyük bir patlama yaşarlar; geri dururlarsa, kamplarını bombalarız. Kapıların ardında kampın tam olarak nerede olduğunu bana söyleyebilir misin?";
			link.l1.go = "mine_attack_23";
		break;
		
		case "mine_attack_23":
			dialog.text = "Kamp, bir dağın eteğinde, alçak bir yerde. Kapıların hemen ötesinde aşağıya inen ve tepenin etrafında dolanan bir patika var. Kamp tam bu tepenin arkasında kurulmuş.";
			link.l1 = "Harika! Patikanın tepesine yerleşip tepeden yuvalarına birkaç bomba atacağız! O zaman hepsi dört bir yana kaçışacak!";
			link.l1.go = "mine_attack_24";
		break;
		
		case "mine_attack_24":
			dialog.text = "Lanet olsun, "+pchar.name+"   Aferin! Tam yol ileri! Randolf'u senin emrine bırakıyorum, o benim en iyi topçumdur. Onu topçubaşı yap, seni asla yarı yolda bırakmaz. Şimdi birliğime dönüyorum.";
			link.l1 = "Pekala. Sen kapıları kırana kadar yarım saat boyunca onların mevzilerini cehenneme çevireceğim.";
			link.l1.go = "mine_attack_25";
		break;
		
		case "mine_attack_25":
			dialog.text = "Zamanında yetişmeye çalışacağım. Kampta görüşürüz!";
			link.l1 = "Anlaştık... Takım! Komutumu dinleyin! Topu yeni bir mevziye taşımaya hazırlanın! Barut, bomba ve saçma da alın! Kapılardan geçip madene gidiyoruz. İleri, marş!";
			link.l1.go = "mine_attack_26";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", 5);
			if (GetCharacterIndex("Svensons_off_2") != -1)
			{
				sld = characterFromId("Svensons_off_2");
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "", 5);
			}
		break;
		
		case "mine_attack_26":
			DialogExit();
			int n = Findlocation("mine_exit");
			DeleteAttribute(&locations[n], "mine_bandits");
			LocatorReloadEnterDisable("mine_exit", "reload1_back", false);
			pchar.quest.Saga_MineAttack_07.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_07.win_condition.l1.location = "Mine";
			pchar.quest.Saga_MineAttack_07.function = "Saga_MineGunAttack";
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("mine_exit", "reload2_back", true);
			LAi_LocationDisableOfficersGen("mine_exit", false); // офицеров пускать
			n = Findlocation("mine");
			locations[n].models.always.Gun = "mortair";
			Locations[n].models.always.Gun.locator.group = "goto";
			Locations[n].models.always.Gun.locator.name = "fire"; // орудие - к бою!
			Locations[n].hidden_sound = true;
		break;
		
		case "mine_attack_27":
			dialog.text = "Of, çok mu geç kaldık? "+pchar.name+"?";
			link.l1 = "Jan, lanet olsun! Neden bu kadar geciktin? Ekibim az önce ağır bir darbe aldı!";
			link.l1.go = "mine_attack_28";
		break;
		
		case "mine_attack_28":
			dialog.text = "Şu lanet ahşap çit gerçekten de sağlam çıktı. Güç kullanarak kırdık... Gürültünü ve kargaşayı duyduk. Belli ki burayı güzelce temizlemişsin! Yerle bir olup yanıyor!";
			link.l1 = "Randolf'un işleri... Keşke görebilseydin, nihayet göğüs göğüse çarpışmaya girmeden önce kaç alçağı toprağa verdik!";
			link.l1.go = "mine_attack_29";
		break;
		
		case "mine_attack_29":
			dialog.text = "Caramba! Şapka çıkarıyorum sana, "+pchar.name+" . Aferin! Şimdi, kayıplar hakkında... Savaşta olduğun sürece her zaman olur böyle şeyler.";
			link.l1 = "Şimdi yapmamız gereken, madenin kendisini temizlemek. İçeride saklanan hayatta kalanlar olabilir.";
			link.l1.go = "mine_attack_30";
		break;
		
		case "mine_attack_30":
			dialog.text = "Hadi gidelim, sadece ikimiz. Orada neler oluyor görelim.";
			link.l1 = "Harika bir plan gibi geliyor!";
			link.l1.go = "mine_attack_31";
		break;
		
		case "mine_attack_31":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCheckMinHP(npchar, 10, true, "");
			TakeNItems(npchar, "potion2", 8); 
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4", "Mine_mines", "reload", "reload1", "", -1);
			LAi_LocationDisableOfficersGen("Mine_mines", true);//офицеров не пускать
			pchar.quest.Saga_MineAttack_08.win_condition.l1 = "locator";
			pchar.quest.Saga_MineAttack_08.win_condition.l1.location = "mine";
			pchar.quest.Saga_MineAttack_08.win_condition.l1.locator_group = "reload";
			pchar.quest.Saga_MineAttack_08.win_condition.l1.locator = "reload4";
			pchar.quest.Saga_MineAttack_08.function = "Saga_MineAttackMines";
		break;
		
		case "mine_attack_32a":
			dialog.text = "Henüz tüm madeni aramadık! Eminim ki burada hâlâ birkaç serseri daha saklanıyor!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "mine_attack_32a";
		break;
		
		case "mine_attack_32":
			dialog.text = "Sanırım başka bir alçak kalmadı...";
			link.l1 = "Jan, buraya sadece durumu anlamak için geldiğimizi sanıyordum...";
			link.l1.go = "mine_attack_33";
		break;
		
		case "mine_attack_33":
			dialog.text = "Ha-ha, peki, bunun özel bir keşif, kanlı bir keşif olacağını söylememiştim... Uzun zamandır böyle bir ısınma yapmamıştım! Artık herkes emin olabilir ki bu madenden tek bir alçak bile kaçamadı!";
			link.l1 = "Peki şimdi ne yapacağız, Jan?";
			link.l1.go = "mine_attack_34";
		break;
		
		case "mine_attack_34":
			dialog.text = "Ne demek, şimdi ne yapacağız? Altın ve gümüş arayacağız tabii ki. Jackman'ın burada böyle bir siper kurmasının sebebi canı sıkıldığı için değildi. Buraya tam bir garnizon yerleştirmiş. Madendeki köleleri gördün mü? Cevheri nerede sakladıklarını bulmalısın.";
			link.l1 = "Pekâlâ. O zaman sen köleleri sorgula, ben de yukarı çıkıp kamptaki bütün evleri arayacağım, belki bir şey bulurum.";
			link.l1.go = "mine_attack_35";
		break;
		
		case "mine_attack_35":
			dialog.text = "Seni yakaladım! Hadi, şimdi hareket et!";
			link.l1 = "...";
			link.l1.go = "mine_attack_36";
		break;
		
		case "mine_attack_36":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_SetImmortal(npchar, true);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("mine", "reload1", true);
			LocatorReloadEnterDisable("mine", "reload6", true);//закрыть выходы с рудника
			pchar.quest.Saga_Mine_letter.win_condition.l1 = "item";
			pchar.quest.Saga_Mine_letter.win_condition.l1.item = "letter_mine";
			pchar.quest.Saga_Mine_letter.function = "Saga_FindMineLetter";
			NextDiag.CurrentNode = "mine_attack_36a";
		break;
		
		case "mine_attack_36a":
			dialog.text = "Git, dostum. Ve şu zavallı barakaları alt üst et!";
			link.l1 = "Yoldayım!";
			link.l1.go = "exit";
			NextDiag.TempNode = "mine_attack_36a";
		break;
		
		case "mine_attack_37":
			dialog.text = "Ha-ha! "+pchar.name+", benimle birlikte bu madeni alt üst etmeye gönüllü olman harika! Bu, gerçekten şanslı bir yıldızın altında doğduğunun bir başka açık göstergesi.";
			link.l1 = "Altın buldun mu?";
			link.l1.go = "mine_attack_38";
		break;
		
		case "mine_attack_38":
			dialog.text = "Evet, kahretsin! Altın değil, gümüş, hem de hatırı sayılır bir yığın. Bir gün daha geç kalsaydık, kampı çoktan boşaltmış olurlardı. O yüzden burada bu kadar serseri vardı - hepsi koruma ekibiydi.\nSenin sayende tam zamanında yetiştik. Sensiz hâlâ adam toplamaya çalışıyor olurdum. Tebrikler, ortak!";
			link.l1 = "Ha! Anladım... Ne kadar gümüşümüz var?";
			link.l1.go = "mine_attack_39";
		break;
		
		case "mine_attack_39":
			dialog.text = "Yaklaşık dört bin birimimiz var. Bunu ikiye böleceğiz – yarısı bana, yarısı sana, anlaştığımız gibi.";
			link.l1 = "Harika! Bu mallardan bir yığın para kazanabiliriz!";
			link.l1.go = "mine_attack_40";
		break;
		
		case "mine_attack_40":
			dialog.text = "Kesinlikle... Değerli bir şey bulabildin mi?";
			link.l1 = "Hayır. Bu barakalarda tek bir dublon bile yok. Ama bazı evraklar buldum. Okuyunca öğrendim ki bu madenin sahibi Port Royal'den Lawrence Beltrope adında biriymiş.";
			link.l1.go = "mine_attack_41";
		break;
		
		case "mine_attack_41":
			dialog.text = "Gerçekten mi? Şu belgeleri bir göreyim...";
			link.l1 = "Buyurun.";
			link.l1.go = "mine_attack_42";
		break;
		
		case "mine_attack_42":
			RemoveItems(pchar, "letter_mine", 1);
			dialog.text = "(okuyor)... Peki... Beltrope mi? Bu soyadı bir yerden hatırlıyorum. Ah, evet! Thomas Beltrope! Bu ilginç... Tamam, Blueweld'e döndüğümde bununla ilgileneceğim. Eğer sakıncası yoksa bu belgeleri yanımda tutacağım?";
			link.l1 = "Hiç de değil. Onlara hiçbir şekilde ihtiyacım yok.";
			link.l1.go = "mine_attack_43";
		break;
		
		case "mine_attack_43":
			dialog.text = "Güzel. Şimdi en güzel kısmı kaldı, gümüşü gemilere taşıyacağım. Miskitolar bu konuda bize yardım edecekler. Bir araba ayarlayacağız... Bu arada, sen git biraz dinlen, "+pchar.name+" . Bunu herkesten çok sen hak ediyorsun!";
			link.l1 = "Teşekkürler, Jan. Şu tepenin üzerinde kamp kuracağız, bu is kokusu çekilecek gibi değil. Evet, bir de şu kulübelerdeki yangınları söndürmemiz gerek. Kim bilir, belki bir gün işimize yararlar...";
			link.l1.go = "mine_attack_44";
		break;
		
		case "mine_attack_44":
			dialog.text = "Madeni sahiplenmeyi mi düşünüyorsun? Ha-ha! Ben de bu fikri düşündüm ama yağmalamak başka, sahiplenmek bambaşka bir iş. Dostum, zaten buranın bir sahibi var. İngiliz yetkililerle başımız derde girebilir.\nAyrıca konuştuğum köleler, buradaki tüm damarların neredeyse tamamen tükenmiş olduğunu söylediler – buradan daha önce defalarca büyük miktarda gümüş çıkarılmış. Korkarım bu madenin işi bitmiş.";
			link.l1 = "Hm... Göreceğiz. Belki de her şey tükenmemiştir. Peki, gerçekten biraz dinlenmeliyim. Sonra görüşürüz, Jan";
			link.l1.go = "mine_attack_45";
		break;
		
		case "mine_attack_45":
			dialog.text = "Devam et. Hiçbir şey için endişelenme. Geri kalan her şeyi biz hallederiz.";
			link.l1 = "...";
			link.l1.go = "mine_attack_46";
		break;
		
		case "mine_attack_46":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "rld", "attack1", "Saga_MineWaitTime", -1);
			n = Findlocation("mine");
			DeleteAttribute(&locations[n], "hidden_sound");
			DeleteAttribute(&locations[n], "hidden_fire");
			n = Findlocation("mine_exit");
			DeleteAttribute(&locations[n], "models.always.Gun1");
		break;
		
		case "mine_attack_47":
			dialog.text = "Güzelce dinlendin mi, "+pchar.name+"?";
			link.l1 = "Fena değildi... Ama açıkçası, bir meyhaneye gidip içki içmek ve temiz bir yatakta uyumak için can atıyorum.";
			link.l1.go = "mine_attack_48";
		break;
		
		case "mine_attack_48":
			dialog.text = "Hindiler gümüşü kıyıya getirdi ve subaylarımın gözetiminde gemine yüklüyorlar. Artık geri dönebilirsin. Rom, meyhane ve yatak hayalin yakında gerçekleşecek. Ayrıca, beş gün sonra evime uğramanı isterim, hâlâ yapacak çok işimiz var.";
			link.l1 = "Pekala, Jan. Beş gün sonra Blueweld'de görüşürüz! Bol şans!";
			link.l1.go = "mine_attack_49";
		break;
		
		case "mine_attack_49":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4", "none", "", "", "", 15.0);
			LocatorReloadEnterDisable("shore53", "boat", false);
			LocatorReloadEnterDisable("mine", "reload1", false);
			LocatorReloadEnterDisable("mine", "reload6", false);
			LocatorReloadEnterDisable("mine_01", "reload3_back", false);
			LocatorReloadEnterDisable("mine_exit", "reload2_back", false); //открыть выходы с рудника
			LAi_LocationDisableOfficersGen("mine_mines", false); // офицеров пускать
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			SetFunctionTimerCondition("Saga_ReturnFromMine", 0, 0, 5, false); // таймер
			pchar.questTemp.Saga.Mines = "true"; // после Саги рудник будет разрабатываться
			ChangeCharacterComplexReputation(pchar, "fame", 2);
			DoQuestReloadToLocation("Shore53", "goto", "goto6", "");
		break;
		// <-- штурм рудника
		
		case "helensleep":
			dialog.text = "";
			link.l1 = "Jan, bana bağırma. Hadi her şeyi aklı başında insanlar gibi çözelim – unutma, yapacak işlerimiz var!";
			link.l1.go = "helensleep_1";
		break;
		
		case "helensleep_1":
			dialog.text = "Şimdi köpeklerimi üstüne salarım, seni sümüklüböcek! Levasseur'u unut, defol git!";
			link.l1 = "Jan! Beni dinle...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenSleep_SvensonThrowOut");
		break;
		
		case "after_drinking":
			dialog.text = "Hangi fıçı? Helen'e gelince, ona güzel bir ders vereceğim... Şaka yapıyorum Charles, şaka yapıyorum! Durumu anlıyorum, Joanna'ya gelince - umarım bu hikaye onu biraz düşündürür - son zamanlarda özellikle huysuzlaştı, biliyorsun... Eh, hayat böyle. Neyse, Cartagena'da sana bol şans!";
			link.l1 = "Tekrar görüşene dek, Jan.";
			link.l1.go = "exit";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
