#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

	switch(Dialog.CurrentNode)
	{
		case "First time":
			// --> калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche.SeekAmulet") && hrand(1) == 0 && sti(Pchar.money) >= 2000) 
			{
				dialog.text = "Bakın efendim, eğlenceli küçük bir şey almak istemez misiniz? Fiyatı uygun, sadece birkaç bin peso...";
				link.l1 = "Hmm. Muhtemelen bu 'küçük şeyi' çaldın ve şimdi de üstünden atmaya mı çalışıyorsun?";
				link.l1.go = "caleuche";
				break;
			}
			// <-- калеуче
			if (npchar.quest.meeting == "0")
			{
				dialog.text = LinkRandPhrase("Merhaba. Benim adım "+GetFullName(npchar)+". Sanmıyorum ki tanıştığımıza memnun oldunuz, ama belki en azından adımı hatırlarsınız...","Selamlar, "+GetAddress_Form(NPChar)+" . Benim adım "+GetFullName(npchar)+".","Benim adım "+GetFullName(npchar)+", "+GetAddress_Form(NPChar)+". Tanıştığımıza memnun oldum.");
				link.l1 = RandPhraseSimple("Selamlar.","Merhaba.");
				link.l1.go = "First time";
				// карибские нравы
				if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy_drink" && pchar.location == "portobello_town")
				{
					link.l2 = "Hey, dinle, bu zavallı sadakalar yerine birkaç bin peso kazanmak ister misin?";
					link.l2.go = "trial";
				}
				// --> Тайна Бетси Прайс
				if (CheckAttribute(pchar, "questTemp.TBP_BuyKulon3") && pchar.location == "Villemstad_town")
				{
					link.l2 = "O kameolu kolyeyi... Nerede buldun?";
					link.l2.go = "TBP_Kulon_1";
				}
				// <-- Тайна Бетси Прайс
				npchar.quest.meeting = "1";
			}			
			else
			{
				dialog.text = NPCStringReactionRepeat("Ne hallere düştüm bak...","Sadakayla yaşamak kolay değil...","Bu yoksulluktan kurtulmak için her şeyimi verirdim!","Yine sen mi?..","block",1,npchar,Dialog.CurrentNode);

				link.l1 = HeroStringReactionRepeat("Anladım. Pek de önemli bir şey değil.","Elbette. Biliyorsun, tarihteki en büyük adam aynı zamanda en yoksuluydu.","O zaman bütün gün burada oturmak yerine bir şeyler yapmaya başlamalısın.","Ah-ha. Şimdiden canını mı sıkıyorum?",npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "pester", npchar, Dialog.CurrentNode);
				link.l2 = RandPhraseSimple("Ne istiyorsun?","Ne istiyorsun?");
				link.l2.go = "Whants";
				// карибские нравы
				if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy_drink" && pchar.location == "portobello_town")
				{
					DelLandQuestMark(npchar);
					link.l2 = "Hey, dinle, bu zavallı sadakalar yerine birkaç bin peso kazanmak ister misin?";
					link.l2.go = "trial";
				}
				// --> Тайна Бетси Прайс
				if (CheckAttribute(pchar, "questTemp.TBP_BuyKulon3") && pchar.location == "Villemstad_town")
				{
					link.l2 = "O mücevherli kolyeyi... Nereden buldun?";
					link.l2.go = "TBP_Kulon_1";
				}
				// <-- Тайна Бетси Прайс
				link.l3 = LinkRandPhrase("Bana ilginç bir şey anlatabilir misin?","Kasabada neler var yeni?","Ah, en son dedikoduları duymak isterim...");
				link.l3.go = "rumours_poor";
			}
			NextDiag.TempNode = "First time";
		break;
		case "pester":
			dialog.text = RandPhraseSimple("Hayır, neden, şimdiden sıkıldın mı? Gördüğün gibi pek meşgul sayılmam...","Sadece beni yoruyor. Fakir olsam da, hâlâ bir adamım.");
			link.l1 = "Heh, anladım...";
			link.l1.go = "exit";
		break;
		//выходы
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//милостыня
		case "Whants":
			if (!CheckAttribute(npchar, "wants_date") || GetNpcQuestPastDayParam(npchar, "wants_date") >= 1 || bBettaTestMode)
    		{
				dialog.text = PCharRepPhrase("Hmm, "+GetAddress_Form(NPChar)+", senin hakkında çok kötü şeyler söylüyorlar. Ama ben insanlara inanmaya devam ediyorum - senin gibi olanlara bile. Lütfen, bana ekmek ve su için sadaka ver, bana acı.","Sana yalvarıyorum, "+GetAddress_Form(NPChar)+"! Lütfen, yoksul bir adamdan yüz çevirmeyin, bir öğün yemek için sadaka verin...");
				link.l1 = RandPhraseSimple("Sana hiçbir şey vermeyeceğim.","Parasız da idare edersin.");
				link.l1.go = "exit";
				Link.l2 = "Peki, tam olarak ne kadar ihtiyacın var?";
				Link.l2.go = "Whants_1";
			}
			else
			{
				dialog.text = PCharRepPhrase("Senden mi? Hiçbir şey.","Bir şeye ihtiyacım yok, "+GetAddress_Form(NPChar)+", teşekkür ederim.");
				link.l1 = RandPhraseSimple("Hmm, peki.","Görünüşe bakılırsa, senin hayatın o kadar da kötü değilmiş, dostum.");
				link.l1.go = "exit";
			}
		break;
		case "Whants_1":
			dialog.text = "Bir kuruşu bile geri çevirmezdim, "+GetAddress_Form(NPChar)+". Cebinizdeki para ve merhametinizin yettiği kadar...";
			Link.l1.edit = 2;			
			link.l1 = "";
			link.l1.go = "Whants_2";
		break;
		case "Whants_2":
			SaveCurrentNpcQuestDateParam(npchar, "wants_date");
			int iTemp = sti(dialogEditStrings[2]);
			if (iTemp <= 0 || sti(pchar.money) < iTemp)
			{
				dialog.text = "Zayıf ve yorgunlarla alay etmek günahtır...";
				link.l1 = "Ha-ha-ha! Gerçekten sana para vereceğimi mi sandın, sen aklını yitirmiş dilenci?!";
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", -2);
				break;
			}
			if (iTemp > 0 && iTemp <= 100)
			{
				dialog.text = "Teşekkür ederim "+FindRussianMoneyString(iTemp)+", "+GetAddress_Form(NPChar)+". Şimdi bu parayla biraz ekmek alabilirim...";
				link.l1 = "Al bakalım, serseri - git biraz kendine gel.";
				link.l1.go = "exit";
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
			if (iTemp > 100 && iTemp <= 500)
			{
				dialog.text = "Teşekkür ederim, "+GetAddress_Form(NPChar)+" . Bu parayla bir hafta geçinebilirim!";
				link.l1 = "Yardım etmekten memnuniyet duydum.";
				link.l1.go = "exit";
				OfficersReaction("good");
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
			if (iTemp > 500 && iTemp <= 1000)
			{
				dialog.text = "Teşekkür ederim, "+GetAddress_Form(NPChar)+". Herkese senin iyiliğinden bahsedeceğim!";
				link.l1 = "Bu gerçekten gerekli değil.";
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", iTemp/2000.0+0.5);
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
			if (iTemp > 1000 && iTemp <= 5000)
			{
				dialog.text = "Teşekkür ederim, saygıdeğer "+GetSexPhrase("efendim","hanımefendi")+" "+GetAddress_Form(NPChar)+"… Tanrı seni korusun…";
				link.l1 = "Evet, O'nun koruması kesinlikle fena olmazdı!";
				link.l1.go = "exit";
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), iTemp/10000.0+0.5);
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
			if (iTemp > 5000 && iTemp <= 10000)
			{
				dialog.text = "Teşekkür ederim, "+GetSexPhrase("en değerli efendim","en değerli hanımefendi")+" "+GetAddress_Form(NPChar)+". Size en iyi dileklerimi sunarım!";
				link.l1 = "Teşekkür ederim, dostum.";
				link.l1.go = "exit";
				AddCharacterExpToSkill(pchar, "Leadership", iTemp/5000.0);
				AddCharacterExpToSkill(pchar, "Fortune", iTemp/5000.0);
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
                 if (iTemp > 10000 && iTemp < 25000)
			{
				dialog.text = "Dinle, "+GetAddress_Form(NPChar)+", deli misin nesin? Bana veriyorsun "+FindRussianMoneyString(iTemp)+"! Böyle bir parayı kabul edemem, bunda kesin bir bit yeniği vardır... Beni rahat bırak!";
				link.l1 = "Peki, nasıl istersen...";
				link.l1.go = "exit";
			}
                 if (iTemp == 25000)
			{
				dialog.text = "Yirmi beş bin kabul edildi ... Bu para Lelya ve benim için bir yıl boyunca yeter!";
				link.l1 = "Önce bu yılı sağ salim atlat...";
				link.l1.go = "exit";
			}
			if (iTemp > 25000)
			{
				dialog.text = "Dinle, "+GetAddress_Form(NPChar)+", deli misin nesin? Bana veriyorsun "+FindRussianMoneyString(iTemp)+"! Böyle bir parayı kabul edemem, bunda bir bit yeniği olmalı... Beni rahat bırak!";
				link.l1 = "Peki, nasıl istersen...";
				link.l1.go = "exit";
			}
		break;
		
		case "trial":
			DelLandQuestMark(npchar);
			dialog.text = "Aptalca bir soru, señor! Tabii ki isterim! Ama... ne yapmam gerekecek? Elbette bana o parayı sadece güzel gülüşüm için vermeyeceksinizdir.";
			link.l1 = "Elbette hayır. Şimdi beni iyi dinle. Ben bizzat valinin adına hareket ediyorum. Ekselansları, tersanede birinin kasıtlı olarak 'Alacantara' adlı kalyonunun denize indirilmesini sabote ettiğinden şüpheleniyor. Ve bu şüpheleri, yakın zamanda bir Fransız casusu yakalandıktan sonra daha da arttı...";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "";
			link.l1 = "Majesteleri zaten gemi ustasının bahanelerini dinledi, ama doğruyu söylediğinden emin değil. Kim işlere sabotaj yapıyor ve nedenini bulmamız lazım. Rıhtıma git, etrafa bir bak ve işçilere 'Alacantara' neden hâlâ denize açılamıyor, bir öğren bakalım...";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			dialog.text = "";
			link.l1 = "Kimse senden şüphelenmeyecek, hatta bir yığın tütün bile ele geçirebilirsin. Bana gelince, kimse bana bir şey söylemeyecek. Herkes kimin için çalıştığımı bilecek. Eğer öğrenmeye değer bir şey bulursan, üç bin peso alacaksın. Bu, en az bir ay boyunca 'işini' bırakman için yeterli.";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			dialog.text = "Üç bin peso mu? Ama, saygıdeğer señor...";
			link.l1 = "Benimle pazarlık mı yapıyorsun, yoksa ne? Ha, bir de bu oyalamaların arkasında kimin olduğunu öğrenirsen, sana iki bin daha veririm. Anlaştık mı?";
			link.l1.go = "trial_4";
		break;
		
		case "trial_4":
			dialog.text = "Pekâlâ, señor. Çok da zor olmamalı – eski dostlarımın çoğu bu aralar limanda çalışıyor. Ben de eskiden denizciydim, hem de epey önce. On yıl kadar oldu...";
			link.l1 = "Hikayeni sonra anlatırsın. Gece on birden sonra iskelede buluşalım. Şimdi git.";
			link.l1.go = "trial_5";
		break;
		
		case "trial_5":
			DialogExit();
			AddDialogExitQuestFunction("Trial_Poorman_DlgExit");
		break;
		
		case "trial_6":
			dialog.text = "İyi akşamlar, señor...";
			link.l1 = "Peki? Bir şey öğrenebildin mi?";
			link.l1.go = "trial_7";
			DelLandQuestMark(npchar);
		break;
		
		case "trial_7":
			dialog.text = "Yaptım, señor, yaptım. Bana anlattıklarınla ne kadar örtüşüyor, emin değilim... Parayı getirdin mi? Beş bin peso.";
			if (sti(pchar.money) >= 5000)
			{
				link.l1 = "Endişelenme. Al paranı. Şimdi dökül bakalım.";
				link.l1.go = "trial_8";
			}
			else
			{
				link.l1 = "Önce bilgi, sonra para. Hadi, vaktimi boşa harcama!";
				link.l1.go = "trial_fail";
			}
		break;
		
		case "trial_fail":
			dialog.text = "Beni kandırmaya çalışıyorsun, señor! Eğer ödeme yapmayacaksan – git ve başkasından kendin iste. Sakın kılıcına davranmayı aklından bile geçirme, yoksa muhafızları çağırırım!";
			link.l1 = "...";
			link.l1.go = "trial_fail_1";
		break;
		
		case "trial_fail_1":
			DialogExit();
			AddDialogExitQuestFunction("Trial_FailPoormanInPort");
		break;
		
		case "trial_8":
			AddMoneyToCharacter(pchar, -5000);
			dialog.text = "Bak, mesele şöyle: 'Alcantara' uzun zamandır sefere hazır, ama valinin emriyle özellikle yüklenmemiş. Bana anlatılan bu. Şimdi de marangozlar geminin kalkışını etkilemeyen ufak tefek işler yapıyorlar.\nHerkes Cartagena'dan gelecek bir barkı bekliyor. Mesele şu ki, kaptanına göre 'Alcantara'nın barut stoğu yetersiz. Bu yüzden gemi günlerdir burada bekliyor, 'Puebla' barutu getirene kadar.\nAma herkes bu bekleyişin tamamen vakit kaybı olduğunu düşünüyor, o yüzden eğer 'Puebla' üç gün içinde gelmezse, 'Alcantara' barutsuz demir alacak...";
			link.l1 = "Öyle mi? Bunu sana kim söyledi? İsmi ne?";
			link.l1.go = "trial_9";
		break;
		
		case "trial_9":
			dialog.text = "'Alcantara'dan bir denizci - Felipe Dabinho... Ama bu zaten hiç de gizli bir şey değil, bizzat Valinin emriyle olmuş...'";
			link.l1 = "Anladım. Tam da beklediğim gibi. Fransız casusları şehirde, ama şu ahmaklar pazar kadınları gibi gevezelik ediyorlar, inanılır gibi değil! Her yeni gelen, Majestelerinin planları hakkında istediği her şeyi öğrenebilir. Ah, o Felipe Dabinho şimdi büyük belada! 'Alacantara'nın lostromosu da öyle! Mürettebatının disiplin nedir bilmemesi tamamen onun suçu!";
			link.l1.go = "trial_10";
		break;
		
		case "trial_10":
			dialog.text = "Oh... Yani, en başından beri biliyordun? Ama neden... Benim suçum değil! Bunu yapmamı sen söyledin!";
			link.l1 = "Bu senin suçun değildi, endişelenmene gerek yok, kimse seni cezalandırmayacak. Artık biliyoruz ki 'Alacantara' mürettebatı, gizli kalması gereken bilgileri bile düşmana anlatabiliyor. Peki, şimdi gidebilirsin. Yardımın için teşekkürler. Git, paranı harca.";
			link.l1.go = "trial_11";
			link.l2 = "Elveda. (Onu öldür)";
			link.l2.go = "trial_11a";
		break;
		
		case "trial_11a":
			DialogExit();
			AddDialogExitQuestFunction("Trial_KillPoormanInPort");
		break;
		
		case "trial_11":
			DialogExit();
			AddDialogExitQuestFunction("Trial_PeacePoormanInPort");
		break;
		
		// --> калеуче
		case "Caleuche":
			dialog.text = "Affedersiniz, beyefendi... Bunu zar oyununda bir yabancıdan kazandım. Şanslı bir iyileştirme muskası sandım ama yanılmışım... Hastalıkları iyileştirmiyor ve çarşıdaki tüccarlar da ilgilenmiyor. Ama işte siz buradasınız - bir denizci, bir kaptan, okumuş bir insansınız. Bir bakın, belki işinize yarar.\nSizin için bu birkaç bin küçük bir meblağ, ama benim için bir ay boyunca bir parça ekmek ve bir yudum rom demek. Bakın, beyefendi...";
			link.l1 = "Peki, göster...";
			link.l1.go = "Caleuche_1";
		break;
		
		case "Caleuche_1":
			Log_Info("You got a strange amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "Buyur...";
			link.l1 = "Eh işte... İlginç bir şey, kabul ediyorum. Eminim bu, yerlilerin köylerinden çalınmıştır. Peki, alıyorum. İşte paran.";
			link.l1.go = "Caleuche_2";
		break;
		
		case "Caleuche_2":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "Teşekkür ederim, efendim! Umarım bu size şans getirir! Tanrı sizi korusun!";
			link.l1 = "Bol şans, dostum. Tüm parayı bir anda meyhanede harcama.";
			link.l1.go = "Caleuche_3";
		break;
		
		case "Caleuche_3":
			DialogExit();
			GiveItem2Character(pchar, "kaleuche_amulet1"); 
		break;
		// <-- калеуче
		
		// --> Тайна Бетси Прайс
		case "TBP_Kulon_1":
			dialog.text = "Eh, "+GetAddress_Form(NPChar)+", neden eski bir ıvır zıvırla ilgileniyorsun?";
			link.l1 = "Senin aptal kafanı çizmemle tekmeyi bastığımda, neden umursadığımı hemen anlarsın.";
			link.l1.go = "TBP_Kulon_TO";
			if (CheckAttribute(pchar, "questTemp.TBP_BuyKulon2"))
			{
				link.l2 = "Bu kolye Betsy Price'a aitti. Peki, bunu nerede buldun?";
				link.l2.go = "TBP_Kulon_leadership";
			}
			DeleteAttribute(pchar, "questTemp.TBP_BuyKulon3");
		break;

		case "TBP_Kulon_TO":
			dialog.text = "Fenerli evin yanında yatıyordu, "+GetAddress_Form(NPChar)+". Bir adamın kaba çizmeleriyle çamura ezilmişti. Ama o evde uzun zamandır kimse yaşamıyor, ben de sahipsiz olduğuna karar verdim...";
			link.l1 = "Hmm...";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "FencingH", 100);
			DeleteAttribute(pchar, "questTemp.TBP_BuyKulon2");
		break;

		case "TBP_Kulon_leadership":
			dialog.text = "Fenerli evin yanında yatıyordu, "+GetAddress_Form(NPChar)+". Bir kaba adamın çizmesiyle çamura ezilmiş. Ama o evde uzun zamandır kimse yaşamıyor, ben de terk edilmiş olduğuna karar verdim...";
			link.l1 = "Hmm...";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			DeleteAttribute(pchar, "questTemp.TBP_BuyKulon2");
		break;
		// <-- Тайна Бетси Прайс
	}
}
