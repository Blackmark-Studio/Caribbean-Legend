void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i, n, iTemp, addGold, NextMonth;
	string attrL, sStr, Month;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Bir şey mi istediniz?";
			link.l1 = "Yok, bir şey yok.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// диалоги в ПУ
		case "SharlieEpilog_Pikar_1":
			dialog.text = "Ne insanlar! Kendisi "+GetTitle(NPChar,true)+" "+pchar.lastname+" kendi şahsımda! ";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive"))
			{
				link.l1 = ""+npchar.name+"! Seni burada göreceğimi hiç beklemezdim... Hatta açıkçası, hâlâ hayatta olduğunu bile düşünmemiştim!";
				link.l1.go = "SharlieEpilog_Pikar_2";
			}
			else
			{
				link.l1 = "Gözlerime inanamıyorum... Yakışıklı mı? Ama... nasıl?";
				link.l1.go = "SharlieEpilog_PikarResurrected_1";
			}
			PlaySound("Voice\" + LanguageGetLanguage() + "\LE\Rocur\Rocur_03.wav");
		break;
		
		case "SharlieEpilog_Pikar_2":
			if (IsStateTitle())
			  {
				dialog.text = "Ha-ha! Ama bak, bunu boşuna söyledin. Gördüğün gibi, sapasağlam ayaktayım. İşte, kendime şöyle 'tertemiz' bir gemi almaya karar verdim. Peki ya sen... anlat bakalım: nasıl geldin bu hallere, ha dostum?";
			  }
			  else 
			  {
				dialog.text = "Ha-ha! Bunu boşuna yaptın. Gördüğün gibi, sapasağlamım. Bak, kendime şöyle 'tertemiz' bir gemi almaya karar verdim. Peki ya sen... anlat bakalım: seni buralara hangi rüzgar attı, ha dostum?";
			  }
			link.l1 = "Burada değil. Hadi meyhaneye gidelim – işler bekler.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_WithPikarToTavern");
		break;
		
		case "SharlieEpilog_PikarResurrected_1":
			dialog.text = "Şş... Bağırma öyle. Güzelim artık geçmişte kaldı, sanırım Prens de öyle. Öyle değil mi?";
			link.l1 = "Ama ben kendi gözlerimle gördüm...";
			link.l1.go = "SharlieEpilog_PikarResurrected_2";
		break;

		case "SharlieEpilog_PikarResurrected_2":
			dialog.text = "Beni öldürdüler mi diyorsun? Keşke öyle olsaydı, dostum. Bana inan.";
			link.l1 = "Hadi meyhaneye gidelim. Bana her şeyi anlatırsın.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_WithPikarToTavern");
		break;
		
		case "SharlieEpilog_Captain_1":
			dialog.text = "...";
			link.l1 = "Demek ki, siz ' pinesinin yeni sahibisiniz"+GetShipName("Ulysse")+"'?";
			link.l1.go = "SharlieEpilog_Captain_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\z_arest_02.wav");
		break;
		
		case "SharlieEpilog_Captain_2":
			dialog.text = "Ben. "+GetFullName(npchar)+", madem bu kadar merak ediyorsunuz. Peki siz kimsiniz?";
			link.l1 = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+", ve bu gemiyi sizden satın almak istiyorum.";
			link.l1.go = "SharlieEpilog_Captain_3";
		break;
		
		case "SharlieEpilog_Captain_3":
			dialog.text = "Tabii, tabii, çok duydum. Ben de artık bu tekneyi isteyenlerden kurtuldum sanmıştım. Sizi hayal kırıklığına uğratmak zorunda kalacağım, "+GetTitle(NPChar,true)+" - '"+GetShipName("Ulysse")+"' artık benim, ve çok yakında onunla Bordeaux'ya gidiyorum. Ticaret işine girip de ilk fırsatta hemen anlaşmayı bozmak istemem. Uğursuzluk getirir, bilirsiniz.";
			link.l1 = "Bordeaux mu dediniz? İlginç... Belki de size kârlı bir teklifim olur. Bunu bir bardak rom eşliğinde konuşsak mı?";
			link.l1.go = "SharlieEpilog_Captain_4";
		break;
		
		case "SharlieEpilog_Captain_4":
			dialog.text = "Ne romdan ne de kârlı tekliflerden vazgeçmek âdetim değildir. Hadi gidelim.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_WithPikarToTavern");
		break;
		
		// диалоги в таверне
		case "SharlieEpilog_Pikar_5":
			if (IsStateTitle())
			  {
				dialog.text = "Pekâlâ, senin şerefine, "+GetTitle(npchar,false)+" "+pchar.lastname+"   Biliyordum, senin gibi bir adam Tiraks’ın uşağı olarak fazla kalmaz. Ama bu kadar önemli biri olacağını... şaşırtmayı biliyorsun, gerçekten.";
				link.l1 = "Ha-ha. Kim konuşuyor, bak hele. Demek tüccar olmaya karar verdin?";
			  }
			  else 
			  {
				dialog.text = "Bir buluşmaya! Ense kökümde hissettim, yine karşılaşacağız.";
				link.l1 = "Ha-ha. Ona! Demek tüccar olmaya karar verdin?";
			  }
			
			link.l1.go = "SharlieEpilog_Pikar_6";
		break;

		case "SharlieEpilog_Pikar_6":
			dialog.text = "İnsanın ömrü boyunca iki üç dublo için boynunu cellada uzatacak hali yok ya. Gerekli yerlere yağ sürdüm, gereksizlerin ağzını kapattım – işte bak: artık ne hırsızım ne korsan, saygın bir tüccarım.";
			link.l1 = "Bu tam bir sürpriz oldu. Şimdi artık, yeni yetme bir pinas kaptanına teklif etmeyi düşündüğüm şeyi sana nasıl sunacağımı bilemiyorum "+GetShipName("Ulysse")+"'.";
			link.l1.go = "SharlieEpilog_Pikar_7";
		break;

		case "SharlieEpilog_Pikar_7":
			dialog.text = "Hadi ama, anlat olduğu gibi. Biz seninle yüz yıldır tanışıyoruz.";
			link.l1 = "Biliyor musun... Karayiplere buraya, senin satın aldığın pinasla geldim. Onun açık artırmaya çıkarıldığını duyunca, onu geri almak istedim - ve onunla eve, Fransa'ya dönmek niyetindeydim.";
			link.l1.go = "SharlieEpilog_Pikar_8";
		break;

		case "SharlieEpilog_Pikar_8":
			dialog.text = "Ha-ha-ha-ha! Bekle... ah-ha-ha-ha-ha!..";
			link.l1 = "Peki, komik olan ne?";
			link.l1.go = "SharlieEpilog_Pikar_9";
		break;

		case "SharlieEpilog_Pikar_9":
			dialog.text = "Ben daha ihaleyi yeni kazanmıştım, yanıma bir zampara geldi – genç, bakımlı biri: beni ve eşyalarımı Bordeaux'ya götür, sevgili dostum, karşılığında iyi para alırsın, dedi. Ne parası – koca bir lanet çuval dolusu altın teklif etti.";
			link.l1 = "Öyle mi? Ha-ha. Gerçekten komikmiş. Peki sen ne yaptın? Kabul ettin mi?";
			link.l1.go = "SharlieEpilog_Pikar_10";
		break;

		case "SharlieEpilog_Pikar_10":
			dialog.text = ""+pchar.name+",   Atlantik'i sıradan bir geçiş için bir yığın altından vazgeçecek kadar enayi değilim. Evet, birkaç ay kuru bisküvi kemirip tuzlu et çiğnemek gerekecek. Ama biliyor musun, ben boynumu daha azı için de riske atmak zorunda kalmıştım. O yüzden, tabii ki bu işte varım.";
			link.l1 = "Öyleyse sana da aynı teklifi sunabilirim. Beni Bordeaux'ya götürürsen, aynı yığınla altın senin olacak.";
			link.l1.go = "SharlieEpilog_Pikar_11";
		break;

		case "SharlieEpilog_Pikar_11":
			dialog.text = "Yolcu olmaya hazır mısın? Bizde kurallar bellidir – gemide tek bir kaptan olur. Ve benim gemimde o kaptan benim.";
			link.l1 = "Neden olmasın? Bir nefes alırım, hayatı düşünürüm. Belki de gerçekten bir yerde kalıp, sakinleşmem gerekiyordur. Şimdi bunu hayal etmek bile zor, ama belki bunda bir anlam vardır. Sonuçta sen bile artık savaşlardan uzak durmaya karar verdin.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1.go = "SharlieEpilog_Pikar_12_wife";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Pikar_12";
			}
		break;
		
		case "SharlieEpilog_Pikar_12_wife":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive"))
			{
				dialog.text = "Ah, benim de seninki gibi güzel bir karım olsaydı, belki ben de denizi bırakır, bir köşeye yerleşirdim: bir ev yapar, şarap satar, geçinirdim. Neyse ki geçim derdim yok artık – sen beni İspanyolların elinden kurtardıktan sonra zamanı boşa harcamadım.";
			}
			else
			{
				dialog.text = "Ah, benim de seninki gibi güzel bir karım olsaydı, belki ben de denizi bırakır, bir köşeye yerleşirdim: bir ev yapar, şarap satarak geçinirdim. Neyse ki yaşamak için paramız olurdu – o dul plantasyon sahibinden kalan miras az buz değilmiş.";
			}
			link.l1 = "Karım! Şeytan, "+npchar.name+", henüz onunla bu konuda konuşmadım.";
			link.l1.go = "SharlieEpilog_Pikar_13_wife";
		break;
		
		case "SharlieEpilog_Pikar_13_wife":
			dialog.text = "Bunun için daha fazlasıyla vaktin var. Ben de teknemi adam akıllı donatmalıyım. Tüm işlerini halledince kıçını buraya getir. Yola çıkmadan önce güzel bir eğlence yaparız.";
			link.l1 = "İşte bu tam bana göre! Merak etme, fazla beklemene gerek kalmayacak.";
			link.l1.go = "SharlieEpilog_Pikar_14_wife";
		break;
		
		case "SharlieEpilog_Pikar_14_wife":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive")) {AddQuestRecord("SharlieEpilog", "11_1");}
			else {AddQuestRecord("SharlieEpilog", "11_5");}
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_Pikar_12":
			dialog.text = "Ah, bir karım olsaydı, belki ben de denizi bırakır, bir köşeye yerleşirdim: bir ev yapar, biraz da şarap satarak geçinirdim. Ama şimdilik... deniz benim evim.";
			link.l1 = "Plantasyonlarımdan şarapla, ha-ha! Bordeaux'da, "+npchar.name+", oradaki kızlar tam göz alıcı! Belki sen de kendine birini bulursun – aşk işlerinde hiç fena değiller. Şunu düşündüm: önümüzdeki aylarda göreceğimiz tek suratlar senin tayfanın yüzleri olacak. Yola çıkmadan önce şu yerel genelevde güzel bir eğlence yapalım.";
			link.l1.go = "SharlieEpilog_Pikar_13";
		break;
		
		case "SharlieEpilog_Pikar_13":
			dialog.text = "Siz, Mösyö, ne teklif edeceğinizi biliyorsunuz. Bütün işlerinizi hallettikten sonra, kıçınızı buraya getirin. Sonra geneleve de uğrarız, merak etmeyin.";
			link.l1 = "O halde, vakit kaybetmeyelim. Hadi başlayalım!";
			link.l1.go = "SharlieEpilog_Pikar_14";
		break;
		
		case "SharlieEpilog_Pikar_14":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive")) {AddQuestRecord("SharlieEpilog", "11_2");}
			else {AddQuestRecord("SharlieEpilog", "11_6");}
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_PikarResurrected_3":
			dialog.text = "Özgürlük için!";
			link.l1 = "Ve senin için, Jean! Senin dirilişine! Hâlâ inanamıyorum. Nasıl?";
			link.l1.go = "SharlieEpilog_PikarResurrected_4";
		break;

		case "SharlieEpilog_PikarResurrected_4":
			dialog.text = "Beni savaş alanından sürükleyip çıkardılar – can çekişiyordum, tepeden tırnağa kana bulanmıştım. Bir barakaya attılar ve orada ölüme terk ettiler, sanki bir leşmişim gibi. Köleler arasında uyanık bir adam vardı – Moko. İşte o, hayatımı kurtardı: yarayı kendi gömleğimden kopardığı bir parça ile sardı, bana su verdi.";
			link.l1 = "Yani, İspanyollar seni bunca şeyden sonra sağ mı bıraktı?";
			link.l1.go = "SharlieEpilog_PikarResurrected_5";
		break;

		case "SharlieEpilog_PikarResurrected_5":
			dialog.text = "Gördüğün gibi. Ama bunu iyi niyetlerinden yapmadılar. İntikam istiyorlardı – sıkı sorgu, işkence. Yaktılar, dövdüler, kestiler. Gözümü oyacaklarını söylediler – sırf bana olan büyük sevgilerinden. Ama sonra biri, korsanların benim için intikam hazırlığında olduğunu ve bıçaklarını bilemeye başladıklarını fısıldadı. Plantasyon sahibinin gözü seğirmeye başladı. Bizim tayfanın ziyaretini beklemeden, apar topar Campeche’deki mülklerine kaçtı. Beni, Moko’yu ve diğerlerini de yanına aldı, şahit kalmasın diye. Geri kalanlara da öldüğümü söylediler – ve mesele orada kapandı.";
			link.l1 = "Peki, sonra ne oldu? Nasıl özgürlüğüne kavuştun? Ve nasıl oldu da burada buldun kendini, Allah aşkına?";
			link.l1.go = "SharlieEpilog_PikarResurrected_6";
		break;

		case "SharlieEpilog_PikarResurrected_6":
			dialog.text = "Şans, dostum. Kör, pis bir şans. Beni plantasyona götürdüler – işkence devam etti. O alçak, acımı her saniye zevkle izlemeye karar vermişti, ama her geçen gün daha da güçsüzleşti... ta ki sıtmadan geberene kadar. Ondan sonra kimsenin bana aldırdığı yoktu. Beni tarlaya sürdüler, hayvan gibi, bir de üstüne bolca kırbaçladılar.";
			link.l1 = "Hâlâ anlamıyorum, oradan nasıl kurtuldun?";
			link.l1.go = "SharlieEpilog_PikarResurrected_7";
		break;

		case "SharlieEpilog_PikarResurrected_7":
			dialog.text = "Christopher Myngs'i duydun mu?";
			link.l1 = "Alonso bir şeyler söylemişti... Campeche baskını! O zaman İspanyolları fena dağıtmışlardı. Yani seni onlar mı kurtardı?";
			link.l1.go = "SharlieEpilog_PikarResurrected_8";
		break;

		case "SharlieEpilog_PikarResurrected_8":
			dialog.text = "Tam olarak değil. Kendimizi kendimiz kurtardık. Muhafızlar İngiliz bukanyerleriyle çarpışırken, Moko'yla birlikte barakanın çatısında bir gedik bulduk ve isyan başlattık. Silah deposunu ve o merhum alçak plantasyoncunun karısının hazinesini ele geçirdik.";
			link.l1 = "Hazine mi?! Bu beklenmedikti.";
			link.l1.go = "SharlieEpilog_PikarResurrected_9";
		break;

		case "SharlieEpilog_PikarResurrected_9":
			dialog.text = "Fazla düşünmedik – silahlarımızı ve eşyalarımızı alıp ormana daldık. İki gün boyunca sık ormanda ilerledik, sonunda Kan Peç yerlilerinin köyüne rastladık. Şamanları görünüşte İspanyollara boyun eğiyordu ama onlara pek de sıcak bakmıyordu. Moko onunla hemen anlaştı – bizi köyde barındırdılar, karşılığında cephanemizin yarısını ve kiminle olursa olsun savaşta yardımımızı istediler. İşte böyle, orada bir buçuk yıl kaldım.";
			link.l1 = "Artık eskisi gibi değilsin, Jean. Bundan sonra sen Şanslısın.";
			link.l1.go = "SharlieEpilog_PikarResurrected_10";
		break;

		case "SharlieEpilog_PikarResurrected_10":
			dialog.text = "Ha-ha. İtirazım yok. Sonra bizim batabilde bir Fransız vaiz çıktı karşımıza. Hemen anladık: oradan prangayla değil, özgür çıkmak için bir şans. Onun korumalarını kandırdık – ve kısa süre sonra Tortuga'ya doğru yelken açtık.\nSonrası, senin de tahmin edeceğin gibi, artık ölümle köşe kapmaca oynamamaya karar verdim. Eski işimi bıraktım... ve fırsatını bulunca bir şeyler satın aldım."+GetShipName("Ulysse")+"'.\n"+"Peki ya sen? Nasıl geldin bu hallere? Biliyordum, senin gibi gözü kara biri Tiraks'ın uşağı olarak fazla dayanmaz. Ama böyle önemli bir adam olacağını... şaşırtmayı iyi biliyorsun, şeytan alası.";
			link.l1 = "Ha-ha. Kim konuşuyor bak sen. Demek tüccar olmaya karar verdin?";
			link.l1.go = "SharlieEpilog_Pikar_6";
		break;
		
		case "SharlieEpilog_Captain_5":
			dialog.text = "Denizde olanlar için!";
			link.l1 = "Ve hanımefendi şansa!";
			link.l1.go = "SharlieEpilog_Captain_6";
		break;

		case "SharlieEpilog_Captain_6":
			dialog.text = "Pekâlâ, sadede gelelim. Bana ne teklif etmek istediniz?";
			link.l1 = "Bordeaux'ya gidiyorsunuz... Görüyorsunuz, ben de oraya gidiyorum.";
			link.l1.go = "SharlieEpilog_Captain_7";
		break;

		case "SharlieEpilog_Captain_7":
			dialog.text = "Sizi gemime almamı mı istiyorsunuz? Bildiğim kadarıyla sizin de bir geminiz olmalı. Belki de koca bir filonuz vardır. Ama yine de başkasının gemisinde yolculuk etmeye karar verdiniz. Doğru mu anlıyorum?";
			link.l1 = "Aynen öyle. Son yaşadıklarımız beni düşündürdü: belki de artık demir atıp biraz durulmanın zamanı gelmiştir... Sanırım geminizde sıradan bir yolcu olmak, yeni hayatın ritmine ayak uydurup uyduramayacağımı anlamama yardımcı olacak.";
			link.l1.go = "SharlieEpilog_Captain_8";
		break;

		case "SharlieEpilog_Captain_8":
			dialog.text = "Hmm... Demek artık boş yere boynunuzu riske atmak istemiyorsunuz? Tanıdık bir his. Ben de... Neyse, önemli değil. Gemide sizin için de, maiyetiniz için de yer bulunur. Yolculuğunuzun ücreti zaten genç bir Fransız tarafından ödendi – hem de hızlı gitmemiz için, o yüzden ambarları yüklemeyeceğim. Ödeme meselesine gelince...";
			link.l1 = "Endişelenmeyin, kaptan. İşvereniniz kadar cömertim ve aynı miktarı ödemeye hazırım.";
			link.l1.go = "SharlieEpilog_Captain_9";
		break;

		case "SharlieEpilog_Captain_9":
			dialog.text = "Mükemmel! O zaman anlaştık mı?";
			link.l1 = "Anlaştık! Buna içilir!";
			link.l1.go = "SharlieEpilog_Captain_10";
		break;

		case "SharlieEpilog_Captain_10":
			dialog.text = "Evet, rom harika... Gemiyi adam etmek ve gerekli her şeyi almak için iki haftaya ihtiyacım olacak. Ondan sonra yola çıkabiliriz.";
			link.l1 = "O zaman iki hafta sonra yine burada buluşuruz. Görüşmek üzere, kaptan.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1.go = "SharlieEpilog_Captain_11_wife";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Captain_11";
			}
		break;
		
		case "SharlieEpilog_Captain_11_wife":
			DialogExit();
			AddQuestRecord("SharlieEpilog", "11_3");
			AddQuestUserData("SharlieEpilog", "sName", GetFullName(npchar));
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_Captain_11":
			DialogExit();
			AddQuestRecord("SharlieEpilog", "11_4");
			AddQuestUserData("SharlieEpilog", "sName", GetFullName(npchar));
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_Pikar_WaitInTavern":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Ne dersin, dostum, işlerini hallettin mi? Şu kümese nasıl eğlenilir gösterelim mi?";
				link.l1 = "Daha zamanı değil, "+npchar.name+",   hâlâ   halletmem   gereken   birkaç   işim   kaldı.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Kaptan, gemiye binmeye hazır mısınız?";
				link.l1 = "Ne yazık ki, meslektaşım, hâlâ yapacak işlerim var.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "SharlieEpilog_Pikar_WaitInTavern";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				// только если знаком с Пикаром и поговорил с женой
				link.l2 = "Hey, meyhaneci! Herkese içki benden! Ve öyle sıradan bir şey değil, en iyisinden getir bakalım!";
				link.l2.go = "SharlieEpilog_Pikar_WaitInTavern_2";
			}
		break;
		
		case "SharlieEpilog_Pikar_WaitInTavern_2":
			dialog.text = "...";
			link.l1 = "Bizim için, dostum. Tuzlu rüzgara, uçsuz bucaksız denize ve hep çağıran, hep ulaşılamayan ufka...";
			link.l1.go = "SharlieEpilog_FrameInSea";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_FrameInSea":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_FrameInSea");
		break;
		
		case "SharlieEpilog_Mary_1":
			dialog.text = "...";
			link.l1 = ""+npchar.name+", tatlım, seninle babam hakkında konuşmak istiyorum.";
			link.l1.go = "SharlieEpilog_Mary_2";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Mary_2":
			dialog.text = "Ne oldu, sevgilim? Umarım onunla her şey yolundadır, di mi?";
			link.l1 = "Pek istediğimiz gibi değil, doğrusu. Onun fazla zamanı kalmamış gibi görünüyor ve en çok endişelendiren мысль şu ki, son yolculuğuna çıkmadan önce beni bir daha göremeyebilir.";
			link.l1.go = "SharlieEpilog_Mary_3";
		break;

		case "SharlieEpilog_Mary_3":
			dialog.text = ""+pchar.name+"...";
			link.l1 = "Biliyorum, canım, biliyorum... Ama hayat böyle. Keşke onunla tanışabilseydiniz. O da benim ne kadar harika bir eşim olduğunu görsün ve bize hayır duasını versin.";
			link.l1.go = "SharlieEpilog_Mary_4";
		break;

		case "SharlieEpilog_Mary_4":
			dialog.text = "Ya ona hoş gelmezsem ne olacak, di mi? Sonuçta ben soylu bir aileden gelmiyorum...";
			link.l1 = "Saçmalık, "+npchar.name+", ona nasıl hoş gelmezsin ki? Sen tam bir harikasın! Benim kalbimi fethettiysen, onun kalbini de fethedersin.";
			link.l1.go = "SharlieEpilog_Mary_5";
		break;

		case "SharlieEpilog_Mary_5":
			dialog.text = "Gerçekten böyle mi düşünüyorsun, sevgilim? O zaman ona bir an önce gitmemiz gerek.";
			link.l1 = "Tam da bunu yapacağım. Hatta bize bir gemi bile buldum. İki hafta sonra yola çıkıyoruz.";
			link.l1.go = "SharlieEpilog_Mary_6";
		break;

		case "SharlieEpilog_Mary_6":
			dialog.text = "Gemi mi? Kendi teknemizle gitmeyecek miyiz?";
			link.l1 = "Hayır, tatlım. Biz pinasla gideceğiz '"+GetShipName("Ulysse")+"'.   Bu gemiyle Karayiplere geldim — bu gemiyle de ayrılacağım.";
			link.l1.go = "SharlieEpilog_Mary_7";
		break;

		case "SharlieEpilog_Mary_7":
			dialog.text = "Ve sen kaptan olmayacak mısın?";
			link.l1 = "Er ya da geç bu rolden zaten vazgeçmem gerekecekti. Umarım, bu sadece geçicidir. Ama her halükarda, gelecekte beni nelerin beklediğini hissetmek fena olmaz.";
			link.l1.go = "SharlieEpilog_Mary_8";
		break;

		case "SharlieEpilog_Mary_8":
			dialog.text = "Peki ya subaylarımız? Hepsini yanımıza alamayız ki. Hem burada seni bekleyeceklerini de sanmam.";
			link.l1 = "Öhöm... Evet, haklısın. Her biriyle konuşmam gerekecek ve muhtemelen sonsuza dek veda edeceğim. Kolay olmayacak tabii ki — birlikte neler yaşadığımızı düşününce.";
			link.l1.go = "SharlieEpilog_Mary_9";
		break;
			
		case "SharlieEpilog_Mary_9":
			dialog.text = "Belki de veda etmeden önce meyhanede küçük bir ziyafet vermek gerekir?";
			link.l1 = "Ben de bunu düşündüm, sevgilim. Biliyor musun... galiba haklısın. Gerçekten de iyi bir fikir bu.";
			link.l1.go = "exit";
			link.l2 = "Bunun iyi bir fikir olduğunu sanmıyorum. Sessizce ayrılalım... Böyle herkes için daha iyi olur, sanırım. Belki sadece en yakın dostlarımızı çağırırız...";
			link.l2.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_FarewellOfficers");
		break;
		
		case "SharlieEpilog_Helena_1":
			dialog.text = "...";
			link.l1 = "Sevgilim, seninle babam hakkında konuşmak istiyorum.";
			link.l1.go = "SharlieEpilog_Helena_2";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Helena_2":
			dialog.text = "Tabii ki, "+pchar.name+". Umarım onunla her şey yolundadır?";
			link.l1 = "Tam olarak değil. O zaten uzun zamandır hasta ve korkarım ki hastalığı yakında galip gelecek... Babam tüm bunlara büyük bir cesaretle katlanıyor. Onu gerçekten endişelendiren tek şey, beni bir daha göremeyebileceği. Onu ziyaret etmek istiyorum... ve seni onunla tanıştırmak. Evliliğimiz için onun hayır duasını almak.";
			link.l1.go = "SharlieEpilog_Helena_3";
		break;

		case "SharlieEpilog_Helena_3":
			dialog.text = "Onunla tanışmak için sabırsızlanıyorum, sevgilim. Ne zaman yola çıkıyoruz?";
			link.l1 = "İki hafta sonra. Ama hepsi bu kadar değil. Kendi gemimizle gitmeyeceğiz. Eski Dünya'ya bizi bir pinas götürecek. "+GetShipName("Ulysse")+" -   işte beni buraya bir zamanlar getiren o adam.";
			link.l1.go = "SharlieEpilog_Helena_4";
		break;

		case "SharlieEpilog_Helena_4":
			dialog.text = ""+pchar.name+", ama uzun bir yolculuktan önce gemi değiştirmek uğursuzluk getirir.";
			link.l1 = "Gemiyi değiştirmeyeceğiz, sevgilim. Yolcu olacağız.";
			link.l1.go = "SharlieEpilog_Helena_5";
		break;

		case "SharlieEpilog_Helena_5":
			dialog.text = "Ama... sevgilim, anlamıyorum...";
			link.l1 = "Gerekli, "+npchar.name+". Er ya da geç kaptanlığı bırakmam gerekecek. Ve şimdiden, bunun bana neler hissettireceğini bilmek istiyorum.";
			link.l1.go = "SharlieEpilog_Helena_6";
		break;

		case "SharlieEpilog_Helena_6":
			dialog.text = "Eğer böyle karar verdiysen... Peki ya subaylarımız? Hepsini yanımıza alamayız ki. Ayrıca, burada seni bekleyeceklerini de sanmıyorum.";
			link.l1 = "Öhöm... Evet, haklısın. Her biriyle konuşmam gerekecek ve muhtemelen sonsuza dek veda edeceğim. Kolay olmayacak, birlikte neler yaşadığımızı düşününce.";
			link.l1.go = "SharlieEpilog_Helena_7";
		break;
			
		case "SharlieEpilog_Helena_7":
			dialog.text = "Belki de veda etmeden önce meyhanede küçük bir ziyafet vermek gerekir?";
			link.l1 = "Ben de bunu düşündüm, sevgilim. Biliyor musun... galiba öyle yapacağız. Gerçekten de iyi bir fikir.";
			link.l1.go = "exit";
			link.l2 = "Bunun iyi bir fikir olduğunu sanmıyorum. Sessizce ayrılalım... Böyle herkes için daha iyi olur sanırım. Ancak, belki en yakın dostlarımızı davet edebiliriz...";
			link.l2.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_FarewellOfficers");
		break;
		
		// Диалог с Алонсо в таверне Сен-Пьера
		case "SharlieEpilog_AlonsoInTavern":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				dialog.text = "Kaptan... Meyhaneciyle konuştum bile – elindeki en iyi içkiyi hazırladı. Ne zaman başlıyoruz?";
				link.l1 = "Şimdi hemen! Hey, meyhaneci! Herkese içki benden!";
				link.l1.go = "SharlieEpilog_AlonsoInTavern_1";
			}
			else
			{
				dialog.text = "Kaptan, bana 'Ulysse'yi nasıl öğrendiğinizi anlatacağınıza söz vermiştiniz.";
				link.l1 = "Hatırlıyorum, hatırlıyorum. Hey, meyhaneci! Bu masaya en iyi romdan getir.";
				link.l1.go = "SharlieEpilog_AlonsoInTavern_3";
			}
			link.l2 = "Erken, "+npchar.name+".   Hâlâ   halletmem   gereken   acil   işlerim   var.";
			link.l2.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_AlonsoInTavern";
		break;
		
		case "SharlieEpilog_AlonsoInTavern_1":
			dialog.text = "...";
			link.l1 = "Ne dersin, dostum, çağır herkesi – Saint-Pierre'e gerçek denizciler nasıl eğlenir, gösterelim!";
			link.l1.go = "SharlieEpilog_AlonsoInTavern_2";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_AlonsoInTavern_2":
			dialog.text = "Ha-ha! Kaptan, inanmazsınız – onları çoktan çağırdım!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_FrameInSea";
		break;
		
		case "SharlieEpilog_AlonsoInTavern_3":
			dialog.text = "...";
			link.l1 = "Bize, "+npchar.name+"   Şansa ve yelkenlerimizi dolduran rüzgara!";
			link.l1.go = "SharlieEpilog_FrameInSea";
			DelLandQuestMark(npchar);
		break;
		
		// На пинасе Улисс
		case "SharlieEpilog_Alonso_1":
			dialog.text = "Ne fırtına kopardık, kaptan. Ha-ha. Sanırım meyhaneyi tam bir yıkımdan sadece meyhanecinin azıcık rom stoğu kurtardı.";
			link.l1 = "Hatırlatma, "+npchar.name+",   şimdi   biraz   rahatladım   ancak.";
			link.l1.go = "SharlieEpilog_Alonso_2";
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "tutorial_4", "", -1);
			CharacterTurnByLoc(pchar, "quest", "quest6");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "tutorial_5", "", -1);
			CharacterTurnByLoc(npchar, "quest", "quest7");
		break;
		
		case "SharlieEpilog_Alonso_2":
			dialog.text = "Nasıl isterseniz, efendim "+pchar.lastname+". Ha-ha. Ama Martinique'e krallar gibi veda ettik. Orada sizin gidişinizi daha uzun süre unutamayacaklar.";
			link.l1 = "Bence biraz abarttık, meyhaneciyi sandala bindirip Le François'ya içki almaya gönderdik.";
			link.l1.go = "SharlieEpilog_Alonso_2_1";
		break;
		
		case "SharlieEpilog_Alonso_2_1":
			if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2)
				{
					dialog.text = "Ha-ha-ha. Onun için endişelenmeyin. Bu günlerde öyle bir servet kazandı ki, bir çiftlik alabilir, üstüne bir de unvan sahibi olabilir.";
				}
			else
				{
					dialog.text = "Ha ha ha. Onun için endişelenmeyin. Bu günlerde öyle çok altın kazandı ki, bir çiftlik alabilir, üstüne bir de unvan sahibi olur. Keşke subaylardan biriyle konuşmuş olsaydınız. Onların eksikliğini hissedeceğiz.";
				}
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Alonso_3";
		break;
		
		case "SharlieEpilog_Alonso_3":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
				{
					sld = CharacterFromID("Helena");
					locCameraFromToPos(-8.97, 6.39, -12.78, true, -8.54, 4.94, -13.90);
				}
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
				{
					sld = CharacterFromID("Mary");
					locCameraFromToPos(-3.62, 4.03, 2.30, true, -4.98, 2.62, 3.26);
					// locCameraFromToPos(-4.13, 4.23, 2.55, true, -5.71, 2.54, 3.58);
				}
				dialog.text = "Görünüşe göre, "+sld.name+" hâlâ size kızgın, çünkü bütün gece boyunca ortada yoktunuz.";
			}
			else
			{
				dialog.text = "Şu tüccarla olan meselede… orada siz, kaptan, gerçekten biraz fazla gittiniz.";
			}
			link.l1 = "Lanet olsun, ille de Jean'la şu yerel dükkâna girmemiz mi gerekiyordu…";
			link.l1.go = "SharlieEpilog_Alonso_4";
		break;
		
		case "SharlieEpilog_Alonso_4":
			dialog.text = "Sizi nasıl yakalayamadılar ki? Ne komik olurdu - "+GetTitle(PChar,true)+" birkaç şişe şarap çalmaya çalışırken yakalandı.";
			link.l1 = "Komik mi buluyorsun, "+npchar.name+",   ama ben   her şeyin   yarısını bile hatırlamıyorum.   En son bu kadar sarhoş olduğumda... sanırım... sanırım hiç olmamıştı.";
			link.l1.go = "SharlieEpilog_Alonso_5";
			locCameraFromToPos(-8.74, 6.30, 7.38, true, -14.34, 4.16, 6.56);
		break;
		
		case "SharlieEpilog_Alonso_5":
			dialog.text = "O zaman ilk adım bizden, kaptan. Ha-ha. Hoşuma gitti. Tekrar yapardım. Ne zaman dönüyoruz dediniz?";
			link.l1 = "Gitsen iyi olur, eşyalarımıza bir bak bakalım. Her şeyi aldık mı? Ben sonra inerim – şu an ambarın havası bana hiç iyi gelmez.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_UlysseInSea_8");
		break;
		
		// диалог с Алонсо у горы золота
		case "SharlieEpilog_Alonso_11": // этап 1
			dialog.text = "...";
			link.l1 = "Şuna bir bak... gemi nasıl da sarsıldı, harika değil mi.";
			link.l1.go = "SharlieEpilog_Alonso_12";
			SharlieEpilog_GoldInTheDeck_1_1();
		break;
		
		case "SharlieEpilog_Alonso_12":
			dialog.text = "Burada ise tam bir lanet olası altın yığını var, kaptan!";
			link.l1 = "Görüyorum, "+npchar.name+".   Bütün bunları hemen sandıklara saklamamız gerek, mürettebat görmeden.   Onlara böyle bir ayartı hiç lazım değil.";
			link.l1.go = "SharlieEpilog_Alonso_13";
		break;
		
		case "SharlieEpilog_Alonso_13":
			dialog.text = "Hayır, dayanamam...";
			link.l1 = "Ne?";
			link.l1.go = "exit";
			locCameraFromToPos(-1.28, 7.70, -10.26, true, 0.74, 5.42, -9.49);
			AddDialogExitQuestFunction("SharlieEpilog_GoldInTheDeck_2");
		break;
			
		case "SharlieEpilog_Alonso_21": // этап 2
			dialog.text = "...";
			link.l1 = "Hey, ne yapıyorsun?";
			link.l1.go = "SharlieEpilog_Alonso_22";
			// SharlieEpilog_GoldInTheDeck_6();
		break;
		
		case "SharlieEpilog_Alonso_22":
			dialog.text = "...";
			link.l1 = "Hadi kalk. Zamanını buldun...";
			link.l1.go = "SharlieEpilog_Alonso_23";
		break;
		
		case "SharlieEpilog_Alonso_23":
			dialog.text = "Bize katılın, kaptan.";
			link.l1 = "Kalk, artık saçmalamayı bırak.";
			link.l1.go = "SharlieEpilog_Alonso_24";
		break;
		
		case "SharlieEpilog_Alonso_24":
			dialog.text = "Rahatlayın biraz. Bunu hissetmeniz lazım.";
			link.l1 = "Pekâlâ, canın cehenneme. Hadi bakalım, çekil biraz.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GoldInTheDeck_7");
		break;
		
		case "SharlieEpilog_Alonso_31": // этап 3
			dialog.text = "Her zaman böyle yapmayı hayal etmiştim...";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Alonso_32";
			SharlieEpilog_GoldInTheDeck_10();
		break;
		
		case "SharlieEpilog_Alonso_32":
			dialog.text = "Harika bir his, değil mi, kaptan?";
			link.l1 = "Ha-ha-ha. Karayipler'e geldim, sadece kardeşimin nasıl olduğunu öğrenmek için. Babam kesinlikle böyle bir son beklemiyordu. Ha-ha!";
			link.l1.go = "SharlieEpilog_Alonso_33";
		break;
		
		case "SharlieEpilog_Alonso_33":
			dialog.text = "Bayım "+GetTitle(NPChar,false)+" "+pchar.lastname+"... Ha-ha! Takımadalara ilk geldiğinizde nasıldınız, hatırlıyor musunuz?";
			link.l1 = "Tabii ki hatırlıyorum. Ha-ha. Şimdi güvertede dolaşan o zamane züppeyle bir zamanlar aynı kişi olduğuma inanmak zor. Şu lanetli Karayiplerde neler yaşamadım ki… Entrikalar, ölüler, kardeşim Kukulkan…";
			link.l1.go = "SharlieEpilog_Alonso_34";
		break;
		
		case "SharlieEpilog_Alonso_34":
			dialog.text = "Şansınız gerçekten yaver gitmiş, kaptan. Böyle bir servet yapmak ve hâlâ hayatta olmak… herkesin harcı değil.";
			link.l1 = "Eh işte. Tamam, yeter bu aylaklık. Ne olur ne olmaz – birisi gerçekten fark edebilir.";
			link.l1.go = "exit";
			locCameraSleep(true);
			AddDialogExitQuestFunction("SharlieEpilog_GoldInTheDeck_11");
		break;
		
		// диалоги в катсцене с брашпилем
		case "SharlieEpilog_windlass_1":
			dialog.text = "...";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				link.l1 = "Bak dostum, bu gemideki ırgatın emniyet mandalı hiç güven vermiyor bana. Birinin yanlışlıkla onu devre dışı bırakmasından korkuyorum.";
			}
			else
			{
				link.l1 = "Dinleyin kaptan, bu gemideki ırgatın emniyet mandalı hiç hoşuma gitmiyor. Fazla güvenilir değil. Birisi yanlışlıkla onu yerinden çıkarıverirse, kötü olur.";
			}
			link.l1.go = "SharlieEpilog_windlass_2";
			locCameraFromToPos(-7.57, 9.68, -21.21, true, -9.79, 7.76, -20.01);
		break;
		
		case "SharlieEpilog_windlass_2":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Hadi ama, "+pchar.name+", gemide herkes biliyor ki…";
			}
			else
			{
				dialog.text = "Hadi ama kaptan. Kimin aklına gelir ki...";
			}
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_windlass_3");
		break;
		
		case "SharlieEpilog_windlass_3": // диалог Пикара и дворянина
			dialog.text = "Hey, sen, kalın kafalı... Ne haltlar karıştırıyorsun? Sana kimse yamuk bacaklarını her yere sokmamayı öğretmedi mi?";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_windlass_4";
			locCameraFromToPos(-10.28, 9.94, -22.90, true, -9.29, 7.86, -21.36);
			NPCsLookEachOther("SharlieEpilog_Pikar", "SharlieEpilog_Bernard_Clone");
			CharacterTurnByChr(pchar, CharacterFromID("SharlieEpilog_Bernard_Clone"));
		break;
		
		case "SharlieEpilog_windlass_4":
			dialog.text = "...";
			link.l1 = "Sakin ol, kendini unutma! Ben bir soyluyum ve asla izin vermem...";
			link.l1.go = "SharlieEpilog_windlass_5";
		break;
		
		case "SharlieEpilog_windlass_5":
			dialog.text = "Benim gemimde sen hiç kimsesin. Burada benim tayfamın senden daha fazla hakkı var. O yüzden ya sessizce oturup kimseye engel olmazsın, ya da seni bizzat ben denize atarım.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_windlass_6";
		break;
		
		case "SharlieEpilog_windlass_6": // диалог Пикара и Шарля
			dialog.text = "...";
			link.l1 = "Ha ha ha. Kendime dışarıdan bakmış gibi oldum.";
			link.l1.go = "SharlieEpilog_windlass_7";
			SharlieEpilog_windlass_9_1();
		break;
		
		case "SharlieEpilog_windlass_7":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Ne diyorsun?";
				link.l1 = "Evet, önemli değil, "+npchar.name+".   Yolcumuza bu kadar sert davranma.   O daha buralara alışmadı.   Sonuçta, biz de seninle bir günde denizci olmadık.";
			}
			else
			{
				dialog.text = "Ne diyorsunuz?";
				link.l1 = "Önemsemeyin, "+npchar.name+".   Ve yolcunuzu da fazla sıkı yargılamayın.   Tüm bunlar onun için yeni.   Sonuçta, biz de hemen deniz kurdu olmadık.";
			}
			link.l1.go = "SharlieEpilog_windlass_8";
		break;
		
		case "SharlieEpilog_windlass_8":
			dialog.text = "Onun yeteneğiyle adam daha çok ırgat makarasına dolanır, denizci olacağına. Böyle bir şeyi akıl etmek de… ";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				link.l1 = "Kim bilir, kim bilir. Takıma geldiğimde de aynı şekilde kaygısız, meraklı ve kendini beğenmiş bir delikanlıydım.";
			}
			else
			{
				link.l1 = "Kim bilir. Ben de takımadalara ilk geldiğimde aynı senin gibi kaygısız, meraklı ve kendini beğenmiş bir delikanlıydım.";
			}
			link.l1.go = "SharlieEpilog_windlass_9";
		break;
		
		case "SharlieEpilog_windlass_9":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Bunu da mı kıyasladın şimdi.\n"+"Bekle\n"+"Yani onda kendini mi görüyorsun? Ha-ha-ha. O zaman al onu himayene. Ben onunla uğraşacak değilim.";
				link.l1 = "Ben ona göz kulak olurum. Sen onu henüz lime lime etmeden önce. Ama demir için tam bedelini ödesin.";
			}
			else
			{
				dialog.text = "Yani kendinizi onda mı gördünüz? Ha-ha. Peki kaptan, o zaman kefil olun ona. Ben onunla uğraşacak değilim.";
				link.l1 = "Ona göz kulak olurum. Siz onu lime lime etmeden önce. Ama demir için - bedelini ödesin, nasıl gerekiyorsa.";
			}
			link.l1.go = "SharlieEpilog_windlass_10";
		break;
		
		case "SharlieEpilog_windlass_10":
			dialog.text = "Demir atın. Rüzgarı bekliyoruz. Rotayı koruyun.";
			link.l1 = "...";
			link.l1.go = "exit";
			SharlieEpilog_windlass_10();
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoTrollingHighSailor_1");
		break;
		
		// диалоги Старшего матроса и Алонсо		
		case "SharlieEpilog_AlonsoTrollingHighSailor_2": // Алонсо
			dialog.text = "";
			link.l1 = "Demir alın. Rüzgarı yakalayalım. Rotamız kuzeydoğu.";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_3";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_3": // Старший матрос
			dialog.text = "";
			link.l1 = "Demiri kaldırın! Fırtına yelkenini indirin - rüzgarı yakalayacağız. Haydi işe koyulun...";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_4";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_1();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_4": // Алонсо
			dialog.text = "";
			link.l1 = "Ne yapıyorsun?";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_5";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_5": // Старший матрос
			dialog.text = "";
			link.l1 = "Ne yapıyorsun?";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_6";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_1();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_6": // Алонсо
			dialog.text = "";
			link.l1 = "Hayır, ne yapıyorsun?";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_7";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_7": // Старший матрос
			dialog.text = "";
			link.l1 = "Argh... Ne yapıyorsun? Baş tayfa kaptanın komutlarını tekrar ediyor.";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_8";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_1();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_8": // Алонсо
			dialog.text = "";
			link.l1 = "İşte baş tayfa da onları tekrar ediyor.";
			link.l1.go = "exit";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoTrollingHighSailor_2");
		break;
		
		// Шарль ругает Алонсо
		case "SharlieEpilog_AlonsoTrollingHighSailor_9":
			dialog.text = "...";
			link.l1 = "Bırak şimdi, Alonso. Biz burada sadece yolcuyuz. Unuttun mu?";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_10";
			locCameraFromToPos(-8.00, 4.49, -1.91, true, -9.97, 2.64, -1.90);
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_10":
			dialog.text = "Öhöm... Affedersiniz, kaptan. Tutamadım kendimi\nAma değdi doğrusu. Sanki geçmişe gitmiş gibiydim.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoTrollingHighSailor_5");
		break;
		
		// Диалог Шарля с Пикаром о всяком (можно попасть в Поместье де Монпе)
		case "SharlieEpilog_PikarOnUliss":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+"... Ne arzu edersiniz?";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_A"))
				{
					link.l1 = "Peki, dostum, nasıl hissediyorsun kendini?";
					link.l1.go = "SharlieEpilog_PikarOnUliss_A_1";
				}
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_B"))
				{
					if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive"))
					{
						link.l2 = "İtiraf et, "+npchar.name+",   sen zaten Tiraks'tan ayrılmaya karar verdiğinde tüccar olmaya niyetlenmemiş miydin?";
						link.l2.go = "SharlieEpilog_PikarOnUliss_B_1";
					}
					else
					{
						link.l2 = "İtiraf et, "+npchar.name+",   sen   zaten   o   zaman,   plantasyondayken,   tüccar   olmaya   karar   vermiştin,   değil   mi?";
						link.l2.go = "SharlieEpilog_PikarOnUliss_B_1";
					}
				}
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_C"))
				{
					link.l3 = "Bir ulak benimle konuşmaya çalıştı, bunu çok iyi hatırlıyorum. Ama ne için olduğunu bir türlü çıkaramıyorum. Senin bu konuda bir bilgin var mı?";
					link.l3.go = "SharlieEpilog_PikarOnUliss_C_1";
				}
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_E"))
				{
					link.l1 = "Bordeaux'da daha önce bulundunuz mu, kaptan?";
					link.l1.go = "SharlieEpilog_PikarOnUliss_E_1";
				}
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_F"))
				{
					link.l2 = "Kaptan, doğrusu, Martinique'den nasıl ayrıldığımızı pek hatırlamıyorum. Birinden bana önemli bir mektup gelmesi gerekiyordu ama galiba hiç ulaşmadı. Bu konuda size biri başvurdu mu?";
					link.l2.go = "SharlieEpilog_PikarOnUliss_F_1";
				}
			}
			link.l4 = "Hafif bir esinti çıktı galiba. Yelkenleri açma vakti. (Denize açıl)";
			link.l4.go = "SharlieEpilog_PikarOnUliss_D_1";
			link.l5 = "Şimdilik bir şey yok. Ben gidiyorum.";
			link.l5.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_A_1":
			dialog.text = "Ha-ha... Hiç olmadığım kadar! Güçlüyüm, sağlıklıyım.";
			link.l1 = "Gerçekten mi? Halbuki haline bakılırsa, sanki köpekbalığı çiğneyip tükürmüş gibisin.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_A_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_A = true;
		break;

		case "SharlieEpilog_PikarOnUliss_A_2":
			dialog.text = "Sen de konuşacak adamı buldun. Kendin de dövülmüş köpek gibisin.";
			link.l1 = "Ben de aynı şekilde hissediyorum. Ha-ha. Şeytan alsın, ne zaman ve nasıl yola çıktığımızı bile hatırlamıyorum.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_A_3";
		break;

		case "SharlieEpilog_PikarOnUliss_A_3":
			dialog.text = "Ah, güzel bir ziyafetti. Ama şeytan gibi pahalıya patladı. Aptallarım neredeyse genelevi yakıyordu – skandalı örtbas etmek için bir çuval altın saymak zorunda kaldım. Artık bu ahmaklar hayatları boyunca bana borçlu, anlaşılan\nPeki, yolcu olmak nasıl bir his? Özledin mi denizi, yoksa sıkıntıdan ulumaya başladın mı?";
			link.l1 = "Artık kendi kaderimi ellerimde tutmuyormuşum gibi bir his var. Ama aynı zamanda tuhaf bir rahatlama da hissediyorum. Sanki omuzlarımdan bir kasa gülle atmışım gibi.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_A_4";
		break;

		case "SharlieEpilog_PikarOnUliss_A_4":
			dialog.text = "Ha-ha. Madem öyle, eğer canın çok sıkılırsa, seni yanımda subay olarak almaya hazırım.";
			link.l1 = "Oldukça cömert bir teklif, ama reddetmek zorundayım. Tüm Karayipler'de bizim eğlencelerimize yetecek kadar rom bulunmaz.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_1":
			if (IsStateTitle()) 
			{
				dialog.text = "Tam olarak değil, dostum. Böyle bir düşünce zaman zaman aklıma geliyordu, ama pek kulak asmıyordum. İkinci kez aklıma düştü, kulağıma bir söylenti çalındığında — meğer bütün Tiraks'ın sadık köpekleri iz bırakmadan yok olmuş. Hepsi birden — Satır, Kel, hatta o eski pis paspas Leprechaun bile.\nSonra senin ne kadar başarılı olduğunu duyunca, kesin kararımı verdim: bana bu kadar yeter. Sürekli para için kafamı riske atmakla olmuyor bu iş.\nAltınım var, artık hiçbir peruklu herifin önünde sürünmem gerekmez. Ama denizle vedalaşmak... işte buna hazır değildim. O yüzden de iş değiştirmeye karar verdim.";
			} 
			else 
			{
				dialog.text = "Tam olarak değil, dostum. Böyle bir düşünce bazen aklıma gelirdi, ama pek de önemsemezdim. İkinci kez aklıma düştü, kulağıma bir söylenti geldiğinde — güya Tiraks’ın sadık köpeklerinin tamamı iz bırakmadan yok olmuş. Hepsi birden — Satır, Kel, hatta o eski pis paspas Leprechaun bile.\nAma savaşta düşman topları iki kez kafamı uçurmaya ramak kala — işte o zaman kesin kararımı verdim, artık yeter dedim. Sonsuza dek birkaç sikke için kafamı riske atamam.\nAltınım var, öyle ki, bir daha asla peruklu bir herifin önünde eğilmem gerekmez. Ama denizle vedalaşmak… işte buna hazır değildim. O yüzden mesleğimi değiştirmeye karar verdim.";
			}
			link.l1 = "Testere, Kel, Cin... Onların nereye kaybolduğunu biliyor musun?";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_B = true;
		break;

		case "SharlieEpilog_PikarOnUliss_B_2":
			dialog.text = "Hayır, bilmiyorum. Açıkçası, o yaratıkların nereye kaybolduğuna da umurumda değil. İsterse cehennemin dibine gitsinler.";
			link.l1 = "Onları tam da oraya gönderdim.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_3";
		break;

		case "SharlieEpilog_PikarOnUliss_B_3":
			dialog.text = "Demek hepsini sen yok ettin? Vay canına! Peki, Markus bunu sana affetti mi?";
			link.l1 = "O bundan haberdar değil. Ve büyük ihtimalle asla da öğrenmeyecek.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_4";
		break;

		case "SharlieEpilog_PikarOnUliss_B_4":
			dialog.text = "Demek ki, kahretsin, tam zamanında onları terk etmişim, ha-ha. Sen, Allah bilir, benim kafamı da esirgemezdin\nAma bir şeyi anlamıyorum – sana bu neden gerekti, söylesene?";
			link.l1 = "Haklıydın – şu aşağılık herifler, bir avuç altın için her şeyi yapar, ihanet eder, öldürürler. Bizi Güney Main’deki bir yeraltı zindanına çektiler, akıllarına masal gibi bir hazine hikayesi uydurup kandırdılar. Bu baştan sona ince ince planlanmış bir tuzaktı ve o lanet kalın kafalılar yemi hiç düşünmeden yuttu. Payı adilce bölüşmek yerine, paylaşmaya gerek yok diye düşündüler; beni ortadan kaldırıp her şeyi kendilerine almaları daha kolaydı.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_5";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_5":
			dialog.text = "Ve hiç de başaramadılar, ha-ha! Dur bir dakika, bu tuzağı kim kurmuştu ki?";
			if (CharacterIsAlive("Tonzag") && CheckPassengerInCharacter(pchar, "Tonzag"))
			{
				link.l1 = "Bir Zorro varmış, İspanyol halkının intikamcısı — Cartagena’nın öcünü almak için. O katliamdan sağ çıkan biri sonsuza dek zindanda kalmalıydı; bütün çıkışlar kilitlenmişti. Ama o herifin şansı yaver gitmedi — subayım onu alt etti.";
			}
			else
			{
				link.l1 = "Bir Zorro var, İspanyol halkının intikamcısı — Cartagena'nın öcünü almak için. O cehennem gibi katliamdan sağ çıkan biri sonsuza dek zindanda kalmalıydı — bütün çıkışlar sıkı sıkıya kapatılmıştı. Oradan kaçmayı başardım. Ama çok ağır bir bedelle.";
			}
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_6";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_6":
			dialog.text = "En azından hayatta kaldın. Ve sanırım, neredeyse canından olacağın o altınların hepsini de yanında götürdün, değil mi?";
			link.l1 = "Orada hiç altın yoktu. Sadece altın kaplama kurşundu...";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_7";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_7":
			dialog.text = "...";
			link.l1 = "Bütün bunlardan sonra Tiraks'tan ayrılmaya karar verdim. Bunu ilk kez sana anlatıyorum. Subaylarımı saymazsak tabii.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_8";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_8":
			dialog.text = "'Ben seni uyarmıştım' demeyi sevmem, ama... seni uyarmıştım.";
			link.l1 = "Zamanında durmak benim güçlü yanım değil. O yüzden bana birkaç ders vermen gerekecek.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_9";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_9":
			dialog.text = "Beni biliyorsun ya – sana, birkaç kupa güzel rom karşılığında, altınlarımı sakladığım yeri bile anlatırım, hehe.";
			link.l1 = "Benden öyle bir cömertlik bekleme, ha-ha-ha. Sana senin erzakların yeter.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_C_1":
			dialog.text = "Biliyorum. Sana bir takım mektuplar vermeye çalıştı – ya bir Ben’den, ya da Benedict’ten. Sen de sertçe, hiçbir Ben’i tanımadığını söyledin ve eğlencemizi bozmayı sürdürürse onu meyhaneden atmakla tehdit ettin.";
			link.l1 = "Şeytan... Görünüşe bakılırsa bunlar Abbé Benoit'den gelen mektuplarmış. Önemli mektuplar.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_C_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_C = true;
		break;

		case "SharlieEpilog_PikarOnUliss_C_2":
			dialog.text = "Peki, o zaman iyi ki onları aldım. He-he.   İçimden bir ses o veletin doğru kişiye geldiğini söyledi. Al bakalım.";
			link.l1 = "Bana gerçekten çok yardımcı oldun, "+npchar.name+", teşekkür ederim.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_C_3";
		break;

		case "SharlieEpilog_PikarOnUliss_C_3":
			dialog.text = "Bir 'teşekkür' yetmez, dostum. Bana bir içki borçlusun – hem de öyle sıradanından değil, Bordeaux’daki en iyisinden.";
			link.l1 = "Sana içki de olur, dilenci. Romumuz elbette Karayipler'deki gibi değil, ama şarap... Böylesini daha önce hiç içmedin.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_E_1":
			dialog.text = "Hiç olmadı...";
			link.l1 = "Sana imreniyorum. Bordeaux'yu ilk kez görüyormuş gibi tekrar görmek isterdim. Muhtemelen romu tercih edersin, ama yine de belediye binasının yanındaki şarap fuarına uğramanı tavsiye ederim. Bizim clairet şarabımız için Karayiplerdeki uzmanlar servet ödemeye hazır.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_E_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_E = true;
		break;

		case "SharlieEpilog_PikarOnUliss_E_2":
			dialog.text = "Tavsiyeniz için teşekkür ederim. Bir soru sorabilir miyim?";
			link.l1 = "Elbette.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_E_3";
		break;

		case "SharlieEpilog_PikarOnUliss_E_3":
			dialog.text = "Uzun yıllar dümen başında olduktan sonra yolcu olmak nasıl bir his? Yeni durumunuza alışabildiniz mi?";
			link.l1 = "Hm... Kendi kaderimi artık ellerimde tutmadığım hissi peşimi bırakmıyor. Ama aynı zamanda tuhaf bir rahatlama hissediyorum. Sanki omuzlarımdan bir top mermisi sandığı kalkmış gibi. Sanırım, sonuç çıkarmak için henüz erken.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_E_4";
		break;

		case "SharlieEpilog_PikarOnUliss_E_4":
			dialog.text = "Şu lanet durgunluğa öyle güzel yakalandık ki, vaktiniz bol bol olacak.";
			link.l1 = "İyi bir dostlukta, deniz durgun olsa da sıkılmazsın. Doğrusunu söylemek gerekirse, kaptan, bana böyle bir dostluk nasip oldu.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_F_1":
			dialog.text = "Başvurdu. Bir abbatın gönderdiği bir ulak. Size bu mektupları vermeyi hep unutuyorum. Alın, buyurun.";
			link.l1 = "Mükemmel. Bana gerçekten çok yardımcı oldunuz, kaptan. Size minnettarım.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_F = true;
		break;
		
		case "SharlieEpilog_PikarOnUliss_D_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_A")){dialog.text = "Haklısın.";}
			else {dialog.text = "Haklısınız.";}
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarOnUliss_D_2";
		break;
		
		case "SharlieEpilog_PikarOnUliss_D_2":
			dialog.text = "Sağdan rüzgar! Baştan kıç yelkenine kadar her şeyi aç! Tam yol ileri!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_InEstateDeMonpe";
			locCameraFromToPos(-9.34, 8.28, -16.03, true, -9.33, 7.32, -20.48);
			CharacterTurnToLoc(CharacterFromID("SharlieEpilog_Pikar"), "quest", "quest10");
		break;
		
		case "SharlieEpilog_InEstateDeMonpe":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe");
		break;
		
		//Матрос 1 на верхней палубе
		case "SharlieEpilog_Sailor_1":
			dialog.text = "Harika bir kılıç, "+GetTitle(NPChar,true)+".   Bakabilir miyim?";
			link.l1 = "Belki başka bir zaman.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_1";
			PlaySound("Voice\" + LanguageGetLanguage() + "\officer05.wav");
		break;
		
		//Матрос 2 на верхней палубе
		case "SharlieEpilog_Sailor_2":
			dialog.text = "Bu kum saatleri ne zaman çalacak? Az kaldı, dilimi yutacağım.";
			link.l1 = "Sakin ol, denizci.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\other\Matrosi na Korablyah-07.wav");
		break;
		
		//Матрос 3 на орудийной палубе
		case "SharlieEpilog_Sailor_3":
			dialog.text = "Şuna baksana, ne koca bir fare geçti! Yemin ederim, hayatımda böyle büyüğünü görmedim!";
			link.l1 = "Hmm...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_3";
			PlaySound("Voice\" + LanguageGetLanguage() + "\other\Matrosi na Korablyah-04.wav");
		break;
		
		//Матрос 4 на орудийной палубе
		case "SharlieEpilog_Sailor_4":
			dialog.text = "Şimdi ne yapacağım, Mösyö? O kadar içmişim ki, bu gemiye nasıl bindiğimi bile hatırlamıyorum. Ben denizci bile değilim... Evdeyse karım ve iki çocuğum var.";
			link.l1 = "Daha az içmeliydin. Ama artık çok geç - denizci olacaksın.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_4";
			PlaySound("Voice\" + LanguageGetLanguage() + "\Ransack_2.wav");
		break;
		
		//Старший матрос
		case "SharlieEpilog_HighSailor_1":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+".   Gemimizde sizi ağırlamak bizim için bir onurdur.";
			link.l1 = "Oldukça naziksiniz, başçavuş bey. Ne de olsa kibarlık, denizciler arasında pek yaygın bir özellik değildir. Ama mürettebatı utandırmayalım – burası Majestelerinin sarayı değil. Bana sadece kaptan diye hitap et.";
			link.l1.go = "SharlieEpilog_HighSailor_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\YoungMan03.wav");
		break;

		case "SharlieEpilog_HighSailor_2":
			dialog.text = "Denizci olmam çok yeni sayılır. Eskiden Bay Levasseur’un katibiydim. Sonra onu… öhöm… ortadan kaldırdılar, yerine yeni bir vali geldi. Dar çevrelerde hemen yayıldı: Rene de Boisdufle de Laitre denen adam tam bir alçakmış. O zaman anladım ki, düzgün bir iş bulmam artık imkânsız. İnsanlar, her şeyi bildiğimi ama sustuğumu düşünecekler.";
			link.l1 = "Yoksa öyle değil miydi?";
			link.l1.go = "SharlieEpilog_HighSailor_3";
		break;

		case "SharlieEpilog_HighSailor_3":
			dialog.text = "Elbette hayır. Hiçbir zaman başkalarının işine karışmak gibi bir alışkanlığım olmadı. Üstelik, Levasseur merakı acımasızca cezalandırırdı.";
			link.l1 = "Buna inanmakta hiç tereddüt etmiyorum.";
			link.l1.go = "SharlieEpilog_HighSailor_4";
		break;

		case "SharlieEpilog_HighSailor_4":
			dialog.text = "İşte, onu ortadan kaldırdığınızda, ben de ilk karşıma çıkan korsan gemisine tayfa olarak yazıldım. Ve tuhaf bir şekilde, oldukça hızlı alıştım ve değiştim. Hatta en gözü kara haydutlar arasında bile saygı kazanmayı başardım. Ama onların yaptıkları şeyler... Bana göre değildi. Böylece kendimi burada buldum.";
			link.l1 = "Demek, Levaser’in kaderindeki rolümü biliyordun?";
			link.l1.go = "SharlieEpilog_HighSailor_5";
		break;

		case "SharlieEpilog_HighSailor_5":
			dialog.text = "Elbette, kaptan. Ve dünyayı o canavardan kurtardığınız için memnunum. Hem de beni o küf kokulu hücremden çıkardınız. Hayatıma yeniden bakmamı sağladınız.";
			link.l1 = "Ne kadar da dar bir dünya, şaşırtıcı gerçekten...";
			link.l1.go = "SharlieEpilog_HighSailor_6";
		break;

		case "SharlieEpilog_HighSailor_6":
			dialog.text = "Bu her ne kadar çelişkili gelse de, dünya hem çok küçük hem de çok büyük.";
			link.l1 = "İlginç. Hiç böyle düşünmemiştim.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_HighSailor_7";
		break;
		
		case "SharlieEpilog_HighSailor_7":
			dialog.text = "Kaptan "+pchar.lastname+"... Bu akşam harika, değil mi?";
			link.l1 = "Sanırım öyle. Bunu daha da güzel yapacak tek şey kuzeybatıdan esen hafif bir rüzgar olurdu.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_HighSailor_7";
			PlaySound("Voice\" + LanguageGetLanguage() + "\YoungMan03.wav");
		break;
		
		//Диалог с боцманом Моко
		case "SharlieEpilog_Moko_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Kaptan "+pchar.lastname+"...";
				link.l1 = "Aslında… Neyse, önemli değil. Seni hatırlıyorum! Adın Moko. Bir kerede bütün bir fıçı romu içen sendin, değil mi?";
				link.l1.go = "SharlieEpilog_Moko_2";
			}
			else
			{
				dialog.text = "Ne istiyorsunuz… Mösyö?";
				link.l1 = "Her gün böyle bir devi görmüyorsun. Adın ne?";
				link.l1.go = "SharlieEpilog_Moko_4";
			}
			PlaySound("Voice\" + LanguageGetLanguage() + "\citizen\Kapitani Korabley-07.wav");
		break;

		case "SharlieEpilog_Moko_2":
			dialog.text = "Ben... Ve ancak iki gün sonra kendime gelebildim.";
			link.l1 = "Senin yerinde başkası olsa, iki saat bile dayanamazdı. Eğer dövüşün de içkin kadar iyiyse, Jan'ın böyle bir başçavuşa sahip olması tam anlamıyla büyük şans.";
			link.l1.go = "SharlieEpilog_Moko_3";
		break;

		case "SharlieEpilog_Moko_3":
			dialog.text = "Benim de kaptanım konusunda şansım yaver gitti. Onun sayesinde özgürlüğüme kavuştum. Ve sizin sayenizde. Jean’ı kurtarmasaydınız, ben hâlâ plantasyonlarda çürüyordum.";
			link.l1 = "Bu gerçekten ilginç bir maceraydı. Ve sonunda beklediğimden daha iyi bittiğine sevindim.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Moko_repeat";
		break;
		
		case "SharlieEpilog_Moko_4":
			dialog.text = ""+npchar.name+". Bu gemide ben lostromoyum.";
			link.l1 = "Ha-ha, seninle tartışmaya kim cesaret edebilir, görmek isterdim. Kaptanın yanında uzun zamandır mı çalışıyorsun?";
			link.l1.go = "SharlieEpilog_Moko_5";
		break;

		case "SharlieEpilog_Moko_5":
			dialog.text = "Birkaç yıl. Ona çok şey borçluyum. O olmasaydı, ben şimdi çürüyüp gitmiştim...";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Moko_6";
		break;

		case "SharlieEpilog_Moko_6":
			dialog.text = "...";
			link.l1 = "Plantasyonda mı demek istedin?";
			link.l1.go = "SharlieEpilog_Moko_7";
		break;

		case "SharlieEpilog_Moko_7":
			dialog.text = "...";
			link.l1 = "Bırak, "+npchar.name+", tabii ki bana hiçbir şey anlatmamakta özgürsün, ama henüz fark etmediysen, ben o peruklu soylulardan değilim. Kaptan seni fidyeyle mi kurtardı?";
			link.l1.go = "SharlieEpilog_Moko_8";
		break;

		case "SharlieEpilog_Moko_8":
			dialog.text = "Birlikte kaçtık. Maracaibo’daki plantasyondan. Jean olmasaydı başaramazdık. O zamandan beri onun tayfasındayım. Önce tayfa olarak başladım, şimdi ise gemi çavuşuyum.";
			link.l1 = "Kaptan köle miydi? Hiç aklıma gelmezdi. Gerçi benim de dolabımda birkaç iskelet var. İspanyol çizmelerinin altından kurtulmana sevindim, "+npchar.name+". Ee, denizci olmak nasıl bir şey sence?";
			link.l1.go = "SharlieEpilog_Moko_9";
		break;

		case "SharlieEpilog_Moko_9":
			dialog.text = "Sanki daha önce hiç yaşamamışım gibi. Deniz artık benim evim.";
			link.l1 = "Burada seni çok iyi anlıyorum, dostum. Başkası değil, tam ben.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Moko_repeat";
		break;
		
		case "SharlieEpilog_Moko_repeat":
			dialog.text = "Kaptan "+pchar.lastname+"... Size nasıl yardımcı olabilirim?";
			link.l1 = "Teşekkür ederim, "+npchar.name+", şu an hiçbir şeye ihtiyacım yok.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Moko_repeat";
		break;
		
		//Диалог с дворянином Бернардом
		case "SharlieEpilog_Bernard_1":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,true))+"! Bu gemide en azından bir aklı başında yüz görmek ne kadar güzel. Şu... tayfalar... tam birer barbar.";
			link.l1 = "Sizin yerinizde olsam, başkasının gemisinde böyle konuşmazdım. Karayipler’e nasıl düştünüz bilmiyorum ama burada, bilirsiniz, bambaşka kurallar geçerli. Mürettebata saygı göstermeniz iyi olur.";
			link.l1.go = "SharlieEpilog_Bernard_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\citizen\Dvoryane-06.wav");
		break;

		case "SharlieEpilog_Bernard_2":
			dialog.text = "Saygı mı? Onlara mı? Onlar tam birer vahşi! Ben bir soyluyum, "+GetTitle(NPChar,true)+",   düzene, hizmete,   medeniyete alışığım! Bana karşı gelmeye kalksınlar da görelim — babam onları...";
			link.l1 = "Babanız, yolda hummadan öldüğünüzü öğrenecek. Ve muhtemelen aksini kanıtlayamayacak.";
			link.l1.go = "SharlieEpilog_Bernard_3";
		break;

		case "SharlieEpilog_Bernard_3":
			dialog.text = "Lanet olsun şu Albay Fox'a! Her şey onun yüzünden! Kızı uğruna okyanusu aştım, rahatımı feda ettim, o tuhaf bakışlara, o berbat yemeğe, şu... sallantıya katlandım! Şimdi de başkasının gemisinde yol alıyorum!";
			link.l1 = "Albay Fox…";
			link.l1.go = "SharlieEpilog_Bernard_4";
		break;

		case "SharlieEpilog_Bernard_4":
			dialog.text = "Onu tanıyor musunuz, "+GetTitle(NPChar,true)+"?";
			link.l1 = "Öhö... Onu duydum.";
			link.l1.go = "SharlieEpilog_Bernard_5";
		break;

		case "SharlieEpilog_Bernard_5":
			dialog.text = "Yani, demek ki pek bir şey kaçırmamışsınız. O adam kör askeri inatçılığın ve önyargıların vücut bulmuş hali.";
			link.l1 = "O bir asker...";
			link.l1.go = "SharlieEpilog_Bernard_6";
		break;

		case "SharlieEpilog_Bernard_6":
			dialog.text = "Aynen öyle! Ve bu her şeyi anlatıyor. Onun kızıyla görüşmek için geldiğimde, biliyor musunuz ne yaptı? Biliyor musunuz? Beni kapı dışarı etti! Tek kelime etmeden!";
			link.l1 = "Ama siz, anlaşılan, geri adım atmamışsınız?";
			link.l1.go = "SharlieEpilog_Bernard_7";
		break;

		case "SharlieEpilog_Bernard_7":
			dialog.text = "Elbette! Bir hafta boyunca kabul edilmek için uğraştım! Kendimi küçük düşürdüm! Hatta... muhafızlara rüşvet teklif ettim! Sonunda, davetsizce yanına sızmayı başardım. Sadece konuşmak istemiştim!";
			link.l1 = "Bunun onu sevindirdiğini sanmıyorum.";
			link.l1.go = "SharlieEpilog_Bernard_8";
		break;

		case "SharlieEpilog_Bernard_8":
			dialog.text = "Sevindin mi? Ah, tam bir kriz geçirdi! Beni dışarı attılar, konağa yaklaşmamı yasakladılar, babamın gemisine el koydular, sonra da tüm İngiliz kaptanlara beni gemiye almalarını yasakladılar! Mecburen Martinique’te bir Fransız gemisi aramak zorunda kaldım... Tam bir kabustu.";
			link.l1 = "Görünüşe bakılırsa onu fena halde kızdırdınız.";
			link.l1.go = "SharlieEpilog_Bernard_9";
		break;

		case "SharlieEpilog_Bernard_9":
			dialog.text = "Her zaman bana karşıydı. En sevdiği lafı şuydu: 'Subay kızı, subay eşi olur.' Sizi, "+GetTitle(NPChar,true)+",   onun çok daha uygun bir eş olduğunu düşündü.";
			link.l1 = "Belki de bu sefer başka sebepleri vardı...";
			link.l1.go = "SharlieEpilog_Bernard_10";
		break;

		case "SharlieEpilog_Bernard_10":
			dialog.text = "...";
			link.l1 = "Demek buraya sevgilinizle buluşmaya geldiniz.";
			link.l1.go = "SharlieEpilog_Bernard_11";
		break;

		case "SharlieEpilog_Bernard_11":
			dialog.text = "Evet. O Avrupa'dan ayrıldığından beri ondan tek bir satır bile almadım. Eminim, babası mektupları yakalıyor. Beni unutmuş olamaz! Tabii, bana karşı hep mesafeliydi... hatta soğuktu... Ama onun beni hayatından sildiğine inanamıyorum.";
			link.l1 = "Sizi anlıyorum, Mösyö. Ruhsal yaralar, bedensel olanlardan çok daha zor iyileşir. Bir dakika... Neden siz, bir İngiliz olarak, Bordeaux'ya gidiyorsunuz?";
			link.l1.go = "SharlieEpilog_Bernard_12";
		break;

		case "SharlieEpilog_Bernard_12":
			dialog.text = "Evime rezil olarak dönmeye hiç niyetim yok. Her şey yatışana kadar Bordeaux’daki amcamda kalmam gerekecek. Gerçi onun malikanesi bizimkinden çok daha geniş ve zarif. Üstelik hizmetkârları da daha iyi eğitilmiş.";
			link.l1 = "Pekâlâ, sanırım bu en kötü seçenek değil. Belki de kendinize başka bir eş bulursunuz. Bordeaux genç güzellerle doludur, bana inanın.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Bernard_repeat";
		break;
		
		case "SharlieEpilog_Bernard_repeat":
			dialog.text = "Sonunda ne zaman varacağız, "+GetTitle(NPChar,true)+"?   Tüm bu... centilmenlerin arasında dayanılmaz bir şekilde acı çekiyorum.   Acilen bir banyo yapmam gerek.";
			link.l1 = "Korkarım, önümüzdeki iki ay boyunca ancak onu hayal edebilirsiniz.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Bernard_repeat";
			PlaySound("Voice\" + LanguageGetLanguage() + "\citizen\Dvoryane-06.wav");
		break;
		
		//Диалог с Книппелем на корабле Улисс
		case "SharlieEpilog_Knippel_1":
			dialog.text = "Lanet olsun bu durgunluğa, keşke bir top mermisiyle paramparça olsaydı.";
			link.l1 = "Homurdanma, "+npchar.name+", er ya da geç rüzgar yükselecek.";
			link.l1.go = "SharlieEpilog_Knippel_2";
		break;

		case "SharlieEpilog_Knippel_2":
			dialog.text = "Peki o zamana kadar ne yapacağız, efendim? Topların bile kontrolünü yapamıyorum... Sonuçta başkasının gemisindeyiz.";
			link.l1 = "Sadece biraz dinlenmeye çalış. Sürekli çalışacak değilsin ya.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Knippel_repeat";
		break;
		
		case "SharlieEpilog_Knippel_repeat":
			dialog.text = "Lanet olası durgunluk...";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Knippel_repeat";
		break;
		
		//Диалог с Лонгвэем на корабле Улисс
		case "SharlieEpilog_Longway_1":
			dialog.text = "Fena bir gemi değil, kaptan bey. Siz de böyle mi düşünüyorsunuz?";
			link.l1 = "Meifeng'den bile daha mı iyi?";
			link.l1.go = "SharlieEpilog_Longway_2";
		break;

		case "SharlieEpilog_Longway_2":
			dialog.text = "İçin "+npchar.name+"   Mayfeng'den   daha   iyi   bir   gemi   yok.   Bu   gemi   asla   onun   kadar   rüzgara   karşı   bu   kadar   iyi   gidemez.";
			link.l1 = "Sakin ol, "+npchar.name+", şaka yaptım tabii. Elbette, Meifeng rakipsiz. Ama Ulysse de iyi bir gemi. Sağlam bir tekne.";
			link.l1.go = "SharlieEpilog_Longway_3";
		break;

		case "SharlieEpilog_Longway_3":
			dialog.text = ""+npchar.name+" dümene geçmek istemek. Geminin elini dinlediğini hissetmek...";
			link.l1 = "Ne yazık ki, dostum, bu başkasının gemisi. En iyisi, şuradaki iri adama düello teklif et. İkinize de iyi gelir.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Longway_repeat";
		break;
		
		case "SharlieEpilog_Longway_repeat":
			dialog.text = "Rüzgar arkamızdan eserse, hangi hızda gidebiliriz?";
			link.l1 = "Bunu sana kesin olarak söyleyemem, "+npchar.name+". En iyisi, onların dümencisine sor.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Longway_repeat";
		break;
		
		//Диалог с Тонзагом на корабле Улисс
		case "SharlieEpilog_Tonzag_1":
			dialog.text = "Şu koca adamı gördün mü, burada lostromos olmuş? Diyorlar ki, tek eliyle hindistancevizi ezebiliyormuş.";
			link.l1 = "Ha-ha. Görüyorum ki, sen ondan biraz çekiniyorsun?";
			link.l1.go = "SharlieEpilog_Tonzag_2";
		break;

		case "SharlieEpilog_Tonzag_2":
			dialog.text = "Nedenmiş ki? Boyut önemli değil. Daha nelerini hallettim ben.";
			link.l1 = "O zaman belki ona yumruk dövüşü teklif edersin? Bire bir - dürüstçe.";
			link.l1.go = "SharlieEpilog_Tonzag_3";
		break;

		case "SharlieEpilog_Tonzag_3":
			dialog.text = "Ah...";
			link.l1 = "Biraz solgunlaştın sanki. Ha-ha. Neyse, istemiyorsan istemiyorsun. O zaman, kemiklerini fazla zorlamayalım.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tonzag_repeat";
		break;
		
		case "SharlieEpilog_Tonzag_repeat":
			dialog.text = "Bu sularda balık o kadar çok ki, tekneyle kepçe gibi alırsın, ama şu tembeller bir ağ bile atmaya tenezzül etmemişler.";
			link.l1 = "Onların lostromosuyla konuş. Sanırım senin yorumunu takdir edecektir, hehe.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tonzag_repeat";
		break;
		
		//Диалог с Тичингиту, охраняющим золото
		case "SharlieEpilog_Tichingitu_21":
			dialog.text = "Altın güvende, kaptan "+pchar.name+". Tichingitu onu güvenle korumasını söyledim.";
			link.l1 = "Teşekkürler, dostum. Alonso yakında seni değiştirecek.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tichingitu_21";
		break;
		
		//Диалог с Книппелем, охраняющим золото
		case "SharlieEpilog_Knippel_21":
			dialog.text = "Grot direğine Knippel atayım, efendim, bu döküntüde hayatımda gördüğümden daha fazla fare var.";
			link.l1 = "Gemi uzun süre limanda, doğru dürüst gözetim olmadan bekledi. Yeni tayfa yakında onlardan kurtulacaktır.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Knippel_21";
		break;
		
		//Диалог с Лонгвэем, охраняющим золото
		case "SharlieEpilog_Longway_21":
			dialog.text = "Longway zincir sesini duydu. Kaptan demir mi attı?";
			link.l1 = "Sigortayı bizim yolcumuz attırdı. Rüzgar şimdilik çok zayıf, ama umarım bu uzun sürmez.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Longway_21";
		break;
		
		//Диалог с Тонзагом, охраняющим золото
		case "SharlieEpilog_Tonzag_21":
			dialog.text = "Evet, kahretsin... Şu anda şöyle sert bir rom bardağı fena olmazdı.";
			link.l1 = "Akşam yemeği yakında, biraz sabret. Alonso seni değiştirecek.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tonzag_21";
		break;
		
		//Диалог с Мэри перед походом в каюту
		case "SharlieEpilog_Mary_11":
			dialog.text = "...";
			link.l1 = ""+npchar.name+", sevgilim, nasıl hissediyorsun kendini?";
			link.l1.go = "SharlieEpilog_Mary_12";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Mary_12":
			dialog.text = "...";
			link.l1 = "Bırak artık, sevgilim, gerçekten bana darıldın mı sırf şarap almak için dükkâna gittiğim diye?";
			link.l1.go = "SharlieEpilog_Mary_13";
		break;

		case "SharlieEpilog_Mary_13":
			dialog.text = "Şaraba mı gittin? Bari haber verseydin! Nereden bileyim, belki geneleve gittin – biriyle… ya da hepsiyle birden?!";
			link.l1 = "Sevgilim, böyle bir riske girer miydim hiç? Tüm takımadalarda en güzel, en akıllı ve deli gibi kıskanç bir karım var. Sence ben gidip ucuz liman kızlarıyla mı oyalanacağım?";
			link.l1.go = "SharlieEpilog_Mary_14";
		break;

		case "SharlieEpilog_Mary_14":
			dialog.text = "Bari bir laf edebilirdin ya, di mi! Ben orada oturuyordum ve…";
			link.l1 = "Söz veriyorum, bir dahaki sefere sana sadece haber vermekle kalmayacağım – seni de yanımda götüreceğim. Ama şimdi… birden aklıma geldi, kaptan kamarasındaki mobilyalar iyi durumda mı acaba? Özellikle de yatak. Kontrol edelim mi?";
			link.l1.go = "SharlieEpilog_Mary_15";
		break;

		case "SharlieEpilog_Mary_15":
			dialog.text = ""+pchar.name+"... Ya biri içeri girerse?\nHmm... şimdi bunu daha da çok istiyorum.";
			link.l1 = "O halde bir saniye bile kaybetmeyelim.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_1");
		break;
		
		//Диалог с Элен перед походом в каюту
		case "SharlieEpilog_Helena_11":
			dialog.text = "...";
			link.l1 = ""+npchar.name+", sevgilim, nasıl hissediyorsun kendini?";
			link.l1.go = "SharlieEpilog_Helena_12";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Helena_12":
			dialog.text = "...";
			link.l1 = "Bırak şimdi, sevgilim, gerçekten bana darıldın mı sadece şarap almak için dükkâna gittiğim diye?";
			link.l1.go = "SharlieEpilog_Helena_13";
		break;

		case "SharlieEpilog_Helena_13":
			dialog.text = "Beni de yanında götürebilirdin. Yoksa senin o ortaklarından daha kötü mü olurdu sanıyorsun?";
			link.l1 = "Bence onları kolayca gölgede bırakırdın. Ama o zaman aklımda şarap olmazdı.";
			link.l1.go = "SharlieEpilog_Helena_14";
		break;

		case "SharlieEpilog_Helena_14":
			dialog.text = "Peki, ne hakkında?";
			link.l1 = "Seninle oracıkta baş başa kalmak… Ve bu düşünce şu anda aklımdan çıkmıyor.";
			link.l1.go = "SharlieEpilog_Helena_15";
		break;

		case "SharlieEpilog_Helena_15":
			dialog.text = "Öyle mi? Peki, meraklı gözlerden nereye saklanmayı düşünüyorsun?";
			link.l1 = "Kaptanın kamarasında. Sanırım yatağının ne kadar sağlam olduğunu kontrol etmeliyiz.";
			link.l1.go = "SharlieEpilog_Helena_16";
		break;

		case "SharlieEpilog_Helena_16":
			dialog.text = "Ha-ha. Ya kaptan bizi yakalarsa?\nGerçi… sırf bu düşünce bile kalbimi daha hızlı attırıyor.";
			link.l1 = "O halde vakit kaybetmeyelim!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_1");
		break;
		
		//Диалог с Мэри в каюте
		case "SharlieEpilog_Mary_21":
			dialog.text = "Harikaydı, kaptanım...\nSana bir haberim var.";
			link.l1 = "Haber mi? Kulak kesildim.";
			link.l1.go = "SharlieEpilog_Mary_22";
			SharlieEpilog_LoveInCabin_CameraDialog();
		break;

		case "SharlieEpilog_Mary_22":
			dialog.text = ""+pchar.name+"... Bir çocuğumuz olacak. Hamileyim, di mi.";
			link.l1 = "Sevgilim... Bu doğru mu?";
			link.l1.go = "SharlieEpilog_Mary_23";
		break;

		case "SharlieEpilog_Mary_23":
			dialog.text = "Baba olacaksın, "+pchar.name+"!";
			link.l1 = ""+npchar.name+"... Bu inanılmaz!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_6");
		break;
		
		case "SharlieEpilog_Mary_31":
			dialog.text = "Mutlu musun, sevgilim?";
			link.l1 = "Mutlu muyum? Şaka mı yapıyorsun? Tanrım, ben dünyadaki en mutlu insanım! Ama... neden bana daha önce söylemedin?";
			link.l1.go = "SharlieEpilog_Mary_32";
		break;

		case "SharlieEpilog_Mary_32":
			dialog.text = "Yelken açmanı engellemek için mi? Babanla tanışmayı gerçekten çok istiyorum, "+pchar.name+".";
			link.l1 = ""+npchar.name+"...   Seni seviyorum! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_9");
		break;
		
		//Диалог с Элен в каюте
		case "SharlieEpilog_Helena_21":
			dialog.text = "Her zamanki gibi harikaydın, sevgilim. Sana bir haberim var.";
			link.l1 = "Haber mi? Kulak kesildim.";
			link.l1.go = "SharlieEpilog_Helena_22";
			SharlieEpilog_LoveInCabin_CameraDialog();
		break;

		case "SharlieEpilog_Helena_22":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+GetFullName(pchar)+", Monpe şövalyesi - baba olacaksın.";
			link.l1 = "Bu... bu doğru mu?";
			link.l1.go = "SharlieEpilog_Helena_23";
		break;

		case "SharlieEpilog_Helena_23":
			dialog.text = "Bu, adımın      olduğundan ne kadar gerçekse, o kadar gerçek."+npchar.name+". En geç altı ay içinde bir çocuğumuz olacak – küçük bir Mösyö de Mor... ya da belki bir Matmazel.";
			link.l1 = "Elena... Bu inanılmaz!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_6");
		break;
		
		case "SharlieEpilog_Helena_31":
			dialog.text = "...";
			link.l1 = "Demek bu yüzden bizimle ayrılışımızı kutlamak için içmedin! Ama… neden bana daha önce söylemedin?";
			link.l1.go = "SharlieEpilog_Helena_32";
		break;

		case "SharlieEpilog_Helena_32":
			dialog.text = "Senin risk almamaya karar verip takımadada kalmandan korktum. Babanın isteğini yerine getirmeni istedim. Hem de... onunla bizzat tanışmayı çok istiyorum.";
			link.l1 = ""+npchar.name+"…   Seni seviyorum!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_9");
		break;
		
		// Диалог с Пикаром
		case "SharlieEpilog_PikarInCabin_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Bak hele… Burada ne yapıyoruz biz? Küçük Gaskonyalılar mı oynuyoruz?";
				link.l1 = "Ha ha ha! Bir oğlum olacak, "+npchar.name+"! Baba olacağım!";
				link.l1.go = "SharlieEpilog_PikarInCabin_1_1";
			}
			else
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+". Kaptanın kamarasını kaptanın izni olmadan kullanmak, sizin rütbenizde biri için bile fazla değil mi?";
				link.l1 = "Affedersiniz, kaptan. Ama bunun için iyi bir sebebim var! Baba olacağım!";
				link.l1.go = "SharlieEpilog_PikarInCabin_12";
			}
			SharlieEpilog_PikarInCabin_camera_2();
		break;
		
		case "SharlieEpilog_PikarInCabin_1_1":
			locCameraSleep(true);
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				StartInstantDialogTurnToNPC("Helena", "SharlieEpilog_PikarInCabin_2", "Quest\Sharlie\Epilog.c", "Blaze");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				StartInstantDialogTurnToNPC("Mary", "SharlieEpilog_PikarInCabin_2", "Quest\Sharlie\Epilog.c", "Blaze");
			}
		break;

		case "SharlieEpilog_PikarInCabin_2":
			dialog.text = "Ya da kızın!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarInCabin_2_1";
		break;
		
		case "SharlieEpilog_PikarInCabin_2_1":
			StartInstantDialogTurnToNPC("SharlieEpilog_Pikar", "SharlieEpilog_PikarInCabin_3", "Quest\Sharlie\Epilog.c", "Blaze");
		break;

		case "SharlieEpilog_PikarInCabin_3":
			dialog.text = "Bunu benden sakladın mı, alçak? Oysa ben seni dostum sanıyordum!";
			link.l1 = "Ben de yeni öğrendim! Düşünebiliyor musun? Ben! Baba! Olacağım!";
			link.l1.go = "SharlieEpilog_PikarInCabin_4";
		break;

		case "SharlieEpilog_PikarInCabin_4":
			dialog.text = "Ha-ha-ha! Gerçekten çok mutlusun dostum! Seni ilk kez böyle görüyorum\nSiz burada biraz daha sohbet edin, ben de topları kutlama atışına hazırlayayım. Emri vermeye hazır olduğunda bana haber verirsin.";
			link.l1 = "...";
			link.l1.go = "exit";
			locCameraSleep(false);
			SharlieEpilog_PikarInCabin_camera_1();
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_13");
		break;

		case "SharlieEpilog_PikarInCabin_12":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				sld = CharacterFromID("Helena");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				sld = CharacterFromID("Mary");
			}
			dialog.text = "Ha… İnanın bana, buraya neden uğradığınızı tahmin etmiştim.";
			link.l1 = "Hayır, tabii ki değil! "+sld.name+" hamileyim! Bir oğlum olacak!";
			link.l1.go = "SharlieEpilog_PikarInCabin_12_1";
		break;
		
		case "SharlieEpilog_PikarInCabin_12_1":
			locCameraSleep(true);
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				StartInstantDialogTurnToNPC("Helena", "SharlieEpilog_PikarInCabin_13", "Quest\Sharlie\Epilog.c", "Blaze");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				StartInstantDialogTurnToNPC("Mary", "SharlieEpilog_PikarInCabin_13", "Quest\Sharlie\Epilog.c", "Blaze");
			}
		break;

		case "SharlieEpilog_PikarInCabin_13":
			dialog.text = "Ya da kızın!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarInCabin_13_1";
		break;
		
		case "SharlieEpilog_PikarInCabin_13_1":
			StartInstantDialogTurnToNPC("SharlieEpilog_Pikar", "SharlieEpilog_PikarInCabin_14", "Quest\Sharlie\Epilog.c", "Blaze");
		break;

		case "SharlieEpilog_PikarInCabin_14":
			dialog.text = "Öhöm... O halde, tüm kalbimle tebrik ederim!\nEmredeceğim - tüm toplardan şenlik atışı yapacağız. Emri vermeye hazır olduğunuzda haber edin.\nŞimdilik... kamarayı dilediğiniz gibi kullanabilirsiniz.";
			link.l1 = "...";
			link.l1.go = "exit";
			locCameraSleep(false);
			SharlieEpilog_PikarInCabin_camera_1();
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_13");
		break;
		
		// Диалог с Пикаром после интима с женой
		case "SharlieEpilog_PikarZalp_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Öhö-öhö... Şey, baba... görüyorum ki hemen bir varis daha yapmak istedin, ha?";
				link.l1 = "Ha-ha! Benim elimde olsaydı - bir düzine birden yapardım! Peki dostum, tüm toplarla ateş açalım mı?";
				link.l1.go = "SharlieEpilog_PikarZalp_2";
				link.l2 = "Korkarım, dostum, işler böyle yürümüyor. Ama denedik.";
				link.l2.go = "exit";
			}
			else
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar,true))+"...";
				link.l1 = "Ne dersin, kaptan, bütün toplarla ateş mi açalım?";
				link.l1.go = "SharlieEpilog_PikarZalp_3";
				link.l2 = "Şimdi değil.";
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "SharlieEpilog_PikarZalp_1";
		break;
		
		case "SharlieEpilog_PikarZalp_2":
			dialog.text = "Mürettebat sadece bunu bekliyor! Emredin, "+GetTitle(NPChar,true)+".";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarZalp_final";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_PikarZalp_3":
			dialog.text = "Ekip hazır. Emredin.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarZalp_final";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_PikarZalp_final":
			dialog.text = "...";
			link.l1 = "Topçular! Tüm toplardan ateş! Ateş!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_ZalpInSea");
			locCameraFromToPos(-9.34, 8.28, -16.03, true, -9.33, 7.32, -20.48);
			CharacterTurnToLoc(pchar, "quest", "quest10");
			CharacterTurnToLoc(npchar, "quest", "quest10");
		break;
		
		// Диалог с отцом в поместье де Монпе
		case "SharlieEpilog_HenriDeMonper_1":
			NextMonth = GetDataMonth() + 2;
			if (NextMonth == 13) NextMonth = 1;
			else if (NextMonth == 14) NextMonth = 2;
			Month = XI_ConvertString("MonthVoc_" + NextMonth);
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+"... Seni gördüğüme öyle sevindim ki, oğlum!";
			if (GetDataMonth() >= 4 && GetDataMonth() <= 10)
			{
				link.l1 = "Baba... Tekrar evde olduğuma inanamıyorum... Karın nasıl göründüğünü bile unutmuşum. Sanki burada hiçbir şey değişmemiş...";
			}
			else
			{
				link.l1 = "Baba...   Yine evde olduğuma inanamıyorum...   Sanki bu şerefime kar bile yağmaya karar vermiş.  "+month+". Burada hiç bir şey değişmemiş...";
			}
			link.l1.go = "SharlieEpilog_HenriDeMonper_2";
			locCameraFromToPos(-8.76, 7.86, 0.75, true, -7.41, 6.11, 0.18);
			Achievment_Set("ach_CL_202");
		break;
		
		case "SharlieEpilog_HenriDeMonper_2":
			dialog.text = "Ama senin için aynı şeyi söyleyemem! Duruşun, yürüyüşün, yaraların\n"+"Hayır, karşımda artık uzak diyarlara uğurladığım o şımarık çocuk yok.";
			link.l1 = "Karayipler insanı çabuk olgunlaştırıyor, baba. Ama bunu sonra konuşuruz. Anlatın bakalım, sağlığınız nasıl? Umarım hastalık gerilemiştir, zira karşımda tam teçhizatlı duruyorsunuz?";
			link.l1.go = "SharlieEpilog_HenriDeMonper_3";
		break;
		
		case "SharlieEpilog_HenriDeMonper_3":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				dialog.text = "Ne yazık ki, "+pchar.name+",   o   sadece   boğazıma   daha   sıkı   sarıldı.   Ama   sevgili   oğlumu   sıradan   bir   kıyafetle   karşılayabilir   miydim?   Benim   için   bu   büyük   bir   gün,  "+pchar.name+"\n"+"Görünüşe bakılırsa, beni biriyle tanıştırman gerekiyor.";
				link.l1 = "...";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe_10");
			}
			else
			{
				dialog.text = "Ne yazık ki, "+pchar.name+",   yıllar geçtikçe tutuşu daha da güçleniyor. Ama sevgili oğlumu sıradan bir kıyafetle karşılayabilir miydim? Bu benim için büyük bir gün, "+pchar.name+"\n"+"Bakıyorum, yalnız gelmemişsin\n"+"Yolculuktan acıkmışsındır, değil mi? Suzanne senin en sevdiğin tarife göre kaz ciğeri hazırladı!\n"+"Buyurun sofraya - yol üzerinde bizi tanıştırırsın!";
				link.l1 = "İtiraf edeyim, bu kokuyu malikaneye yaklaşırken bile aldım!";
				link.l1.go = "SharlieEpilog_HenriDeMonper_8"; // заходят в поместье
			}
		break;
		
		case "SharlieEpilog_HenriDeMonper_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "...";
			link.l1 = "Baba, size eşimi takdim etmek isterim - "+sld.name+" "+pchar.lastname+". "+sld.name+", bu benim babam - şövalye "+GetCharacterName("Henri")+" "+GetCharacterName("de Monper")+".";
			link.l1.go = "SharlieEpilog_HenriDeMonper_5";
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_5":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				sld = CharacterFromID("Helena");
				dialog.text = ""+pchar.name+", büyülendim! Seçtiğin hanımefendi, burada alışık olduğumuz şımarık sosyete kadınlarına hiç benzemiyor. Tahmin ediyorum ki, oğlumun kalbini yönettiği kadar bir gemiyi de ustalıkla idare ediyordur.";
				link.l1 = "...";
				link.l1.go = "SharlieEpilog_HenriDeMonper_Helena_1";
				CharacterTurnByChr(npchar, sld);
			}
			else
			{
				sld = CharacterFromID("Mary");
				dialog.text = "Sizinle tanışmak benim için büyük bir mutluluk, hanımefendi. Emin olabilirsiniz, oğlumun zevki gerçekten mükemmeldir!";
				link.l1 = "...";
				link.l1.go = "SharlieEpilog_HenriDeMonper_Mary_1";
				CharacterTurnByChr(npchar, sld);
			}
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Helena_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_2":
			dialog.text = "İltifatınız için teşekkür ederim, şövalye! Haklısınız, en sert fırtınada bile dümeni tutabilirim. Ama oğlunuzun kalbine gelince – onu yönetmeye gerek yok. Biz, amaçlarımızda ve arzularımızda biriz.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_HenriDeMonper_Helena_2_1";
			SharlieEpilog_InEstateDeMonpe_11_2();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_2_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Helena_2_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_3":
			dialog.text = "Rahip Benoit sizi akıllı ve cesur bir genç kadın olarak tanımladı - ve sanırım hiç de abartmamış. Ben de mutluyum ki "+pchar.name+"   sende sadece bir eş değil, aynı zamanda ruhumun yoldaşını da buldum\n"+"Yolculuktan acıkmışsındır, değil mi? Suzanne senin en sevdiğin tarifle kaz ciğeri hazırladı!\n"+"Pekâlâ, herkesi sofraya davet ediyorum! Yol boyunca da umarım birbirimizi daha yakından tanırız.";
			link.l1 = "İtiraf edeyim, bu kokuyu daha malikaneye yaklaşırken aldım!";
			link.l1.go = "SharlieEpilog_HenriDeMonper_6";
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Mary_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_2":
			dialog.text = "Sizinle tanıştığıma memnun oldum, şövalye! "+pchar.name+" sizin hakkınızda çok şey anlatmıştı, ve sizi tam da böyle hayal etmiştim, di mi!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_HenriDeMonper_Mary_2_1";
			CharacterTurnByChr(pchar, npchar);
			SharlieEpilog_InEstateDeMonpe_11_2();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_2_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Mary_2_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_3":
			sld = CharacterFromID("Mary");
			dialog.text = ""+pchar.name+", büyülendim! Seçtiğin kadın hiç de pudralı sosyete hanımlarına benzemiyor - ve asıl değeri de işte burada\n"+"Bence sen nazlı, kaprisli zambaklar yerine harika bir gül seçtin.";
			link.l1 = "Yaban gülünü, baba… "+sld.name+"  - gerçek bir hazine. Eminim, onu daha yakından tanıdığınızda bana hak vereceksiniz.";
			link.l1.go = "SharlieEpilog_HenriDeMonper_Mary_4";
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_4":
			if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2) sStr = "ты познакомишь меня с остальными";
			else sStr = "ты представишь меня нашему гостю";
			dialog.text = "O halde bu anı daha fazla ertelemeyelim! Yolculuktan acıkmışsındır, değil mi? Suzanne senin en sevdiğin tarifle kaz ciğeri hazırladı!\n"+"Herkesi sofraya davet ediyorum! Ve umarım yol boyunca, "+sStr+"";
			link.l1 = "İtiraf edeyim, bu kokuyu daha malikaneye yaklaşırken bile almıştım!";
			link.l1.go = "SharlieEpilog_HenriDeMonper_6";
			CharacterTurnByChr(CharacterFromID("HenriDeMonper"), pchar);
		break;
		
		case "SharlieEpilog_HenriDeMonper_6":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe_14");
		break;
		
		case "SharlieEpilog_HenriDeMonper_7":
			dialog.text = "...";
			link.l1 = "Sevgilim, bunu mutlaka denemelisin – bizim aile tarifimizle yapılan kaz ciğeriyle hiçbir şey boy ölçüşemez! Bu tarif bize dedemizden kaldı – ona da Akdeniz ülkelerinden birinden hediye olarak getirmişler.";
			link.l1.go = "SharlieEpilog_HenriDeMonper_8"; // заходят в поместье
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_8":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe_15");
		break;
		
		// диалог на ужине в поместье де Монпе
		case "SharlieEpilog_InKitchenDeMonpe":
			dialog.text = "";
			link.l1 = "Şöleni hüzünle başlatmak istemem, ama aile olarak bizden önce gidenleri hatırlamak boynumuzun borcu. Sizden kadehlerinizi Michel’in anısına kaldırmanızı rica ediyorum. Tanrı ruhuna huzur versin.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_2";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_2":
			dialog.text = "";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_3";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_3":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2) sStr = "добрых друзей";
				else sStr = "соратника";
				dialog.text = "";
				link.l1 = "Sana soracak o kadar çok şeyim var ki, "+pchar.name+"... Ama önce eşini dinlememe izin ver ve "+sStr+". Lütfen, Charles ile nasıl tanıştığınızı anlatın.";
			}
			else
			{
				if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2) sStr = "твоих добрых друзей";
				else sStr = "твоего друга";
				dialog.text = "";
				link.l1 = "Sana sormam gereken o kadar çok şey var ki, "+pchar.name+"... Ama önce dinlememe izin ver "+sStr+". Lütfen anlatır mısınız, Charles ile nasıl tanıştınız.";
			}
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_4";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		// if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
		
		case "SharlieEpilog_InKitchenDeMonpe_4":
			dialog.text = "";
			link.l1 = "Ben de sizin kadar bunu dinlemek için sabırsızlanıyorum!";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_5";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_6";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7";
			}
			else
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_5":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				link.l1 = "Hayatım ciddi tehlikedeydi... "+pchar.name+",   gerçek bir centilmen gibi,   felaketin olmasına izin vermedi!   Benim için araya girdi ve o alçaklarla işini bitirdi, di mi!";
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1 = ""+pchar.name+" beni bir İngiliz alçağının elinden kurtardın, o kadar cüretkârdı ki... beni kaçırmaya kalkıştı. Bir saat bile geç kalsaydın - belki de hiç tanışamayacaktık.";
			}
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_5_1";
			SharlieEpilog_InKitchenDeMonpe_camera_Wife();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_5_1":
			dialog.text = "";
			link.l1 = "Gerçek bir soyluya yakışır şekilde davranacağından hiç şüphem yoktu. Onurumuz, ailemiz için sadece bir kelime değil. Seninle gurur duyuyorum, oğlum.";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_6";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7";
			}
			else
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_6":
			sld = CharacterFromID("Tichingitu");
			dialog.text = "";
			link.l1 = ""+sld.name+" beyaz suratlıların evine girmek, yiyecek bulmak için. Beyaz suratlı yakalamak "+sld.name+" - ve hapse göndermek. Kaptan "+pchar.name+" gelmek, kurtarmak "+sld.name+" hapisten. O zamandan beri "+sld.name+" kaptana hizmet etmek "+pchar.name+" ve son nefesime kadar sadık kalmak.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_6_1";
			SharlieEpilog_InKitchenDeMonpe_camera_Tichingitu();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_6_1":
			sld = CharacterFromID("Tichingitu");
			dialog.text = "";
			link.l1 = "Oğlumun sadece asil bir soylu değil, aynı zamanda iyi yürekli bir insan olduğunu bilmek sevindirici. Onun yanında sizin gibi sadık dostların olması beni mutlu ediyor, "+sld.name+".";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7";
			}
			else
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_7":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "Bir gün kaptan iş ararken evime uğradı. Ona bir görev verdim, o da işin üstesinden geldi. Amirimiz kaptanı sevdi, onu işlerine daha çok dahil etti, beni de kaptanın gemisine gönderdi... göz kulak olmam için. Sonra bu... beyefendi sessizce demir aldı, top güllesi sakalıma, kaptana tek kelime etmeden takımadaları terk etti. Onu kendi başına, kendi başlattığı karmaşanın içinde bıraktı. Ben de kaptana yardımımı teklif ettim ve Richard ona hainlik etmiş olsa da, top güllesi kıçına, kaptan beni kovmadı.";
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7_2";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "Longway ve sayın kaptan aynı adama hizmet ediyordu. Ama o adam Longway'i aldattı. O zaman Longway karar verdi: artık o adama hizmet etmeyecek. Sayın kaptan beni gemisine aldı, subay yaptı ve Longway için çok şey yaptı.";
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7_2";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "İlk kez Bridgetown meyhanesinde karşılaştık: "+pchar.name+"   bir iş arıyordu, ben ise güvenilir birini. Tanışmamız sadece bir başlangıçtı — ardından yollarımızı навсегда birbirine bağlayan olaylar geldi. Onun subayı oldum ve şimdi hiç tereddüt etmeden onu dostum olarak adlandırabilirim — uğruna hayatımı riske atmaya hazır olduğum biri.";
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7_2";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Gambitnik();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_7_2":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "Koşulların ötesinde insanı görebilmek nadir bir yetenektir. Sanırım bu, oğlumun sağduyudan yoksun olmadığını gösteriyor.";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "Oğlumun duygusuz bir asker değil, yoldaşlarına sahip çıkmayı bilen gerçek bir komutan olmasına seviniyorum.";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "Her gün böyle sözler duymak mümkün değil. Sanırım bu, oğlumun sadece yetenekli bir denizci değil, aynı zamanda iyi bir dost olduğunun en iyi kanıtı.";
			}
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_8":
			dialog.text = "";
			link.l1 = "Bordeaux'da tanıştık. Kaptan, yolcu olarak gemimize bindi ve biz onu Martinique'e götürdük. O zamandan beri - buraya gönderilene dek - ekibinin sesi olarak kaldım ve nasıl olduğunu izledim, "+GetFullName(pchar)+" adım adım şu an olduğu kişi haline geliyordu.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8_1";
			SharlieEpilog_InKitchenDeMonpe_camera_Alonso();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_8_1":
			dialog.text = "";
			link.l1 = "Demek, Şarl’ı hâlâ benim ısrarımla aile ocağından ayrılan o yaramaz delikanlı olarak tanıyorsunuz? Sanırım, mösyö, sizinle konuşacak çok şeyimiz будет.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_9";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_9":
			dialog.text = "";
			link.l1 = "Sevgilim "+pchar.name+", uzun ve şanlı bir yol katettin... Sadece bir tavşan postu için vahşi savana gittin, ama bir aslanla savaştın ve zaferle döndün, omuzlarında onun postunu taşıyarak. Artık, hiç olmadığı kadar, malikânemizin ve tüm topraklarımızın geleceği için içim rahat.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_10";
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_10":
			dialog.text = "";
			link.l1 = "Aile işlerimizin tüm sorumluluğunu bir an önce sana devretmek için sabırsızlanıyorum. Önünde çok iş var, ama inanıyorum ki bizzat Tanrı sana lütfuyla bakıyor ve sen sadece sana emanet edilen mirası korumakla kalmayacak, de Monpe ailesinin onurunu ve refahını da artıracaksın.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_11";
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_11": //выбор Шарля
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1 = "Sizin oğlunuz ve varisiniz olmak benim için büyük bir onur. Ailemizin tüm sorumluluklarını seve seve üstleniyorum. Eminim ki eşim de bu yolda bana sadık bir destek olacak. Söz veriyorum, ailemizin adını daha da yüceltmek için elimden gelen her şeyi yapacağım... Ve onun refahına ilk katkım bir çocuğun doğumu olacak!";
				link.l1.go = "SharlieEpilog_ChooseEstate_HaveWife_1";
			}
			else
			{
				link.l1 = "Sizin oğlunuz ve varisiniz olmak benim için büyük bir onur. Ailemizin tüm sorumluluklarını seve seve üstleniyorum ve şanımızı daha da yüceltmek için elimden gelen her şeyi yapacağıma söz veriyorum.";
				link.l1.go = "SharlieEpilog_ChooseEstate_Single_1";
			}
			link.l2 = "Baba, Yeni Dünya'da geçirdiğim yıllar beni değiştirdi. Korkarım, artık buradaki, Avrupa'daki sakin yaşama alışamayacağım.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l2.go = "SharlieEpilog_ChooseCaribbean_HaveWife_1";
			}
			else
			{
				link.l2.go = "SharlieEpilog_ChooseCaribbean_Single_1";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		// --> Выбрал остаться в поместье с женой
		case "SharlieEpilog_ChooseEstate_HaveWife_1":
			dialog.text = "";
			link.l1 = ""+pchar.name+", yok artık...";
			link.l1.go = "SharlieEpilog_HaveWife_12";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
			pchar.questTemp.SharlieEpilog_ChooseEstate = true;
		break;
		
		case "SharlieEpilog_HaveWife_12":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "";
			link.l1 = "Evet, baba. "+sld.name+" hamileyim.";
			link.l1.go = "SharlieEpilog_HaveWife_13";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_HaveWife_13":
			dialog.text = "";
			link.l1 = "Bu gerçekten harika bir haber, sevgili oğlum! Tanrı dualarımı işitti! Buradaki herkes şahit olsun: yeni doğan şerefine, malikanemizin gördüğü en görkemli baloyu düzenleyeceğim! Kaldıralım kadehlerimizi – varisimizin şerefine!";
			link.l1.go = "SharlieEpilog_HaveWife_14";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_HaveWife_14":
			dialog.text = "";
			link.l1 = "Ya da varisi!";
			link.l1.go = "SharlieEpilog_HaveWife_15";
			SharlieEpilog_InKitchenDeMonpe_camera_Wife();
		break;
		
		case "SharlieEpilog_HaveWife_15":
			dialog.text = "";
			link.l1 = "Ailemizin tarihindeki yeni bir sayfa için!";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_HaveWife_16";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_HaveWife_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_HaveWife_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_HaveWife_16":
			dialog.text = "";
			link.l1 = "Gelecekteki savaşçıya ya da iyi bir kıza!";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_HaveWife_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_HaveWife_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Tichingitu();
		break;
		
		case "SharlieEpilog_HaveWife_17":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "Bebek sağlığına!";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "Sizi bir araya getiren o tesadüfe!";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "Ailenizin parlak geleceğine!";
			}
			link.l1.go = "SharlieEpilog_HaveWife_18";
			SharlieEpilog_InKitchenDeMonpe_camera_Gambitnik();
		break;
		
		case "SharlieEpilog_HaveWife_18":
			dialog.text = "";
			link.l1 = "Geleceğin Alonso de Mor'u ya da Alonsita de Mor'u için!";
			link.l1.go = "SharlieEpilog_HaveWife_19";
			SharlieEpilog_InKitchenDeMonpe_camera_Alonso();
		break;
		
		case "SharlieEpilog_HaveWife_19":
			dialog.text = "";
			link.l1 = "Ah-ha-ha!";
			link.l1.go = "SharlieEpilog_HaveWife_20";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_HaveWife_20":
			dialog.text = "";
			link.l1 = "Ha-ha!";
			link.l1.go = "SharlieEpilog_HaveWife_21";
			SharlieEpilog_InKitchenDeMonpe_camera_Wife();
		break;
		
		case "SharlieEpilog_HaveWife_21":
			dialog.text = "";
			link.l1 = "Ha ha ha!";
			link.l1.go = "SharlieEpilog_toast";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_toast":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_toast");
		break;
		// <-- Выбрал остаться в поместье с женой
		
		// --> Выбрал остаться в поместье будучи холостяком
		case "SharlieEpilog_ChooseEstate_Single_1":
			dialog.text = "";
			link.l1 = "Sizin oğlunuz ve varisiniz olmak benim için büyük bir onur. Ailemizin tüm sorumluluklarını seve seve üstleniyorum ve söz veriyorum, ailemizin adını daha da yüceltmek için elimden gelen her şeyi yapacağım.";
			link.l1.go = "SharlieEpilog_ChooseEstate_Single_2";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
			pchar.questTemp.SharlieEpilog_ChooseEstate = true;
		break;
		
		case "SharlieEpilog_ChooseEstate_Single_2":
			dialog.text = "";
			link.l1 = "Söyle, "+pchar.name+",   benim   Yvonne   ile   evlenme   teklifimi   düşündün   mü?";
			link.l1.go = "SharlieEpilog_Single_13";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_Single_13":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_ChooseCaribbean"))
			{
				link.l1 = "İtiraf edeyim baba… Yvonne hiçbir zaman kalbime yakın olmadı. Ama Yeni Dünya’da pek çok güzel kız var. Size söz veriyorum – layık birini bulduğumda, hiç tereddüt etmeyeceğim.";
			}
			else
			{
				link.l1 = "İtiraf edeyim baba… Yvonne hiçbir zaman kalbime yakın olmadı. Ama Fransa’da güzel kızlar çok. Size söz veriyorum – layık birini bulduğumda, hiç beklemeyeceğim.";
			}
			link.l1.go = "SharlieEpilog_Single_14";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_Single_14":
			dialog.text = "";
			link.l1 = "Senin ruh halin bana çok hoş geliyor, sevgili oğlum. Kadehlerimizi kaldıralım – senin için, başarıların için ve eve layık bir dönüş için!";
			link.l1.go = "SharlieEpilog_Single_15";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_Single_15":
			dialog.text = "";
			link.l1 = "Yeni Dünya’da onsuz hayatta kalamayacağımız sadık dostlara!";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_Single_16";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_Single_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Single_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_Single_16":
			dialog.text = "";
			link.l1 = "Büyük yürekli Kaptan Charles'a!";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_Single_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Single_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Tichingitu();
		break;
		
		case "SharlieEpilog_Single_17":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "Kaptanın demir iradesine!";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "Kaptan beyimizin bilgeliğine!";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "Dava uğruna!";
			}
			link.l1.go = "SharlieEpilog_Single_18";
			SharlieEpilog_InKitchenDeMonpe_camera_Gambitnik();
		break;
		
		case "SharlieEpilog_Single_18":
			dialog.text = "";
			link.l1 = "Suyun içinden kuru çıkma yeteneğine!";
			link.l1.go = "SharlieEpilog_toast";
			SharlieEpilog_InKitchenDeMonpe_camera_Alonso();
		break;
		// <-- Выбрал остаться в поместье будучи холостяком
		
		// Шарль губернатор разговаривает с зелёным капитаном
		case "SharlieEpilog_GreenCaptain":
			dialog.text = "";
			link.l1 = "Vali ile görüşmek için çok ısrar ettiğinizi duydum. Peki, Martinik valisinden ne istemiştiniz?";
			link.l1.go = "SharlieEpilog_GreenCaptain_1";
			locCameraFromToPos(-1.80, 3.84, -9.08, true, -2.38, 2.21, -7.33);
			PlaySound("Voice\" + LanguageGetLanguage() + "\officer_common_2.wav");
		break;
		
		case "SharlieEpilog_GreenCaptain_1":
			dialog.text = "Fransa tacı için çalışmak hakkında konuşmak istiyorum.";
			link.l1 = "Evet, size vereceğim bir görev var, ki bunun için hem mümkün olan en büyük çevikliği hem de deniz savaşında ustaca hareket etmeyi göstermeniz gerekecek. Kendinizi göstermeye hazır mısınız?";
			link.l1.go = "SharlieEpilog_GreenCaptain_2";
		break;

		case "SharlieEpilog_GreenCaptain_2":
			dialog.text = "Yüce Efendim, yaklaşan görevin özünü biraz daha ayrıntılı anlatabilir misiniz?";
			link.l1 = "Elbette. İspanyolların 'Santa Esperanza' adında bir kurye gemisini bulmanız, ona çıkıp kaptan kamarasında bulacağınız evrakları bana getirmeniz gerekiyor. Sözünü ettiğim gemi yaklaşık on iki gün sonra Trinidad yakınlarından geçecek.";
			link.l1.go = "SharlieEpilog_GreenCaptain_3";
		break;

		case "SharlieEpilog_GreenCaptain_3":
			dialog.text = "Pekâlâ, bu işi üstleniyorum. Peki, hangi belgeleri aramalıyım?";
			link.l1 = "Posta gönderilerini. Orada, diğer şeylerin arasında, benim için çok önemli belgeler olacak. Ama evrakları karıştırmanıza gerek yok, sadece tüm paketi bana eksiksiz getirin. Bu hizmet için size on beş bin peso ödeyeceğim... Yani, sizi sonuçlarla birlikte konutumda bekliyorum.";
			link.l1.go = "SharlieEpilog_GreenCaptain_4";
		break;

		case "SharlieEpilog_GreenCaptain_4":
			dialog.text = "Sanırım sizi fazla bekletmeyeceğim, Ekselansları.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GuberOnMartinique_5");
		break;
		
		//Шарль разговаривает с комендантом форта
		case "SharlieEpilog_KomendantFort":
			dialog.text = "Yüce Efendim... Rapor vermeme izin var mı?";
			link.l1 = "Rapor verin, "+GetAddress_Form(NPChar)+" "+npchar.lastname+".";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) link.l1.go = "SharlieEpilog_KomendantFort_1";
			else link.l1.go = "SharlieEpilog_KomendantFort_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\military02.wav");
		break;
		
		case "SharlieEpilog_KomendantFort_1":
			dialog.text = "Öhö-öhöm...";
			link.l1 = "Rahatça konuşun. Eşimden hiçbir şey gizlemem.";
			link.l1.go = "SharlieEpilog_KomendantFort_2";
		break;
		
		case "SharlieEpilog_KomendantFort_2":
			dialog.text = "İstihbarat bildiriyor: Willemstad’dan bir filo çıktı. Başlarında ikinci sınıf bir hat gemisi ‘Gouden Leeuw’ var, tam anlamıyla bir deniz canavarı. Filonun toplam ateş gücü iki buçuk yüzü aşkın top ve bin beş yüzden fazla asker. Hedefleri ise Saint-Pierre.";
			link.l1 = "Hm... Demek ki, hazırlık için neredeyse hiç vaktimiz yok.";
			link.l1.go = "SharlieEpilog_KomendantFort_3";
		break;

		case "SharlieEpilog_KomendantFort_3":
			dialog.text = "Ne yapacağız, sayın vali?";
			link.l1 = "Limanda, düşmana arkadan saldırabilecek birkaç gemimiz var...";
			link.l1.go = "SharlieEpilog_KomendantFort_4";
		break;

		case "SharlieEpilog_KomendantFort_4":
			dialog.text = "Onlara iki taraftan saldırmayı mı düşünüyorsunuz?";
			link.l1 = "Aynen öyle. Kale ateşi üzerine çekecek. Gece olunca, komutam altındaki filo denizden saldıracak. Dikkatlerini dağıtacağız, o sırada limandan zift ve tahtalarla doldurulmuş kundak gemileri çıkacak. Filolarından geriye bir kıymık bile kalmayacak.";
			link.l1.go = "SharlieEpilog_KomendantFort_5";
		break;

		case "SharlieEpilog_KomendantFort_5":
			dialog.text = "Mükemmel bir plan, Ekselansları! Hazırlıklara başlama emrini vermeme izin verir misiniz?";
			link.l1 = "Başlayın. Ve Tanrı bizimle olsun.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GuberOnMartinique_11");
		break;
		
		// Стражник вызывает Алонсо
		case "SharlieEpilog_Guard":
			dialog.text = "";
			link.l1 = "Gardiyan, Alonso'yu çağırın.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoArrive");
		break;
		
		//Шарль разговаривает с Алонсо после коменданта
		case "SharlieEpilog_Alonso35":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")))
			{
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
				dialog.text = "Sayın vali...";
				link.l1 = ""+npchar.name+", Hollanda filosu her an buraya gelebilir ve kuşatmayı başlatabilir. Emri dinle: Philippe'i al ve "+sld.name+",   ve hemen onları rahibe götür. O, bütün kadınları, çocukları ve yaşlıları toplasın ve onların güvenliğini sağlasın.";
				link.l1.go = "SharlieEpilog_Alonso36_Wife";
				break;
			}
			dialog.text = "Sayın vali...";
			link.l1 = ""+npchar.name+", Hollanda filosu her an buraya varıp şehri kuşatabilir. Abbaya söyle, tüm kadınları, çocukları ve yaşlıları toplasın ve onların güvenliğini sağlasın. Sana gelince, seni bir brülörün komutasına vermeyi düşünüyorum. Ayrıntıları sonra konuşuruz. Öncelikle sivilleri korumamız gerek.";
			link.l1.go = "SharlieEpilog_Alonso37";
		break;

		case "SharlieEpilog_Alonso36_Wife":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "Sanmıyorum ki "+sld.name+" diğer kadınlara katılmayı kabul edecek. Sıkıntıdan patlıyor.";
			link.l1 = "Hmm... O zaman ona söyle: savaşa hazırlansın. Sen de boş durmayacaksın — branda komuta edeceksin. Ayrıntıları sonra konuşuruz. Şimdi — oğlumla ilgilen.";
			link.l1.go = "SharlieEpilog_Alonso37";
		break;
		
		case "SharlieEpilog_Alonso37":
			dialog.text = "Bir onur sayarım! İzninizle başlayayım mı?";
			link.l1 = "İzin veriyorum. Harekete geç. Her saniyemiz önemli.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GuberOnMartinique_13");
		break;
		// --> Выбрал отправиться назад на Карибы с женой
		case "SharlieEpilog_ChooseCaribbean_HaveWife_1":
			dialog.text = "";
			link.l1 = "Peki... İtiraf etmeliyim, bunu söyleyeceğini tahmin etmiştim – ama yine de başka bir cevap ummuştum. Yine de, seçimine saygı duyuyorum ve seni ikna etmeye çalışmayacağım.";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_2";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
			pchar.questTemp.SharlieEpilog_ChooseCaribbean = true;
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_2":
			dialog.text = "";
			link.l1 = "Sizi hayal kırıklığına uğrattığımı biliyorum. Ama size öyle bir haberim var ki, umarım şimdiye kadar söylenen her şeyi unutturur.";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_3";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_3":
			dialog.text = "";
			link.l1 = "Tüm dikkatimi sana verdim.";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_4";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "";
			link.l1 = "Burada en az bir yıl kalmaya niyetliyim. "+sld.name+" onun durumunda sallantı kesinlikle zararlı.";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_5";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_5":
			dialog.text = "";
			link.l1 = ""+pchar.name+", yok artık...";
			link.l1.go = "SharlieEpilog_HaveWife_12";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		// <-- Выбрал отправиться назад на Карибы с женой
		
		// --> Выбрал отправиться назад на Карибы один
		case "SharlieEpilog_ChooseCaribbean_Single_1":
			dialog.text = "";
			link.l1 = "Pekâlâ... İtiraf edeyim, bunu söyleyeceğini bekliyordum – ama yine de başka bir cevap ummuştum. Yine de seçimine saygı duyuyorum ve seni ikna etmeye çalışmayacağım. Ama söyle bakalım, "+pchar.name+",   benim İvonne ile evlenme teklifimi düşündün mü?";
			link.l1.go = "SharlieEpilog_Single_13";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
			pchar.questTemp.SharlieEpilog_ChooseCaribbean = true;
		break;
		// <-- Выбрал отправиться назад на Карибы один
		
		//Диалог Шарль и Мишеля на Рифе Скелета
		case "SharlieEpilog_Mishelle_1":
			dialog.text = "Duramadın, değil mi?";
			link.l1 = "Sen mi?! Bu bir rüya mı?";
			link.l1.go = "SharlieEpilog_Mishelle_2";
			SharlieEpilog_OnReefs_6();
			PlaySound("Voice\" + LanguageGetLanguage() + "\sharlie\mishelle-04.wav");
		break;

		case "SharlieEpilog_Mishelle_2":
			dialog.text = "Kolay kazanç arzusu, güç, dokunulmazlık yanılsaması… Hangisi seni mahvetti, kardeşim? Hangisi aklını gölgeledi, tıpkı diğer beyazların aklını kararttığı gibi?";
			link.l1 = "Defol! Sen sadece bir hayaletsin! Burada değilsin!";
			link.l1.go = "SharlieEpilog_Mishelle_3";
		break;

		case "SharlieEpilog_Mishelle_3":
			dialog.text = "Hâlâ anlamadın mı? Spectra sunt memoria peccatorum. Aslında hayalet sensin... Karayipler'de anlatılan bir efsane: açgözlülük ve kör kibir tarafından yutulmuş bir adam. Kaç kişiyi altın uğruna öldürdün, "+pchar.name+"?";
			link.l1 = "Pekâlâ, sevgili kardeşim, seni ikinci kez öldürmemde hiçbir sakınca yok! Bunu kendin istedin!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_OnReefs_9");
		break;
		
		
		
		
		
	}
}