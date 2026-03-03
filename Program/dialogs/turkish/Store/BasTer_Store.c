// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Devam et, ne istiyorsun?","Biz de tam bundan bahsediyorduk. Herhalde unuttunuz...","Bugün bu soruyu üçüncü kez gündeme getiriyorsunuz...","Bakın, burası bir dükkân. İnsanlar burada alışveriş yapar. Beni rahatsız etmeyin!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Biliyor musun, "+NPChar.name+", belki bir dahaki sefere.","Doğru, nedense unuttum...","Evet, gerçekten de üçüncü kez...","Hm, yapmam...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			//Jason --> ----------------------------------мини-квест Бесчестный конкурент------------------------------------
			if (CheckAttribute(pchar, "questTemp.Shadowtrader"))
			{
				if(pchar.questTemp.Shadowtrader == "begin" && GetNpcQuestPastDayParam(npchar, "Shadowtrader_date") < 5 && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "Teşekkür ederim Kaptan, isteğimi yerine getirdiğiniz için. Şimdi, artık "+pchar.questTemp.Shadowtrader.Guardername+" burada, en azından biraz daha rahat hissedebilirim.";
					link.l1 = "Hmm... Rahatsız edici olmak istemem ama bana öyle geliyor ki bir sıkıntınız var. Neler olduğunu anlatır mısınız – belki yardımcı olabilirim?"; 
					link.l1.go = "Shadowtrader_fort";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.Trouble") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "Peki? Mektubumu teslim ettin mi?";
					link.l1 = "Var. Komutan, mektubunuzdaki delillerin şehir muhafızlarının harekete geçmesi için yetersiz olduğunu sözlü olarak bildirdi."; 
					link.l1.go = "Shadowtrader_trouble";
					pchar.quest.ShadowtraderTimeFort_Over.over = "yes";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Fort") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store" && CheckAttribute(pchar, "questTemp.Shadowtrader.EndFort"))
				{
					dialog.text = "I have already heard the news - tonight the guards discovered an illegal trading post run by smugglers and arrested them all. It was under the command of a rare piece of scum, but it's alright now; he won't be able to do harm to anyone else for a while.\nThe Commandant told me about your role in all of this, you have my gratitude! You have kept your word! Here, take the money - 15,000 pesos. You have saved me. Nothing threatens my business now!";
					link.l1 = "Rica ederim. Kolaydı."; 
					link.l1.go = "Shadowtrader_complete";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Escape") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "Peki, iyi bir haber var mı, "+pchar.name+"?";
					link.l1 = "Rakibinizi buldum. Artık size sorun olmayacak - onu bu adadan ayrılmaya ikna ettim... Dükkanı şehir kapısına yakın bir evdeydi. Terk edilen yükle ne yapacağınıza siz karar vereceksiniz. Yetkililere teslim edebilir ya da kendiniz almaya çalışabilirsiniz."; 
					link.l1.go = "Shadowtrader_Escape_complete";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Free") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "Haberi zaten duydum - bu gece muhafızlar evlerden birinin altında bir kaçakçı sığınağı bulmuş. İki hain ölü bulunmuş. Harika iş çıkardın, "+pchar.name+", sana hayranım! Al, ödülün - 15.000 peso. Beni gerçekten kurtardın! Artık gerçek ticaret yapacağım!\nBir merakımı gider - onların lideri... ölen iki kişi arasında mıydı?";
					link.l1 = "Hayır. Ama bir daha asla bu kasabada yüzünü göstermeyecek. Şu anda konuşurken, bu adadan onlarca mil uzakta olduğuna inanıyorum."; 
					link.l1.go = "Shadowtrader_complete";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Kill") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "Haberi zaten duydum - dün gece muhafızlar evlerden birinde gizli bir kaçakçı dükkânı bulmuş. Üç hain ölü bulunmuş. Harika iş, "+pchar.name+", sana hayranım! Al bakalım, ödülün - 15.000 peso. Beni gerçekten kurtardın! Artık gerçek ticaret yapacağım!\nBir merakımı gider - onların lideri... ölen iki kişi arasında mıydı?";
					link.l1 = "Evet. Rakibinden sonsuza dek kurtuldun. Artık sana asla sorun çıkarmayacak."; 
					link.l1.go = "Shadowtrader_complete";
					break;
				}
			}
			//<-- мини-квест Бесчестный конкурент
		break;
		
		// --> мини-квест Бесчестный конкурент
		case "Shadowtrader_begin":
			pchar.questTemp.Shadowtrader = "true";
			pchar.questTemp.Shadowtrader_Block = true;
			pchar.questTemp.Shadowtrader.Guardername = GenerateRandomName_Generator(sti(npchar.nation), "man");
			dialog.text = "Lütfen meyhaneye gidip adı   olan bir adamı bulur musun "+pchar.questTemp.Shadowtrader.Guardername+" ve ona mümkün olan en kısa sürede buraya gelmesini söyler misin? Ben dükkandan ayrılamam, o ahmak ise meyhanede oturup roma abanıyor, üstelik nöbette olmasına rağmen buraya gelmeyi aklının ucundan bile geçirmez.";
			link.l1 = "Yardımcı olmaktan her zaman mutluluk duyarım, dostum – hem de özellikle, çünkü zaten meyhaneye gitmeyi düşünüyordum.";
			link.l1.go = "Shadowtrader_begin_1";
			link.l2 = "Benimle dalga mı geçiyorsun? Sana hizmetçi mi görünüyorum? Meyhane şuracıkta, birkaç adım ötede - kendin gidebilirsin.";
			link.l2.go = "exit";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("BasTer");
		break;
		
		case "Shadowtrader_begin_1":
			dialog.text = "Teşekkür ederim! Lütfen ona hemen buraya gelmesini söyleyin. Aman Tanrım, neden bu kadar baş belası olmak zorunda...";
			link.l1 = "Endişelenmeyin. Onu size yönlendireceğim.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.City = npchar.City;
			pchar.questTemp.Shadowtrader.nation = sti(npchar.nation);
			//создаем охранника
			sld = GetCharacter(NPC_GenerateCharacter("ShadowGuarder" , "officer_7", "man", "man", 10, sti(npchar.nation), 5, true, "quest"));
			FantomMakeCoolFighter(sld, 20, 50, 50, "topor_2", "pistol3", "bullet", 50);
			sld.name = pchar.questTemp.Shadowtrader.Guardername;
			sld.lastname = "";
			sld.dialog.FileName = "Quest\LineMiniQuests\ShadowTrader.c";
			sld.dialog.currentnode = "ShadowGuarder";
			sld.greeting = "pirat_common";
			LAi_SetSitType(sld);
			LAi_SetImmortal(sld, true);
			FreeSitLocator(pchar.questTemp.Shadowtrader.City + "_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, pchar.questTemp.Shadowtrader.City + "_tavern", "sit", "sit_front1");
			SaveCurrentNpcQuestDateParam(npchar, "Shadowtrader_date");
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Shadowtrader_fort":
			dialog.text = "Ah, kaptan, yardımınızı gerçekten çok takdir ederim. Bu mektubu mümkün olan en kısa sürede komutana iletebilir misiniz? Bu önemsiz iş için size 300 altın ödeyeceğim – dediğim gibi, dükkânımdan ayrılamam.";
			link.l1 = " Sorun değil. O mektubu ver bana. ";
			link.l1.go = "Shadowtrader_fort_1";
			link.l2 = "Hayır, iyi adamım, o saçmalık için artık vaktim yok.";
			link.l2.go = "Shadowtrader_fort_end";
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_fort_1":
			dialog.text = "Al bakalım. Lütfen bunu bugün ona ver ve cevabını bana getir.";
			link.l1 = "Merak etme, hallederim.";
			link.l1.go = "exit";
			GiveItem2Character(pchar, "letter_1");
			ChangeItemDescribe("letter_1", "itmdescr_letter_1"); // 240912
			pchar.questTemp.Shadowtrader.Tradername = GetFullName(npchar);
			SetFunctionTimerCondition("ShadowtraderTimeFort_Over", 0, 0, 1, false);
			pchar.questTemp.Shadowtrader = "current"
			pchar.questTemp.Shadowtrader.Fort = "true";
			AddQuestRecord("Shadowtrader", "1");
			AddQuestUserData("Shadowtrader", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Shadowtrader.City+"Gen"));
			AddLandQuestMarkToPhantom("baster_prison", "basterJailOff");
		break;
		
		case "Shadowtrader_fort_end":
			dialog.text = "Görünüşe bakılırsa başka birine sormam gerekecek. Rahatsız ettiğim için üzgünüm, kaptan.";
			link.l1 = " Sorun değil. Hoşça kal! ";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader = "true";
			DeleteAttribute(pchar, "questTemp.Shadowtrader_Block");
		break;
		
		case "Shadowtrader_trouble":
			dialog.text = "Öyle mi dedi? Benden ne kanıt istiyor, cesedimi mi?! Böyle devam ederse, yakında bir ceset olacak zaten!..";
			link.l1 = "Hey, hey, "+npchar.name+", sakin ol, yoksa felç geçireceksin. Al, biraz su iç... Şimdi anlat bakalım, ne oldu - belki sana yardımcı olabilirim?";
			link.l1.go = "Shadowtrader_trouble_1";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.Trouble");
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_trouble_1":
			dialog.text = "Ah, kaptan! Lütfen, şu 300 pesoyu alın - neredeyse unutuyordum... Elbette anlatırım, ama nasıl yardımcı olabileceğinizden emin değilim. İşim neredeyse mahvoldu - hepsi o lanet kaçakçılar ve başlarındaki kim olduğu bilinmeyen o alçak yüzünden.";
			link.l1 = "Kaçakçılar mı?";
			link.l1.go = "Shadowtrader_trouble_2";
			AddMoneyToCharacter(pchar, 300);
		break;
		
		case "Shadowtrader_trouble_2":
			dialog.text = "Bu kadar! Şu alçaklar beni kasabadan kovmaya kesin karar vermişler! O zamana kadar her şey her zamanki gibiydi - yasaklı malları yeniden satarlardı, devriyeler yakaladığında ya saklanır ya da rüşvet verirlerdi. Ama son zamanlarda, bir ara sokakta bir dükkan açmışlar ve en çok aranan malları inanılmaz düşük fiyatlara satmaya başlamışlar!\nBenim böyle bir lüksüm olamaz - üstelik vergi ödemek zorundayım - giderek fakirleşiyorum ve denizciler neredeyse artık benden mal almak istemiyorlar - her şeyi bu düzenbazlardan alıyorlar.";
			link.l1 = "Ama yetkililere başvurmalıydınız! Sonuçta, böyle bir kanunsuzluğu durdurmak onların işi.";
			link.l1.go = "Shadowtrader_trouble_3";
		break;
		
		case "Shadowtrader_trouble_3":
			dialog.text = "Son başvurunun sonucunu kendin gördün. Vali çok meşgul, komutan ise kaçakçıların arka sokaklarda dükkân açtığına inanmadı ya da inanmazdan geliyor – ve sanırım mesele de bu\nTabii, neden böyle bir şey yapsınlar ki? Ben de diyorum ki: Bütün bu olanları, beni batırıp şehirden kovmak isteyen bir alçak uydurdu, sonra da sessizce işime el koyup pis işlerini temizleyecek.";
			link.l1 = "Hm... görüşünüz temelsiz değil. Tüccarların doğasında birini kendi çıkarları için kullanmak vardır... Ah, affedersiniz, tabii ki sizi kastetmedim. ";
			link.l1.go = "Shadowtrader_trouble_4";
		break;
		
		case "Shadowtrader_trouble_4":
			dialog.text = "Ah, hiçbir şey... Geçenlerde de bir serseri geldi, utanmadan bana dedi ki, eğer gürültü yapmaya devam edersem dükkanımı yakacaklarmış.\nBen de bir koruma tuttum. "+pchar.questTemp.Shadowtrader.Guardername+" ucuz değil, ama o bir profesyonel ve onun koruması altında kendimi biraz daha huzurlu hissedebiliyorum.";
			link.l1 = "Anlıyorum... Gerçekten tatsız bir hikaye. Görünen o ki, haklıymışsınız - sizin için yapabileceğim bir şey yok. Yine de eminim ki işler yoluna girecektir - böyle karanlık yerler genelde uzun süre ayakta kalmaz. Neyse, bol şanslar!";
			link.l1.go = "Shadowtrader_end";
			link.l2 = "Anladım. Yine de size yardımcı olabilirim belki...";
			link.l2.go = "Shadowtrader_trouble_5";
		break;
		
		case "Shadowtrader_trouble_5":
			dialog.text = "Bana yine de yardım mı teklif ediyorsun? Peki, ne yapacaksın?";
			link.l1 = "O 'meslektaşını' bulup... seni rahat bırakması için onu ikna etmeye çalışacağım. Bilirsin, insanları ikna etme konusunda bazı yeteneklerim var.";
			link.l1.go = "Shadowtrader_trouble_6";
		break;
		
		case "Shadowtrader_trouble_6":
			dialog.text = "Ciddi misiniz? Tanrı adaletli davanızı kutsasın! Beni o pislikten kurtarırsanız size minnettar kalırım.";
			link.l1 = "Pekâlâ, anlaştık. O zaman aramaya başlıyorum.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.seeksmugglers = "true";
			AddLandQuestMark(characterFromId("BasTer_Smuggler"), "questmarkmain");
			AddQuestRecord("Shadowtrader", "2");
			AddQuestUserData("Shadowtrader", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Shadowtrader.City+"Gen"));
			AddQuestUserData("Shadowtrader", "sSex1", GetSexPhrase("ся","ась"));
		break;
		
		case "Shadowtrader_end":
			pchar.questTemp.Shadowtrader = "true";
			CloseQuestHeader("Shadowtrader");
			DeleteAttribute(pchar, "questTemp.Shadowtrader_Block");
			DialogExit();
		break;
		
		case "Shadowtrader_Escape_complete":
			dialog.text = "Gerçekten mi? Artık korkmadan ticaret yapabileceğim, öyle mi? Size minnettarım! İşte ödülünüz - 15.000 peso. Onların evindeki malları ise en iyisi komutana teslim etmek olur sanırım. Tekrar teşekkür ederim!";
			link.l1 = "Rica ederim. Çok da zor olmadı. İkna konusunda iyi olduğumu söylemiştim sana.";
			link.l1.go = "Shadowtrader_complete";
		break;
		
		case "Shadowtrader_complete":
			dialog.text = "Yine beklerim kaptan - sizi her zaman görmekten mutluluk duyarım.";
			link.l1 = "Elbette! Şimdi ise müsaadenizle ayrılıyorum – yapacak işlerim var! Hoşça kalın, ticaretinizde bol şanslar, "+npchar.name+"!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.End");
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.Shadowtrader = "complete";
			AddQuestRecord("Shadowtrader", "11");
			AddQuestUserData("Shadowtrader", "sSex", GetSexPhrase("","а"));
			CloseQuestHeader("Shadowtrader");
			DeleteAttribute(pchar, "questTemp.Shadowtrader_Block");
			DeleteAttribute(pchar, "questTemp.Shadowtrader.EndFort");
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("BasTer");
		break;
		//<-- мини-квест Бесчестный конкурент
	}
	UnloadSegment(NPChar.FileDialog2);
}
