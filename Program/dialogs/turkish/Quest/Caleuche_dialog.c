void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Bu kesinlikle bir hata. Lütfen Jason'a bunun ne zaman ve nasıl olduğunu bildirir misin.";
			link.l1 = "Yapacağım.";
			link.l1.go = "exit";
		break;
		
		// шаман карибов Туттуатхапак
		case "Tuttuat":
			dialog.text = "Neden kulübeme geldin, beyaz adam? Tuttuathapak seni değerli bir misafiri olarak görmüyor.";
			if (GetCharacterFreeItem(pchar, "mushket1") || GetCharacterFreeItem(pchar, "mushket2") || GetCharacterFreeItem(pchar, "mushket7"))
			{
				link.l1 = "Selam olsun sana, büyük şaman Tuttuathapak. Yardımın ve öğüdün için geldim. Lütfen bu tüfeği iyi niyetimin bir göstergesi olarak kabul et.";
				link.l1.go = "Tuttuat_1";
			}
			else
			{
				link.l1 = "Selam sana, ulu şaman Tuttuathapak. Yardımın ve öğüdün için geldim.";
				link.l1.go = "Tuttuat_exit";
			}
		break;
		
		case "Tuttuat_exit":
			dialog.text = "Tuttuathapak beyaz adama yardım etmez. Beyaz adamlar kötü insanlardır. Onlar Kızılderilileri öldürür ve topraklarını alır, Kızılderilileri köle yapar. Tuttuathapak beyaz adama hiçbir öğüt vermez. Şimdi git.";
			link.l1 = "Hmm...";
			link.l1.go = "Tuttuat_exit_1";
		break;
		
		case "Tuttuat_exit_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat";
		break;
		
		case "Tuttuat_1":
			if (GetCharacterFreeItem(pchar, "mushket1")) 
			{
				sTemp = "mushket1";
			}
			else 
			{
				if(GetCharacterFreeItem(pchar, "mushket2"))
				{
					sTemp = "mushket2";
				}
				else
				{
					sTemp = "mushket7";
				}
			}
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			Log_Info("You have given: "+XI_ConvertString(sTemp)+"");
			dialog.text = "Ne vereceğini biliyorsun, beyaz adam. Tuttuathapak hediyeni kabul ediyor. Konuşacak. Benden ne öğüt istiyorsun?";
			link.l1 = "Güneydeki uzak bir yerden geldiğini duydum. Bir Hintli muskası var bende, bilgili biri bana bunun nasıl kullanılacağını senin bilebileceğini söyledi.";
			link.l1.go = "Tuttuat_2";
			DelLandQuestMark(npchar);
			DelMapQuestMarkIsland("Dominica");
		break;
		
		case "Tuttuat_2":
			dialog.text = "Mücevheri göster.";
			link.l1 = "Buyurun, büyük şaman.";
			link.l1.go = "Tuttuat_3";
		break;
		
		case "Tuttuat_3":
			PlaySound("interface\important_item.wav");
			dialog.text = "(muska’ya bakarak)... Arkadaşın doğru söylüyor, beyaz adam. Bu muska halkıma aitti, büyük yerlilere, adları Chavin’di. Lanetli, kutsala saygısız, solgun yüzlü bir köpek tapınağı kirletti ve onu buraya getirdi. Tuttuathapak o iti cezalandırdı.";
			link.l1 = "Onu aklından ettin, öyle mi?";
			link.l1.go = "Tuttuat_4";
		break;
		
		case "Tuttuat_4":
			dialog.text = "Beyaz adam, Tuttuathapak'ı bilgisiyle şaşırtıyor. Evet, o alçak herifin aklını sömürdüm. O ve pis adamları hak ettiklerini buldu.";
			link.l1 = "Anlıyorum... Söylesene, şaman, bu muska ne işe yarar? Belki savaşta korur ya da kötü büyülere karşı bir kalkan olur mu?";
			link.l1.go = "Tuttuat_5";
		break;
		
		case "Tuttuat_5":
			dialog.text = "Bu muska sana bir fayda sağlamaz, beyaz kaptan. Onun gücünü kullanamazsın. Sadece kabilemizin büyük şamanları onu nasıl uyandıracağını bilir.";
			link.l1 = "Hmm... Demek ki, bu kadar uzun bir yolculuğu boşuna yapmışım. Ama belki de bu tılsımın gücünü uyandırabilirsin, büyük şaman? Eminim bir anlaşmaya varabiliriz...";
			link.l1.go = "Tuttuat_6";
		break;
		
		case "Tuttuat_6":
			dialog.text = "Muska'yı uyandırsam bile, gücünü uzun süre elinde tutamazsın. Ama sana bir teklifim var, beyaz adam.";
			link.l1 = "Ne tür bir anlaşma?";
			link.l1.go = "Tuttuat_7";
		break;
		
		case "Tuttuat_7":
			dialog.text = "Tapınağımızdan buna benzer üç muska çalındı. Her birinin farklı güçleri var, ama bir araya geldiklerinde çok, çok güçlü olurlar. Üç muskayı da bulup bana getir, seni ödüllendireceğim. Sana sonsuza dek sahip olabileceğin bir güç vereceğim.";
			link.l1 = "Tam olarak anlamadım... Ne tür bir güçten bahsediyorsun?";
			link.l1.go = "Tuttuat_8";
		break;
		
		case "Tuttuat_8":
			dialog.text = "Her şeyi zamanla öğreneceksin. Bana üç muskanın hepsini bulup getir. Hepsi Karayipler’de. Ara, bul onları. Kolayca tanırsın – birbirlerine benziyorlar. Git, beyaz adam. Tuttuathapak bekliyor ve ruhlardan sana yardım etmelerini diliyor.";
			link.l1 = "...";
			link.l1.go = "Tuttuat_9";
		break;
		
		case "Tuttuat_9":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_10";
			pchar.questTemp.Caleuche = "ghostship"; 
			AddQuestRecord("Caleuche", "3");
			pchar.quest.Caleuche_ghostship.win_condition.l1 = "location";
			pchar.quest.Caleuche_ghostship.win_condition.l1.location = "Dominica";
			pchar.quest.Caleuche_ghostship.function = "Caleuche_PrepareGhostship";
		break;
		
		case "Tuttuat_10":
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && Caleuche_CheckAmulet())
			{
				dialog.text = "Git, beyaz adam. İki muska daha bul.";
				link.l1 = "Onları zaten buldum, büyük şaman. İşte, bakın.";
				link.l1.go = "Tuttuat_33";
			}
			else
			{
				dialog.text = "Git, beyaz adam. Diğer iki tılsımı bul.";
				link.l1 = "...";
				link.l1.go = "Tuttuat_10_1";
			}
		break;
		
		case "Tuttuat_10_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_10";
		break;
		
		case "Tuttuat_11":
			dialog.text = "Yine mi buradasın, beyaz adam? Sanki ormanda vahşi bir jaguarla karşılaşmış gibisin.";
			link.l1 = "Daha da kötüsü, büyük şaman. Denize adım attığım anda, birdenbire devasa bir fırtına çıktı ve ölülerden oluşan bir mürettebatın yönettiği bir gemi bana saldırdı! Kaptanları tamamen yenilmezdi. Önce tılsımı elimden aldı ve neredeyse beni öldürüyordu - zar zor kurtuldum. Sonra da gemimi batıracaklardı, mürettebatımdan sadece bir avuç kişi sağ kaldı.";
			link.l1.go = "Tuttuat_12";
			DelLandQuestMark(npchar);
		break;
		
		case "Tuttuat_12":
			dialog.text = "Kötü haber, beyaz adam. Caleuche tekrar öldürücü darbeye hazırlanıyor.";
			link.l1 = "Caleuche mi? O ölümsüz kaptan gemisine Uçan Kalp diyordu. Demek hayalet gemiyi biliyordun ve bana söylemedin? Eğer bu deniz kâbusunun muska peşinde olduğunu bilseydim, asla...";
			link.l1.go = "Tuttuat_13";
		break;
		
		case "Tuttuat_13":
			dialog.text = "Tuttuathapak beyaz kaptanın üzgün olduğunu görüyor. Beyaz kaptan sakin olmalı.";
			link.l1 = "Sakin olmamı mı istiyorsun?! Aklını mı kaçırdın? Böyle bir şeye karşı nasıl hayatta kalabilirim ki!";
			link.l1.go = "Tuttuat_14";
		break;
		
		case "Tuttuat_14":
			dialog.text = "Evet. Sakin ol ve bağırma. Söyle bana – hâlâ benden sonsuza dek seninle kalacak büyük bir güç almak istiyor musun?";
			link.l1 = "Elbette biliyorum. Ama artık muska bende değil.";
			link.l1.go = "Tuttuat_15";
		break;
		
		case "Tuttuat_15":
			dialog.text = "Sana Caleuche'nin kaptanından tılsımı nasıl alacağını öğreteceğim. Bu kolay olmayacak. Ama başarırsan, onun gemisini ödül olarak alırsın, değerli hazineler bulursun, kendi halkın arasında ün kazanırsın ve benden de bir ödül alırsın.";
			link.l1 = "Lanet olsun! O buruşmuş canavarı zevkle yok ederdim! Ama ne kılıç ne de kurşun ona zarar veremiyorsa, onu nasıl alt edebilirim?!";
			link.l1.go = "Tuttuat_16";
		break;
		
		case "Tuttuat_16":
			dialog.text = "Beni dinlemeye hazır mısın, beyaz kaptan?";
			link.l1 = "Evet, ben de buradayım, büyük şaman.";
			link.l1.go = "Tuttuat_17";
		break;
		
		case "Tuttuat_17":
			dialog.text = "Babam genç bir savaşçı olduğunda, beyaz adamlar Uçan Kalp adında bir gemiyle topraklarıma geldiler. Dağlara çıktılar. Efsaneye göre, atalarımızın tapınağı orada gizliymiş. Jaguar savaşçılarının tapınağı. Beyaz adamlar tapınağı ve altını bulup, kadim kutsal bir şeyi kirlettiler. Chavinlerin büyük hazinesini - ölüm tanrısı ve jaguar adamlarının koruyucusu Yum Cimil'in yeşim kafatasını - alıp götürdüler.\nBeyaz adamlar gemilerine döndüler. Daha fazla altın için geri dönmeye karar verdiler, ama adamlardan biri karaya adım atar atmaz korkunç bir acıyla öldü. Yum Cimil kaptanı ve tayfasını lanetledi. Ölümsüz oldular, ama bir daha asla karaya ayak basamadılar. Takviminize göre yarım yüzyıl boyunca, çok uzun kışlar boyunca denizlerde dolaştılar. İşte böyle ortaya çıktı Caleuche.\nBedenleri kurudu, etleri çürüdü, ama yaşamaya devam ettiler. Bir kolunu ya da bacağını kesersen, yeniden çıkar. İkiye bölsen, tekrar bütün olurlar. Gemileri batarsa, suyun altında onarıp tekrar yelken açarlar.";
			link.l1 = "Harika...";
			link.l1.go = "Tuttuat_18";
		break;
		
		case "Tuttuat_18":
			dialog.text = " Caleuche denizcilerin korkulu rüyasıdır. Sebepsiz saldırır ve kesin bir felaketi beraberinde getirir. Karayipler’de pek sık görülmez. Anavatanımın kıyılarında dolaşmayı tercih eder. Sanırım laneti kaldırmak istiyor. Ama asla bunu başaramayacak.";
			link.l1 = "Neden? Laneti kaldırmak için ne yapmak gerekiyor?";
			link.l1.go = "Tuttuat_19";
		break;
		
		case "Tuttuat_19":
			dialog.text = "Yeşim kafatası. Yum Cimil'in tapınağına, jaguar savaşçılarının mabedine geri götürülmeli. Birkaç tapınak var. Kabilemin yaşlıları, Karayipler'de küçük bir adada bir tanesinin olduğunu söyler. Caleuche bu yüzden oraya yelken açtı. Kafatası tapınağa konduğunda, Yum Cimil'in büyüsü bozulur, onlar ölümlü olur ve artık yaralarını iyileştiremezler.";
			link.l1 = "Ha! Büyük ihtimalle, kafatasını geri getirmeyecekler! Neden getirsinler ki, hem ölümsüz hem de yenilmezler? Üstelik, karaya ayak basmalarına izin yoksa, nasıl geri getirsinler ki, değil mi?";
			link.l1.go = "Tuttuat_20";
		break;
		
		case "Tuttuat_20":
			dialog.text = "Kafatası onlarda değil. Kaptan onu atalarımın topraklarında attı, jaguar adamlarının tapınağından döndüğünde. Yeşim altın değildir, beyaz adamın ona ihtiyacı yoktu, kafatasının gözlerinden o güzel yeşil taşı alamadı. Ve böylece onu attı. Bir denizci onu yerden aldı, lanet ona dokunmadı\nDenizci, Caleuche tayfasının neye dönüştüğünü görünce kaçtı. Köyümüze geldi. Babam o denizciyi ve Yum Cimil'in kafatasını gördü. Sonra beyaz adam kuzeye, kıyı boyunca gitti ve kafatasını da yanında götürdü.";
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				if (CheckAttribute(pchar, "questTemp.Caleuche.SolomonSkul"))
				{
					link.l1 = "Yeşil taşlarla göz çukurlarında bir yeşim kafatası mı? Onu ellerimde tuttum, düşünebiliyor musun? Onu bizzat Solomon'a verdim. Ama o, kızıyla birlikte Avrupa'ya gitti ve anlaşılan kafatasını da yanında götürdü.";
				}
				else
				{
					link.l1 = "Yeşil taşlarla süslenmiş bir yeşim kafatası mı? Kahretsin... Ben... Ben onu kendi ellerimle tuttum! Ve onu bir Portekizliye sattım... Merriman, ya da öyle bir şeydi... Evet, ona öyle diyordu - Yum Cimil'in kafatası! Ona deli gibi sahip olmak istiyordu! Bunun için yarım milyon peso ödedi!";
				}
				link.l1.go = "Tuttuat_21_1";
			}
			else
			{
				link.l1 = "Yeşil taşlarla süslenmiş göz çukurları olan bir yeşim kafatası mı? Yani bulmam gereken şey bu mu? Ama o denizci elli yıl önce ormanda ölmüş olabilir, kafatası da sonsuza dek kaybolmuş olabilir!";
				link.l1.go = "Tuttuat_21_2";
			}
		break;
		
		case "Tuttuat_21_1":
			dialog.text = "Kafatasının Karayipler'de olduğunu biliyorum. Caleuche burada tesadüfen bulunmuyor. Son altı aydır, sık sık adada görülüyor. Eskiden, uzun kışlar boyunca orada değildi. Caleuche'nin kaptanı, jaguar adamların eserini hissedebiliyor. Seni ve gemini de bu şekilde buldu.";
			link.l1 = "Yani, doğru mu anladım, bu kafatasını tekrar bulmam mı gerekiyor? Peki, sonra onunla ne yapmam isteniyor?";
			link.l1.go = "Tuttuat_22";
		break;
		
		case "Tuttuat_21_2":
			dialog.text = "Kafatası burada, Karayipler'de olmalı. Caleuche burada tesadüfen bulunmuyor. Son altı aydır sık sık adada görülüyor. Ondan önce, uzun kışlar boyunca burada değildi. Caleuche'nin kaptanı jaguar adamların eserini hissedebiliyor. Seni ve gemini de böyle buldu.";
			link.l1 = "Yani, doğru mu anladım, bu kafatasını tekrar bulmam mı gerekiyor? Peki, sonra onunla ne yapmam isteniyor?";
			link.l1.go = "Tuttuat_22";
		break;
		
		case "Tuttuat_22":
			dialog.text = "Öncelikle, konuştuğumuz iki tılsımı bulmalısın. Onlar olmadan hiçbir şey yapamazsın. Tılsımlar sana jaguar adamlarına ve karşılaşacağın her düşmana karşı duracak gücü verir.";
			link.l1 = "Jaguar adamlarına karşı mı durmak? Neyden bahsediyorsun?";
			link.l1.go = "Tuttuat_23";
		break;
		
		case "Tuttuat_23":
			dialog.text = "Yeşim kafatasını götürmen gereken tapınak, Karayipler'de ıssız bir adada. Orayı jaguar adamlar koruyor. Hepsi ölmüştü, ama şimdi yeniden yaşıyorlar. Tılsım olmadan onların yanından geçemezsin. Jaguar adamlar hayattayken vahşi savaşçılardı, ölümden sonra ise neredeyse yenilmez oldular. Onlara gücünü bizzat Yum Cimil veriyor.";
			link.l1 = "Ölüler mi? Yine mi? Şanslıyım doğrusu...";
			link.l1.go = "Tuttuat_24";
		break;
		
		case "Tuttuat_24":
			dialog.text = "Neden bu kadar şaşırdın, beyaz kaptan? Yum Cimil ölümün tanrısıdır, yeşim kafatası ise ölüler ve diriler üzerinde güç verir. Karayipler. Onu jaguar adamlar korur. Muska olmadan onların yanından geçemezsin. Muska ile tapınağa girip hayatta kalabilirsin, kafatasını orada bırakır, sonra Caleuche’yi bulur, kaptanını yener ve senden aldığı muskayı geri alırsın.";
			link.l1 = "Ve Caleuche'nin kaptanının bu tılsımlara neden ihtiyacı var?";
			link.l1.go = "Tuttuat_25";
		break;
		
		case "Tuttuat_25":
			dialog.text = "Bence o jaguar adamlarının tapınağına gitmek istiyor ve muska ona yardımcı olacak sanıyor. Ama yanılıyor olabilirim. Yine de, Caleuche her zaman memleketimden gelen eserlerin peşine düşer. Jaguar adamlarının tapınağının olduğu adanın yakınında seyretti ve anavatanımın kıyılarında dolaştı.";
			link.l1 = " Peki o ada nerede? ";
			link.l1.go = "Tuttuat_26";
		break;
		
		case "Tuttuat_26":
			dialog.text = "Önce Yum Cimil'in kafatasını ve tılsımları bulacaksın. Sonra ada hakkında konuşuruz.";
			link.l1 = "Peki. Yeşim kafatasını nerede arayabileceğim konusunda bana bir ipucu verebilir misin?";
			link.l1.go = "Tuttuat_27";
		break;
		
		case "Tuttuat_27":
			dialog.text = "Bilmiyorum. Ama burada, Karayipler'de. Tılsımlar da var. Sor. Ara. Bul.";
			link.l1 = "Heh... Peki, deneyeceğim.";
			link.l1.go = "Tuttuat_28";
		break;
		
		case "Tuttuat_28":
			dialog.text = "Ve sen dikkatli ol, beyaz kaptan. Caleuche, Chavin'in eşyalarını hisseder. Muska sende olduğunda, seni arayacak. Seni bulursa, hemen kaç. Eğer yakalarsa, ölüsün.";
			link.l1 = "Bu lanetli gemi inanılmaz derecede hızlı! Şimdiye kadar gördüğüm tüm gemilerden neredeyse iki kat daha hızlı. Ama rüzgara karşı yol alırken zorlandığını fark ettim.";
			link.l1.go = "Tuttuat_29";
		break;
		
		case "Tuttuat_29":
			dialog.text = "Caleuche lanetli bir gemi - bu yüzden bu kadar hızlı. Kaçmak zor. Caleuche'den daha hızlı bir gemin olmalı. Yoksa ölürsün. Muska'yı bulduğunda, bana getir. Muska'yı gemide tutma.";
			link.l1 = "Zaten aldım. Hikayeniz için teşekkür ederim, büyük şaman. Artık gitme vakti benim için.";
			link.l1.go = "Tuttuat_31";
		break;
		
		case "Tuttuat_31":
			dialog.text = "Ruhlardan sana yardım etmelerini ve seni Caleuche'den korumalarını diliyorum.";
			link.l1 = "...";
			link.l1.go = "Tuttuat_32";
		break;
		
		case "Tuttuat_32":
			DialogExit();
			LocatorReloadEnterDisable("Shore27", "boat", false);
			npchar.dialog.currentnode = "Tuttuat_10";
			pchar.questTemp.Caleuche = "mayak"; 
			AddQuestRecord("Caleuche", "6");
			if (CheckAttribute(pchar, "questTemp.Caleuche.Amuletmaster") && pchar.questTemp.Caleuche.Amuletmaster == "Santiago_Lightman") {AddLandQuestMark(characterFromId("Santiago_Lightman"), "questmarkmain");}
			if (CheckAttribute(pchar, "questTemp.Caleuche.Amuletmaster") && pchar.questTemp.Caleuche.Amuletmaster == "BasTer_Lightman") {AddLandQuestMark(characterFromId("BasTer_Lightman"), "questmarkmain");}
		break;
		
		case "Tuttuat_33":
			if (CheckCharacterItem(pchar, "kaleuche_amulet2")) RemoveItems(pchar, "kaleuche_amulet2", 1);
			else RemoveItems(pchar, "kaleuche_amulet3", 1);
			Log_Info("You have given the amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "(bakıyor) Evet, işte bu. İkinci Chavin tılsımı. İyisin. Hâlâ bir tılsım daha bulman gerekiyor.";
			link.l1 = "Bunu hatırlıyorum, şaman. Yakında elinde olacak.";
			link.l1.go = "Tuttuat_34";
			DelLandQuestMark(npchar);
			DelMapQuestMarkIsland("Dominica");
		break;
		
		case "Tuttuat_34":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_35";
			AddQuestRecord("Caleuche", "22");
			if (!Caleuche_CheckAmulet())
			{
				if (GetCharacterIndex("Map_Caleuche") != -1)
				{
					sld = characterFromId("Map_Caleuche");
					sld.lifeday = 0;
					Map_ReleaseQuestEncounter("Map_Caleuche");
				}
			}
		break;
		
		case "Tuttuat_35":
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && Caleuche_CheckAmulet())
			{
				dialog.text = "Git, beyaz adam. Bir muska daha bul.";
				link.l1 = "Zaten bende var, büyük şaman. Al, bak istersen.";
				link.l1.go = "Tuttuat_36";
			}
			else
			{
				dialog.text = "Git, beyaz adam. Bir muska daha bul.";
				link.l1 = "...";
				link.l1.go = "Tuttuat_35_1";
			}
		break;
		
		case "Tuttuat_35_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_35";
		break;
		
		case "Tuttuat_36":
			if (CheckCharacterItem(pchar, "kaleuche_amulet2")) RemoveItems(pchar, "kaleuche_amulet2", 1);
			else RemoveItems(pchar, "kaleuche_amulet3", 1);
			Log_Info("You have given the amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "(bakıyor) Evet, işte bu. Üçüncü Chavins tılsımı. İyisin. Yum Cimil’in hizmetkârı olan ölü jaguar savaşçılarının yanından geçmek için gereken tüm tılsımları buldun.";
			link.l1 = "Şimdi, anladığım kadarıyla, yeşim kafatasına ihtiyacım olacak mı?";
			link.l1.go = "Tuttuat_37";
			DelLandQuestMark(npchar);
			DelMapQuestMarkIsland("Dominica");
		break;
		
		case "Tuttuat_37":
			dialog.text = "Doğruyu söylüyorsun. Yum Cimil'in yeşim kafatası. Onu Chavin'in tapınağına götürmelisin. O zaman Caleuche sonsuza dek gücünü kaybedecek.";
			link.l1 = "Tuttuathapak, lütfen söyle, nerede aramalıyım? Bir fikrin var mı?";
			link.l1.go = "Tuttuat_38";
		break;
		
		case "Tuttuat_38":
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				dialog.text = "Hayır. En son yeşim kafatasını nerede gördüğünü düşün. Kime verdiğini hatırla. Oradan aramaya başla.";
				link.l1 = "Pekala, büyük şaman. Elimden gelen her şeyi yapacağım.";
				link.l1.go = "Tuttuat_39";
			}
			else
			{
				dialog.text = "Yum Cimil’in kafatasıyla ilgilenen beyaz bir büyücü var. Onu arıyor. Hatta köyümüze bile geldi. Duyduğuma göre büyücü, Hollanda adasında bir evde yaşıyor. Büyücüyü Hollanda adasında bul, belki bir şeyler öğrenirsin.";
				link.l1 = "Pekala, ulu şaman. Elimden gelen her şeyi yapacağım.";
				link.l1.go = "Tuttuat_39";
			}
		break;
		
		case "Tuttuat_39":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_40";
			AddQuestRecord("Caleuche", "23");
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				if (CheckAttribute(pchar, "questTemp.Caleuche.SolomonSkul")) sTemp = "I'll start with Curacao, where I handed it over to Solomon. Maybe I'll find some clue - to find out what happened to the skull.";
				else sTemp = "I'll start with visiting Curacao - there I've sold the jade skull to Joachim Merriman.";
			}
			else sTemp = "Tuttuathapak told me, that a 'white warlock' showed interest in the jade skull, and adviced seeking for him on Dutch islands. Who might that be?";
			AddQuestUserData("Caleuche", "sText", sTemp);
			if (GetCharacterIndex("Map_Caleuche") != -1)
			{
				sld = characterFromId("Map_Caleuche");
				sld.lifeday = 0;
				Map_ReleaseQuestEncounter("Map_Caleuche");
			}
			pchar.questTemp.Caleuche = "skul";
			pchar.quest.Caleuche_villemstad.win_condition.l1 = "location";
			pchar.quest.Caleuche_villemstad.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Caleuche_villemstad.function = "Caleuche_CreateMonk";
			AddMapQuestMarkCity("Villemstad", false);
		break;
		
		case "Tuttuat_40":
			dialog.text = "Git, beyaz adam. Yum Cimil’in yeşim kafatasını bul.";
			if (pchar.questTemp.Caleuche == "island")
			{
				link.l1 = "Burada, büyük şaman, bir bak.";
				link.l1.go = "Tuttuat_45";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "Tuttuat_40_1";
			}
		break;
		
		case "Tuttuat_40_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_40";
		break;
		
		case "Tuttuat_41":
			dialog.text = "Git, beyaz adam. Yum Cimil'in yeşim kafatasını bul.";
			link.l1 = "Bunu yapamayacağım diye korkuyorum. Büyücüyü buldum, ama son anda kafatasıyla birlikte kaçıp gitti. Şu anda nerede olabileceği hakkında hiçbir fikrim yok.";
			link.l1.go = "Tuttuat_42";
		break;
		
		case "Tuttuat_42":
			dialog.text = "Bu çok kötü, beyaz adam. Artık tapınağı geçemeyecek ve Caleuche'yi yenemeyeceksin. Sana hiçbir hediye vermiyorum. Şimdi git.";
			link.l1 = "...";
			link.l1.go = "Tuttuat_43";
		break;
		
		case "Tuttuat_43":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_44";
		break;
		
		case "Tuttuat_44":
			dialog.text = "Şimdi git, beyaz adam.";
			link.l1 = "...";
			link.l1.go = "Tuttuat_44_1";
		break;
		
		case "Tuttuat_44_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_40";
		break;
		
		case "Tuttuat_45":
			dialog.text = "(bakıyor) Evet, tam olarak bu. Çok güzel. Ve çok korkutucu.";
			link.l1 = "Sure... But what's more interesting – I crossed the entire Caribbean Sea from Cuba to Dominica, and the Caleuche never tried to attack me when I had this skull; I didn't even see it. Yet when I was carrying amulets to you, it constantly hunted me down – as soon as I set sail, it found me within a few hours.";
			link.l1.go = "Tuttuat_46a";
			DelLandQuestMark(npchar);
		break;
		
		case "Tuttuat_46a":
			dialog.text = "Bence Caleuche kafatasından korkuyor ya da onu hissedemiyor. Başka bir açıklamam yok. Belki de Yum Cimil yeşim kafatasını Caleuche için lanetin yanı sıra çok tehlikeli yaptı. Belki de kaptanın halkımın üç tılsımını bu kadar çok istemesinin nedeni buydu. Yum Cimil'in büyüsünü nasıl kontrol edeceğine dair bilgi edinmek için.";
			link.l1 = "Yani, yeşim kafatası gemimde olduğu sürece, Caleuche'nin saldırılarından korkmama gerek yok mu?";
			link.l1.go = "Tuttuat_46b";
		break;
		
		case "Tuttuat_46b":
			dialog.text = "Aynen öyle, solgun yüzlü. Kendi gözlerinle görüyorsun.";
			link.l1 = "Çok iyi! O halde, büyük bir geminin komutasını alabilir, düzgün bir tayfa toplayıp o yaşayan ölü adamın üzerindeki büyü kalkınca ona güzel bir karşılama hazırlayabilirim; üstelik beni daha önce yakalamasından da korkmam gerekmeyecek...";
			link.l1.go = "Tuttuat_46c";
		break;
		
		case "Tuttuat_46c":
			dialog.text = "";
			link.l1 = "...bu büyüyle ilgili olarak, bu yeşim kafatasını nereye götürmeliyim?";
			link.l1.go = "Tuttuat_46";
		break;
		
		case "Tuttuat_46":
			dialog.text = "Bunu Chavin'in tapınağına götürmeli ve yolculuğunu tamamlamalısın. Sana bir hikaye anlatmak istiyorum. Dinlemeye hazır mısın, beyaz adam?";
			link.l1 = "Kulaklarım her zaman senin bilgeliğine açıktır, Tuttuathapak.";
			link.l1.go = "Tuttuat_47";
		break;
		
		case "Tuttuat_47":
			dialog.text = "Atalarımın efsanelerinde anlatıldığına göre, çok uzun zaman önce, beyaz yüzlü adamlar henüz topraklarımıza gelmemişken, Chavinlerin büyük reisi çok, çok büyük bir kano yaptırıp bir grup savaşçıyla birlikte onu birçok adanın olduğu diyara göndermiş. Büyük reisin oğlu onlara önderlik etmiş ve aralarında yüksek şamanlardan biri de varmış. Birçok adanın olduğu diyarda, terkedilmiş bir yer bulup oraya yerleşmişler, sadece büyük atalarımızın inşa edebileceği kadar görkemli bir Yum Cimil tapınağı kurmuşlar\nHaberci dönenler iyi haberler getirmiş ama ne reisin oğlunu, ne şamanı, ne de savaşçıları bir daha kimse görmemiş. Efsaneye göre, orada kalıp yaşamışlar ama en bilge şaman ruhlarla konuşmuş ve orada artık hiç kimsenin yaşamadığını, Yum Cimil’in o topraklara hükmettiğini söylemiş\nBirçok adanın olduğu diyar, Karayiplerdir, beyaz adam. Yum Cimil’in tapınağı, ne beyazların ne de Kızılderililerin yaşadığı bir adadadır. Orada yalnızca Yum Cimil’in hizmetkarları, Chavinavi’ler, hâlâ tapınağın koridorlarını bekler.";
			link.l1 = "   Peki bu ada nerede? ";
			link.l1.go = "Tuttuat_48";
		break;
		
		case "Tuttuat_48":
			dialog.text = "Anlattıklarından anladığım kadarıyla, bu köyün bulunduğu adadan, soluk yüzlülerin 'kuzey' dediği yönde, üç adanın ortasında küçük bir ada var ve dördüncü tarafında ise büyük su — okyanus bulunuyor.";
			link.l1 = "Hmm... Dominika'nın kuzeyinde, adalardan oluşan bir üçgenin içinde, tam okyanusun kenarında mı? Vay canına, orası epey geniş bir deniz! Kimsenin adını bile duymadığı küçücük bir adayı orada nasıl bulacağım ki?";
			link.l1.go = "Tuttuat_49";
		break;
		
		case "Tuttuat_49":
			dialog.text = "Kesin olarak söyleyemem. Ama başka bir hikaye daha biliyorum. Bunu kardeşlerinden duymuş olabilirsin. Yaklaşık yirmi kış önce, bir beyaz adam o adayı buldu. Yanında bir kadın ve yaşlı bir adamla birlikte Yum Cimil’in tapınağına girdi ve güçlü bir eser aldı – Yükselen Güneş’in Küresi. Adanın kıyılarında, solgun yüzlü kaptana Caleuche saldırdı.\nSolgun yüzlü adam akıllıydı. Caleuche’nin kaptanını ve mürettebatını yükselen güneşle kör etti. Caleuche’nin laneti zayıfladı ve kaptan onu batırdı, fakat Yükselen Güneş’in Küresi yok oldu. O solgun yüzlü adamı bulursan, sana adanın yerini söyleyecek.";
			if (CheckAttribute(pchar, "questTemp.NatanStory")) link.l1 = "Ha! Sanırım o 'solgun yüzlü adamı' tanıyorum... Anlatılanlar fazlasıyla benziyor. Yani, Caleuche batırılmış mı?";
			else link.l1 = "Hmm... Demek ki, Caleuche batırılmış?";
			link.l1.go = "Tuttuat_50";
		break;
		
		case "Tuttuat_50":
			dialog.text = "Evet, ama lanet onları ölümden koruyor. Onlar bunu düzelttiler ve sonsuz yolculuklarına devam ettiler.";
			link.l1 = "Pekala, anladım. Ama tapınakta ne yapmalıyım? Kafatasını nereye koyacağım? Orayı koruyan jaguar savaşçılarını nasıl alt edebilirim? Eğer onlar da o büyücü Merriman’ın çağırdığı Chavinavi’ler gibiyse, oraya tek başıma gitmek delilik olur – her biri on asker kadar güçlü.";
			link.l1.go = "Tuttuat_51";
		break;
		
		case "Tuttuat_51":
			dialog.text = "Hayır, değiller. Kafataslı beyaz büyücü tarafından çağrılan Chavinavi'ler zayıftır. Yum Cimil'in bizzat çağırdıklarından çok daha güçsüzler. Onlara asla zarar veremezsin, ama onlar silahlarının tek dokunuşuyla seni öldürürler.";
			link.l1 = "Dur bir dakika - o 'solgun yüzlü adam' tapınağa nasıl girdi ve eseri nasıl çaldı?";
			link.l1.go = "Tuttuat_52";
		break;
		
		case "Tuttuat_52":
			dialog.text = "O ilk solgun yüzlü adam tapınağa girmeden önce, tapınak ölü ataların ruhları tarafından korunuyordu. Solgun yüzlü adam güçlü bir savaşçıydı ve onları yendi. Yükselen güneşin küresini çaldığında, Yum Cimil öfkelendi. Solgun yüzlü adamın üzerine ateş ve kükürt yağdırdı ve tapınağı neredeyse yok etti, ama adam eseriyle kaçmayı başardı. Şimdi Yum Cimil, tapınağı koruması için yenilmez jaguar savaşçılarını çağırdı.";
			link.l1 = "Harika! Peki, oraya gizlice nasıl gireceğim, söyler misin?";
			link.l1.go = "Tuttuat_53";
		break;
		
		case "Tuttuat_53":
			dialog.text = "I help you, white man. I give you two Chavin amulets you bring me. I will speak to the ancestor spirits and empower the amulet. When you have one with you, you can fight jaguar warriors like common soldiers; you will be like one of them, though very strong. The amulet will protect you and give your weapon the power to harm the Chavinavi of the temple.";
			link.l1 = "Muska   gerçekten   işe   yarayacak   mı,   emin   misin?";
			link.l1.go = "Tuttuat_54";
		break;
		
		case "Tuttuat_54":
			dialog.text = "I know. I speak to the ancestors. I am a great shaman. You trust me. You take two amulets. One protects. The other empowers your weapon. You must use one amulet. Which one - you choose. If you do not wear an amulet, you will perish to the jaguar warriors\nAnd remember, at midnight Yum Cimil brings back to life all the warriors you kill. You must figure out the timing so you do not fight them twice, or do so; the spirits tell me that you could.";
			link.l1 = "Anladım.";
			link.l1.go = "Tuttuat_55";
		break;
		
		case "Tuttuat_55":
			dialog.text = "Muska­ları alıyorsun. İşte buradalar. Unutma, güçleri sınırlı. Bir ay sonra etkileri azalır. Unutma, söylemiştim, onların gücünü elinde tutamazsın. Sadece kabilemizin büyük şamanı bu gücü kullanabilir.";
			link.l1 = "Hatırlıyorum. Peki, sadece bir ayım mı var? Bir ay mı?";
			link.l1.go = "Tuttuat_56";
		break;
		
		case "Tuttuat_56":
			dialog.text = "Evet. Yum Cimil tapınağına vardığında, sunağı ve içindeki büyük Akbaba heykelini bulmalısın. Burası tapınağın en önemli kısmı. Buraya Yum Cimil’in yeşim kafatasını yerleştirirsen, Caleuche’nin üzerindeki lanet kalkacak. Sana tekrar saldırdığında, onu sıradan bir adam gibi alt edebileceksin. Sonra da senden aldığı tılsımı bana getirirsin.";
			link.l1 = "Condor mu? Ne oldu?";
			link.l1.go = "Tuttuat_57";
		break;
		
		case "Tuttuat_57":
			dialog.text = "Condor, memleketimin dağlarında yaşayan muazzam bir kuştur. Atalarım, memleket hasretiyle tapınağın yakınına bir Condor heykeli dikmişler.";
			link.l1 = "Pekala, onu arayacağım...";
			link.l1.go = "Tuttuat_58";
		break;
		
		case "Tuttuat_58":
			dialog.text = "Dikkatli ol. Tapınakta jaguar savaşçılarından başka birçok tehlike pusuda bekliyor.";
			link.l1 = "Hangi tehlikeler?";
			link.l1.go = "Tuttuat_59";
		break;
		
		case "Tuttuat_59":
			dialog.text = "Kesin olarak bilmiyorum. Kendin gör. Bu bir tuzak da olabilir, sadece bir karışıklık da. Tapınağa girmek zordur. Giriş mühürlü, onu açmanın bir yolunu bulmalısın. Atalarım sadece büyük savaşçılar ve şamanlar değil, aynı zamanda büyük ustalardı. Açmak için düşünmen gerek.";
			link.l1 = "Heh! Kulağa korkutucu geliyor, ama hepsi gelsin! Zaman kaybetmeyeceğim. Hemen yelken açıyorum!";
			link.l1.go = "Tuttuat_60";
		break;
		
		case "Tuttuat_60":
			dialog.text = "Git, beyaz savaşçı. Jaguar savaşçılarına ve Caleuche'ye karşı sana yardım etmesi için ruhları çağıracağım. Unutma, tılsımlar kullanırsan sana yardım edebilirim, yoksa yok olacaksın";
			link.l1 = "Teşekkür ederim, ulu şaman... Bunu gerçekleştireceğim.";
			link.l1.go = "Tuttuat_61";
		break;
		
		case "Tuttuat_61":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_62";
			npchar.greeting = "Tuttuat_3";
			Log_Info("You have received two amulets");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "kaleuche_amulet2");
			GiveItem2Character(pchar, "kaleuche_amulet3");
			// преобразуем амулеты
			ChangeItemDescribe("kaleuche_amulet2", "itmdescr_kaleuche_amulet2_sword");
			ChangeItemDescribe("kaleuche_amulet3", "itmdescr_kaleuche_amulet3_shield");
			sld = ItemsFromID("kaleuche_amulet2");
			AddDescriptor(sld, M_AMULET_TYPE, AMULET_PAGAN);
			aref modifier = AddCallback(sld, CT_COMMON, "KaleucheAmuletAttack");
			modifier.arg0 = 0.25;
			sld.picIndex = 13;
			sld.picTexture = "ITEMS_36";
			sld.groupID = TALISMAN_ITEM_TYPE;
			sld.unique = true;	
			sld.ItemType = "ARTEFACT";
			sld = ItemsFromID("kaleuche_amulet3");
			AddDescriptor(sld, M_AMULET_TYPE, AMULET_PAGAN);
			SetModifierFromSource(sld, HAS + M_CANT_BE_POISONED, true, TALISMAN_ITEM_TYPE);
			SetModifier(sld, M_REDUCE_DAMAGE, 0.25);
			sld.picIndex = 14;
			sld.picTexture = "ITEMS_36";
			sld.groupID = TALISMAN_ITEM_TYPE;
			sld.unique = true;	
			sld.ItemType = "ARTEFACT";
			SetFunctionTimerCondition("Caleuche_TuttuatAmuletOver", 0, 0, 30, false); // таймер
			// делаем доступным Хаэль Роа
			n = FindIsland("KhaelRoa");
			Islands[n].visible = true;
			Island_SetReloadEnableGlobal(Islands[n].id, true);
			Islands[n].reload.l1.radius = 150.0;
			Islands[n].reload.l2.label = "Shore64_1";
			Islands[n].reload.l2.name = "reload_2";
			Islands[n].reload.l2.go = "";
			Islands[n].reload.l2.emerge = "";
			Islands[n].reload.l2.radius = 0.0;
			Islands[n].reload.l2.pic = 0;
			Islands[n].reload.l2.tex = "t1";
			pchar.questTemp.Caleuche = "khaelroa";
			pchar.quest.Caleuche_khaelroa_arrive.win_condition.l1 = "location";
			pchar.quest.Caleuche_khaelroa_arrive.win_condition.l1.location = "KhaelRoa_port";
			pchar.quest.Caleuche_khaelroa_arrive.function = "Caleuche_KhaelRoaArrive";
			AddQuestRecord("Caleuche", "34");
			if (CheckAttribute(pchar, "questTemp.NatanStory")) 
			{
				pchar.questTemp.Caleuche.NatanInfo = "true";
				AddQuestUserData("Caleuche", "sText", "But I have a clue: it seems that white captain, who had visited the temple of the Chavins, is none other than my good friend Nathaniel Hawk. I remember him saying that he had a map of that island in Maroon Town. Guess I will pay Nathan a visit.");
			}
			else AddQuestUserData("Caleuche", "sText", "That's a huge area in the sea, but I have no choice. I'll have to scour it entirely. Shaman said North of Dominica, and not too far so I could steadily move North, it might very well be a bit to the East or West. He also mentioned some Captain that destroyed the undead ship maybe I will be lucky and I might find him one day, alas, he said that I have only one month to hold this power or whatever it is, oh well it is what it is, let the search begin!");
		break;
		
		case "Tuttuat_62":
			if (pchar.questTemp.Caleuche == "regard" && CheckCharacterItem(pchar, "kaleuche_amulet1") && CheckCharacterItem(pchar, "kaleuche_amulet2") && CheckCharacterItem(pchar, "kaleuche_amulet3")) 
			{
				dialog.text = "Ruhlarla konuşurum. Adadaydın, Yum Cimil'in tapınağında. Caleuche'yi ve tılsımı buldun mu?";
				link.l1 = "Haklısınız, büyük şaman. Adayı buldum, tapınağa girdim ve yeşim kafatasını içeriye bıraktım.";
				link.l1.go = "Tuttuat_63";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "Git, beyaz savaşçı.";
				if (CheckAttribute(pchar, "questTemp.Caleuche.AmuletOver"))
				{
					link.l1 = "Tuttuathapak, bak... Kafatasını tapınağa zamanında götüremedim ve tılsımlarının gücü kayboldu.";
					link.l1.go = "Tuttuat_82";
				}
				else
				{
					link.l1 = "...";
					link.l1.go = "Tuttuat_62_1";
				}
			}
		break;
		
		case "Tuttuat_62_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_62";
		break;
		
		case "Tuttuat_63":
			npchar.greeting = "Tuttuat_2";
			pchar.quest.Caleuche_TuttuatAmuletOver.over = "yes"; //снять таймер
			if(IsEquipCharacterByArtefact(pchar, "kaleuche_amulet2")) RemoveCharacterEquip(pchar, TALISMAN_ITEM_TYPE);
			if(IsEquipCharacterByArtefact(pchar, "kaleuche_amulet3")) RemoveCharacterEquip(pchar, TALISMAN_ITEM_TYPE);
			dialog.text = "Caleuche'nin lanetini kaldırdın. Sonrasında seni buldu mu?";
			link.l1 = "Evet. Onunla adada karşılaştık. Onunla dövüştüm ve galip geldim. Artık üç muskanın hepsi bende. Al, hepsi burada.";
			link.l1.go = "Tuttuat_64";
		break;
		
		case "Tuttuat_64":
			RemoveItems(pchar, "kaleuche_amulet1", 1);
			RemoveItems(pchar, "kaleuche_amulet2", 1);
			RemoveItems(pchar, "kaleuche_amulet3", 1);
			Log_Info("You have given three Chavin amulets");
			PlaySound("interface\important_item.wav");
			dialog.text = "Sen hızlı ve güçlü bir savaşçısın, solgun yüzlü. Tuttuathapak beyaz adamları sevmez, ama cesur ve yetenekli bir savaşçıya saygı duyarım. Çok iyi iş çıkardın. Denizleri Caleuche’den kurtardın. Bana üç muska getirdin. Seni ödüllendireceğim.";
			link.l1 = "Bana 'sonsuzca elimde tutabileceğim bir güç' vaat etmiştin, değil mi?";
			link.l1.go = "Tuttuat_65";
		break;
		
		case "Tuttuat_65":
			dialog.text = "Doğru söylüyorsun. Sana o gücü vereceğim. Karayipler'de, benim bildiğim o bitkinin sırrını bilen yok. Dinle beni, solgun yüzlü! Evimde bir şifalı bitki var. Biz ona Manga Rosa deriz. O bitkiyi duydun mu?";
			if (CheckAttribute(pchar, "questTemp.Mangarosa.Tell"))
			{
				link.l1 = "Evet. Onu ellerimde tuttum. Çingeneler ona büyük ilgi gösteriyor. Ve onlardan biri, şifacı Amelia, hatta...";
				link.l1.go = "Tuttuat_66";
			}
			else
			{
				link.l1 = "Hiçbir fikrim yok...";
				link.l1.go = "Tuttuat_66_1";
			}
		break;
		
		case "Tuttuat_66":
			dialog.text = "Şifacı Amelia'yı duydum. Biraz bilgisi var, ama çok değil. Manga Rosa'nın sırrını bilmiyor. Onun tüm gücünü ancak, Manga Rosa'nın buraya getirildiği memleketimden büyük bir şaman kullanabilir.";
			link.l1 = "Hangi güç?";
			link.l1.go = "Tuttuat_67";
		break;
		
		case "Tuttuat_66_1":
			dialog.text = "Bu ot memleketimde yetişir, ama Karayipler'de de bulunabilir. Uzun boylu, açık yeşil bir bitkidir; yaprakları, parmaklarını açmış bir palmiye gibi ve hoş bir kokusu vardır. Onu hemen tanırsın, başka bir şeyle karıştırmazsın. Bu bitkinin sırlarını bilirim. Ondan güç elde edebilirim.";
			link.l1 = "Anlıyorum, ama ne tür bir güç?";
			link.l1.go = "Tuttuat_67";
		break;
		
		case "Tuttuat_67":
			dialog.text = "Manga Rosa iksirleri yapabilirim. Çok güçlü iksirler. Karayipler'de bunları benden başka kimse yapamaz. Benim iksirlerim bir adamı sonsuza dek daha güçlü, daha hızlı, daha zeki, daha keskin gözlü, daha yakışıklı ve daha şanslı yapar. Senin için böyle üç iksir hazırlayacağım.";
			link.l1 = "Çok ilginç!";
			link.l1.go = "Tuttuat_68";
		break;
		
		case "Tuttuat_68":
			dialog.text = "Sen büyük bir savaşçısın, bu yüzden önce seni daha dayanıklı yapacak bir iksir ve seni daha çevik yapacak bir iksir lazım. Üçüncü iksiri ise ilk ikisini yaptıktan sonra sen seçeceksin. Ama bunları hazırlamam için bana Manga Rosa getirmelisin – bende hiç yok.";
			link.l1 = "Manga Rosa'yı nerede aramalıyım?";
			link.l1.go = "Tuttuat_69";
		break;
		
		case "Tuttuat_69":
			dialog.text = "Manga Rosa, Karayipler'de nadir bulunan bir ottur. İnsanların pek uğramadığı yerlerde yetişir. Akılsızlar onu toplar, kurutur ve içerler. Hem de çok akılsızlar. SAKIN İÇME! Gücünü boşa harcamış olursun... Ormanları ve koyları, aptalların ayak basmadığı gizli yerleri ara. Dikkatlice bak. Her iksir için beş Manga Rosa sapına ihtiyacım var.";
			link.l1 = "Pekala, büyük şaman. Yeterince Manga Rosa bulunca sana geri döneceğim.";
			link.l1.go = "Tuttuat_70";
		break;
		
		case "Tuttuat_70":
			dialog.text = "Git, beyaz savaşçı. Bana Manga Rosa'yı getir. Pişman olmayacaksın. İksirlerim en iyisidir. Ruhlara, arayışında sana yardım etmelerini söyleyeceğim.";
			link.l1 = "Teşekkürler! Görüşürüz, şaman!";
			link.l1.go = "Tuttuat_71";
		break;
		
		case "Tuttuat_71":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_72";
			pchar.questTemp.Caleuche = "mangarosa";
			pchar.questTemp.Caleuche.Mangarosa = 0;
			AddQuestRecord("Caleuche", "41");
		break;
		
		case "Tuttuat_72":
			dialog.text = "İksir için beş dal Manga Rosa getirdin mi?";
			if (GetCharacterItem(pchar, "cannabis7") >= 5)
			{
				link.l1 = "Evet. İşte ihtiyacın olan beş bitki.";
				link.l1.go = "Tuttuat_73";
			}
			link.l2 = "Henüz değil, ulu şaman. Arayışım sürüyor...";
			link.l2.go = "Tuttuat_72_1";
		break;
		
		case "Tuttuat_72_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_72";
		break;
		
		case "Tuttuat_73":
			RemoveItems(pchar, "cannabis7", 5);
			switch (sti(pchar.questTemp.Caleuche.Mangarosa))
			{
				case 0:
					dialog.text = "Çok iyi. Güneş battıktan sonra yarın gel. Sana reflekslerini ve çevikliğini artıracak iksirler hazırlayacağım.";
					link.l1 = "Pekâlâ, şaman. Yarın akşam geleceğim.";
					link.l1.go = "Tuttuat_74";
					pchar.questTemp.Caleuche.Mangarosa = 1;
				break;
				
				case 1:
					dialog.text = "Çok iyi. Yarın, güneş battıktan sonra gel. Sana dayanıklılığını artıracak iksirler hazırlayacağım.";
					link.l1 = "Pekala, şaman. Yarın akşam geleceğim.";
					link.l1.go = "Tuttuat_74";
					pchar.questTemp.Caleuche.Mangarosa = 2;
				break;
				
				case 2:
					dialog.text = "Çok güzel. Hangi iksiri seçiyorsun? Güç, keskin görüş, zeka, güzellik ya da şans iksiri?";
					link.l1 = "Güç iksiri.";
					link.l1.go = "Tuttuat_77_1";
					link.l2 = "Keskin görüş iksiri.";
					link.l2.go = "Tuttuat_77_2";
					link.l3 = "Zeka iksiri.";
					link.l3.go = "Tuttuat_77_3";
					link.l4 = "Güzellik iksiri.";
					link.l4.go = "Tuttuat_77_4";
					link.l5 = "Şans iksiri.";
					link.l5.go = "Tuttuat_77_5";
				break;
			}
		break;
		
		case "Tuttuat_74":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_75";
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1 = "Timer";
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.hour  = 19.0;
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Caleuche_mangarosa_potion.function = "Caleuche_MangarosaPotion";
		break;
		
		case "Tuttuat_75":
			if (CheckAttribute(pchar, "questTemp.Caleuche.Potion"))
			{
				sTemp = "";
				if (sti(pchar.questTemp.Caleuche.Mangarosa) == 1) sTemp = "  It make your movements faster, and you better fight with fine light weapons.";
				if (sti(pchar.questTemp.Caleuche.Mangarosa) == 2) sTemp = "  It make you more hardy in long journeys, and you better fight with sharp sabers.";
				dialog.text = "İksirin hazır, solgun yüzlü savaşçı. Al bakalım."+sTemp+"";
				link.l1 = "Teşekkür ederim, ulu şaman.";
				link.l1.go = "Tuttuat_76";
			}
			else
			{
				dialog.text = "Henüz hazır değil, beyaz adam. Sonra gel. Beni rahatsız etme.";
				link.l1 = "Peki...";
				link.l1.go = "Tuttuat_75_1";
			}
		break;
		
		case "Tuttuat_75_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_75";
		break;
		
		case "Tuttuat_76":
			if (sti(pchar.questTemp.Caleuche.Mangarosa) > 2)
			{
				dialog.text = "Tüm söz verdiğim iksirleri senin için hazırladım. Artık daha güçlü olacaksın. Mutlu musun?";
				link.l1 = "Evet, büyük şaman. Gerçekten de buna değer bir ödüldü.";
				link.l1.go = "Tuttuat_78";
			}
			else
			{
				dialog.text = "Beş tane daha Manga Rosa sapı bul, bana getir. Sana bir iksir daha yapacağım.";
				link.l1 = "Sana daha fazlasını getireceğim. Görüşürüz!";
				link.l1.go = "Tuttuat_77";
			}
		break;
		
		case "Tuttuat_77":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_72";
			DeleteAttribute(pchar, "questTemp.Caleuche.Potion");
			if (sti(pchar.questTemp.Caleuche.Mangarosa) == 1)
			{
				ChangeItemDescribe("kaleuche_amulet1", "itmdescr_kaleuche_amulet1_potion");
				sld = ItemsFromID("kaleuche_amulet1");
				sld.name = "itmname_kaleuche_amulet1_potion";
				sld.groupID = SPECIAL_ITEM_TYPE;
				sld.picIndex = 15;
				sld.picTexture = "ITEMS_35";
				sld.price = 0;
				sld.Weight = 1.0;
				sld.ItemType = "SUPPORT";
				GiveItem2Character(pchar, "kaleuche_amulet1");
			}
			if (sti(pchar.questTemp.Caleuche.Mangarosa) == 2)
			{
				ChangeItemDescribe("kaleuche_amulet2", "itmdescr_kaleuche_amulet2_potion");
				sld = ItemsFromID("kaleuche_amulet2");
				sld.name = "itmname_kaleuche_amulet2_potion";
				sld.groupID = SPECIAL_ITEM_TYPE;
				sld.picIndex = 15;
				sld.picTexture = "ITEMS_35";
				sld.price = 0;
				sld.Weight = 1.0;
				sld.ItemType = "SUPPORT";
				GiveItem2Character(pchar, "kaleuche_amulet2");
			}
		break;
		
		case "Tuttuat_77_1":
			dialog.text = "Yarın yine gel, her zamanki gibi. Sana daha güçlü olman için bir iksir hazırlarım, böylece büyük bir baltayla daha iyi dövüşürsün.";
			link.l1 = "Pekala.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 31;
		break;
		
		case "Tuttuat_77_2":
			dialog.text = "Yarın yine gel, her zamanki gibi. Sana gözlerini keskinleştirecek bir iksir hazırlarım, böylece her hedefi görecek ve kükreyen ateşli silahlarla daha isabetli vuracaksın.";
			link.l1 = "Pekala.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 32;
		break;
		
		case "Tuttuat_77_3":
			dialog.text = "Yarın yine gel, her zamanki gibi. Sana aklını açacak bir iksir hazırlarım, düşmanlarından da saklanırsan iyi edersin.";
			link.l1 = "Pekala.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 33;
		break;
		
		case "Tuttuat_77_4":
			dialog.text = "Yarın yine gel, her zamanki gibi. Sana daha yakışıklı olmanı sağlayacak bir iksir hazırlarım, insanları ikna etmede de daha başarılı olursun.";
			link.l1 = "Pekala.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 34;
		break;
		
		case "Tuttuat_77_5":
			dialog.text = "Yarın yine gel, her zamanki gibi. Sana şansını artıracak bir iksir hazırlayacağım, böylece talihin açık olacak.";
			link.l1 = "Peki.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 35;
		break;
		
		case "Tuttuat_78":
			dialog.text = "Sanatımı, büyük bir şamanın sanatını beğenmene sevindim.";
			link.l1 = "Söylesene Tuttuathapak, bu üç muskaya neden ihtiyacın vardı? Sadece merak ettim...";
			link.l1.go = "Tuttuat_79";
		break;
		
		case "Tuttuat_79":
			dialog.text = "Bu iki tılsımın gücünü şimdiden hissedebiliyorsun. Ruhlar onları güçlendirmemde bana yardımcı olacak ve üç tılsım bir araya geldiğinde, atalarım olan büyük Chavinlerin şaman bilgeliği ve aydınlanması bana bahşedilecek.";
			link.l1 = "Anladım. Peki, bir kez daha mükemmel iksirlerin için teşekkür ederim. Gerçekten harika bir şamansın. Artık gitme vakti geldi. Hoşça kal Tuttuathapak, umarım tekrar görüşürüz.";
			link.l1.go = "Tuttuat_80";
		break;
		
		case "Tuttuat_80":
			dialog.text = "Elveda, beyaz savaşçı. Artık beni aramana gerek yok. Atalarımın bilgeliğini kavramak için inzivaya çekiliyorum. Ruhlar yolculuklarında sana yardımcı olsun!";
			link.l1 = "Peki o zaman... hah... ruhlar senin yolunu da aydınlatsın, büyük şaman. Elveda...";
			link.l1.go = "Tuttuat_81";
		break;
		
		case "Tuttuat_81":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			GiveItem2Character(pchar, "kaleuche_amulet3");
			ChangeItemDescribe("kaleuche_amulet3", "itmdescr_kaleuche_amulet3_potion");
			sld = ItemsFromID("kaleuche_amulet3");
			sld.name = "itmname_kaleuche_amulet3_potion";
			sld.groupID = SPECIAL_ITEM_TYPE;
			sld.picIndex = 15;
			sld.picTexture = "ITEMS_35";
			sld.price = 0;
			sld.Weight = 1.0;
			sld.reaction = sti(pchar.questTemp.Caleuche.Mangarosa);
			sld.ItemType = "SUPPORT";
			i = sti(sld.reaction);
			ChangeItemDescribe("kaleuche_amulet3", "itmdescr_kaleuche_amulet"+i+"_potion");
			AddQuestRecord("Caleuche", "42");
			pchar.questTemp.Caleuche = "end";
			CloseQuestHeader("Caleuche");
			DeleteAttribute(pchar, "questTemp.Caleuche.Mangarosa");
			DeleteAttribute(pchar, "questTemp.Caleuche.Potion");
		break;
		
		case "Tuttuat_82":
			Log_Info("You have given amulets");
			RemoveItems(pchar, "kaleuche_amulet2", 1);
			RemoveItems(pchar, "kaleuche_amulet3", 1);
			dialog.text = "Beni üzdün, solgun yüzlü. Bu tılsımlara güç vermek için ruhlarla bir ritüel yaptım, ama sen bunu boşa harcadın. Üzgünüm. Şimdi git. Tuttuathapak'ın sana söyleyecek başka bir şeyi yok.";
			link.l1 = "Üzgünüm, gerçekten çok şanssızdım... Neyse. Elveda, şaman.";
			link.l1.go = "Tuttuat_83";
		break;
		
		case "Tuttuat_83":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Caleuche", "43");
			pchar.questTemp.Caleuche = "end";
			CloseQuestHeader("Caleuche");
			sld = ItemsFromID("SkullAztec");
			sld.price = 10000;
		break;

		// капитан Калеуче
		case "CaleucheCap":
			PlaySound("Voice\English\LE\Baltazar_de_Kortes\Baltazar_01.wav");
			dialog.text = "Her şey boşuna, denizci. Beni alt edemezsin. Güvertede yatan adamlarım da kemiklerini toplayıp şafaktan önce tekrar ayağa kalkacak. Biz öldürülemeyiz, çünkü ölüm bizi sonsuza dek terk etti.";
			link.l1 = "Kahretsin! Ölü müsün, diri misin? Büyük ihtimalle hâlâ yaşıyorsun – ölüler genelde sessiz yatar ve kılıç sallamaz. Ama sen kimsin, neden gemime saldırdın?";
			link.l1.go = "CaleucheCap_1";
		break;
		
		case "CaleucheCap_1":
			dialog.text = "Ben, Uçan Kalp'in Balthazar de Cordes'iyim. Hakkımda hiçbir şey bilmeyen zavallı korkaklar bana Uçan Hollandalı'nın kaptanı Van der Decken derler. Ama bu önemli değil. Önemli olan, üzerinde bir tılsımın olması ve şimdi onu alacak olmam. Ona ihtiyacım var! Bunu hissediyorum! Chavinlerin büyük tılsımı, üçünden biri, sonunda benim olacak! Önümde diz çök, ölümlü! Belki de ölümünü acısız kılarım!";
			link.l1 = "Cehenneme git, ceset!";
			link.l1.go = "CaleucheCap_2";
		break;
		
		case "CaleucheCap_2":
			DialogExit();
			npchar.MultiFighter = 4.0;
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_SetCheckMinHP(pchar, 10, true, "Caleuche_GhostshipGetOut");
		break;
		
		case "CaleucheCap_3":
			PlaySound("Voice\English\LE\Baltazar_de_Kortes\Baltazar_02.wav");
			dialog.text = "Buna inanamıyorum! Kendi kanımı en son ne zaman gördüğümü ya da acı hissettiğimi hatırlamıyorum... NASIL OLUR?!";
			link.l1 = "Bu sefer kaybettin, Balthazar de Cordes. Hikayeni biliyorum. Yeşim kafatası Chavinlerin tapınağına geri döndü ve Yum Cimil'in laneti artık senin ya da tayfanın üzerinde değil. Artık denizcilerini hayata döndüremeyeceksin.";
			link.l1.go = "CaleucheCap_4";
		break;
		
		case "CaleucheCap_4":
			dialog.text = "Ha, demek kendini bir kurtarıcı mı sanıyorsun? Hayır! Balthazar de Cordes, elinde kalan şu azıcık hayatı bile kolay kolay teslim etmez!";
			link.l1 = "Flying Heart'ın son yolculuğu burada, Khael Roa'da sona eriyor. Ve bu kez, yirmi beş yıl önce yaptığın gibi gemini denizin dibinden çıkaramayacaksın.";
			link.l1.go = "CaleucheCap_5";
		break;
		
		case "CaleucheCap_5":
			PlaySound("Voice\English\LE\Baltazar_de_Kortes\Baltazar_03.wav");
			dialog.text = "Şahin! Yirmi beş yıl geçti, ama hâlâ dün gibi hatırlıyorum. Bizi kör eden ve gemimi ikiye bölen o kürenin parlaklığını. Bu, Uçan Kalp’in ve Balthazar de Cordes’in ilk ve son yenilgisi oldu... O halde, son bir kez daha kılıçlarımızı çaprazlayalım, kaptan! Savaşta ölüm hafif ve hoş karşılanır!";
			link.l1 = "...";
			link.l1.go = "CaleucheCap_6";
		break;
		
		case "CaleucheCap_6":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Caleuche_ChangeShip");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Caleuche_Alonso_1":
			dialog.text = "Pislikten arındırdık tekneyi, Kaptan. Bu sefer ölüler yerlerinde kaldı. Ama şu teknenin nasıl hâlâ su üstünde durduğunu... vallahi bilmiyorum.";
			link.l1 = "Lanet onu ayakta tutuyordu, Alonso. Ama artık o iş bitti.";
			link.l1.go = "Caleuche_Alonso_2";
		break;
		
		case "Caleuche_Alonso_2":
			dialog.text = "Emirleriniz nedir? Onu ateşe verip bu işi bitirelim mi?";
			link.l1 = "Düşüneceğim. Parçalanıyor olsa bile, 'Flying Heart' neredeyse gemimizi delik deşik ediyordu.";
			link.l1.go = "Caleuche_Alonso_3";
		break;

		case "Caleuche_Alonso_3":
			dialog.text = "Ateş gücü bu harabede bolca var, lanet olsun ona... Asıl söylemek istediğim şu - mürettebatta bir denizcimiz var, Jacques...";
			link.l1 = "Jacques Trudeau? Onu hatırlıyorum. Bize yakın zamanda katılmıştı, değil mi?";
			link.l1.go = "Caleuche_Alonso_4";
		break;

		case "Caleuche_Alonso_4":
			dialog.text = "Şey, Kaptan. O herifin değerli şeyleri bulmakta müthiş bir yeteneği var - gerçekten müthiş. Ölüler sessizleşir sessizleşmez, hemen bir ranza atladı, altına süründü - ve bir sandık çıkardı. Sandığın içindeyse - beş bin dublon vardı!";
			link.l1 = "Beş bin mi? Hm... Görünen o ki, Balthazar de Cordes ve tayfası lanetten kurtulmayı gerçekten ummuşlar. Ceblerini altınla doldurmuşlar, kolay bir hayatın hayalini kurmuşlar... her şey bittiğinde.";
			link.l1.go = "Caleuche_Alonso_5";
		break;
		
		case "Caleuche_Alonso_5":
			dialog.text = "Bizim tayfa da böyle yaşamaktan şikayetçi olmaz, Kaptan... Eğer adamlarla paylaşırsan, bunu asla unutmazlar. Ama paylaşmazsan - bunu da akıllarından çıkarmazlar.";
			link.l1 = "Haklısın, Alonso. Mürettebatı biraz şımartmalıyız – bunu hak ettiler. Yarısını onlara dağıt, ve Jacques – bir hafta boyunca nöbetlerden muaf tut. Bugün grog yerine rom servisine izin veriyorum. Ama tetikte ol – denizin hataları affetmediğini biliyorsun.";
			link.l1.go = "Caleuche_Alonso_6";
			link.l2 = "Hm... Belki de haklısın, Alonso. Mürettebatın biraz rahatlamaya ihtiyacı var. Onlara ganimetin dörtte birini ver. Ve şu ayyaşların, bir limana demir atmadan önce kutlamaya başlamadıklarından emin ol.";
			link.l2.go = "Caleuche_Alonso_7";
			link.l3 = "Bu aylaklar ilk limanda meyhane ve genelevlere dağılsınlar diye mi? Onları tek tek toplamak için bir ay harcayacak değilim. Verdiğim maaşlar yeter de artar. Ve doblonları buraya getir. Kimsenin onları saklama fikrine kapılmaması için.";
			link.l3.go = "Caleuche_Alonso_8";
		break;
		
		case "Caleuche_Alonso_6":
			dialog.text = "Olur, Kaptan. Merak etmeyin, adamlarınız sizi asla yarı yolda bırakmaz.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Caleuche_AlonsoAfterWinOnShip_2");
		break;
		
		case "Caleuche_Alonso_7":
			dialog.text = "Tamam, Kaptan. O şeytanları dizginlemeyi bilirim - bana güvenebilirsin.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Caleuche_AlonsoAfterWinOnShip_3");
		break;
		
		case "Caleuche_Alonso_8":
			dialog.text = "Emredersiniz, Kaptan. Mürettebat elbette daha fazlasını ummuştu... ama burada kaptan sizsiniz, karar size ait.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Caleuche_AlonsoAfterWinOnShip_4");
		break;
		
		// --> // наш матрос на берегу
		case "on_coast":
			dialog.text = "Sonunda uyandınız, kaptan... Nasıl hissediyorsunuz?";
			link.l1 = "Kahretsin, ne oldu? Başım ağrıdan çatlıyor...";
			link.l1.go = "on_coast_1";
		break;
		
		case "on_coast_1":
			dialog.text = "Kaptanın kamarasına girdiğimizde, sen hâlâ yerde yatıyordun, en ufak bir hareket bile etmiyordun. Adamlar seni kaldırıp bizim gemiye sürüklediler – tam zamanında, çünkü güvertede yatan ölüler tekrar ayağa kalkmaya başlamıştı\nEn Kutsal Meryem Ana ve tüm Azizler adına! Hemen halatları kestik ve uzaklaşmaya çalıştık, ama onların gemisinden gelen bir salvo bizim eski tekneyi anında parçalara ayırdı ve kontrolü kaybettik. Sonra yelkenlerini açıp göz açıp kapayıncaya kadar ortadan kayboldular\nBizim gemi karaya oturdu ve hayatta kalabilen herkes bir sandalla kıyıya ulaştı. Bugün birçok iyi adam öldü... keşke gemide kalsaydık... Ama fırtınanın gemiyi tamamen yok edeceğinden emindik.";
			link.l1 = "Sizin suçunuz değil, beyler. Doğru kararı verdiniz. Teşekkür ederim, bunu unutmayacağım.";
			link.l1.go = "on_coast_2";
		break;
		
		case "on_coast_2":
			dialog.text = "Seni tekneye sürükledik, sonra da karaya çıkardık. Neredeyse ölüyordun...";
			link.l1 = "Sana hayatımı borçluyum. Ne kadar zamandır burada baygın yatıyordum?";
			link.l1.go = "on_coast_3";
		break;
		
		case "on_coast_3":
			dialog.text = "Bir gün boyunca seninle ilgilendik. Yaralarını temizleyip sardık, ilaç verdik ve biraz da rom içirdik. Yakında iyileşirsin.";
			link.l1 = "Bu sefer kesinlikle ölmeyeceğim. Gerçi pek iyi hissetmiyorum...";
			link.l1.go = "on_coast_4";
		break;
		
		case "on_coast_4":
			dialog.text = "Kesinlikle öyle... Uçan Hollandalı mıydı bu, Kaptan? Neden bize saldırdılar? Ve neden gemiye çıkmadan önce ateş açmadılar da, sonrasında tek bir salvo ile neredeyse gemimizi batırdılar?";
			link.l1 = "Kaptanları, Tuttuathapak adında bir Hintli şamana bahsettiğim tılsımı istiyordu. Bu yüzden bizi hemen batırmadılar, ama liderleri tılsımı alır almaz hızla işimizi bitirdiler... Ne korkunç bir şey! Ölülerin kullandığı bir gemi! İnanılır gibi değil...";
			link.l1.go = "on_coast_5";
		break;
		
		case "on_coast_5":
			dialog.text = "Evet, şimdi Sıra bize geldi ve Uçan Hollandalı'yla karşılaştık. Fırsat bulduğumda kiliseye gidip, bu mucizevi kurtuluşum için bir mum yakacağım ve Rabbimize dua edeceğim...";
			link.l1 = "Ben de... sanırım. Ama önce o köye geri döneceğim. Tuttuathapak'a her şeyi anlatmam lazım. O lanetli gemi bize musallat oldu çünkü tılsım yüzündendi! Eminim o kızıl derili şeytan, şu yaşayan ölülerin o şeye neden ihtiyaç duyduğunu az çok biliyordu.";
			link.l1.go = "on_coast_6";
		break;
		
		case "on_coast_6":
			dialog.text = "Peki. Ama dikkatli ol, Kaptan, yaraların daha yeni iyileşti. En azından yanında birini götür, ne olur ne olmaz.";
			link.l1 = "Dikkatli olacağım, söz veriyorum. Beni terk etmediğin için teşekkür ederim!";
			link.l1.go = "on_coast_7";
		break;
		
		case "on_coast_7":
			dialog.text = "Ne diyorsun Kaptan! Senin için dünyanın öbür ucuna gider, binlerce ölüyle savaşırız! Çok şey kaybettik, bu lanet olası bir utanç, ama bu hikaye efsane olarak yaşayacak.";
			link.l1 = "...";
			link.l1.go = "on_coast_8";
		break;
		
		case "on_coast_8":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("Caleuche", "5");
		break;
		
		// Фергус Хупер
		case "fergus":
			dialog.text = "Hey! Sana satacak kadar yılan derisi henüz toplamadım, o yüzden defol git!";
			link.l1 = "Hmm... Sen Fergus Hooper mısın?";
			link.l1.go = "fergus_1";
			DelLandQuestMark(npchar);
		break;
		
		case "fergus_1":
			dialog.text = "Hayır, benim adım Tuttuathapak, ve hemen defolup gitmezsen seni lanetlerim. O yüzden acele etsen iyi olur, yoksa...";
			link.l1 = "... aklımı kaybedeceğim, kendi gemimi yakacağım ve tayfam beni öldürüp tüm eşyalarımı alacak. Doğru mu?";
			link.l1.go = "fergus_2";
		break;
		
		case "fergus_2":
			sld = characterFromId(pchar.questTemp.Caleuche.Amuletmaster);
			dialog.text = "Ah... Ne oluyor, sen kimsin!? Nasıl...";
			link.l1 = "Ortak bir dostumuz var, Fergus. O bir deniz feneri bekçisi ve adı "+GetFullName(sld)+". Bana senden bahsetti ve seni bulmamı istedi. Bu arada, Şaman Tuttuathapak'ı şahsen tanıyorum, yani şakan işe yaramadı, üzgünüm. Dinle, ben bela aramıyorum. Senden bir şey satın almak istiyorum, ama yılan derisi değil.";
			link.l1.go = "fergus_3";
		break;
		
		case "fergus_3":
			dialog.text = "Demek eski dostumu tanıyorsun! Nasıldır, hâlâ o deniz fenerinde sıkıntıdan ölmedi mi? Lütfen otur, denizci, benimle bir içki iç!";
			link.l1 = "Üzgünüm Fergus, gerçekten fazla vaktim yok. Dinle, o Hintli tılsımına ihtiyacım var, merhum kaptanının Tuttuathapak ile Main’den getirdiği tılsımlardan birine. Sana iyi bir fiyat ödeyeceğim ve böylece tehlikeli bir musibetten de kurtulmuş olacaksın.";
			link.l1.go = "fergus_4";
		break;
		
		case "fergus_4":
			dialog.text = "Peki bunun nesi tehlikeli? Şimdiye kadar bana bir zararı dokunmadı. Sadece işe yaramaz bir taş işte";
			link.l1 = "Artık denizlerde olmadığın için böyle. Benim de yakın zamana kadar buna benzer bir tılsımım vardı. Bir hayalet gemi bu şeylerin peşinde.";
			link.l1.go = "fergus_5";
		break;
		
		case "fergus_5":
			dialog.text = "Şaka mı yapıyorsun, dostum? Yoksa Tuttuathapak'ı tanımak sana ağır mı geldi? Dikkat et, Kaptan, o kızıl derili şeytan aklını başından alır...";
			link.l1 = "İster inan ister inanma, ama ben gerçeği söylüyorum. Kendi gözlerimle görmesem ben de inanmazdım. Kutsal Kitap üzerine yemin edebilirim, ya da istersen benimle birlikte olanlara sorabilirsin. Caleuche ile karşılaştıktan sonra zar zor kurtuldum.";
			link.l1.go = "fergus_6";
		break;
		
		case "fergus_6":
			dialog.text = "Caleuche mi?";
			link.l1 = "Çoğu kişi ona Uçan Hollandalı der, ama asıl adı Uçan Kalp. Neyse. Şu tılsımı bana sat. Zaten sana bir faydası yok, biliyorum.";
			link.l1.go = "fergus_7";
		break;
		
		case "fergus_7":
			dialog.text = "Evet, doğru. Bu sadece işe yaramaz bir süs eşyası, gerçi oldukça güzel. Bak, hiç düşünmeden sana satardım ama artık bende değil. Diğer eşyalarla birlikte kulübemden çalındı, ben ormanda avlanırken. Bu da oldukça yakın zamanda oldu, yaklaşık bir ay önce. Üzgünüm, sana bu konuda yardımcı olamam.";
			link.l1 = "Ve kim çaldı bunu?";
			link.l1.go = "fergus_8";
		break;
		
		case "fergus_8":
			dialog.text = "Gerçekten evimi kimin soyduğunu bilseydim burada oturuyor olacağımı mı sanıyorsun? Belize dışında bir grup hırsız ve haydut cirit atıyor, şehirde de onların muhbirleri var. En azından komutan böyle düşünüyor. Ben de kesinlikle onların işi olduğuna inanıyorum.";
			link.l1 = "Komutan haydutları biliyor ama yine de hiçbir şey yapmıyor mu?";
			link.l1.go = "fergus_9";
		break;
		
		case "fergus_9":
			dialog.text = "Ne yapıyor mu, yapmıyor mu bilmiyorum. Tek bildiğim, eşyalarımın kaybolduğu ve senin kıymetli muskanda onlarla birlikte gittiği. Bu haydutları bulmaya çalış – belki cebinde bulursun. Onu satabildiklerini sanmam – tüccarların böyle şeylere ihtiyacı yoktur.";
			link.l1 = "Pekala, gidip komutanla konuşacağım. İyi şanslar, Fergus!";
			link.l1.go = "fergus_10";
		break;
		
		case "fergus_10":
			DialogExit();
			AddQuestRecord("Caleuche", "9");
			pchar.questTemp.Caleuche.Bandos = "start"; 
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddLandQuestMarkToPhantom("beliz_prison", "belizJailOff");
		break;
		
		// бандит в городе
		case "Beliz_townbandos":
			dialog.text = "Hey! Ne istiyorsun? Misafir beklemiyordum. Defol git!";
			link.l1 = "Neden bu kadar kaba davranıyorsun, dostum? Sadece bir şey sormak istemiştim...";
			link.l1.go = "Beliz_townbandos_1";
		break;
		
		case "Beliz_townbandos_1":
			dialog.text = "Duymadın mı? Defol git yoksa seni kapıdan tekmelerim!";
			link.l1 = "Hmm... Belki de aradığım kişi sensin sonunda. Fazlasıyla gergin görünüyorsun, dostum...";
			link.l1.go = "Beliz_townbandos_2";
		break;
		
		case "Beliz_townbandos_2":
			dialog.text = "Çok akıllı olduğunu mu sanıyorsun? Son kez söylüyorum: ya hemen defolup gidersin, ya da muhafızları çağırırım ve seni hapse atarlar!";
			link.l1 = "Beni hapse atacak mısın? Ne kadar ilginç. Biliyor musun, artık neredeyse eminim ki aradığım kişiyi buldum. Peki, kabul ediyorum. Haydi muhafızları çağıralım, sonra da komutanın ofisine birlikte, mutlu bir aile gibi yürüyelim. Az önce oradaydım, yolu hatırlıyorum... Muhafızlar! MUHAFIZLAR!";
			link.l1.go = "Beliz_townbandos_3";
		break;
		
		case "Beliz_townbandos_3":
			dialog.text = "Siktir git! Seni gebertirim!";
			link.l1 = "Oh ho-ho! Pekâlâ, deneyebilirsin!";
			link.l1.go = "Beliz_townbandos_4";
		break;
		
		case "Beliz_townbandos_4":
			DialogExit();
			DeleteAttribute(npchar, "CityType");
			DeleteAttribute(npchar, "city"); // чтобы не было НЗГ
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Caleuche_BelizTownbandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
			pchar.quest.Caleuche_letter.win_condition.l1 = "item";
			pchar.quest.Caleuche_letter.win_condition.l1.item = "kaleuche_letter";
			pchar.quest.Caleuche_letter.function = "Caleuche_FindLetter";
		break;
		
		// главарь лесных бандосов
		case "Beliz_forestbandos":
			dialog.text = "Hey, yolcu! Hoş geldin, hoş geldin... Akşam yemeği, konaklama - paran neye yeterse hepsi burada. Hazır ol, ceplerini boşaltacaksın!";
			link.l1 = "O kadar da acele etme, iyi adamım. Seninle bir işim var.";
			link.l1.go = "Beliz_forestbandos_1";
		break;
		
		case "Beliz_forestbandos_1":
			dialog.text = "İş mi? Ha-ha! Senin tek işin, tüm gümüş ve altınını teslim etmek!";
			link.l1 = "Artık sus. Belize'den beklediğin mektubu getirdim. Haberci muhafızları geçemediği için işi bana bıraktı.";
			link.l1.go = "Beliz_forestbandos_2";
		break;
		
		case "Beliz_forestbandos_2":
			dialog.text = "Göster bana!";
			link.l1 = "Al bakalım...";
			link.l1.go = "Beliz_forestbandos_3";
		break;
		
		case "Beliz_forestbandos_3":
			Log_Info("You have given a note");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "kaleuche_letter", 1);
			dialog.text = "(okuyor) Hm... Bu gerçekten garip... Sen nasıl karıştın bu işe?";
			link.l1 = "Sana zaten söyledim, adamını yakaladılar, ben de onun işini aldım. Bana para ve senden sıcak bir karşılama sözü vermişti...";
			link.l1.go = "Beliz_forestbandos_4";
		break;
		
		case "Beliz_forestbandos_4":
			dialog.text = "A warm welcome? Alright, pal. We'll warm you up, feed you, give you money and all that stuff - but you, you too, will have to prove us that you're not a guards' hound. We've got a score to settle now\nA merchant has recently arrived to a nearby cove; apparently, he wants to sneak into the city with his wares past the customs office. But we will still exact the duty from him. We are lawful folk after all! You'll come with us. Do you know which end of the sword goes where?";
			link.l1 = "Ve bu görevden bana da bir pay düşecek mi?";
			link.l1.go = "Beliz_forestbandos_5";
		break;
		
		case "Beliz_forestbandos_5":
			dialog.text = "Elbette yapacaksın! Eğer savaşta cesur olursan ve hayatta kalırsan. Ama kolay bir iş bekleme, tüccar yalnız değil, yanında bir koruma var, hem de oldukça kalabalık bir koruma. Neyse, vakit geldi - avımız yakın. Çocuklar! Silahlarınızı hazırlayın, yola çıkıyoruz!";
			link.l1 = "...";
			link.l1.go = "Beliz_forestbandos_6";
		break;
		
		case "Beliz_forestbandos_6":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			LocatorReloadEnterDisable(pchar.location, "reload2_back", true);
			LocatorReloadEnterDisable(pchar.location, "reload3_back", true);
			for (i=1; i<=6; i++)
			{
				sld = characterFromId("Beliz_forestbandos_"+i);	
				LAi_SetActorType(sld);
				LAi_group_MoveCharacter(sld, "TMP_FRIEND");
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "Beliz_ExitTown", "goto", "goto"+(rand(1)+1), "", 10.0);
			}
			DoQuestCheckDelay("OpenTheDoors", 12.0);
			pchar.quest.Caleuche_bandosrobb.win_condition.l1 = "location";
			pchar.quest.Caleuche_bandosrobb.win_condition.l1.location = "Beliz_ExitTown";
			pchar.quest.Caleuche_bandosrobb.function = "Caleuche_JungleBandosRobbery";
		break;
		
		case "Beliz_forestbandos_7":
			dialog.text = "Korkak olmadığını görüyorum. Aferin! Payını hak ettin. Nasıl istersin? Nakit mi? Mal mı? Yanlarında bolca içki vardı, iyi fiyata gider.";
			link.l1 = "Nakit.";
			link.l1.go = "Beliz_forestbandos_8_1";
			link.l2 = "Mal.";
			link.l2.go = "Beliz_forestbandos_8_2";
		break;
		
		case "Beliz_forestbandos_8_1":
			Log_Info("You have received 100 doubloons");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "gold_dublon", 100);
			dialog.text = "Al bakalım! Ve bu kese de mektubu ulaştırdığın için.";
			link.l1 = "Teşekkürler! İşte tam da böyle seviyorum!";
			link.l1.go = "Beliz_forestbandos_9";
		break;
		
		case "Beliz_forestbandos_8_2":
			Log_Info("You have received 30 bottles of rum");
			Log_Info("You have received 12 bottles of wine");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "potionrum", 30);
			TakeNItems(pchar, "potionwine", 12);
			dialog.text = "Al bakalım! Yeter ki kendini içkiye boğup ölme, ha-ha-ha! Şu keseyi de mektubu getirdiğin için veriyorum.";
			link.l1 = "Teşekkürler! İşte tam da böyle seviyorum!";
			link.l1.go = "Beliz_forestbandos_9";
		break;
		
		case "Beliz_forestbandos_9":
			Log_Info("You have received a purse");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "purse2", 1);
			dialog.text = "Bana oldukça düzgün biri gibi görünüyorsun. Başka bir iş ister misin? Bana getirdiğin o mektup hakkında.";
			link.l1 = "Tabii.";
			link.l1.go = "Beliz_forestbandos_10";
		break;
		
		case "Beliz_forestbandos_10":
			dialog.text = "O zaman mağaraya gel. İki tane var. Ormanda en son buluştuğumuz yere git, sonra sol patikayı seç. Üç gün sonra gece yarısından bire kadar mağaranın girişinde buluşuyoruz, anladın mı? Uslu durursan, seni de çetemize alırız. Ama unutma – kasabada bir laf edersen, işin biter. Uzanır elim, unutma.";
			link.l1 = "Beni korkutmayı bırak artık. Anladım. Balık gibi sessiz olacağım. Üç gün sonra beni bekle, orada olacağım. Kolay paraya bayılırım!";
			link.l1.go = "Beliz_forestbandos_11";
		break;
		
		case "Beliz_forestbandos_11":
			dialog.text = "Pekala, dostum. Şimdi kaybol buradan, yoksa muhafızlar gelir. Biz de gidiyoruz.";
			link.l1 = "Yine görüşürüz, dostum...";
			link.l1.go = "Beliz_forestbandos_12";
		break;
		
		case "Beliz_forestbandos_12":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LocatorReloadEnterDisable("Beliz_Jungle_01", "reload2_back", false);
			LocatorReloadEnterDisable("Beliz_Jungle_01", "reload3_back", false);
			LocatorReloadEnterDisable("Beliz_CaveEntrance_2", "reload1_back", true); // закрываем пещеру
			SetFunctionTimerCondition("Caleuche_CaveOpen", 0, 0, 1, false); // таймер
			SetFunctionTimerCondition("Caleuche_BelizbandosClear", 0, 0, 4, false); // таймер
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			for (i=1; i<=6; i++)
			{
				if (GetCharacterIndex("Beliz_forestbandos_"+i) != -1)
				{
					sld = characterFromId("Beliz_forestbandos_"+i);	
					LAi_SetActorType(sld);
					LAi_group_MoveCharacter(sld, "TMP_FRIEND");
					LAi_ActorRunToLocation(sld, "reload", "reload1_back", "", "", "", "OpenTheDoors", 20.0);
				}
			}
			AddQuestRecord("Caleuche", "13");
			// костер
			ref location = &Locations[FindLocation("Beliz_Jungle_01")];
			DeleteAttribute(location, "fire");
			sld = ItemsFromID("fire");
			sld.shown = false;
			// пакуем схрон в пещере
			pchar.GenQuestBox.Beliz_Cave_2 = true;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.kaleuche_amulet2 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.suit4 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.purse1 = 7; // Addon-2016 Jason
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.purse2 = 3; // Addon-2016 Jason
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.potion2 = 10;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.potionrum = 55;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.indian_3 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.obereg_4 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.berserker_potion = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.jewelry2 = 15;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.jewelry3 = 33;
			// меняем флаг
			pchar.questTemp.Caleuche.Bandos = "know";
			SaveCurrentQuestDateParam("questTemp.Caleuche.belizbandos");
			AddLandQuestMarkToPhantom("beliz_prison", "belizJailOff");
		break;
		
		// спалили бандосы в пещере
		case "Beliz_cavebandos":
			dialog.text = "Ne! Demek bizim malımıza göz diktin? Bununla paçayı sıyıramayacaksın, pislik herif!";
			link.l1 = "Kime kurt dedin az önce, pislik?!";
			link.l1.go = "Beliz_cavebandos_1";
		break;
		
		case "Beliz_cavebandos_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_Delete("EnemyFight");
			DialogExit();
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Beliz_cavebandos_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			if (MOD_SKILL_ENEMY_RATE > 4)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Beliz_cavebandos_3", "citiz_23", "man", "man", 30, PIRATE, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, 30, 70, 70, "blade_10", "pistol1", "bullet", 150);
				ChangeCharacterAddressGroup(sld, pchar.location, "monsters", "monster16");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Caleuche_CaveBandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// капитан гарпии
		case "reginald":
			dialog.text = "Merhaba, meslektaşım! Seni buraya ne getirdi?";
			link.l1 = TimeGreeting()+", mynheer Jackson. Sonunda sizi bulduğuma sevindim.";
			link.l1.go = "reginald_1";
			DelLandQuestMark(npchar);
		break;
		
		case "reginald_1":
			dialog.text = "'Mynheer Jackson', ha-ha! Doğrusunu söylemek gerekirse, yakında ben de kendime öyle diyeceğim. Şu lanet Şirket için durmaksızın çalışıyorum... ama iyi ödüyorlar, hem de çok iyi!.. Peki, seni buraya ne getirdi dostum?";
			link.l1 = "Ortak tanıdığımız, deniz feneri bekçisi, sende eski bir Kızılderili tılsımı olduğunu söyledi. Sanırım şimdiye kadar ona bir fayda bulamadın, ama benim ona gerçekten ihtiyacım var. Onu senden satın almak istiyorum.";
			link.l1.go = "reginald_2";
		break;
		
		case "reginald_2":
			dialog.text = "Ha, o süslü zımbırtıyı emekli lostromoya sorduğum şeyi mi diyorsun? Evet dostum, haklısın, aslında hiç işe yaramadı, sadece güzel görünüyor.";
			link.l1 = "Ne kadar istiyorsun?";
			link.l1.go = "reginald_3";
		break;
		
		case "reginald_3":
			dialog.text = "Bakın, ufak bir sorun var... Açıklamama izin verin. Şu anda yanımda değil. Hiçbir zaman işime yaramadığı için, kıyıdaki sandığımda, diğer eşyalarımın arasında bıraktım.";
			link.l1 = "Ah, demek bu yüzden hâlâ... neyse, boşver. Hadi şu sandığına gidelim, tılsımı senden satın alacağım. Bu kadar basit. Nerede saklıyorsun?";
			link.l1.go = "reginald_4";
		break;
		
		case "reginald_4":
			dialog.text = "O kadar da basit değil aslında. Sandığım Barbados'ta, deniz fenerinin kulesinde ve ben yokken kimse ondan faydalanamasın diye güvenli bir şekilde kilitli. Ve gerçekten üzgünüm ama seninle Barbados'a gelemem. Hollandalılarla yaptığım sözleşmeye göre Philipsburg ile Port Royal arasında sefer yapmalı ve programa harfiyen uymalıyım. Barbados ise bu rotanın yakınından bile geçmiyor.";
			link.l1 = "Ve biz ne yapabiliriz? O muska bana gerçekten, ama gerçekten lazım!";
			link.l1.go = "reginald_5";
		break;
		
		case "reginald_5":
			dialog.text = "Hmm... Şey, bir seçenek var. Sandığımın anahtarını sana veririm, sen de tek başına Barbados'a gidersin. Ama içindekilerin hepsinin karşılığını bana ödemek zorundasın, ondan sonra onları alabilirsin. Güvensizlik için üzgünüm - ama beni anlamalısın. Seni daha önce hiç görmedim.";
			link.l1 = "Ne kadar?";
			link.l1.go = "reginald_6";
		break;
		
		case "reginald_6":
			dialog.text = "Beş yüz altın sikke. Daha azına olmaz.";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "İşte oldu! Altının burada.";
				link.l1.go = "reginald_10";
			}
			link.l2 = "Hmm... Yanımda o kadar çok dublon yok.";
			link.l2.go = "reginald_7";
		break;
		
		case "reginald_7":
			dialog.text = "O halde parayı bulduğunda tekrar yanıma gel. Beni bir kez bulduysan, yine bulursun. Bir süre daha St. Martin ile Jamaika arasında seyredeceğim.";
			link.l1 = "Pekâlâ, anlaştık.";
			link.l1.go = "reginald_8";
		break;
		
		case "reginald_8":
			DialogExit();
			NextDiag.CurrentNode = "reginald_9";
			npchar.DeckDialogNode = "reginald_9";
			AddLandQuestMark(npchar, "questmarkmain");
		break;
		
		case "reginald_9":
			dialog.text = "Yine sen, dostum? 500 altının var mı?";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Evet. İşte altının.";
				link.l1.go = "reginald_10";
			}
			link.l2 = "Henüz değil, ama üzerinde çalışıyorum.";
			link.l2.go = "reginald_8";
		break;
		
		case "reginald_10":
			RemoveDublonsFromPCharTotal(500);
			DelLandQuestMark(npchar);
			
			dialog.text = "Harika! Ve işte anahtarınız. Sadece bir ricam var: İçindekileri aldıktan sonra lütfen anahtarı kilitte bırakın. Yeni bir kilit ve anahtar yaptırmak istemem.";
			link.l1 = "Pekâlâ.";
			link.l1.go = "reginald_11";
		break;
		
		case "reginald_11":
			dialog.text = "O zaman sana iyi şanslar, dostum! İyi yolculuklar!";
			link.l1 = "Ve size de... İyi yolculuklar, Bay Jackson!";
			link.l1.go = "reginald_12";
		break;
		
		case "reginald_12":
			DialogExit();
			AddDialogExitQuestFunction("Caleuche_SpawnItemsInTheChest");
			AddQuestRecord("Caleuche", "20");
		break;
		
		case "Caleuche_Reginald_21":
			dialog.text = "Ne istiyorsun bizden, şeytanın işi misin? Burası Hollanda Batı Hindistan Şirketi'nin gemisi ve böyle numaralar cezasız kalmaz. Seni ve o çapulcu tayfanı dünyanın öbür ucuna kadar kovalayacaklar.";
			link.l1 = "Hollandalılar ya da onların ticaret şirketi umurumda bile değil. Benim peşinde olduğum eski bir Hint tılsımı var, ve biliyorum ki o sende – ya da en azından bir zamanlar sendeydi.";
			link.l1.go = "Caleuche_Reginald_22";
		break;

		case "Caleuche_Reginald_22":
			dialog.text = "Sen delirdin mi? Bir süs eşyası için gemiye saldırıyorsun?";
			link.l1 = "Kes sesini ve ver şunu, belki sağ kalırsın.";
			link.l1.go = "Caleuche_Reginald_23";
		break;

		case "Caleuche_Reginald_23":
			dialog.text = "Lanet olsun... Yanımda değil. Barbados'ta.";
			link.l1 = "O zaman şu delik deşik teknen hemen dibe iner ve sen de ambarımda farelere arkadaşlık edersin. Yol boyunca bana tam olarak nerede bulacağımı anlatman için bolca vaktimiz olacak. Ve bana güven – gemide, en inatçı kafadan bile sırları döktürebilecek adamlarım var... nezakete hiç gerek yok.";
			link.l1.go = "Caleuche_Reginald_24";
		break;

		case "Caleuche_Reginald_24":
			dialog.text = "Buna gerek yok. Deniz fenerindeki bir sandıkta. Kilitli. İşte anahtarı.";
			link.l1 = "Akıllıca bir seçim, dostum. Keşke senin gibilerden daha çoğu da aynı aklı gösterebilseydi... ellerim bu kadar kana bulanmazdı.";
			link.l1.go = "Caleuche_Reginald_24_1";
			link.l2 = "Akıllıca seçtin. Ama bak... Seni yaşatamam. Doğruca o Hollandalı tüccarlara koşarsın, onların dikkatini üzerime çekmek istemem.";
			link.l2.go = "Caleuche_Reginald_24_2";
		break;
		
		case "Caleuche_Reginald_24_1":
			dialog.text = "O sandık, yıllar boyunca Hollandalılara hizmet ederek kazandığım her şeyi saklıyor...";
			link.l1 = "O zaman anlaştık: sandık benim, sen de canını kurtarıyorsun. Uygun mu...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Caleuche_EndFightWithReginald");
		break;
		
		case "Caleuche_Reginald_24_2":
			dialog.text = "Argh...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Caleuche_KillToReginald");
		break;
		
		// монах в Виллемстаде
		case "monk_caleuche":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("villemstad");
			npchar.lifeday = 1;
			dialog.text = "Merhaba, Kaptan "+GetFullName(pchar)+" Willemstad'a hoş geldiniz, sizi ağırlamaktan memnuniyet duyarım.";
			link.l1 = "Merhaba, Baba. Seni hatırlamıyorum. Birbirimizi tanıyor muyuz?";
			link.l1.go = "monk_caleuche_1";
		break;
		
		case "monk_caleuche_1":
			dialog.text = "Geminiz limana yanaştıktan sonra sizinle ilgili biraz araştırma yaptım. Ve sanırım sizden bir konuda yardım isteyebilirim.";
			link.l1 = "Çok ilginç. Peki neden ben?";
			link.l1.go = "monk_caleuche_2";
		break;
		
		case "monk_caleuche_2":
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				dialog.text = "Çünkü Özgür Eyaletler Cumhuriyeti için çok şey yaptınız. Şirketle aranız iyi ve valiyle dostsunuz. Şimdiden birkaç makama başvurdum ama geri çevrildim, yine de sizin gibi asil birinin Rabbimizin bir hizmetkârından gelen mütevazı bir ricayı geri çevirmeyeceğini umuyorum.";
			}
			else
			{
				dialog.text = "Çünkü valimizin hizmetinde değilsiniz. Şirket için çalışmıyorsunuz ve ordumuzla da bir bağlantınız yok - yoksa muhtemelen beni de daha önce başvurduğum ve geri çevrildiğim diğer yetkililer gibi, can sıkıcı bir sinekmişim gibi bir kenara iterdiniz.";
			}
			link.l1 = "Peki, öyleyse. Ne istiyorsun, anlat bakalım?";
			link.l1.go = "monk_caleuche_3";
		break;
		
		case "monk_caleuche_3":
			sld = characterFromId("Villemstad_Priest");
			dialog.text = "Bankanın arkasında bir ev var. Orada yaşayan bir hanımefendi, evindeki bir odayı çok şüpheli bir tipe kiralıyordu; ne buradan, ne de Hollandalıydı. Ve böylece başrahibimiz, Rahip "+sld.name+", onu tanımıştı\nO, Engizisyon tarafından cadılık ve şeytani güçlerle işbirliği yapmakla suçlanan Portekizli Joachim Merriman’dı. Engizisyondan kaçmak için Yeni Dünya’ya sığınmıştı. Biliyorsun, İspanyollar genellikle gözden düşenleri sapkınlık ve cadılıkla suçlayıp kazığa oturturlar, ama... Bu sefer haklıydılar. Merriman gerçekten bir büyücüydü\nBir süre Willemstad’da yaşadı, sonra ortaya çıktığı gibi aniden ortadan kayboldu. Bir süre sonra, ona odasını kiralayan kadın bir daha asla o evden çıkarken görülmedi. Hiçbir zaman! Ve o günden beri hiçbir yerde görülmedi\nGeceleri ise, bazen vatandaşlar ikinci kattaki pencerelerden kırmızı-mavi ışıkların yanıp söndüğünü ve neredeyse şeytani çığlıklar gibi tuhaf sesler duyduklarını söylüyorlar. Baba "+sld.name+" appealed to the commandant. He sent a patrol of four soldiers; they searched the house, but found nothing: neither the landlady herself, nor anyone else, nor anything suspicious at all\nBut these strange things keep happening. The landlady has never shown up, and this hellish light can still be seen there at night. Besides, two beggars have recently gone missing as well. I heard them talking at the parvis – they knew there were no owners in the house, so they decided to lodge there. No one has seen them since.";
			link.l1 = "Anladığım kadarıyla, o eve girip gerçekten ne olduğunu öğrenmemi istiyorsun?";
			link.l1.go = "monk_caleuche_4";
		break;
		
		case "monk_caleuche_4":
			dialog.text = "Kesinlikle, asil efendim. Lütfen Kutsal Kilise'ye yardım edin. Komutan, devriyesinin hiçbir şey bulamadığını söyleyip hayal gördüğümüzü düşünüyor. Hükümet de aynı şekilde düşünüyor. Halk ise umursamıyor, çünkü bunu kendilerine yönelik açık bir tehdit olarak görmüyorlar.";
			link.l1 = "Hmm... Ve oraya gece gitmem mi gerekiyor?";
			link.l1.go = "monk_caleuche_5";
		break;
		
		case "monk_caleuche_5":
			sld = characterFromId("Villemstad_Priest");
			dialog.text = "Yes, mynheer. It's quiet there during the day, that's why the soldiers didn't find anything. I think the commandant is afraid for his men; I would be too. But please, I beg of you. Father "+sld.name+" will thank you and reward you for your service. Once you've been to that den during the night, please tell him what you find there. I assure you, our misgivings are well-founded.";
			link.l1 = "Pekala. Düşüneceğim.";
			link.l1.go = "monk_caleuche_6";
		break;
		
		case "monk_caleuche_6":
			dialog.text = "Teşekkür ederim, kaptan. Umarım bu mütevazı ricamı geri çevirmezsiniz. Lütfen, bunu Rabbimizin, inancımızın ve kutsal olan her şeyin hatrına yapın. Benim de kutsamamla gidin.";
			link.l1 = "...";
			link.l1.go = "monk_caleuche_7";
		break;
		
		case "monk_caleuche_7":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload7_back", "none", "", "", "", -1);
			AddQuestRecord("Caleuche", "24");
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				if (CheckAttribute(pchar, "questTemp.Caleuche.SolomonSkul")) sTemp = "visit the house of Joaquim Merriman, where, according to him, strange things happen at night. Remembering that special gleam in Merriman's eyes when he looked at the jade skull, I feel a little creepy. It seems that the old Jew could not resist the sum of half a million pesos. Whatever the case, I don`t feel like going to Merriman former abode at night.";
				else sTemp = "visit the house of my old acquaintance Joachim Merriman, where, allegedly, strange things are happening at nights. I still remember that glitter in Merriman's eyes, when he was looking at the skull, and honestly I feel frightened. I am not really fond of the idea to visit his former abode in the night, who knows what kind of devils lurk there.";
			}
			else sTemp = "visit the house at the back of the bank, where some Joachim Merriman had been renting a room. Apparently it is that warlock, of which Tuttuathapak was talking about. According to the monk, strange things are happening in this house in the night. I really feel uncomfortable about visiting the warlock's former home, who knows what kind of devils lurk there.";
			AddQuestUserData("Caleuche", "sText", sTemp);
			i = Findlocation("Villemstad_town");
			DeleteAttribute(&locations[i], "reload.l14.close_for_night");
			pchar.quest.Caleuche_villemstadhouse.win_condition.l1 = "location";
			pchar.quest.Caleuche_villemstadhouse.win_condition.l1.location = "Villemstad_houseSp1_room";
			pchar.quest.Caleuche_villemstadhouse.win_condition.l2 = "Hour";
			pchar.quest.Caleuche_villemstadhouse.win_condition.l2.start.hour = 1.00;
			pchar.quest.Caleuche_villemstadhouse.win_condition.l2.finish.hour = 3.00;
			pchar.quest.Caleuche_villemstadhouse.function = "Caleuche_CreateJoakimSkel";
		break;
		
		// охотник у пещеры
		case "cavehunter":
			dialog.text = "Dur bir dakika, dostum. Canını düşünüyorsan oraya gitmesen iyi olur.";
			link.l1 = "Peki, mesele ne?";
			link.l1.go = "cavehunter_1";
		break;
		
		case "cavehunter_1":
			dialog.text = "Bana güven, bilmek istemezsin. Ama Ölüm köşe başında bekliyor ve Kitap üzerine yemin ederim ki sağ çıkamayacaksın, hayal gücünü aşan şeyler var.";
			link.l1 = "Peki, madem öyle diyorsun, kaderi zorlamayacağım. Uyardığın için sağ ol.";
			link.l1.go = "cavehunter_2";
		break;
		
		case "cavehunter_2":
			dialog.text = "Rica ederim. O yoldan uzak dur.";
			link.l1 = "...";
			link.l1.go = "cavehunter_3";
		break;
		
		case "cavehunter_3":
			DialogExit();
			npchar.dialog.currentnode = "cavehunter_4";
		break;
		
		case "cavehunter_4":
			dialog.text = "O yoldan uzak dur, dostum.";
			link.l1 = "Evet, hatırlıyorum...";
			link.l1.go = "cavehunter_4_1";
		break;
		
		case "cavehunter_4_1":
			DialogExit();
			npchar.dialog.currentnode = "cavehunter_4";
		break;
		
		case "cavehunter_5":
			sld = characterFromId("Havana_Priest");
			dialog.text = "Oraya gitmek istediğine emin misin?";
			link.l1 = "Kesinlikle. "+sld.name+"Havana'daki kilisenin başrahibi beni buraya gönderdi. Burada neler olup bittiğini anlamalı ve gereken önlemleri almalıyım.";
			link.l1.go = "cavehunter_6";
			DelLandQuestMark(npchar);
		break;
		
		case "cavehunter_6":
			dialog.text = "Burada neler oluyor? Kendi gözlerinle gördüğünde korkudan titrememek elde değil.";
			link.l1 = "Yani yürüyen ölüler mi?";
			link.l1.go = "cavehunter_7";
		break;
		
		case "cavehunter_7":
			dialog.text = "Evet.   Ve söylediklerime inanmakta fayda var.";
			link.l1 = "Ve sana inanıyorum. O uğursuz şeyi Willemstad'da zaten görüp yok ettim. Şimdi de oraya girip bu mağarada saklanan tüm pisliği yok edeceğim.";
			link.l1.go = "cavehunter_8";
		break;
		
		case "cavehunter_8":
			int icpy = GetOfficersQuantity(pchar);
			switch (icpy)
			{
				case 0:
					dialog.text = "Oraya tek başına mı gideceksin? Senin sonun geldi, dostum. Orada ne kadar çok şey olduğunu hayal bile edemezsin. Neyse, gitmek zorundaysan git, ben de kiliseye gidip ruhunun huzuru için bir mum yakacağım.";
					link.l1 = "Beni hemen toprağa verme. Daha beterlerini gördüm.";
					link.l1.go = "cavehunter_exit";
				break;
				
				case 1:
					dialog.text = "Sadece ikiniz mi? Korkarım pek uzağa gidemezsiniz. Orada ne kadar çoklarından olduğunu hiç bilmiyorsunuz. Bu intihar olur.";
					link.l1 = "Bizi henüz iyi tanımıyorsun, dostum. Kenara çekil, biz de bu günahkar inini temizleyelim.";
					link.l1.go = "cavehunter_exit";
				break;
				
				case 2:
					dialog.text = "Sadece üçünüz mü? Bunu göze alıyorsanız, demek ki tecrübeli savaşçılarsınız. Ama yine de başaramayacağınızdan korkuyorum. O mağaranın içinde ne kadar çok o şeylerden olduğunu tahmin bile edemezsiniz.";
					link.l1 = "Bizi pek tanımıyorsun, dostum. Kenara çekil, biz de bu lanetli inin temizliğini yapalım.";
					link.l1.go = "cavehunter_exit";
				break;
				
				case 3:
					dialog.text = "Siz korkak değilsiniz, görüyorum. Ama o yaratıklardan kaç tane olduğunu gerçekten bilmiyorsunuz. Böyle bir işte, her adam önemlidir. Kahretsin, sizinle geleceğim ve o pislikleri tüfeğimle vuracağım!";
					link.l1 = "Sen cesur bir insansın, dostum. Yardımını geri çevirmem. Hadi gidelim!";
					link.l1.go = "cavehunter_9";
				break;
			}
		break;
		
		case "cavehunter_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
		break;
		
		case "cavehunter_9":
			DialogExit();
			npchar.quest.caleuche = true;
			npchar.dialog.currentnode = "cavehunter_10";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			// закрываем локаторы выхода
			LocatorReloadEnterDisable("Cuba_Jungle_07", "reload1_back", true);
			LocatorReloadEnterDisable("Cuba_Jungle_07", "reload3_back", true);
		break;
		
		case "cavehunter_10":
			dialog.text = "Hadi gidelim! Kahrolsun o pis ölüler!";
			link.l1 = "...";
			link.l1.go = "cavehunter_10_1";
		break;
		
		case "cavehunter_10_1":
			DialogExit();
			npchar.dialog.currentnode = "cavehunter_10";
		break;
		
		case "cavehunter_11":
			dialog.text = "Bu tam bir katliamdı! Kim tahmin edebilirdi ki bu kadar ölü burada saklanıyor! Neyse, en azından artık biraz dinlenebiliriz... Lütfen seni buraya gönderen o başrahibine bundan bahset. Umarım Engizisyon, raporundan sonra bu işin aslını öğrenir. Sonuçta ölülerle uğraşmak onların işi, ben ise sadece sıradan bir avcıyım.";
			link.l1 = "Ona mutlaka söyleyeceğim. Yardımın için teşekkürler dostum. Sen nadir bir insansın, ölümle yüzleşmeye cesaret edecek pek az kişi var! Bol şans!";
			link.l1.go = "cavehunter_exit";
		break;
		
		// солдат в крипте при провале
		case "cryptguard":
			dialog.text = "Olduğun yerde kal! Burası yasak bölge!";
			link.l1 = "Ehh... Peki orada ne var?";
			link.l1.go = "cryptguard_1";
		break;
		
		case "cryptguard_1":
			dialog.text = "Orada tehlikeli bir büyücü bulundu. Sadece kutsal babalar ve onlara eşlik eden askerler içeri girebilir.";
			link.l1 = "Anladım. Büyücü tutuklandı mı?";
			link.l1.go = "cryptguard_2";
		break;
		
		case "cryptguard_2":
			dialog.text = "Böyle soruları yanıtlamaya yetkim yok, señor. Artık gitme vaktiniz geldi.";
			link.l1 = "Pekala, anladım. İyi şanslar!";
			link.l1.go = "cryptguard_3";
		break;
		
		case "cryptguard_3":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Caleuche", "31");
			CloseQuestHeader("Caleuche");
			pchar.questTemp.Caleuche = "end";
		break;
		
		// чавинави-вождь
		case "Chavinavi":
			PlaySound("Voice\English\LE\Chavinavi\Chavinavi_01.wav");
			dialog.text = "Kıpırdama, insan! Tapınağın tam kalbindesin ve artık geri dönmek için çok ileri gittin.";
			link.l1 = "Sen kimsin?!";
			link.l1.go = "Chavinavi_1";
		break;
		
		case "Chavinavi_1":
			dialog.text = "Ben Chavinavi'nin reisi, bu kutsal yerin koruyucusu ve bekçisiyim. Bu tapınağa giren ilk kişi sen değilsin, ama senden önce sadece iki adam ve bir kadın buraya girip sağ çıkabildi. Şimdi seninle konuşmamın tek nedeni de bu. Neden geldin buraya, solgun yüz?";
			link.l1 = "Buraya eski bir kalıntı getirdim, yeşim kafatası. Elli yıl önce, ana karanın derinliklerindeki bir Hint tapınağından alınmıştı. Mabedi bulup emaneti tanrınıza geri verecektim.";
			link.l1.go = "Chavinavi_2";
		break;
		
		case "Chavinavi_2":
			dialog.text = "Senin gibi birinden böyle sözler duymak garip. Sana inanmıyorum. Siz soluk yüzlüler hep bir şeyler almaya gelirsiniz, ama asla karşılığında hiçbir şey vermezsiniz.";
			link.l1 = "Yalan söylemiyorum. Kafatasını geri vererek, Karayip Denizi'ni dehşete düşüren hayalet geminin kaptanının üzerine konmuş laneti kaldıracağım, onu tekrar ölümlü yapacağım ve dünyayı ondan sonsuza dek kurtaracağım.";
			link.l1.go = "Chavinavi_3";
		break;
		
		case "Chavinavi_3":
			dialog.text = "Tanrımızın o laneti kaldıracağını nereden biliyorsun, soluk yüz? Tanrımız seninle mi konuşuyor?";
			link.l1 = "Hayır. Buraya, Tuttuathapak adında büyük bir şamanın tavsiyesiyle geldim. Onun dediğine göre, kafatası lanetin anahtarı ve Karayipler'de başka tapınak yok. Ve biliyor musun, bence o gerçekten geçmişin ruhlarıyla konuşabiliyor. Belki de seninle bile, jaguar savaşçılarının reisi.";
			link.l1.go = "Chavinavi_4";
		break;
		
		case "Chavinavi_4":
			dialog.text = "Sözlerin beni şaşırtıyor, beyaz yüzlü, ama sana hâlâ tamamen güvenemem. Yine de, eğer bu tapınağa kutsal eşyamızı geri getirmek için geldiysen, şüphesiz şamanımız sana burası hakkında, nasıl yaratıldığı, tarihi ve burada yaşayanlar hakkında bilgi vermiştir\nEğer öyleyse, sorularımın hepsine kolayca cevap verebilirsin. O zaman bana karşı samimi olduğunu kabul eder, geçmene izin veririm ve dahası, seni ödüllendiririm.";
			link.l1 = "O zaman sor!";
			link.l1.go = "question1";
		break;
		
		case "question1":
			dialog.text = "I am the chieftain of the Chavinavi, and the jaguar warriors. Thousand years ago I was human; now I am carrying out my sacred duty in these chambers. Which god commands me?";
			link.l1 = "Mictlantecuhtli.";
			link.l1.go = "question1_l";
			link.l2 = "Kukulcan.";
			link.l2.go = "question1_l";
			link.l3 = "Yum Cimil.";
			link.l3.go = "question1_r";
			link.l4 = "Inti.";
			link.l4.go = "question1_l";
			link.l5 = "Kauil.";
			link.l5.go = "question1_l";
		break;
		
		case "question1_r":
			dialog.text = "Sizin solgun yüzlü halkınız gelmeden önce, kuzeydeki büyük karlar ile güneydeki geniş ovalar arasında kalan bu toprakların tamamı, tek bir ailenin kardeşleri olarak bize aitti...";
			link.l1 = "";
			link.l1.go = "question2";
		break;
		
		case "question1_l":
			dialog.text = "Siz solgun yüzlü insanlar gelmeden önce, kuzeydeki büyük kar yığınlarından güneydeki uçsuz bucaksız ovalara kadar bu toprakların tamamı, tek bir ailenin kardeşleri olarak bize aitti...";
			link.l1 = "";
			link.l1.go = "question2";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question2":
			dialog.text = "Bu tapınağı hangi Kızılderili kabilesi inşa etti?";
			link.l1 = "Inka.";
			link.l1.go = "question2_l";
			link.l2 = "Chavins.";
			link.l2.go = "question2_r";
			link.l3 = "Maya.";
			link.l3.go = "question2_l";
			link.l4 = "Aztek.";
			link.l4.go = "question2_l";
			link.l5 = "Arawak.";
			link.l5.go = "question2_l";
		break;
		
		case "question2_r":
			dialog.text = "Halkımız ilerledi, bilgelik kazandı ve yeni ormanları, ovaları, adaları fethetti. Bu tapınağı inşa edenler, Büyük Su'nun ötesindeki ormanlardan geldiler...";
			link.l1 = "";
			link.l1.go = "question3";
		break;
		
		case "question2_l":
			dialog.text = "Halkımız ilerledi, bilgelik kazandı ve yeni ormanları, ovaları ve adaları fethetti. Bu tapınağı inşa edenler, Büyük Su'nun ötesindeki ormanlık topraklardan geldiler...";
			link.l1 = "";
			link.l1.go = "question3";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question3":
			dialog.text = "O muhteşem insanların grubuna kim liderlik etti?";
			link.l1 = "Büyük reis.";
			link.l1.go = "question3_l";
			link.l2 = "Büyük rahip.";
			link.l2.go = "question3_l";
			link.l3 = "Büyük reisin oğlu.";
			link.l3.go = "question3_r";
			link.l4 = "Büyük rahibin oğlu.";
			link.l4.go = "question3_l";
			link.l5 = "Partinin bir lideri yoktu.";
			link.l5.go = "question3_l";
		break;
		
		case "question3_r":
			dialog.text = "Hintli halkı, cesur savaşçılar ve gezginler olarak, yeni bir yere yerleşseler bile her zaman vatanlarını sevdiler ve ona saygı duydular. Evlerine olan sevgilerinin bir göstergesi olarak, tapınakta yuvalarının simgesi olan bir kuş şeklinde bir heykel yaptılar. O heykel arkamda...";
			link.l1 = "";
			link.l1.go = "question4";
		break;
		
		case "question3_l":
			dialog.text = "Hintli savaşçılar, cesur savaşçılar ve gezginler olarak, yeni bir yere yerleşseler bile her zaman vatanlarını sevdiler ve ona saygı duydular. Yurtlarına olan sevgilerinin bir göstergesi olarak, tapınakta evlerinin simgesi olan bir kuş şeklinde bir heykel yaptılar. O, arkamda...";
			link.l1 = "";
			link.l1.go = "question4";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question4":
			dialog.text = "Bu kuşun adı ne?";
			link.l1 = "Albatros.";
			link.l1.go = "question4_l";
			link.l2 = "Eagle.";
			link.l2.go = "question4_l";
			link.l3 = "Akbaba.";
			link.l3.go = "question4_l";
			link.l4 = "Roc.";
			link.l4.go = "question4_l";
			link.l5 = "Condor.";
			link.l5.go = "question4_r";
		break;
		
		case "question4_r":
			dialog.text = "Refah yılları gelip geçti, bir lambanın alevi gibi sönüp gitti ve hayat adayı terk etti. Burada yalnızca tapınak kaldı, eski Hintlilerin büyük gücünün bir hatırası olarak. Son şaman, cesurlara güç veren ve kötülere ceza yağdıran kutsal bir güneş küresini bir kaideye bıraktı. O küre, senden önce burada olan adam tarafından alındı.";
			link.l1 = "";
			link.l1.go = "question5";
		break;
		
		case "question4_l":
			dialog.text = "Refah yılları gelip geçti, bir lambanın alevi gibi sönüp gitti ve hayat adayı terk etti. Burada yalnızca tapınak kaldı, eski Hintlilerin büyük gücünün bir hatırası olarak. Son şaman, cesurlara güç veren ve kötülere ceza yağdıran kutsal bir güneş küresini bir kaideye bıraktı. O küre, senden önce burada bulunan adam tarafından alındı.";
			link.l1 = "";
			link.l1.go = "question5";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question5":
			dialog.text = "O kutsal kürenin adı neydi?";
			link.l1 = "Parlayan güneşin küresi.";
			link.l1.go = "question5_l";
			link.l2 = "Güneş ışınlarının küresi.";
			link.l2.go = "question5_l";
			link.l3 = "Öğle güneşinin küresi.";
			link.l3.go = "question5_l";
			link.l4 = "Yükselen güneşin küresi.";
			link.l4.go = "question5_r";
			link.l5 = "Günbatımı küresi.";
			link.l5.go = "question5_l";
		break;
		
		case "question5_r":
			if (CheckAttribute(pchar, "questTemp.Caleuche.QuestionFail"))
			{
				PlaySound("Voice\English\LE\Chavinavi\Chavinavi_02.wav");
				dialog.text = "Yanlış cevaplar bana yalan söylediğini gösteriyor, beyaz adam! Kötü niyetlerle geldin! Tapınağın ve kutsal alanın koruyucularını atlatmayı başardın, kapının mekanizmasını çözdün - ama yine de benimle ölümcül bir dövüşten kaçamayacaksın. Hazır ol, solgun yüzlü, öleceksin!";
				link.l1 = "Peki, madem ısrar ediyorsun - bakalım ne kadar büyük bir savaşçısın...";
				link.l1.go = "chavinavi_fight";
			}
			else
			{
				dialog.text = "Halkımı ve tapınağımı bu kadar iyi bilmen sana yakışıyor, solgun yüzlü. Şimdi sana inanıyorum. Git ve buraya neden geldiysen onu yerine getir. Kutsal emaneti, bir zamanlar doğan güneşin küresiyle taçlanan, kondorun önündeki kaidenin üzerine yerleştir.\nSonra bana dön. Yum Cimil'e olan bağlılığın ve kardeşlerin tarafından çalınanı kendi isteğinle geri getirme kararın ödüllendirilmeli.";
				link.l1 = "Güveniniz için teşekkür ederim, büyük reis.";
				link.l1.go = "chavinavi_exit";
			}
		break;
		
		case "question5_l":
			PlaySound("Voice\English\LE\Chavinavi\Chavinavi_02.wav");
			dialog.text = "Yanlış cevaplar bana yalan söylediğini gösteriyor, beyaz adam! Kötü niyetlerle geldin! Tapınağın ve kutsal alanın koruyucularını atlatmayı başardın, kapının mekanizmasını çözdün - ama yine de benimle ölümcül bir dövüşten kaçamayacaksın. Hazır ol, solgun yüzlü, öleceksin!";
			link.l1 = "Pekâlâ, madem ısrar ediyorsun - bakalım ne kadar büyük bir savaşçısın...";
			link.l1.go = "chavinavi_fight";
		break;
		
		case "chavinavi_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_Delete("EnemyFight");
			DialogExit();
			n = 1;
			if (MOD_SKILL_ENEMY_RATE > 2) n = 3;
			if (MOD_SKILL_ENEMY_RATE > 4) n = 5;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("TopChavinavi_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Caleuche_TopChavinaviDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "chavinavi_exit":
			DialogExit();
			sld = ItemsFromID("SkullAztec");
			sld.shown = "0";
			sld.useLocation = "KhaelRoa_Treasure_Alcove";
			sld.useLocator = "button01";
			LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
		break;
		
		case "Chavinavi_5":
			PlaySound("Voice\English\LE\Chavinavi\Chavinavi_03.wav");
			dialog.text = "Verdiğin sözü tuttun, soluk yüzlü. Kardeşlerinin çoğu gibi yalancı çıkmadığın için memnunum. Ben de sözümü tutacağım. Al, bu hediyemi kabul et – jaguar savaşçılarının kudretinin simgesi. Yum Cimil’in kendisi bu postu kendi gücünden bir parça ile kutsadı.";
			link.l1 = "Vay canına! Ne kadar da güzel!";
			link.l1.go = "Chavinavi_6";
		break;
		
		case "Chavinavi_6":
			GiveItem2Character(pchar, "KhaelRoa_item");
			Log_Info("You have received jaguar's pelt");
			PlaySound("interface\important_item.wav");
			dialog.text = "Bu sıradan bir post değil. Onu giydiğinde, jaguar savaşçısının gücüne sahip olacaksın. Ateş püsküren ve kurşun saçan silahının gücü on kat artacak, düşmanlarının cesetleriyle savaş alanını doldurabileceksin\nAma hiçbir ölümlü, Yum Cimil’in bu posta yerleştirdiği güce dayanamaz. Onu serbest bıraktığında, bir sonraki gece yarısına kadar seninle kalacak, sonra ise kaybolacak. Dikkatli ol, soluk tenli, ve gücünü önemsiz bir çatışmada boşa harcama.";
			link.l1 = "Teşekkür ederim! Onu sadece düşmanlar tarafından tamamen bunaldığımda kullanacağım.";
			link.l1.go = "Chavinavi_7";
		break;
		
		case "Chavinavi_7":
			dialog.text = "Şimdi git. Ve kardeşlerini bu kutsal odaların huzurunu bozmamaları için uyar. Jaguar savaşçıları soluk tenlilere asla merhamet göstermez ve onlara hiç şans tanımaz.";
			link.l1 = "Elveda, reis.";
			link.l1.go = "Chavinavi_8";
		break;
		
		case "Chavinavi_8":
			DialogExit();
			LAi_SetPlayerType(pchar);
			n = 1;
			if (MOD_SKILL_ENEMY_RATE > 2) n = 3;
			if (MOD_SKILL_ENEMY_RATE > 4) n = 5;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("TopChavinavi_"+i);	
				LAi_SetWarriorType(sld);
				LAi_CharacterDisableDialog(sld);
			}
			AddQuestRecord("Caleuche", "38");
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeIndianRelation(10.0);
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
