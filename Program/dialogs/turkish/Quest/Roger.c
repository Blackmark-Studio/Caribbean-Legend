// диалоги персонажей по пиратской линейке // Addon 2016-1 Jason пиратская линейка
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp, attrL;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	if(HasSubStr(attrL, "ShipStockManBack_"))
 	{
        i = findsubstr(attrL, "_" , 0);
	 	NPChar.ShipToStoreIdx = strcut(attrL, i+1, strlen(attrL)-1); // индех в конце
 	    Dialog.CurrentNode = "ShipStockManBack";
 	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "Ne istiyorsun?";
			link.l1 = "Gitmeliyim...";
			link.l1.go = "exit";
		break;
		
		// Лопе Монторо
		case "Mtr_officer":
			if (pchar.questTemp.Mtraxx != "fail" && pchar.questTemp.Mtraxx == "jewelry_5")
			{
				pchar.quest.Mtraxx_JewelryHavanaOver.over = "yes"; //снять таймер
				dialog.text = "Allah aşkına, sen de kimsin be?";
				link.l1 = "İyi günler, don Lope. Henüz tanışmamış olsak da, şimdi tanışmak için en uygun zaman. Özellikle de sizi bu zor durumdan kurtarmaya bu kadar hevesliyken...";
				link.l1.go = "Mtr_officer_1";
			}
			else
			{
				dialog.text = "Ne istiyorsun?";
				link.l1 = "Gitmeliyim...";
				link.l1.go = "exit";
			}
		break;
		
		case "Mtr_officer_1":
            dialog.text = "Yardım mı? Ben mi? Ne ilginç bir durum! Söyler misiniz, señor, bu cömertlik nereden geliyor?";
			link.l1 = "Elbette. Eski kaptanınız Esberdo Cabanas'ı arıyorum ve fazla vaktim yok... İdealim, onun gizli tuttuğu o yerde kendisiyle buluşmak. Hatta oraya ondan önce varırsam daha da iyi olur.";
			link.l1.go = "Mtr_officer_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtr_officer_2":
            dialog.text = "Ha-ha! Bu zavallı aptala çenesini kapalı tutmasını söylemiştim! Mavi kehribar, değil mi?";
			link.l1 = "Doğru yolda düşünüyorsunuz, iyi beyefendi.";
			link.l1.go = "Mtr_officer_3";
		break;
		
		case "Mtr_officer_3":
            dialog.text = "O halde acele edelim. Beni buradan çıkarmanın bir yolunu bulursan, sana her ayrıntıyı anlatmak isterim. Bu deliğe nasıl düştüğümü biliyor musun?";
			link.l1 = "Genel olarak, evet, yapıyorum.";
			link.l1.go = "Mtr_officer_4";
		break;
		
		case "Mtr_officer_4":
            dialog.text = "Olanlar olduğunda sırılsıklam sarhoştum. Kahrolası barmenin yüzünden! Hiçbir şey hatırlamıyorum. Her şeyi bana ancak 'Cantavro'nun ambarında uyandığımda anlattılar. Eğer hemen denize açılıp gitseydik, her şey geride kalacaktı, hem komutan hem de alcalde göz yumacaktı. Ama o lanet Don Esberdo beni doğrudan hapse attı. Sence bunu 'doğru olanı yapmak' için mi yaptı? Keşke öyle olsaydı, o alçak sadece kehribar payımı kendine ayırmak istedi. Sahilde bulduğumuzdan daha fazlası suyun altında olabilir diye fikri ortaya atan bendim. Onu nasıl çıkaracağımızı bulan da bendim. Güzel bir pay alacaktım ama... ah, o herifin evladı! Neyse, yeter bu kadar. Ne alcalde, ne komutan, ne de Don de Toledo burada çürümeme razı. O köylüyle inek karısı güvercinliğe fitne sokmasaydı... her halükârda, bana yardım etmene kimse karşı çıkmaz. Valinin yanına git, Avrupa'dan eski dostummuşsun gibi davran – ben de bunu doğrulayacağım. Bu arada, adın neydi?";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "Mtr_officer_5";
		break;
		
		case "Mtr_officer_5":
            dialog.text = ""+GetFullName(pchar)+", wonderful. Go see don Diego de Toledo and ask him for advice. Remember, you only have three days; chasing the 'Cantavro' would be pointless after that. Set me free and I will give you everything you need to deal with that bastard, Cabanas.";
			link.l1 = "Valiye hemen gideceğim, don Lope. Bu durumu ikimiz için de çözmek adına elimden geleni yapacağım.";
			link.l1.go = "Mtr_officer_6";
		break;
		
		case "Mtr_officer_6":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_6";
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Roger_1", "8");
			SetFunctionTimerCondition("Mtraxx_TimeclearPrison", 0, 0, 4, false); // таймер
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			AddLandQuestMark(characterFromId("Havana_Mayor"), "questmarkmain");
		break;
		
		case "Mtr_officer_7":
			pchar.quest.Mtraxx_TimeclearPrison.over = "yes"; //снять таймер
            dialog.text = "Demek o sahtekâr ve onun geveze tavuğu intikamlarını aldılar, ben de nihayet bu bataklıktan kurtuldum. Size minnettarım, señor, üzerinize düşeni yaptınız. Şimdi de bana kendi işimi yapmama izin verin.";
			link.l1 = "Tamamen dinliyorum!";
			link.l1.go = "Mtr_officer_8";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtr_officer_8":
            dialog.text = "Good. During our previous patrol, we were caught in a storm that forced us off course. We landed on the beach of the Western Main, not far from the Mosquito Coast, to replenish our fresh water. There, we discovered a rich deposit of blue amber. I did some prospecting and found a pile of it underwater. We needed better equipment to collect it, which is why we decided to return later.\nEsberdo had bought five longboats in Havana for the Indians to dive and gather the amber. You know the rest of the story – the scoundrel got rid of me and sailed away. Find him at the Mosquito Coast, north of Blueweld, and make haste – by my reckoning, you have about seven days to get there. I hope you catch the bastard in the middle of his gathering, take all his amber, and stab his belly repeatedly. Be careful, though; my former captain is a skilled fighter and seaman. Godspeed, señor.";
			link.l1 = "Sana da, Lope. Hoşça kal!";
			link.l1.go = "Mtr_officer_9";
		break;
		
		case "Mtr_officer_9":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_10";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Roger_1", "12");
			SetFunctionTimerCondition("Mtraxx_TimeclearGulf", 0, 0, 7, false); // таймер
			pchar.quest.mtr_jewelry_gulf.win_condition.l1 = "location";
			pchar.quest.mtr_jewelry_gulf.win_condition.l1.location = "Santacatalina";
			pchar.quest.mtr_jewelry_gulf.function = "Mtraxx_JewelryGulf";
			DeleteAttribute(pchar, "GenQuest.PrisonQuestLock");
			DelMapQuestMarkCity("Havana");
			AddMapQuestMarkShore("Shore53", true);
		break;
		
		// Росарио Гусман
		case "Mtr_rosario":
            dialog.text = "Bir şey sormak ister misiniz, efendim?";
			link.l1 = "Don Montoro hakkında. Eski dostuz, ve onun başına gelen talihsizlikleri duyduğumda gerçekten üzüldüm. Don Diego de Toledo beni size gönderdi, ortak dostumuzu kurtarmak için zaten bir girişimde bulunduğunuzu söyledi...";
			link.l1.go = "Mtr_rosario_1";
		break;
		
		case "Mtr_rosario_1":
            dialog.text = "Hm... señor, bu biraz... beklenmedik oldu ama Lope'nin bir dostuyla tanıştığıma sevindim! Uzun zamandır şansı yaver gitmiyordu, şimdi de bu...";
			link.l1 = "Ona nasıl yardım edebiliriz? Asil bir hidalgo toplumun pisliği arasında çürümemeli!";
			link.l1.go = "Mtr_rosario_2";
		break;
		
		case "Mtr_rosario_2":
            dialog.text = "Bir iş adamı! Zavallı Lope'ye yardım etmek hem kolay hem de zor. Lope'nin tartışmak talihsizliğine uğradığı fırsatçıyla konuştum. Bize beş yüz dublon karşılığında uzlaşmayı kabul etti. Kendisi ve karısının 'acıları' için hatırı sayılır bir meblağ. Ne yazık ki, gereken paranın ancak yarısını - iki yüz elli dublon - toplayabildim.";
			link.l1 = "Yani, sana iki yüz elli doblon daha getirirsem, Don Lope serbest bırakılacak mı?";
			link.l1.go = "Mtr_rosario_3";
		break;
		
		case "Mtr_rosario_3":
            dialog.text = "Evet. Açgözlü herif bana, Lope'un verdiği tazminatı herkese duyuracağına söz verdi. Ayrıca valiye de af dileyecek.";
			if (PCharDublonsTotal() >= 250) // belamour legendary edition
			{
				link.l1 = "İstediğin para yanımda. Al bakalım, bu açgözlü burjuva boğazında kalsın.";
				link.l1.go = "Mtr_rosario_4";
			}
			link.l2 = "Parayı en kısa sürede bulmak için elimden geleni yapacağım.";
			link.l2.go = "Mtr_rosario_5";
		break;
		
		case "Mtr_rosario_4":
			RemoveDublonsFromPCharTotal(250); // belamour legendary edition
			PlaySound("interface\important_item.wav");
            dialog.text = "Kendi kulaklarıma inanamıyorum! Señor, kesinlikle Tanrı tarafından gönderildiniz!";
			link.l1 = "Adamımızı ne zaman serbest bırakacaklar?";
			link.l1.go = "Mtr_rosario_8";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtr_rosario_5":
            dialog.text = "Bunu duyduğuma sevindim, señor. Sen gerçek bir Lope dostu ve gerçek bir asilzadesin.";
			link.l1 = "Hoşça kal!";
			link.l1.go = "Mtr_rosario_6";
		break;
		
		case "Mtr_rosario_6":
            DialogExit();
			AddQuestRecord("Roger_1", "10");
			npchar.dialog.currentnode = "Mtr_rosario_7";
		break;
		
		case "Mtr_rosario_7":
            dialog.text = "Parayı getirdin mi?";
			if (PCharDublonsTotal() >= 250) // belamour legendary edition
			{
				link.l1 = "İstediğin miktar şu anda yanımda. Al bakalım, bu açgözlü burjuva boğazında kalsın.";
				link.l1.go = "Mtr_rosario_4";
			}
			link.l2 = "Hâlâ bunun peşindeyim.";
			link.l2.go = "Mtr_rosario_7_1";
		break;
		
		case "Mtr_rosario_7_1":
            DialogExit();
			npchar.dialog.currentnode = "Mtr_rosario_7";
		break;
		
		case "Mtr_rosario_8":
            dialog.text = "Parayı bu gece o sinsi herife götüreceğim. Arkadaşımızın serbest bırakılması için yarına kadar bir emir çıkacağına inanıyorum. Ve umarım sonra hep birlikte kutlamak için buluşuruz?";
			link.l1 = "Tabii ki, don Rosario. Artık gitmeliyim. Görüşürüz!";
			link.l1.go = "Mtr_rosario_9";
		break;
		
		case "Mtr_rosario_9":
            DialogExit();
			AddQuestRecord("Roger_1", "11");
			npchar.lifeday = 1;
			SaveCurrentNpcQuestDateParam(NPChar, "LifeTimeCreate");
			npchar.dialog.currentnode = "Mtr_rosario_10";
			pchar.quest.mtr_prisoner.win_condition.l1 = "Timer";
			pchar.quest.mtr_prisoner.win_condition.l1.date.hour  = 12;
			pchar.quest.mtr_prisoner.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtr_prisoner.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtr_prisoner.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtr_prisoner.function = "Mtraxx_PrisonerFree";
		break;
		
		case "Mtr_rosario_10":
            dialog.text = "Yakında arkadaşımız özgür olacak!";
			link.l1 = "...";
			link.l1.go = "exit";
			npchar.dialog.currentnode = "Mtr_rosario_10";
		break;
		
		// Лысый Джеффри
		case "Jeffry":
			pchar.quest.Mtraxx_SilkCPVOver.over = "yes"; //снять прерывание
            dialog.text = "Hey, ne halt ediyorsun gemimde? Seni davet ettiğimi hatırlamıyorum, ha?";
			link.l1 = "Sakin ol, Geffrey. Ben Tyrex'tenim, gemi ipeği işi için geldim.";
			link.l1.go = "Jeffry_1";
		break;
		
		case "Jeffry_1":
            dialog.text = "A-ah, well, let's talk then. What's he planning? I've already spoken to the smugglers; if you ask me, they offer a fair price for the goods...";
			link.l1 = "Ve ne kadar, müsaadenizle sorabilir miyim?";
			link.l1.go = "Jeffry_2";
		break;
		
		case "Jeffry_2":
            dialog.text = "Bir rulo için 1.300 peso. Bence bu iyi bir fiyat.";
			link.l1 = "Evet, Tyrex bir rulo için 4 altın istiyor. Bir kuruş bile eksik olmaz. Hem de doblon olarak. Bana o fiyata uygun alıcı bulmam için iş verdi.";
			link.l1.go = "Jeffry_3";
		break;
		
		case "Jeffry_3":
            dialog.text = "Ha-ha-ha, delikanlı, ne şanslısın! Marcus'un iştahı yerinde! Hadi bakalım, öyle bir alıcı bul da görelim, seni izlemek harika olurdu.";
			link.l1 = "Evet, bu gerçekten çok komik ve eğlenceli, değil mi? Mutlu mu görünüyorum? Hayır, görünmüyorum. O yüzden gülmeyi bırakıp bana yardım etmeni öneririm.";
			link.l1.go = "Jeffry_4";
		break;
		
		case "Jeffry_4":
            dialog.text = "Peki, peki dostum... Tanrım, şaka kaldıracak biri değilsin galiba? Ama anlıyorum, Tyrex'in hayallerinden sen sorumlu değilsin, bu işten hepimiz nasibimizi alacağız, bana güven. Peki sana nasıl yardımcı olabilirim? Bunu dükkânlarda satamazsın, gümrük de olmaz, geriye sadece kaçakçılar kalıyor. Başka kimin ihtiyacı olabilir? Bir fikrin var mı?";
			link.l1 = "Hispaniola'dan beri bunu düşünüyorum... Neyse. Düzenli bir alıcı bulmak için sadece iki ayım var. Bu konuda bir şeyler yapılmalı. Emrin, en yakın koyda karaya çıkıp tamir işlerini başlatmak.";
			link.l1.go = "Jeffry_5";
		break;
		
		case "Jeffry_5":
            dialog.text = "İki ay mı?! Ne oluyor be? Boşver gitsin. 'Yılan'ın gerçekten tamire ve temizliğe ihtiyacı var, yoksa bir barın peşine bile düşemez. Hey, Fransız yosmaları! Kel Geffrey'in tayfası iki ay boyunca Capsterville'de kalıyor! Ha-ha-ha!... Neyse, sana bol şans dostum, o anlamsız arayışlarında. Eğer Marcus'un bu lanet ipek için istediği parayı ödemeye hazır bir enayi bulursan - nerede olduğumu biliyorsun.";
			link.l1 = "Bekle! Bu ipekten bir top ver bana. Malları potansiyel alıcılara göstermem gerek.";
			link.l1.go = "Jeffry_6";
		break;
		
		case "Jeffry_6":
            dialog.text = "Tabii, sorun değil. Onu sandalına alabilirsin... Hey çocuklar! Bir balya ipeği kaptanın teknesine atın!";
			link.l1 = "Güzel. Pekâlâ, alıcıyı bulduğumda görüşürüz!";
			link.l1.go = "Jeffry_7";
		break;
		
		case "Jeffry_7":
            DialogExit();
			AddQuestRecord("Roger_2", "3");
			npchar.DeckDialogNode = "Jeffry_8";
			npchar.dialog.currentnode = "Jeffry_8";
			pchar.questTemp.Mtraxx = "silk_2";
			AddCharacterGoods(pchar, GOOD_SHIPSILK, 1);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Mtraxx_SilkTimeOver", 0, 0, 61, false); // таймер
		break;
		
		case "Jeffry_8":
            dialog.text = "Başka bir şey var mı, dostum?";
			link.l1 = "Şu anda bir şey yok...";
			link.l1.go = "Jeffry_8_1";
		break;
		
		case "Jeffry_8_1":
            DialogExit();
			npchar.DeckDialogNode = "Jeffry_8";
			npchar.dialog.currentnode = "Jeffry_8";
		break;
		
		case "Jeffry_9":
			pchar.quest.Mtraxx_SilkTimeOver.over = "yes";
            dialog.text = "Nasıl gidiyor, dostum?";
			link.l1 = "İyi gidiyor. Bize bir alıcı buldum. Rulo başına 5 doblon. Tyrex'in hoşuna gideceğine inanıyorum.";
			link.l1.go = "Jeffry_10";
		break;
		
		case "Jeffry_10":
            dialog.text = "Yok artık! Sen tam bir şeytanın evladısın, ne kadar da beceriklisin! Bunu nasıl başardın, ha?";
			link.l1 = "Uzun bir hikaye, Geffrey. Şimdi dinle. Jamaika'daki Cape Negril'e 10'u ile 15'i arasında varmalısın. Orada seni gece bekliyor olacaklar. Parola: 'Lyonlu bir tüccar'. Anladın mı? Tekrar et.";
			link.l1.go = "Jeffry_11";
		break;
		
		case "Jeffry_11":
            dialog.text = "A merchant from Lyons. Got it. I should tell my purser to write it down; he's the only man here who can write. Ha-ha!";
			link.l1 = "Ambarında yüz rulo var mı?";
			link.l1.go = "Jeffry_12";
		break;
		
		case "Jeffry_12":
            dialog.text = "Daha fazlası da var.";
			link.l1 = "Harika. O halde yelken açma zamanı geldi. Beni hayal kırıklığına uğratma!";
			link.l1.go = "Jeffry_13";
		break;
		
		case "Jeffry_13":
            dialog.text = "Sakin ol dostum, her şey olması gerektiği gibi olacak.";
			link.l1 = "Yolun açık olsun, Geoffrey. Belki tekrar karşılaşırız.";
			link.l1.go = "Jeffry_14";
		break;
		
		case "Jeffry_14":
            DialogExit();
            AddQuestRecord("Roger_2", "22");
			pchar.questTemp.Mtraxx = "silk_14"; // к Тираксу
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "mtraxx_12";
			pchar.quest.mtraxx_hide_jeffry.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_hide_jeffry.function = "Mtraxx_SilkHideJeffry";
		break;
		
		case "Jeffry_15":
            dialog.text = "Ho-ho-ho! Kurnaz Charlie Prince, bizzat kendisi! Seni tekrar görmek güzel, dostum!";
			link.l1 = "Kel Geffrey! Charlie Prince, mı dedin? Ha!";
			link.l1.go = "Jeffry_15x";
		break;
		
		case "Jeffry_15x":
            dialog.text = "Soyadını daha önce hiç duymadım mı? Artık La Vega'da sana böyle diyorlar.";
			link.l1 = "Charlie'nin nereden geldiğini anlıyorum, ama neden Prens?";
			link.l1.go = "Jeffry_15y";
		break;
		
		case "Jeffry_15y":
            dialog.text = "Pekala, La Vega'daki tek soylu piç sensin! Ha-ha-ha! Nasılsın? Pasquale'nin dükkanına uğradın mı? O yaşlı heriften malzeme aldın mı?";
			link.l1 = "Bir daha asla!";
			link.l1.go = "Jeffry_16";
		break;
		
		case "Jeffry_16":
            dialog.text = "K-ha! Neden, onu sevmedin mi? Sana tuzlu eti rom fiyatına mı sattı?";
			link.l1 = "Daha da kötüsü! Ondan abanoz yüklü bir Hollanda kervanı hakkında bilgi aldım. O kervanı bulmak, tüccarı ele geçirmek ve sonra o lanet abanozu bir düzine fareden korumak hiç kolay olmadı! Ve tahmin et ne oldu, o alçak bana bir parça için 150 peso ödedi. Bir parça lanet abanoz için, Geffrey!";
			link.l1.go = "Jeffry_17";
		break;
		
		case "Jeffry_17":
            dialog.text = "Bu her zaman olur dostum, sana temin ederim. Lavoisier senin gibi bir düzine iyi adamı çoktan kandırdı. Sana gerçekten bir şeyler ödemiş, bu onun için nadir bir durum. Biz onun 'ipuçlarını' açlıktan ölsek bile kabul etmeyiz.";
			link.l1 = "Teşekkür ederim dostum, en azından artık ilk ve tek enayi olmadığımı biliyorum! Ama bu sefer o alçak kendi başını yaktı. Beni gördüğü güne lanet edeceğinden emin olacağım.";
			link.l1.go = "Jeffry_18";
		break;
		
		case "Jeffry_18":
            dialog.text = "Hey-hey-hey! Dur biraz, Prens, biraz sakin ol. Burada bu tüccara dokunulmaz. Onu soymaya kalkarsan Marcus peşine düşer. Söylesene, seni Lavoisier’ye Tyrex mi gönderdi?";
			link.l1 = "Hm. Evet... Neden?";
			link.l1.go = "Jeffry_19";
		break;
		
		case "Jeffry_19":
            dialog.text = "Dinle... (sesini alçaltarak) Diyorlar ki, Dörtgöz Marcus'la ortak çalışıyor. Şimdi anlıyor musun beni? Bu yüzden hiçbir korsan asla Lavoisier'nin gemilerine saldırmaya cesaret edemez, yoksa işleri biter.";
			link.l1 = "Anladım. Uyarın için sağ ol, Geffrey. Hoşça kal ve yolun açık olsun!";
			link.l1.go = "Jeffry_20";
		break;
		
		case "Jeffry_20":
            dialog.text = "Sana da, dostum.";
			link.l1 = "...";
			link.l1.go = "Jeffry_21";
		break;
		
		case "Jeffry_21":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 15.0);
			AddQuestRecord("Roger_4", "10");
			CloseQuestHeader("Roger_4");
			QuestSetCurrentNode("Terrax", "mtraxx_34"); // релиз-правка
			bDisableFastReload = false;
			pchar.questTemp.Mtraxx.CharleePrince = "true"; // атрибут - ГГ известный пират
			pchar.questTemp.CharleePrince = true; // атрибут для найма команды 
		break;
		
		case "Jeffry_22":
            dialog.text = "Ho-ho-ho, Prens! Havai fişekleri kimin yaptığını merak ediyordum! İspanyollar çıkarsa diye bir grup tüfekçi getirdim.";
			link.l1 = "Geffrey? Sen de mi buradasın? Ama nasıl? Hazine haritasını sen de mi aldın?";
			link.l1.go = "Jeffry_23";
			QuestPointerDelLoc("Judgement_dungeon_05", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_04", "reload", "reload1");
		break;
		
		case "Jeffry_23":
            dialog.text = "Dostum, paramı böyle saçma şeylere harcamam. Bana, bu zindanlara güvenli bir geçişten bahseden bir gezginin günlüğünü getirdiler.";
			link.l1 = "Bunu sana kim getirdi?";
			link.l1.go = "Jeffry_24";
		break;
		
		case "Jeffry_24":
            dialog.text = "Bir ayyaş işte. Tek istediği bir içki için yüz peso bulmaktı.";
			link.l1 = "Tortuga'da mı oldu?";
			link.l1.go = "Jeffry_25";
		break;
		
		case "Jeffry_25":
            dialog.text = "Hayır. Barbados muydu? Prens, neden bu kadar endişelisin? Ne kadar çok kişi olursak, hazineleri o kadar hızlı taşıyabiliriz!";
			link.l1 = "Hoşuma gitmedi bu. Böyle tesadüflere inanmam. Bu günlüğü yazan Camilla'nın babası olabilir mi?";
			link.l1.go = "Jeffry_26";
		break;
		
		case "Jeffry_26":
            dialog.text = "Camilla kim?";
			link.l1 = "Bana bu yerin haritasını iki yüz pesoya satan kadın!";
			link.l1.go = "Jeffry_27";
		break;
		
		case "Jeffry_27":
            dialog.text = "Heh... Prens, fazla düşünüyorsun. Hadi hazine avına çıkalım. Hadi!";
			link.l1 = "Gerek yok. Onları zaten buldum... Aşağıda, zindanda, demir parmaklıkların arkasındalar. Onları oradan çıkarmamız gerekecek. Dinle, Geffrey, bir şey daha var! Pala Pelly de buradaydı!";
			link.l1.go = "Jeffry_28";
		break;
		
		case "Jeffry_28":
            dialog.text = "Pala mı? O zaman bugün şanslı günümüz! Ama şimdi nerede o?";
			link.l1 = "Aşağıda... ölü. Onunla hazineye yakın bir yerde karşılaştım. Aklını kaçırdı, açgözlülükten çığlık atmaya başladı. Sonra o ve yanındakiler bana saldırdı.";
			link.l1.go = "Jeffry_29";
		break;
		
		case "Jeffry_29":
            dialog.text = "Hm... Pelly'nin parayla hiç şansı yoktu. O kadar altını görünce kesin delirmiştir.";
			link.l1 = "Belki öyledir... ama Geffrey, sen anlamıyorsun! Üçümüz de buraya geldik! Ve hepimiz aynı ipucunu aldık! Sence bu tesadüf mü? Biri açıkça hepimizi aynı yere çekmek istiyor, ve burası gerçekten bir mezar gibi.";
			link.l1.go = "Jeffry_30";
		break;
		
		case "Jeffry_30":
            dialog.text = "Altını gördün mü peki?";
			link.l1 = "Kendi gözlerimle gördüm. Birkaç devasa sandık, madeni paralar ve külçelerle doluydu.";
			link.l1.go = "Jeffry_31";
		break;
		
		case "Jeffry_31":
            dialog.text = "O halde neden endişeleniyorsun, Prens? Yolu göster, şu külçelerine bir bakalım. Sonra altını paylaşırız.";
			link.l1 = "Ah, belki de haklısın, neyse... Hadi gidelim.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionWithJeffry");
		break;
		
		case "Jeffry_32":
            //PlaySound("Voice\English\LE\Jeffry\Jeffry_gold.wav");
			dialog.text = "Ne gösteri ama! Bu ne büyük bir altın yığını! Şimdi Cutlass'ın neden delirdiğini anlıyorum. Gerçekten çok şanslıyız, Prens! Ne dersin, burada ne kadar altın bulacağız sence?";
			link.l1 = "Oldukça fazla. Şu parmaklıklarla işimiz bittiğinde kesin olarak anlayacağız.";
			link.l1.go = "Jeffry_33";
		break;
		
		case "Jeffry_33":
            dialog.text = "Evet, parmaklık çok sağlam, çıplak ellerimizle ya da kılıçlarla bunu kıramayız. Haklısın dostum – ya alet bulmamız gerek ya da bolca barut. Hey, bak! O da ne!?";
			link.l1 = "...";
			link.l1.go = "Jeffry_34";
		break;
		
		case "Jeffry_34":
            DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Mtraxx_RetributionJeffryMushketer", 0.1);
		break;
		
		case "Jeffry_35":
            PlaySound("Voice\English\LE\Jeffry\Jeffry_mozila.wav");
			dialog.text = RandSwear()+"Ne biçim saçmalık bu!";
			link.l1 = "Seni kahrolası yılan!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionJeffryFight");
		break;
		
		// Билли Сипатый
		case "Billy":
			pchar.quest.Mtraxx_BillySeaTimeOver.over = "yes"; //снять таймер
			PlaySound("VOICE\English\LE\Billy\Billy_01.wav");
            dialog.text = "Vallahi, bu yıl 'Uçan Balık'ta böyle bir şey yaşandıysa köpekbalığı beni yutsun... çocuklar, burada bir misafirimiz var! Hayatında ne ters gitti de benim eski tekneyi ziyaret etmeye karar verdin, dostum?";
			link.l1 = "Selam! Sana Husky Billy diyorlar, değil mi?";
			link.l1.go = "Billy_1";
		break;
		
		case "Billy_1":
            dialog.text = "Sesimden anlamıyor musun, kaptan? Eskiden İngiliz ve İspanyol tüccarlarını korkudan altlarına yaptırırdı. Ne günlerdi onlar!... Şimdi ise yaşlı Billy, en sevdiği adanın kıyılarında, kıymetli sandalında hayatının sonunu bekliyor...";
			link.l1 = "Sana bir iş teklifim var, Billy. Jamaika civarındaki her şeyden haberdar olduğunu söylediler bana. Doğru mu bu?";
			link.l1.go = "Billy_2";
		break;
		
		case "Billy_2":
            dialog.text = "Sana böyle söylendiyse, öyle olmalı, sence de öyle değil mi? Yengecin taşlarıyla oynama, konuş. Benimle ne işin var?";
			link.l1 = "Pekâlâ. Port Royal'da bir gemi yapımcısı var. Müşterilerine özel hizmetler sunuyor ve üretimiyle bu hizmetler için gemi ipeğine ihtiyaç duyuyor. Bu malın ticareti burada yasak olduğundan, kendine yasa dışı bir tedarikçi bulmuş. Ona gemi ipeğini kimin sağladığını ve bunu nasıl yaptığını öğrenmek istiyorum.";
			link.l1.go = "Billy_3";
		break;
		
		case "Billy_3":
            dialog.text = "Ho-ho-ho, bak hele şuna! Albay D'Oyley için mi çalışıyorsun, evlat?";
			link.l1 = "Yine başlıyoruz! Hayır, ben Marcus Tyrex ile çalışıyorum. O, gemi ipeği pazarında pay istiyor ve bu gemi yapımcısı da 'yabancılarla' iş yapmaya ödü kopuyor...";
			link.l1.go = "Billy_4";
		break;
		
		case "Billy_4":
            dialog.text = "Oh, so you're working for the Code Keeper! That's great news... if you're not lying, of course. I don't give a damn about shipbuilders; arrest one and another will take his place. But I do give a damn about my old girl. The 'Flying Fish' is in a bad way. Do you understand me?\nBring me another longboat, a new one, and a roll of ship silk—the same kind you're talking about. Billy will make a proper sail out of it, so he can outfox the patrols, ha-ha-ha! In return, Billy will tell you everything about the shipbuilder and his source of silk. Trust me, son, I know everything you want to know. I just need to make sure you're an honest pirate and not some arse-licking redcoat!";
			link.l1 = "Yeni bir sandal mı? Ne dersin, sana onu alacak kadar para vereyim? Üstüne biraz da fazladan eklerim.";
			link.l1.go = "Billy_5";
		break;
		
		case "Billy_5":
            dialog.text = "Heh, kaptan, yaşlı Billy şehirde pek hoş karşılanmaz. Port Royal'de beni hâlâ çok iyi hatırlıyorlar ve o kayada eski dostlarımın arasında asılma fikri hiç hoşuma gitmiyor. O yüzden, evlat, bana yepyeni bir sandal getirmeni bekliyorum. Üç gün boyunca Negril Burnu'nda olacağım. İpeği de unutma!";
			link.l1 = "Pekâlâ, Billy. Sandalını ve bir rulo yelken bezini alacaksın. Yakında döneceğim.";
			link.l1.go = "Billy_6";
		break;
		
		case "Billy_6":
            dialog.text = " Pekala, Billy seni kıyıda bekliyor olacak, kaptan. Yakında görüşürüz!";
			link.l1 = "...";
			link.l1.go = "Billy_7";
		break;
		
		case "Billy_7":
            DialogExit();
			AddQuestRecord("Roger_2", "8");
			npchar.dialog.currentnode = "Billy_8";
			pchar.questTemp.Mtraxx = "silk_7";
			SetFunctionTimerCondition("Mtraxx_BillyTimeOver", 0, 0, 3, false); // таймер
			pchar.quest.mtr_billy_coast.win_condition.l1 = "ExitFromLocation";
			pchar.quest.mtr_billy_coast.win_condition.l1.location = pchar.location;
			pchar.quest.mtr_billy_coast.function = "Mtraxx_BillyOnCoast";
			locations[FindLocation("shore35")].DisableEncounters = true; //энкаутеры закрыть
			npchar.DontDeskTalk = true;
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
		break;
		
		case "Billy_8":
			PlaySound("VOICE\English\LE\Billy\Billy_02.wav");
            dialog.text = "Ne? Bana şimdiden bir sandal mı getirdin?";
			link.l1 = "Sen tam bir şakacısın, ha, Billy?";
			link.l1.go = "exit";
		break;
		
		case "Billy_9":
            dialog.text = "Peki kaptan, yepyeni sandalım ne olacak?";
			if(Companion_CheckShipType(SHIP_TARTANE) && GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0)
			{
				link.l1 = "İş tamam, Husky. O, kargo ambarında bir rulo gemi ipeğiyle birlikte teslim edildi. Artık eski tekneni batırmakta özgürsün.";
				link.l1.go = "Billy_11";
			}
			else
			{
				PlaySound("VOICE\English\LE\Billy\Billy_02.wav");
				link.l1 = "Hâlâ bunun üzerindeyim. Bekle.";
				link.l1.go = "Billy_10";
			}
		break;
		
		case "Billy_10":
			DialogExit();
			npchar.dialog.currentnode = "Billy_9";
		break;
		
		case "Billy_11":
			PlaySound("VOICE\English\LE\Billy\Billy_03.wav");
			pchar.quest.Mtraxx_BillyTimeOver.over = "yes"; //снять прерывание
            dialog.text = "Lanet olsun! Beş yıldır Billy'nin aldığı en iyi haber bu! Heh, bu şişeyi açmak için harika bir sebep...";
			link.l1 = "Ben almayayım.   Peki, ipek tedarikçisi hakkında ne diyorsun?";
			link.l1.go = "Billy_12";
		break;
		
		case "Billy_12":
            dialog.text = "Yazık oldu, yepyeni 'Uçan Balık'ıma içebilirdik! Neyse... Dinle bak evlat\nHer ayın ortasında, 10'u ile 15'i arasında, İngiliz bayrağı taşıyan bir brigantin Portland Cove'a yanaşıyor. Eğer gerçekten İngilizse, ölmeden bir damla rom içmeyeyim! Geminin adı 'Utrecht' ve güneybatıdan, Curaçao'nun olduğu yerden geliyor. Belli ki Hollandalı bir kaptan, hemen anlaşılıyor\nHer zaman aynı grup onları kıyıda karşılıyor, başlarında o kurnaz gemi yapımcısının ustabaşı var. Hollandalıların orada indirdiği gemi ipeğini teslim alan da o. Eminim gemi ipeğidir, çünkü sadece Hollandalılar onu öyle paketler.";
			link.l1 = "Her ay, öyle mi dedin?";
			link.l1.go = "Billy_13";
		break;
		
		case "Billy_13":
            dialog.text = "Gerçekten de, evlat, geçen yıl tek bir ayı bile kaçırmadılar. O suratsız, sakallı tayfayla konuşmak istiyorsan, her ayın 10'u ile 15'i arasında, gece vakti Portland Cove'da beklemeni öneririm. Uzun teknemdeki yepyeni ipek yelkenin hatrına yemin ederim!";
			link.l1 = "Heh! Parama değdi gibi görünüyor. Yolun açık olsun Billy, devriyelerden kendini koru, yoksa beni gerçekten çok kızdırırsın.";
			link.l1.go = "Billy_14";
		break;
		
		case "Billy_14":
            dialog.text = "Ha, yaşlı Billy Jamaika kıyılarında gerçek bir eğlence koparmak üzere! Yolun açık olsun, kaptan! İyi avlar!";
			link.l1 = "Sana da aynısı, Billy!";
			link.l1.go = "Billy_15";
		break;
		
		case "Billy_15":
            DialogExit();
			npchar.lifeday = 0;
			pchar.questTemp.Mtraxx = "silk_8";
			chrDisableReloadToLocation = true;//закрыть локацию
			locations[FindLocation("shore35")].DisableEncounters = false; //энкаутеры открыть
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 20.0);
			AddDialogExitQuestFunction("Mtraxx_BillyTakeShip");
			AddQuestRecord("Roger_2", "9");
			//
			if (GetDataDay() >= 1 && GetDataDay() <= 9)
			{
				DoQuestFunctionDelay("Mtraxx_SilkCreateSmuggler", 1.0);
			}
			
			if (GetDataDay() >= 10 && GetDataDay() <= 15)
			{
				int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+2;
				if (iRank > 45) iRank = 45;
				Group_FindOrCreateGroup("Mtr_Utreht");
				sld = GetCharacter(NPC_GenerateCharacter("Cap_Utreht", "mercen_19", "man", "man", iRank, ENGLAND, -1, true, "quest"));
				FantomMakeCoolSailor(sld, SHIP_BRIGANTINE, "Utrecht", CANNON_TYPE_CULVERINE_LBS18, 50, 50, 50);
				FantomMakeCoolFighter(sld, iRank, 50, 50, "blade_13", "pistol5", "bullet", 100);
				sld.name = "Joachim";
				sld.lastname = "Gusen";
				sld.DontRansackCaptain = true;
				sld.AnalizeShips = true;
				sld.Coastal_Captain = true; // правки прогона 3
				DeleteAttribute(sld, "SaveItemsForDead");
				sld.Ship.Mode = "pirate";
				SetSailsColor(sld, 2);
				sld.ship.Crew.Morale = 40+MOD_SKILL_ENEMY_RATE*4;
				sld.Ship.Crew.Exp.Sailors = 60+MOD_SKILL_ENEMY_RATE*4;
				sld.Ship.Crew.Exp.Cannoners = 40+MOD_SKILL_ENEMY_RATE*4;
				sld.Ship.Crew.Exp.Soldiers = 40+MOD_SKILL_ENEMY_RATE*4;
				if (MOD_SKILL_ENEMY_RATE > 4) SetCharacterPerk(sld, "MusketsShoot");
				SetCharacterGoods(sld, GOOD_SHIPSILK, 80);

				Group_AddCharacter("Mtr_Utreht", "Cap_Utreht");
				Group_SetGroupCommander("Mtr_Utreht", "Cap_Utreht");
				Group_SetTaskAttackInMap("Mtr_Utreht", PLAYER_GROUP);
				Group_SetAddress("Mtr_Utreht", "Jamaica", "Quest_Ships", "Quest_Ship_4");
				Group_SetTaskRunaway("Mtr_Utreht", PLAYER_GROUP);
				Group_LockTask("Mtr_Utreht");
				
				pchar.quest.mtr_silksmuggler_AfterBattle.win_condition.l1 = "Group_Death";
				pchar.quest.mtr_silksmuggler_AfterBattle.win_condition.l1.group = "Mtr_Utreht";
				pchar.quest.mtr_silksmuggler_AfterBattle.function = "Mtraxx_SilkSmugglerAfterBattle";
				
				SetTimerFunction("Mtraxx_SilkSmugglerFail", 0, 0, 2);
			}
			
			if (GetDataDay() >= 16 && GetDataDay() <= 20)
			{
				SetTimerFunction("Mtraxx_SilkCreateSmuggler", 0, 0, 15);
			}
			if (GetDataDay() >= 21 && GetDataDay() <= 26)
			{
				SetTimerFunction("Mtraxx_SilkCreateSmuggler", 0, 0, 10);
			}
			if (GetDataDay() >= 27 && GetDataDay() <= 31)
			{
				SetTimerFunction("Mtraxx_SilkCreateSmuggler", 0, 0, 5);
			}
		break;
		
		// мастеровой с верфи Порт-Ройаля
		case "Mtr_acceptor_fight":
            LAi_group_Delete("EnemyFight");
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation("shore36")], false);
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Mtr_acceptor_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Mtraxx_SilkWrongTalk");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Mtr_acceptor":
            dialog.text = "Hey, denizci, Jamaika'ya yeni mi geldin, ha?";
			link.l1 = "Hm. Doğru. Sorun ne?";
			link.l1.go = "Mtr_acceptor_1";
		break;
		
		case "Mtr_acceptor_1":
            dialog.text = "Burada, denizde ilginç bir şey gördün mü?";
			link.l1 = "Evet, gördüm. Bir brigantin, İngiliz devriye korvetiyle çatışmaya girdi. İngilizler onlara ağır darbe vurdu, Hollandalılar ise kaçmaya çalışırken yüklerini denize attı.";
			link.l1.go = "Mtr_acceptor_2";
		break;
		
		case "Mtr_acceptor_2":
            dialog.text = "Neden bu kadar emin konuşuyorsun, onun Hollandalı olduğuna? Akıllı bir Hollandalı Port Royal’a bu kadar yaklaşmayı asla düşünmez...";
			link.l1 = "İngiliz bayrağı çekmişti, ama ismi... 'Utrecht'. Pek İngilizce sayılmaz, değil mi? Hollandalılardı diyorum sana, belki de kaçakçıydılar. Devriye kesinlikle onları bekliyordu.";
			link.l1.go = "Mtr_acceptor_3";
		break;
		
		case "Mtr_acceptor_3":
            dialog.text = "Siktir!";
			link.l1 = "Pek de memnun görünmüyorsun bundan...";
			link.l1.go = "Mtr_acceptor_4_1";
			link.l2 = "Bu brigantini burada mı bekliyordun?";
			link.l2.go = "Mtr_acceptor_7";
		break;
		
		case "Mtr_acceptor_4_1":
            dialog.text = "Neden olayım ki?";
			link.l1 = "Hadi ama. Kim olduğunu biliyorum. Sen Port Royal tersanesinin ustabaşısısın ve bir brigantinle getirilecek çok özel bir yükü bekliyorsun.";
			link.l1.go = "Mtr_acceptor_wrong";
			link.l2 = "Bunu yüzünden okumak mümkün, işte orada!";
			link.l2.go = "Mtr_acceptor_4_2";
		break;
		
		case "Mtr_acceptor_wrong":
            dialog.text = "Argh! Çocuklar, bu bir kılık değiştirmiş devriye! İşlerini bitirin ve hemen buradan defolun!";
			link.l1 = "Lanet olsun! Bekle, sen ya...";
			link.l1.go = "Mtr_acceptor_fight";
		break;
		
		case "Mtr_acceptor_4_2":
            dialog.text = "Kaba mı oluyorsun, 'deniz kurdu'? Dikkat et diline, yoksa...";
			link.l1 = "Hadi ama. Belli ki canın sıkkın. Gerçekten bu Hollandalıların gelmesini mi bekliyordun?";
			link.l1.go = "Mtr_acceptor_4_3";
			link.l2 = "Yoksa ne? Bana hayat dersi mi vereceksin?";
			link.l2.go = "Mtr_acceptor_6";
		break;
		
		case "Mtr_acceptor_4_3":
            dialog.text = "Öyle olsaydım ne olurdu? Neden umurunda?";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l1 = "Gerçekten de bilmiyorum. Burada bekleyen sensin, ben değilim. Önünde bir sonsuzluk var.";
				link.l1.go = "Mtr_acceptor_4_4";
			}
			link.l2 = "Ah, umursamak için fazlasıyla sebebim var. Brigantin'in ambarında ne olduğunu biliyorum. Gemi ipeği. Burada olma sebebin de bu, değil mi?";
			link.l2.go = "Mtr_acceptor_wrong";
		break;
		
		case "Mtr_acceptor_4_4":
            dialog.text = "Hm... Sonsuzluk?";
			link.l1 = "Denizin dibinden geri dönmek bir ömür sürer. Senin brigantinin bir devriye korveti tarafından batırıldı, dostum. Hem de öylece. Yine de, savaş hem ganimet hem de kayıp getirir. O batan Hollandalıdan iyi para kazanacağım.";
			link.l1.go = "Mtr_acceptor_4_5";
		break;
		
		case "Mtr_acceptor_4_5":
            dialog.text = "Ve tam olarak nasıl, merak ediyorum?";
			link.l1 = "Kaçmaya çalışırken denize attıkları şeyleri satacağım. Neredeyse her şey kayboldu, ama değerli gemi ipeği mantar gibi yüzüyordu. Çoğunu kurtardım, bu yüzden yarın şehre gidip bir alıcı bulacağım. Nereden kazanıp nereden kaybedeceğini asla bilemezsin.";
			link.l1.go = "Mtr_acceptor_4_6";
		break;
		
		case "Mtr_acceptor_4_6":
            dialog.text = "Bekle!";
			link.l1 = "Vay canına! Şimdi ne olacak?";
			link.l1.go = "Mtr_acceptor_4_7";
		break;
		
		case "Mtr_acceptor_4_7":
            dialog.text = "Ne kadar ipek toplamayı başardın?";
			link.l1 = "Ve sana ne? Bu ipek benim! Yoksa valinin köpeği misin? Sen de...";
			link.l1.go = "Mtr_acceptor_4_8";
		break;
		
		case "Mtr_acceptor_4_8":
            dialog.text = "Kılıcını kınında tut, denizci. Ben ne köpeğim, ne de ispiyoncu. Biz yerel tersanede çalışıyoruz... Bu ipek bize gelmeliydi ve anladığım kadarıyla şimdi sende. Hepsini senden satın alacağım, bu ipeğe ihtiyacımız var, dostum.";
			link.l1 = "Gerçekten mi? İlginç... Ne kadar?";
			link.l1.go = "Mtr_acceptor_4_9";
		break;
		
		case "Mtr_acceptor_4_9":
			i = GetSquadronGoods(pchar, GOOD_SHIPSILK);
            dialog.text = "Bir rulo için iki buçuk bin. Fiyatı iyi, daha iyisini bulamazsın.";
			link.l1 = "Şans bana güldü! Benim var "+FindRussianQtyString(i)+" Parayı göster, hemen karaya teslim edilmesini emredeceğim.";
			if (i > 80) link.l1.go = "Mtr_acceptor_4_11";
			else link.l1.go = "Mtr_acceptor_4_10";
		break;
		
		case "Mtr_acceptor_4_10":
            dialog.text = "Anlaştık!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CargoSilk");
			AddCharacterExpToSkill(pchar, "Fortune", 300);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
		break;
		
		case "Mtr_acceptor_4_11":
            dialog.text = "Hm... Joachim sadece seksen tomar teslim edecekti - bu kadarını kurtarmış olamazsın... yani ya burada kirli bir oyun çeviriyorsun ya da... ispiyoncusun! Çocuklar, onu öldürün ve hemen buradan defolun!";
			link.l1 = "Siktir!";
			link.l1.go = "Mtr_acceptor_fight";
		break;
		
		case "Mtr_acceptor_5":
            dialog.text = "";
			link.l1 = "Harika bir anlaşma, dostum! Neden bu kadar keyifsizsin? Denizin dibindeki Hollandalılar için mi endişeleniyorsun? Böyle şeyler olur, kafana takma!";
			link.l1.go = "Mtr_acceptor_5_1";
		break;
		
		case "Mtr_acceptor_5_1":
            dialog.text = "Evet, tabii... Onlar bizim düzenli tedarikçimizdi. Şimdi ipeği nereden bulacağız? Zaten hep eksik kalıyor ve tüm ticaret Albay D'Oyley'in doğrudan kontrolünde. Kahretsin, lanet olsun...";
			link.l1 = "Hm... Dinle dostum, sanırım bu konuda sana yardımcı olabilirim.";
			link.l1.go = "Mtr_acceptor_5_2";
		break;
		
		case "Mtr_acceptor_5_2":
            dialog.text = "Gerçekten mi? Peki bize nasıl yardım edeceğini düşünüyorsun? Her ay yüz rulo mu teslim edeceksin?";
			link.l1 = "Ben mi? Hmm, sanmıyorum ama Marcus Tyrex kesinlikle isterdi. Onu duydun mu?";
			link.l1.go = "Mtr_acceptor_5_3";
		break;
		
		case "Mtr_acceptor_5_3":
            dialog.text = "K-ha! Demek korsansın?";
			link.l1 = "Hayır, onlarla sadece özel durumlarda iş yaparım. Marcus'un düzenli olarak gemi ipeği partileri aldığını ve bunu parası yeten herkese sattığını kesin olarak biliyorum. Burada bir top için 2.500 peso falan demiyorum. Eğer her top için ona 5 altın dublon ödeyebiliyorsan, seni ipeğe boğar, bundan emin olabilirsin.";
			link.l1.go = "Mtr_acceptor_5_4";
		break;
		
		case "Mtr_acceptor_5_4":
            dialog.text = "Bu ilginç bir haber... Marcus Tyrex, diyorsun? Sadece doblonla mı?..";
			link.l1 = "Hadi ama dostum, ipeği kimden aldığın gerçekten bu kadar önemli mi? Para paradır, bankada her zaman peso'yu doblona çevirebilirsin. Ee, ne diyorsun, kod bekçisinin kulağına seninle ilgili bir iki laf fısıldayayım mı? Zaten La Vega'ya gidiyorum.";
			link.l1.go = "Mtr_acceptor_5_5";
		break;
		
		case "Mtr_acceptor_5_5":
            dialog.text = "Pekala. Anlaştık. Şartlarımız şunlar: Her ayın 10'u ile 15'i arasında yüz somunluk bir parti teslim edilecek. Burada bekleyeceğiz... dur, buluşma yerini değiştirelim, burası artık tehlikeli. Maroon Town yakınlarındaki Cape Negril'de bekleyeceğiz, orası daha güvenli olur. Parola - 'Lyonslu bir tüccar'.";
			link.l1 = "Anlaştık, dostum. Ne yolculuktu ama! Tyrex böyle bir alıcı için bana bir iki dublon öder! Ha-ha! Pekâlâ, artık gitmeliyim. Gelecek ay Tyrex'in gemisini bekle. Sana ve ailene bol şans!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CargoSilkWin");
		break;
		
		case "Mtr_acceptor_6":
            dialog.text = "Sana biraz edep öğrettikten sonra hayat dersi almana gerek kalmayacak.";
			link.l1 = "Sert mi davranıyorsun, marangoz? Peki, o zaman şu brigantinini beklemeye devam et, ama biraz zaman alacak.";
			link.l1.go = "Mtr_acceptor_6_1";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "Hey, öğretmen, benim de sana birkaç dersim var!";
				link.l2.go = "Mtr_acceptor_6_2";
			}
		break;
		
		case "Mtr_acceptor_6_1":
            dialog.text = "Marangoz mu? Lanet olsun, bunu nereden biliyorsun? K-ha! Kahretsin çocuklar, bu gizlenmiş bir devriye! Onu öldürün ve hemen defolup gidin!";
			link.l1 = "Kahretsin!";
			link.l1.go = "Mtr_acceptor_fight";
		break;
		
		case "Mtr_acceptor_6_2":
            dialog.text = "Bizi rahat bırak, balık pulu, seninle uğraşacak vaktimiz yok. Defol!";
			link.l1 = "Belirli bir Hollanda gemisini mi bekliyorsun? Kolay gelsin. Önünde sonsuz bir zaman var.";
			link.l1.go = "Mtr_acceptor_4_4";
		break;
		
		case "Mtr_acceptor_7":
            dialog.text = "Ne saçmalıyorsun sen?";
			link.l1 = "Anladım. Ama, olur da öyleyse, unut gitsin. O gelmeyecek, bir devriye korveti sayesinde. Dürbünle dövüşün sonunu gördüm. Çok hızlı oldu ve buradan pek uzakta değildi";
			link.l1.go = "Mtr_acceptor_7_1";
		break;
		
		case "Mtr_acceptor_7_1":
            dialog.text = "Yine de, hiçbir şeyi ya da kimseyi beklemiyoruz, ve...";
			link.l1 = "Bak, gerçekten umurumda değil. Şehir devriyesinden değilim ve ne yaptığınla ilgilenmiyorum, ben de melek sayılmam. Kaçakçılık yapıyorsan, o senin işin. Sadece seni uyarmak istedim. Sana bol şans, dostum.";
			link.l1.go = "Mtr_acceptor_7_2";
		break;
		
		case "Mtr_acceptor_7_2":
            dialog.text = "Bekle... 'Utrecht'in battığından emin misin?";
			link.l1 = "Kesinlikle. Kaçmaya çalıştı, ambarındaki her şeyi denize attı, değerli gemi ipeğini bile esirgemediler, ama böylesine radikal önlemler bile bir korvetin hız avantajına karşı işe yaramadı.";
			link.l1.go = "Mtr_acceptor_7_3";
		break;
		
		case "Mtr_acceptor_7_3":
            dialog.text = "Ne yazık...   peki ipeksiz ne yapacağız şimdi? Kahretsin!";
			link.l1 = "Gemi ipeğine ihtiyacın var mı?";
			link.l1.go = "Mtr_acceptor_7_4";
		break;
		
		case "Mtr_acceptor_7_4":
            dialog.text = "Neden soruyorsun, satıyor musun?";
			link.l1 = "Ben değilim, ama öyle biri tanıyorum. Cömert ve düzenli bir alıcı arıyor. Sence bu işe uygun musun?";
			link.l1.go = "Mtr_acceptor_7_5";
		break;
		
		case "Mtr_acceptor_7_5":
            dialog.text = "Ve o adam kim?";
			link.l1 = "La Vega'nın baronu Marcus Tyrex, namıdiğer Kod Muhafızı. Düzenli olarak gemi ipeği partileri alır, bu yüzden her zaman satacak bir miktarı olur. Sanırım fiyatın yeterince yüksek olursa, sana da satmayı düşünebilir.";
			link.l1.go = "Mtr_acceptor_7_6";
		break;
		
		case "Mtr_acceptor_7_6":
            dialog.text = "Demek korsansın?";
			link.l1 = "Neden umursuyorsun? Eğer cesaretin varsa, seninle Tyrex arasında bir anlaşma ayarlayabilirim. Yoksa - o zaman hoşça kal.";
			link.l1.go = "Mtr_acceptor_7_7";
		break;
		
		case "Mtr_acceptor_7_7":
            dialog.text = "Pekala, pekala, sinirlenme. Tabii ki biliyorum. Tyrex'le bir anlaşma yapmak istiyorum. Ama senin bundan ne çıkarın var?";
			link.l1 = "Eğer yük için iyi bir fiyat teklif edersen, Marcus'tan yardımlarım karşılığında muhtemelen güzel bir para alırım. Peki, ne diyorsun?";
			link.l1.go = "Mtr_acceptor_7_8";
		break;
		
		case "Mtr_acceptor_7_8":
            dialog.text = "Bir rulo için 5 doblon. Bundan daha iyi bir fiyat bulamazsın, bana güven.";
			link.l1 = "5 altın sikke mi? Hm. Fena değil. Böyle bir alıcı için Tyrex bana bayağı borçlanacak sanırım. Pekala, anlaştık, ona haber veririm. Ama bana fiyat konusunda yalan söylediysen, o zaman başın belada olur.";
			link.l1.go = "Mtr_acceptor_7_9";
		break;
		
		case "Mtr_acceptor_7_9":
            dialog.text = "Endişelenmeyin, biz dürüst insanlarız. Şartlarımız şöyle: her ayın 10'u ile 15'i arasında yüz somunluk bir parti. Burada bekleyeceğiz... durun, buluşma yerini değiştirelim, burası artık tehlikeli. Cape Negril'de, Maroon Town yakınında bekleyeceğiz, orası daha güvenli olmalı. Parola - 'Lyonslu bir tüccar'.";
			link.l1 = "Anlaşıldı. İlk parti gelecek ay hazır olacak.";
			link.l1.go = "Mtr_acceptor_7_10";
		break;
		
		case "Mtr_acceptor_7_10":
            dialog.text = "Tyrex'e bu sefer daha fazla yük getirebileceğini söyle, çünkü bu ay için ipeğimiz kalmadı.";
			link.l1 = "Yapacağım. Yolun açık olsun, dostum.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CargoSilkWin");
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
		break;
		
		// Тесак Пелли
		case "Pelly":
            dialog.text = "Selam! Seni gemime ne getirdi, dostum?";
			link.l1 = "Hey, Cutlass. Marcus Tyrex beni gönderdi. Maracaibo'ya bir yürüyüş bizi bekliyor.";
			link.l1.go = "Pelly_1";
		break;
		
		case "Pelly_1":
            dialog.text = "A-ah, sonunda. Demek bu yolculukta yeni patronum sizsiniz. Güzel. Yeni amiralimin adı ne?";
			link.l1 = "Kaptan "+GetFullName(pchar)+".";
			link.l1.go = "Pelly_2";
		break;
		
		case "Pelly_2":
            dialog.text = "Emirleriniz, Amiral "+GetFullName(pchar)+"?";
			link.l1 = "Biz Lake Maracaibo'ya ayrı ayrı yelken açacağız. Sen gece varıp gizlice Guajira Körfezi'ne çıkmalısın. Orada beni bekle ve bu arada küçük bir kamp kur. Ben ise İspanyol limanına çıkacağım.";
			link.l1.go = "Pelly_3";
		break;
		
		case "Pelly_3":
            dialog.text = "Emredersiniz, Amiral!";
			link.l1 = "Oraya varman ne kadar sürecek?";
			link.l1.go = "Pelly_4";
		break;
		
		case "Pelly_4":
            dialog.text = "Hmmm... Yaklaşık bir hafta sürer. Bir gün eksik, bir gün fazla, her şey rüzgâra bağlı.";
			link.l1 = "Güzel. O halde vakit kaybetmeyelim. Guajira Körfezi'nde görüşürüz, dostum.";
			link.l1.go = "Pelly_5";
		break;
		
		case "Pelly_5":
            dialog.text = "Başüstüne, Amiral!";
			link.l1 = "...";
			link.l1.go = "Pelly_6";
		break;
		
		case "Pelly_6":
            DialogExit();
			AddQuestRecord("Roger_3", "3");
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true;
			Mtraxx_PlantContinue();
		break;
		
		case "Pelly_7":
            dialog.text = "Emirleriniz nedir, Amiral?";
			link.l1 = "Şu anda bir şey yok. Operasyonumuzla meşgulüm.";
			link.l1.go = "Pelly_wait";
			if (pchar.questTemp.Mtraxx == "plant_3")
			{
				link.l1 = "Kıyıda büyük bir sandık hazırlayın. İçine tutsak kardeşlerimiz için silah toplayacağız.";
				link.l1.go = "Pelly_7_1";
			}
			if (pchar.questTemp.Mtraxx == "plant_6" && CheckAttribute(pchar, "questTemp.mtraxx_PlantInfoTovar"))
			{
				dialog.text = "Peki, Handsome'ın olayı ne? Ellerim Don'un kanını dökmek için kaşınıyor!";
				link.l1 = "Durum düşündüğümüzden daha karmaşık. Plantasyondaki muhafızların çok dikkatli olduğunu söyledi. Silahları içeri sokmanın tek yolu, malların arasına saklamak. Acilen kahve, kopra ya da vanilya sevkiyatı bulmamız gerekecek – buradaki toprak sahibi sadece bunlarla ilgileniyor, başka hiçbir şeyle değil.";
				link.l1.go = "Pelly_70";
				DelLandQuestMark(npchar);
			}
			if (pchar.questTemp.Mtraxx == "plant_8" && pchar.location.from_sea == "Shore37")
			{
				link.l1 = "Leave the camp and assemble a storm squad. It's time to march; we attack under the cover of darkness.";
				link.l1.go = "Pelly_11";
				DelLandQuestMark(npchar);
			}
		break;
		
		case "Pelly_wait":
             DialogExit();
			 npchar.dialog.currentnode = "Pelly_7";
		break;
		
		case "Pelly_7_1":
            dialog.text = "Dinle, Amiral, bir süredir düşünüyorum...";
			link.l1 = "Ne o, Terrax sana o pala sallaman yerine kafa yorman için mi para veriyor, ha, Cutlass?";
			link.l1.go = "Pelly_35";
		break;
		
		case "Pelly_8":
            dialog.text = "Hey! Plantasyonda bir isyan var, değil mi Amiral? Alevler! Bundan biraz altın çıkaracağız!..";
			link.l1 = "Kıyıda bir sandığa ihtiyacım var, Cutlass.";
			link.l1.go = "Pelly_9";
		break;
		
		case "Pelly_9":
            dialog.text = "Emredersiniz, Amiral!";
			link.l1 = "...";
			link.l1.go = "Pelly_10";
		break;
		
		case "Pelly_10":
            DialogExit();
			npchar.dialog.currentnode = "Pelly_7";
			pchar.questTemp.Mtraxx = "plant_4";
			pchar.questTemp.Mtraxx.Chest = "true";
			// подгружаем сундук в локу и меняем локаторы
			int n = Findlocation("Shore37");
			Locations[n].models.always.locators = "shore03_q_locators";
			locations[n].models.always.chest = "chest_quest";
			Locations[n].models.always.chest.locator.group = "box";
			Locations[n].models.always.chest.locator.name = "private1";
			Locations[n].models.always.chest.tech = "DLightModel";
			DoQuestReloadToLocation("Shore37", "goto", "goto5", "Mtraxx_PlantChestReady");
		break;
		
		case "Pelly_11":
            dialog.text = "Hemen, Amiralim!..";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantPrepareMarch");
		break;
		
		case "Pelly_12":
            dialog.text = "Adamlar hazır ve beklemede, Amiral!";
			link.l1 = "İleri!";
			link.l1.go = "Pelly_13";
		break;
		
		case "Pelly_13":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			chrDisableReloadToLocation = false;
		break;
		
		case "Pelly_14":
            dialog.text = "Amiralim, kurtarmamız gereken Tyrex'in arkadaşı galiba... biraz ölü.";
			link.l1 = "Yes, but nothing could be done there. You saw the guards; we were lucky to stay alive.";
			link.l1.go = "Pelly_15";
		break;
		
		case "Pelly_15":
            dialog.text = "Amiral, Marcus sana kızacak. Şu anda yanına gitme. Ben gidiyorum. Sen de gitmelisin.";
			link.l1 = "Evet...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantFailFinal");
		break;
		
		case "Pelly_16":
            dialog.text = "Kötü haber, Amiral. Doğudan üzerimize gelen bir İspanyol filosu var. Kaçacak vaktimiz yok.";
			link.l1 = "Kaç tanesi?";
			link.l1.go = "Pelly_17";
		break;
		
		case "Pelly_17":
            dialog.text = "Üç gemi. Bir sürü top. Yandık."; // лесникПОСЛЕДНЕЕ
			link.l1 = "Göreceğiz.";// Жан, ты отправляйся на борт к Тесаку. Тесак, поднимешь испанский флаг и на всех парусах прочь отсюда - глядишь, за торговца сойдёшь. А я пойду прямо на испанцев - отвлеку их от вас. Увидимся в Ла Веге у Тиракса.";
			link.l1.go = "Pelly_181";
		break;
		case "Pelly_181":
	    	DialogExit();
		   sld = characterFromId("Mrt_Rocur");
		   sld.Dialog.currentnode = "Pelly_182";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		case "Pelly_182":
		   dialog.text = ""; 
		   link.l1 = "Jean, sen Cutlass'ın gemisine git.";
		   link.l1.go = "Pelly_183"; 
		break;
		case "Pelly_183":
		     DialogExit();
			sld = characterFromId("Pelly");
			sld.Dialog.currentnode = "Pelly_18";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		case "Pelly_18":
            dialog.text = "";//"Но...";
			link.l1 = "Kılıcım, İspanyol bayrağını çekip hemen buradan defolmalısın. Onları senin için oyalayacağım. Hepinizi La Vega’da göreceğim.";//"Отставить! Тесак, за Жана Пикара отвечаешь головой перед Тираксом. Все на борт!";
			link.l1.go = "Pelly_19";
		break;
		
		case "Pelly_19":
            dialog.text = "Ama...";
			link.l1 = "İtiraz yok! Palanı kap, Picard Tyrex’in yerine ulaşamazsa senin başın yanar. Herkes güverteye!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantSeaEscape");
		break;
		
		case "Pelly_20":
            dialog.text = "Emirleriniz nedir, Amiral?";
			link.l1 = "Savaşa hazır olun. Benim komutumla saldırın!";
			link.l1.go = "Pelly_21";
		break;
		
		case "Pelly_21":
            dialog.text = "Emredersiniz, Amiral... buyruğunuzla!";
			link.l1 = "...";
			link.l1.go = "Pelly_22";
		break;
		
		case "Pelly_22":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
		break;
		
		case "Pelly_23":
            dialog.text = "Ho-ho! Merhaba, Prens. Seni Tortuga'ya ne getirdi?";
			link.l1 = "Yine Marcus'un işi. Dinle, Cutlass, şu evde yaşayan herif neden beni içeri almıyor?";
			link.l1.go = "Pelly_24";
		break;
		
		case "Pelly_24":
            dialog.text = "Gaspard Altındiş mi? O sadece güvendiği insanlarla çalışır. Diğerlerinin onunla iş yapabilmesi için bir tavsiyeye ihtiyacı olur. Parlak mücevherler satmak mı istiyorsun? İstersen sana kefil olabilirim...";
			link.l1 = "Yani o bir tefeci mi? Faizi ne kadar?";
			link.l1.go = "Pelly_25";
		break;
		
		case "Pelly_25":
            dialog.text = "Kardeşim, bir şeyi atlıyorsun. Gaspard tefeci değildir, sen gitmelisin "+GetFullName(characterFromId("Tortuga_usurer"))+" eğer ihtiyacın olursa. Goldenteeth her türlü değerli taş ve mücevheri satın alır. Ayrıca, iyi öder ve asla saçma sorular sormaz. Buradaki her korsan kaptan onun müşterisidir.";
			link.l1 = "Anladım... Bazılarının ona paralarını bile emanet ettiğini duydum...";
			link.l1.go = "Pelly_26";
		break;
		
		case "Pelly_26":
            dialog.text = "Ha-ha!   Bunu sana kim söylediyse yalancının teki, git ve utanmaz gözlerinin içine tükür. Gaspard yalnızca mücevher işiyle uğraşır, hep öyle olmuştur. Başkalarının parasıyla ne işi olsun ki, bela mı arıyor?";
			link.l1 = "Anladım. Teşekkürler, Cutlass, denizde görüşürüz!";
			link.l1.go = "Pelly_27";
			link.l2 = "Hmm, gerçekten öyle mi. Yani, ıvır zıvır mı alıyor? İlginç... Benim için bir iki güzel söz edebileceğini mi söylüyorsun?";
			link.l2.go = "Pelly_27z";
		break;
		
		case "Pelly_27":
            dialog.text = "Görüşürüz, Prens.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekReadLogbookThird");
		break;
		
		case "Pelly_27z":
            dialog.text = "Elbette! Artık bizdensin, hehe! Burada biraz bekle.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekPellyTalkGems");
		break;
		
		case "Pelly_28z":
            dialog.text = "Her şey yolunda! Artık Goldentooth, Charlie Prince’in ona gelip ıvır zıvır satabileceğini biliyor. Yalnız şunu unutma: Onun fiyatı iyi olsa da, o pinti tefecilerin verdiğinden yine de düşük. Ama her şeyi tonla alır! Hem de gereksiz sorular sormadan, dediğim gibi.";
			link.l1 = "İşte benim yakışıklı oğlum! Aferin sana, Paul! Artık bütün ganimeti boşaltacak bir yerim var!";
			link.l1.go = "Pelly_29z";
		break;
		
		case "Pelly_29z":
            dialog.text = "Hayır, Jean Picard 'Yakışıklı', ben ise 'Pala', haha! Elveda, Prens!";
			link.l1 = "Teşekkürler, Cutlass, denizde bol şans!";
			link.l1.go = "Pelly_27";
		break;
		
		case "Pelly_28":
			PlaySound("VOICE\English\LE\Pelly\Pelly_03.wav");
            dialog.text = "Senin için üç kuşum var, Prens. Gardıroplarda ve bir yatağın altında saklanırken buldum onları. Güzel şeyler, değil mi? Ha-ha-ha!";
			link.l1 = "Bence de öyleler. Hem de bakımlılar. Don Stubborn onlara gerçekten değer veriyor olmalı.";
			link.l1.go = "Pelly_29";
		break;
		
		case "Pelly_29":
            DialogExit();
			sld = CharacterFromID("Mtr_CartahenaMayorClone");
			sld.dialog.currentnode = "CartahenaMayor_8";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Pelly_30":
			PlaySound("VOICE\English\LE\Pelly\Pelly_04.wav");
            dialog.text = "Selam sana! Ne halt ediyorsun burada, Prens?";
			link.l1 = "Pala mı?.. Sesleri ve gürültüyü takip ediyordum, ama karşımda seni bulacağımı hiç düşünmemiştim. Nasıl oldu da kendini burada buldun?";
			link.l1.go = "Pelly_31";
			QuestPointerDelLoc("Judgement_dungeon_01", "reload", "reload2_back");
			QuestPointerDelLoc("Judgement_dungeon_02", "reload", "reload2");
			QuestPointerDelLoc("Judgement_dungeon_03", "reload", "reload2");
			QuestPointerDelLoc("Judgement_dungeon_04", "reload", "reload2");
			QuestPointerDelLoc("Judgement_dungeon_05", "quest", "pelly");
		break;
		
		case "Pelly_31":
            dialog.text = "Hayır, burada ne işin var! Hep etrafımdasın! Tyrex seni de bu hazine için mi gönderdi, doğru mu? Caramba, yine geç kaldım...";
			link.l1 = "Tyrex mi? Hayır... Bir harita aldım bir kadından. Muhtemelen sana da bir kopyasını sattı, değil mi? Tortuga'da mı? Ne kurnaz bir kadın. Ama yalan söylemedi - şu altın yığınına bak! Daha fazla adamla geri döneceğim, hepsini taşımak için...";
			link.l1.go = "Pelly_32";
		break;
		
		case "Pelly_32":
            dialog.text = "Elbette, bu bir yığın altın! Ama ne senin, ne de Tyrex’in! Önce ben buldum! O altınlar benim! Nasıl öğrendiğimin bir önemi yok! Bu seni hiç ilgilendirmez!";
			link.l1 = "Sakin ol, Cutlass, neden bu kadar öfkelisin? Şu yığına bak - burada milyonlarca var. Belki daha da fazla! İkimize de yetecek kadar!";
			link.l1.go = "Pelly_33";
		break;
		
		case "Pelly_33":
            dialog.text = "Her zaman pastanın en iyi dilimi sana düşer, Prens! Ama bu sefer öyle olmayacak! Hazine benim! Önce ben buldum!";
			link.l1 = "Lanet olsun, Paul, neyin var senin? Burada anlaşamıyor muyuz? Bu altının yarısı bile bir servet. Daha önce hiç böyle bir parayı elinde tutmadın. Üstelik, bir gün kârlı bir iş bulursam sana da haber verebilirim.";
			link.l1.go = "Pelly_34";
		break;
		
		case "Pelly_34":
            dialog.text = "Beni mi kandırmaya çalışıyorsun, Prens? Hiçbir şekilde olmaz! Sana tek bir kuruş, tek bir altın vermem! Çok geç kaldın!\nAh, neyin peşinde olduğunu anladım! Bu altını asla alamayacaksın!!!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionPellyFight");
		break;
		
		case "Pelly_35": //
            dialog.text = "Çok komik. Gerçekten. Sen tam bir komedyensin, Amiral. Ama doğru – Marcus, onu alt etmeye çalışanları, senin gibi olanları sevmez. Ama zeki adamlara değer verir.";
			link.l1 = "Pekala, pekala. Peki, aklında ne var?";
			link.l1.go = "Pelly_36";
		break;
		
		case "Pelly_36":
            dialog.text = "Seninle Handsome'ın açıkça düşünmediği bir şey var. Plantasyonda isyan çıkarmayı planlıyorsun. Harika fikir — eğer amaç yağma yapmak ya da ortalığı karıştırmaksa. Ama...";
			link.l1 = "Ama ne? İsyana karşı mısın? Korktun mu?";
			link.l1.go = "Pelly_37";
		break;
		
		case "Pelly_37":
            dialog.text = "Ben mi? Ha! Asla. Ama bir düşün, ya Handsome o katliamda ölürse ne olacak? Marcus'a ne diyeceğiz? Sana söyleyeyim - ne dersek diyelim fark etmez. Yine de derimizi yüzecek.";
			link.l1 = "Hmm. Peki, dahiyane planın ne? Onu bir şekilde buradan çıkarmamız gerekiyor.";
			link.l1.go = "Pelly_38";
		break;
		
		case "Pelly_38":
            dialog.text = "Evet, öyle. Bu yüzden... neden onu satın almayalım? Yani... resmen, tabii. Bir avuç altınla bu alçaklardan herkesi satın alabilirsin – kendi annelerini bile. Zavallı Jean için ne diyebiliriz ki?";
			link.l1 = "Ha! Cutlass, gerçekten bir plantasyona gidip Picard'ı satın almak istediğimi mi söylememi öneriyorsun? Bir de kimin için çalıştığımı da mı anlatayım, eğlence olsun diye? Aklını mı kaçırdın?";
			link.l1.go = "Pelly_39";
		break;
		
		case "Pelly_39":
            dialog.text = "Bunu söylemene gerek yok. Aslında tam tersi - kendini bir tüccar gibi göster. Elbette, bu rol için cesaretin yok ama bir korsana da benzemiyorsun. Alınma Amiral, ama gerçek bu. O plantasyona gir, kendinden emin davran ve Jean’ı iste. Sahibi kim olduğunu tahmin edebilir ama bunu belli etmez. Dediğim gibi - bir avuç altın ağızları kapatır.";
			link.l1 = "Peki bu... altın el bize kaça mal olacak? Tüm dağ mı?";
			link.l1.go = "Pelly_40";
		break;
		
		case "Pelly_40":
            dialog.text = "Belki öyle. Ama altınından vazgeçmek, kafandan vazgeçmekten iyidir. Sen karadayken ben boş durmadım – korsan gibi görünmeyen bir şeyler giyip, plantasyon ve onun mütevazı sahibi hakkında biraz soruşturdum.";
			link.l1 = "Ne buldun, Cutlass?";
			link.l1.go = "Pelly_41";
		break;
		
		case "Pelly_41":
            dialog.text = "Tabiri caizse, piyasa fiyatları. Bu, değerli bir tutsağın onun eline ilk kez düşüşü değil. Genellikle ya darağacında ya da daha kötüsü Engizisyon'un zindanlarında son bulurlar.";
			link.l1 = "Ve onları kaça satıyor?";
			link.l1.go = "Pelly_42";
		break;
		
		case "Pelly_42":
            dialog.text = "Önemli biri için mi? Beş yüz sikke. Tabii ki doblon olarak.";
			link.l1 = "BEŞ YÜZ MÜ?!";
			link.l1.go = "Pelly_43";
		break;
		
		case "Pelly_43":
            dialog.text = "Plantasyon sahipleri, ne bekliyordun?";
			link.l1 = "Bu fiyata küçük bir orduyu donatabilirim! Peki neden gemimde bir isyan için cephane yığıyorum o zaman? Küçük bir savaş için bu yeter de artar.";
			link.l1.go = "Pelly_44";
		break;
		
		case "Pelly_44":
            dialog.text = "Silahlar, ne olursa olsun, ekibin için ileride işe yarayacak. Peki, ne diyorsun?";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				if (PCharDublonsTotal() >= 500)
				{
					link.l1 = "(Güvenilir) Sadece şunu söyleyeceğim, eğer Terrax'ın ödülü burada harcadığımızdan az çıkarsa komik olurdu. Ama haklısın – hayatımız daha değerli. Dublonlar bende.";
					link.l1.go = "Pelly_45";
				}
				link.l2 = "Şu anda öyle bir altın dağım yok.";
				link.l2.go = "Pelly_44_1";
				Notification_Perk(true, "Trustworthy");
			}
			else Notification_Perk(false, "Trustworthy");
			link.l3 = "Biliyor musun, Cutlass? Boşver. Biz korsan mıyız, değil miyiz? Ya Jean? Yoksa onun tek meziyeti güzel yüzü mü? Bir sandık hazırla – orijinal plana sadık kalıyoruz.";
			link.l3.go = "Pelly_62";
		break;
		
		case "Pelly_44_1":
            dialog.text = "Bunu yaparsan şaşırırım – bu çok büyük bir meblağ. Peki, hazır olduğunda ya da daha iyi bir fikrin olursa, gel beni bul.";
			link.l1 = "Yapacağım. Burada bekle.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Pelly_44_2";
		break;
		
		case "Pelly_44_2":
			dialog.text = "Pekala Amiral, Picard'ı kurtarmak için yeterince altın biriktirebildin mi?";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Evet, sonunda başardım. Umarım bu işe yarar.";
				link.l1.go = "Pelly_45";
			}
			link.l2 = "Hâlâ üzerinde çalışıyorum, Cutlass.";
			link.l2.go = "exit";
			link.l3 = "Ben o açgözlü plantasyon sahiplerine dişimle tırnağımla kazandığım parayı vermem! Sandığı hazırla - biz de talihli centilmenler gibi davranacağız. Kararım bu.";
			link.l3.go = "Pelly_9";
			NextDiag.TempNode = "Pelly_44_2";
		break;
		
		case "Pelly_45":
            dialog.text = "Vay canına. Ekibimize yeni katıldın ama şimdiden böyle paralar saçıyorsun!";
			link.l1 = "Para her şey demek değil. Ama Terrax'ın ihtişamında güneşlenmek? Buna paha biçilemez.";
			link.l1.go = "Pelly_46";
			pchar.questTemp.mtraxx_PlantVykup = true;
		break;
		
		case "Pelly_46":
            dialog.text = "Buna itiraz edemem. Ama dediğiniz gibi, mesele sadece para değil - başka önemli bir şey daha var, Amiral.";
			link.l1 = "Şimdi merak ettim. Ne oldu?";
			link.l1.go = "Pelly_47";
		break;
		
		case "Pelly_47":
            dialog.text = "Sana plantasyon hakkında her şeyi araştırdığımı söylemiştim. Burada hangi malların talep gördüğünü ve piyasada döndüğünü de biliyorum. Eğer kendini yasal bir tüccar gibi göstermek istiyorsan, bir tomar altını plantasyon sahibinin masasına bırakmak yerine bu mallardan stoklasan iyi edersin.";
			link.l1 = "Anlaşıldı. Ne tür mallardan bahsediyoruz?";
			link.l1.go = "Pelly_48";
		break;
		
		case "Pelly_48":
            dialog.text = "Şey, canlı mallar dışında, hehe, buradaki plantasyon sahibi kahve, kopra ve vanilya alıp satar, ticaretini yapar. Yani...";
			link.l1 = "Bunlardan bir an önce bir yerden stok yapmam lazım. Ya da bir kervana saldırıp ihtiyacım olanı taşıdığını ummam gerek.";
			link.l1.go = "Pelly_49";
		break;
		
		case "Pelly_49":
            dialog.text = "Herhangi bir kervan değil bu. Ayrılmak istemesem de, kendime bir koz sakladım. Tam da ihtiyacın olanı taşıyan bir kervan yakında gelecek. Ama bir şartı var...";
			link.l1 = "Ah, şimdi ne oldu?";
			link.l1.go = "Pelly_50";
		break;
		
		case "Pelly_50":
            dialog.text = "Fransız bayrağı altında.";
			link.l1 = "Ne?!";
			link.l1.go = "Pelly_51";
		break;
		
		case "Pelly_51":
            dialog.text = "Öfkeni anlıyorum, ha-ha. Karar senin... Amiral. Detayları öğrenmek ister misin?";
			link.l1 = "Lanet olsun... Peki, anlat bakalım. Fazla vaktimiz yok – eğer sen ya da ben onlara yanaşmazsak, başkası yapacak.";
			link.l1.go = "Pelly_52";
			// link.l2 = "Fransızlara dokunmam, mecbur kalmadıkça. Konu kapanmıştır.";
			// link.l2.go = "Pelly_51_1";
		break;
		
		case "Pelly_51_1":
            dialog.text = "O zaman en iyisi, bütün o malları kendi başına toplamaya başla, hem de çabuk ol, yoksa Pretty Boy başkasına satılır. Ben de burada sonsuza kadar oyalanamam.";
			link.l1 = "Öyle tahmin etmiştim.";
			link.l1.go = "Pelly_51_2";
		break;
		
		case "Pelly_51_2": // добываем товары сами
            DialogExit();
			
			LAi_SetActorType(npchar);
			AddQuestRecord("Roger_3", "28");
			SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe", 0, 0, 14, false);
			SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe_time", 0, 0, 45, false);
		break;
		
		case "Pelly_52":
            dialog.text = "İşte bu! Bunu yapabileceğini biliyordum... Amiral. Şimdi anlaşmamız şöyle: Güvenilir bir kaynağımın bildirdiğine göre, yaklaşık iki hafta sonra Guadeloupe açıklarında kahve ve baharat taşıyan bir Fransız konvoyu görünecek. Konvoy büyük ve iyi silahlanmış, o yüzden iyice hazırlan.";
			link.l1 = "Başka ne seçeneğim var ki?";
			link.l1.go = "Pelly_53";
		break;
		
		case "Pelly_53": // наводка на караван с нужными товарами
            DialogExit();
			
			LAi_SetActorType(npchar);
			AddQuestRecord("Roger_3", "28");
			SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe", 0, 0, 14, false);
			SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe_time", 0, 0, 45, false);
		break;
		
		case "Pelly_54": // провал выкупа Красавчика
            dialog.text = "Keyfin yok gibi, Amiral. Yakışıklı nerede? Her şey suya mı düştü?";
			link.l1 = "Gerçekten de. Güzel para kazandım, ama o inatçı eşek Picard'ı bana satmayı reddetti – bir yığın dublon teklif etsem bile!";
			link.l1.go = "Pelly_55";
		break;
		
		case "Pelly_55":
            dialog.text = "Ne aptal! Şimdi ne olacak?";
			link.l1 = "Mal sahibine malları boşaltmak için çoktan anlaştım. Artık eski plana dönmemiz gerekecek - ya şimdi ya asla!";
			link.l1.go = "Pelly_56";
		break;
		
		case "Pelly_56":
            dialog.text = "Ama Handsome ve diğerleri için henüz hiçbir şey hazırlamadık ki!";
			link.l1 = "Vakit yok! Gemilere binin - silahları ve ilaçları ambarlarımızdan malların çuvallarına gizleyeceğiz. Ve İspanyol bayrağını çekmeyi sakın unutmayın!";
			link.l1.go = "Pelly_57";
		break;
		
		case "Pelly_57":
            dialog.text = "Kulağa mantıklı geliyor.";
			link.l1 = "Her neyse, başka bir şeye vaktimiz yok. Hadi! Boşaltma yakında başlayacak.";
			link.l1.go = "Pelly_58";
		break;
		
		case "Pelly_58":
            DialogExit();
			DoQuestFunctionDelay("Mtraxx_PlantWaitDay", 1.0);
		break;
		
		case "Pelly_59":
            dialog.text = "Kimleri görüyorum! Yakışıklı! Yüzün sapasağlam, yürüyüşün de kendinden emin olduğuna göre, her şey yolunda gitti sanırım?";
			link.l1 = "Pürüzsüz demek az kalır - hem kavgadan kaçındım hem de Jean’i geri aldım, üstüne biraz da para kazandım. Planın kusursuz işledi, Paul. Ufukta bir sorun yok, değil mi?";
			link.l1.go = "Pelly_60";
		break;
		
		case "Pelly_60":
            dialog.text = "Olduğu kadar sessiz. Marcus'a mı dönüyorsun?";
			link.l1 = "Pekâlâ.";
			link.l1.go = "Pelly_61";
		break;
		
		case "Pelly_61":
            DialogExit();
			AddDialogExitQuestFunction("Mtraxx_PlantSuccessfulRedemption");
		break;
		
		case "Pelly_62":
            dialog.text = "Hmm, nasıl isterseniz, Amiral. Ama Handsome'a bir şey olursa, Terrax'a uyarımı dikkate almadığınızı mutlaka bildiririm. Kaçış için her şey hazır mı?";
			link.l1 = "Sandığımdakileri bir kez daha kontrol edip sayayım.";
			link.l1.go = "Pelly_63";
		break;
		
		case "Pelly_63":
            dialog.text = "Emin olabilirsin. Çabalarımın karşılığı olarak küçük bir ücret karşılığında yardımcı olabilirim, heh-heh.";
			link.l1 = "Nasıl oldu?";
			link.l1.go = "Pelly_64";
		break;
		
		case "Pelly_64":
            dialog.text = "Maracaibo'da bir silah kaçakçısı tanıdığım var. Kılık değiştirip gizlice içeri gireceğim, ona parasını vereceğim ve silahların buraya kaçırılmasını ayarlayacağım. Ama sana pahalıya patlayacak – altın doblonlar, hem de nakit.";
			link.l1 = "Ve neden beni bu adamla daha önce tanıştırmadın? Bu bana ne kadara patlayacak?";
			link.l1.go = "Pelly_65";
		break;
		
		case "Pelly_65":
            dialog.text = "Sana tüm muhbirlerimi de mi tanıtayım? Peki. Masraflar, riskler ve benim payım derken... Yakışıklı'nın fidyesiyle aşağı yukarı aynı tutar.";
			link.l1 = "Pala, Allah'tan kork...";
			link.l1.go = "Pelly_66";
		break;
		
		case "Pelly_66":
            dialog.text = "Ne Tanrı'dan ne de senden korkarım, Amiral. Ama Jean'i kurtaramazsak Marcus'un öfkesinden? O başka bir mesele. Peki, ne yapıyoruz? Sandıkla ilgili yardıma ihtiyacın var mı?";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Pekala, devam et - zaten yeterince zaman kaybedildi. Al, bu miktar doğru olmalı.";
				link.l1.go = "Pelly_68";
			}
			link.l2 = "Bu çok para, Paul. Bunu biraz düşünmem gerek.";
			link.l2.go = "Pelly_67";
			link.l3 = "Bu kadar az sayıda silah için bu fiyat fazla yüksek! Toptan çok daha ucuza alabilirim. Sağ ol, bu işi kendim hallederim.";
			link.l3.go = "Pelly_67_1";
		break;
		
		case "Pelly_67":
            dialog.text = "Pekâlâ, düşün bakalım. Ama unutma—sen düşünürken, Handsome'ın yüzündeki ve vücudundaki morlukların sayısı saat başı artıyor, heh-heh-heh.";
			link.l1 = "Sana doblonları getireceğim...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Pelly_67_2";
		break;
		
		case "Pelly_67_1":
            dialog.text = "Bu işin büyüklüğü değil, zamanı ve riskleri önemli. Ama sen bilirsin.";
			link.l1 = "Bana güven, biliyorum. Sadece sandığı hazırla - bundan sonrasını ben hallederim.";
			link.l1.go = "Pelly_10";
		break;
		
		case "Pelly_67_2":
            dialog.text = "Hazır mısınız, Amiral? Silahlar konusunda yardıma ihtiyacınız var mı, yoksa hâlâ altınınız mı eksik?";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Sonunda yeterince topladım! Al şunu ve artık hallet şu işi – sinirlerimi bozuyor.";
				link.l1.go = "Pelly_68";
			}
			link.l2 = "Ağzını topla, Cutlass. Hazırım, ama parayı toparlamak için biraz daha zamana ihtiyacım var.";
			link.l2.go = "Pelly_67";
			link.l3 = "Bu kadar az sayıda silah için bu fiyat çok fazla! Toptan alsam çok daha ucuza mal olurdu. Sağ ol, ben bu işi kendim hallederim.";
			link.l3.go = "Pelly_67_1";
		break;
		
		case "Pelly_68":
            dialog.text = "Ah, bu ne kadar çok dublon böyle! Ama merak etme – her bir kuruş plan için harcanacak. Yoksa Marcus mezardan kalkıp beni bulur, heh-heh. Şimdi hadi, Git Yakışıklı'ya, Amiral, ve ona her şeyin hazır olduğunu söyle.";
			link.l1 = "Burada emirleri ben veriyorum. Şimdi, hareket et.";
			link.l1.go = "Pelly_69";
			RemoveDublonsFromPCharTotal(500);
		break;
		
		case "Pelly_69":
            DialogExit();
			sld = characterFromId("Pelly");
			sld.dialog.currentnode = "Pelly_7";
			pchar.questTemp.Mtraxx = "plant_5";
			AddQuestRecord("Roger_3", "30");
			sld = characterFromId("Mrt_Rocur");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "rocur_wait";
			sld.greeting = "Rocur_02";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Pelly_70":
            dialog.text = "Evet, bu bir sorun. Planınız nedir, Amiral?";
			link.l1 = "Bunlardan bir an önce bir yerden stok yapmam lazım. Ya da bir kervana saldırıp ihtiyacım olanı taşımasını umacağım.";
			link.l1.go = "Pelly_49";
			DeleteAttribute(pchar, "questTemp.mtraxx_PlantInfoTovar");
		break;
		
		// Жан Пикар
		case "rocur":
            dialog.text = "Benden ne istiyorsun?";
			link.l1 = "Arkadaşım, Jean Picard'ı arıyorum. O isim sana bir şey ifade ediyor mu?";
			link.l1.go = "rocur_1";
		break;
		
		case "rocur_1":
            dialog.text = "Bir ihtimal var. Ancak, yüzünü hatırlamıyorum.";
			link.l1 = "Çok sert olma, Jean. Beni buraya Marcus Tyrex gönderdi. Emrim seni buradan çıkarmak.";
			link.l1.go = "rocur_2";
		break;
		
		case "rocur_2":
            dialog.text = "Marcus? Şşş... Sessiz ol. Üzgünüm dostum, bunu bilmiyordum. Ama burada konuşmamalıyız, lanet muhafızlar her yerde ve hep kulak kesiliyorlar... Görüyorum ki İspanyollar arasında hoş karşılanan birisin, gece kulübelerden birinde beni bul, konuşuruz. Seni bekleyeceğim, kardeşim.";
			link.l1 = "...";
			link.l1.go = "rocur_3";
		break;
		
		case "rocur_3":
            DialogExit();
			AddQuestRecord("Roger_3", "6");
			LAi_CharacterDisableDialog(npchar);
			Mtraxx_PlantMakeMaxRocurClone();
		break;
		
		case "rocur_4":
            dialog.text = "Burada güvendesin... Adın ne, kardeşim?";
			link.l1 = "Kaptan "+GetFullName(pchar)+". Şimdi söyle bakalım, bu belaya nasıl bulaştın. Tyrex her şeyi bilmek istiyor.";
			link.l1.go = "rocur_5";
		break;
		
		case "rocur_5":
            dialog.text = "Willemstad'daki bir meyhanede bir yabancı yanıma yaklaştı... Hollanda kervanını yağmalamak için bana ortaklık teklif etti. Benim bir brigantinim vardı, onun ise oldukça sıradışı bir polakresi. Caracas yakınlarında bir kervanı yakaladık ve yağmaladık... Geceydi, ganimeti paylaşıyorduk ki karanlıkta devasa bir İspanyol kalyonu belirdi\nOrtağım kaçtı, ben de öyle. Ama hasarlı brigantiniyle bir kalyondan ve iki başka gemiden kaçmak imkânsızdı. Bizi ele geçirdiler ve hayatta kalan herkesi buraya, sanki hayvanmışız gibi sattılar.";
			link.l1 = "Anladım. Sence bu bir kaza mıydı? Galyon hakkında konuşuyorum.";
			link.l1.go = "rocur_6";
		break;
		
		case "rocur_6":
            dialog.text = "Kim bilir ki. Belki de silah seslerini duymuşlardır, Ana Cadde'den pek uzakta değildi.";
			link.l1 = "Hmm. Mümkün. Eski yoldaşınla daha önce tanıştın mı? Kim o?";
			link.l1.go = "rocur_7";
		break;
		
		case "rocur_7":
            dialog.text = "Never met him before. Said his name was Ignacio Marco, a privateer in service of England. He struck me as a serious man, that's why I agreed to take part in this endeavour. He's a seasoned sailor and a captain, that's for certain; he's got a dashing crew behind him, and his polacre is a beauty. You don't see a ship like that every day.";
			link.l1 = "Ignacio Marco mu? Bir İngiliz korsanı mı? İspanyol muymuş?";
			link.l1.go = "rocur_8";
		break;
		
		case "rocur_8":
            dialog.text = "O Portekizli, İspanyol değil. Britanya korsanlık mektubunda ne sakınca var? Aramızda zaten bir sürü İspanyol var, bunu biliyorsun.";
			link.l1 = "Anladım. Peki, buradan kaçışın hakkında konuşalım. Bir fikrin var mı?";
			link.l1.go = "rocur_9";
		break;
		
		case "rocur_9":
            dialog.text = "Kaç kişisiniz?";
			link.l1 = "Gemi̇m, bir barkantin, ve Pelly the Cutlass'ın adamları. Gemim Maracaibo limanında demirli. Cutlass Guajira Körfezi'ne çıktı ve orada kamp kurdu.";
			link.l1.go = "rocur_10";
		break;
		
		case "rocur_10":
            dialog.text = "Hmm...";
			link.l1 = "Ne sandın, Tyrex buraya bir savaş gemisi mi gönderecekti?";
			link.l1.go = "rocur_11";
		break;
		
		case "rocur_11":
            dialog.text = "Hiçbir şey beklemiyordum. Aslında, Marcus'un beni unutmamasına şaşırdım.";
			link.l1 = "Tabii ki yapmadı. Peki, bir fikrin var mı?";
			link.l1.go = "rocur_12";
		break;
		
		case "rocur_12":
            dialog.text = "No chance of escaping from here – this plantation is too well guarded, and there are wild jungles all around. No point in storming it either; you don't have enough men, plus there's a fort nearby.";
			link.l1 = "Belki sen ve adamların içeriden bize yardım edebilirsiniz? Onlara arkadan sert bir darbe vurun.";
			link.l1.go = "rocur_13";
		break;
		
		case "rocur_13":
            dialog.text = "Ne ile? Ellerimizle ve paslı pala mı?";
			link.l1 = "Ya silahların olsaydı ne olurdu?";
			link.l1.go = "rocur_14";
		break;
		
		case "rocur_14":
            dialog.text = "Pekala, o zaman onlara günlerini gösterirdik. Ama bir sorun var: içeri ne getirirsen getir, her şeyi kontrol ediyorlar, silah kaçırmanın imkanı yok. Bu yüzden bunu unutmanı öneririm.";
			link.l1 = "Ve yine de, şu anda en iyi seçeneğimiz bu. Sana ve adamlarına nasıl silah ulaştırabileceğimi düşüneceğim... Söylesene, aranızda kaç kişi dövüşebiliyor?";
			link.l1.go = "rocur_15";
		break;
		
		case "rocur_15":
            dialog.text = "Otuz kafa, derim.";
			link.l1 = "O zaman otuz pala... Tabancalar da fark yaratır diye düşünüyorum.";
			link.l1.go = "rocur_16";
		break;
		
		case "rocur_16":
            dialog.text = "Kaptan, bunda gerçekten ciddi misiniz?";
			link.l1 = "Ben geldim. Buraya bilerek geldim, şaka yapmak için değil. Başka neye ihtiyacın var?";
			link.l1.go = "rocur_17";
		break;
		
		case "rocur_17":
            dialog.text = "Very well... Let's give it a try at least. We need simple cold steel - my boys are not trained to work with fancy rapiers and the like. The same goes for handguns, the cheapest will do just fine. If you can get us a musket or two, that would help us a lot as well; I have a couple of lads who are good with muskets. Bullets, gunpowder. Healing potions are most welcome.";
			link.l1 = "Anlaşıldı. Kılıçlar ve baltalar geminin cephaneliğinden alınabilir. Geri kalanını bulmak daha zor. Hepsini toparladığımda sana haber vereceğim.";
			link.l1.go = "rocur_18";
		break;
		
		case "rocur_18":
            dialog.text = "Lütfen acele et, kardeşim. Burada yarım yılımız yok, şu lanet hayvan işleri bizi teker teker öldürüyor. Bana ihtiyacın olursa - gece yanıma gel.";
			link.l1 = "Anladım dostum. Bekle, seni fazla bekletmemeye çalışacağım. Ve dikkatli ol, onlara seni gözden çıkarmaları için henüz bir sebep verme.";
			link.l1.go = "rocur_19";
		break;
		
		case "rocur_19":
            DialogExit();
			AddQuestRecord("Roger_3", "7");
			npchar.dialog.currentnode = "rocur_wait";
			pchar.questTemp.Mtraxx = "plant_3";
			pchar.questTemp.Mtraxx.MagicBox = "Baster";
			AddLandQuestMark(characterFromId("Fadey"), "questmarkmain");
			AddMapQuestMarkCity("baster", false);
			pchar.quest.Mtraxx_PlantPrepareTimeOver.over = "yes"; //снять таймер
			SetFunctionTimerCondition("Mtraxx_SeekWeaponOver", 0, 0, 30, false); // таймер
		break;
		
		case "rocur_wait":
            dialog.text = "Bir haber var mı, dostum? Silahları topladın mı?";
			if (pchar.questTemp.Mtraxx == "plant_5")
			{
				link.l1 = "Evet. Bir sandık mühimmat Guajira Körfezi'nde. Geriye sadece onu plantasyona gizlice sokmanın bir yolunu bulmak kaldı.";
				link.l1.go = "rocur_20";
			}
			else
			{
				link.l1 = "Halledeceğim. Bekle.";
				link.l1.go = "rocur_wait_1";
			}
		break;
		
		case "rocur_wait_1":
            DialogExit();
			npchar.dialog.currentnode = "rocur_wait";
		break;
		
		case "rocur_20":
            dialog.text = "Pekala, kaptan. Bunu nasıl yapacağımı zaten düşünüyordum.";
			link.l1 = " Bunu duyduğuma sevindim. Ne düşünüyorsun? ";
			link.l1.go = "rocur_21";
			DelLandQuestMark(npchar);
		break;
		
		case "rocur_21":
            dialog.text = "They produce sugar and grow cocoa beans on this plantation. Sometimes its head sells the goods himself; it's more profitable that way. Make him an offer. Pay him not with money, but with goods. Something you can pack into boxes, like copra, vanilla, or coffee. Put some effort into bargaining, but don't overdo it\nStash weapons in one or two boxes and mark them. Arrange an exchange in the evening so they will have to leave the boxes outside overnight\nAt night, we will find your marked boxes, arm ourselves, and give hell to the Spanish. With your help, of course.";
			link.l1 = "İyi düşündün, kardeşim! Çok iyi, bu plan hoşuma gitti. Buna sadık kalalım.";
			link.l1.go = "rocur_22";
		break;
		
		case "rocur_22":
            dialog.text = "Son bir şey daha - takas için sadece bir çeşit mal teklif et. Daha fazla çeşit mal, muhafızların daha fazla kutu işaretlemesi demek.";
			link.l1 = "Katılıyorum. O zaman sadece bir çeşit seçeceğim. Kahve, vanilya ve kopra demiştin, değil mi?";
			link.l1.go = "rocur_23";
		break;
		
		case "rocur_23":
            dialog.text = "Evet. Bu, plantasyonun başındaki kişiye iyi bir anlaşma gibi gelecektir.";
			link.l1 = "Anladım. Anlaşma sağlandığında sana haber vereceğim.";
			link.l1.go = "rocur_24";
		break;
		
		case "rocur_24":
            DialogExit();
			AddQuestRecord("Roger_3", "9");
			npchar.dialog.currentnode = "rocur_wait_2";
			pchar.questTemp.Mtraxx = "plant_6";
			pchar.questTemp.mtraxx_PlantInfoTovar = true;
			AddLandQuestMark(characterFromId("Pelly"), "questmarkmain");
		break;
		
		case "rocur_wait_2":
            dialog.text = "Git, dostum, zaman altın değerinde ve bizim hiç yok...";
			link.l1 = "";
			link.l1.go = "rocur_wait_3";
		break;
		
		case "rocur_wait_3":
            DialogExit();
			npchar.dialog.currentnode = "rocur_wait_2";
		break;
		
		case "rocur_25":
            dialog.text = "...";
			link.l1 = "(sessizce) Anlaştık. Sandıklar yarın akşam plantasyona teslim edilecek. İhtiyacın olan sandıkların üzerinde 'W' harfi var. Diğerlerinde ise alfabenin kalan harfleri var. Adamlarını hazırla. Şafaktan önce, saat üç civarında saldıracağız.";
			link.l1.go = "rocur_25x";
			DelLandQuestMark(npchar);
		break;
		
		case "rocur_25x":
            dialog.text = "Sinyalini verdiğinde başlayacağız...";
			link.l1 = "";
			link.l1.go = "rocur_26";
		break;
		
		case "rocur_26":
            DialogExit();
			LAi_CharacterDisableDialog(npchar);
			DoQuestFunctionDelay("Mtraxx_PlantWaitDay", 3.0);
		break;
		
		case "rocur_27":
            dialog.text = "Sonunda! Yeniden denizi göreceğim! Neredeyse nasıl göründüğünü ve nasıl koktuğunu unutmuştum. Aferin kaptan! Sana borçlandım.";
			link.l1 = "Boşver şimdi, sonra hallederiz... Hadi gemiye çıkalım ve buradan gidelim!";
			link.l1.go = "rocur_28";
		break;
		
		case "rocur_28":
            DialogExit();
			sld = characterFromId("Pelly");
			sld.Dialog.currentnode = "Pelly_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "rocur_29":
            dialog.text = "Selamlar "+pchar.name+". Seni tekrar görmek güzel, ayrıca bu macerada yanında olmaktan da mutluyum. Bu iş zor olacak, ama eminim birlikte üstesinden geleceğiz.";
			link.l1 = "Nice to see you again, Picard. I'm all ears; tell me about this adventure of yours.";
			link.l1.go = "rocur_30";
		break;
		
		case "rocur_30":
            dialog.text = "Ben bunu zaten Marcus'a anlattım, şimdi de sana anlatacağım. Maracaibo'daki plantasyonda köle olarak çalışırken, İspanyollardan bir şey öğrendim. Sarhoş olduklarında oldukça geveze olurlar... Dinle, Maracaibo Körfezi'nin güneydoğusunda küçük bir köy var. İki dağın arasında, ormanın derinliklerinde saklanıyor. İsmi de tam bir bela: Santiago-de-Los-Caballeros-de-Merida. Biz ona kısaca Merida diyelim\nHenüz pek ilginç gelmedi, değil mi? Köyü çevreleyen dağlar, değerli taşlarla doluymuş. Zümrütler, opaller ve efsanevi ateş opalleri...\nAnladığım kadarıyla, Merida'nın yerleşimcileri bu taşlardan genel valiye bahsetmemiş. Ama yakında o da öğrenecek, bu yüzden İspanyol sömürge memurları gelmeden önce Merida'yı ziyaret etmeliyiz.";
			link.l1 = "Yerleşimi yağmalamak ister misin?";
			link.l1.go = "rocur_31";
		break;
		
		case "rocur_31":
            dialog.text = "Aynen öyle. Küçük bir garnizonla ormanlar ve dağlar arasında kaybolmuş durumda - bir korsan birliği için kolay bir av. Üstelik denizden de çok uzaktalar, onlara kimsenin saldırmasını beklemiyorlar, mızraklı ve yaylı vahşiler dışında.";
			link.l1 = "Yerleşimde değerli taşlar olduğundan ne kadar eminsin?";
			link.l1.go = "rocur_32";
		break;
		
		case "rocur_32":
            dialog.text = "Eğer bu macera yanlış bir iz çıkarsa, bizzat senin geminde subay ya da tayfa olarak hizmet edeceğim. Güverteleri temizleyecek, borcumu sana ve Marcus’a ödeyene kadar sayısız çatışmada savaşacağım.";
			link.l1 = "Anladım... Peki, Merida'ya nasıl gidileceğini biliyor musun?";
			link.l1.go = "rocur_33";
		break;
		
		case "rocur_33":
            dialog.text = "Tabii ki ormanın içinden geçen tam yolu bilmiyorum, ama yerli halktan bir rehber tutacağız. Maracaibo Gölü'nün güneyine çıkmalıyız, bir yerli köyü bulup yolu bilenleri aramalıyız.";
			link.l1 = "...";
			link.l1.go = "rocur_34";
		break;
		
		case "rocur_34":
            DialogExit();
			sld = characterFromId("Terrax");
			sld.Dialog.currentnode = "mtraxx_38";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_35":
            dialog.text = "Captain, I am deeply sorry for my language, but why the actual fuck are we not in Merida yet? Huh? You have spat on our common cause! Leprechaun and I are leaving without you. I will explain everything to Tyrex, and you should go. Here, take 50,000 pesos for your help in Maracaibo; I borrowed them from friends. Farewell, damn shame, I thought better of you.";
			link.l1 = "Hmm... Üzgünüm.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_MeridaTimeOverFail");
		break;
		
		case "rocur_36":
            dialog.text = "İşte geldik. Önümüzde orman var. Önce bir Kızılderili köyü bulup bir rehber hakkında soruşturalım.";
			link.l1 = "Hadi yapalım. Luke, söylemek istediğin bir şey var mı... ya da belki bir tavsiyen?";
			link.l1.go = "rocur_37";
		break;
		
		case "rocur_37":
            DialogExit();
			sld = characterFromId("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_38":
            dialog.text = "Merida garnizonu işini bitirdi. Köyde ciddi bir direniş beklemiyorum. Hadi gidelim!";
			link.l1 = "Saldırın!!!";
			link.l1.go = "rocur_39";
		break;
		
		case "rocur_39":
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_ExitTown", "reload1_back", true);
			pchar.quest.mtraxx_merida_town.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_town.win_condition.l1.location = "Merida_Town";
			pchar.quest.mtraxx_merida_town.function = "Mtraxx_MeridaTown";
			Mtraxx_MeridaCheckOurWarriors();
			AddQuestRecord("Roger_5", "16");
		break;
		
		case "rocur_40":
            dialog.text = "Bitti! Artık kahraman kalmadı. Şimdi bu 'şehrin' valisiyle konuşmalıyız. Umarım ikna edilebilir bir tiptir.";
			link.l1 = "Katılıyorum, hadi onu 'ikna edelim'!.. Jean! Beni takip et!";
			link.l1.go = "rocur_41";
		break;
		
		case "rocur_41":
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_Town", "gate_back", true);
			pchar.quest.mtraxx_merida_townhall.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_townhall.win_condition.l1.location = "Merida_townhall";
			pchar.quest.mtraxx_merida_townhall.function = "Mtraxx_MeridaTownhall";
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			sld = characterFromId("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddQuestRecord("Roger_5", "17");
		break;
		
	case "rocur_42": //злой вариант
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_Town", "reload3", true); 
			pchar.questTemp.Mtraxx = "merida_success";
			pchar.quest.mtraxx_merida_exit.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_exit.win_condition.l1.location = "Merida_Town";
			pchar.quest.mtraxx_merida_exit.function = "Mtraxx_MeridaExit";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			
			sld = characterFromId("Merida_Head");
			LAi_SetActorType(sld);
			
			pchar.questTemp.Mtraxx_MeridaZloVariant = true;
			
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload1", "Mtraxx_MeridaExitResidensia", -1);
		break;
		
		case "rocur_43": //мирный вариант
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_Town", "reload3", true); 
			pchar.questTemp.Mtraxx = "merida_success";
			pchar.quest.mtraxx_merida_exit.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_exit.win_condition.l1.location = "Merida_Town";
			pchar.quest.mtraxx_merida_exit.function = "Mtraxx_MeridaExit";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			
			sld = characterFromId("Merida_Head");
			LAi_SetActorType(sld);
			
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto2", "Mtraxx_MeridaGiveJewelry", -1);
			
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload1", "Mtraxx_MeridaExitResidensia", -1);
		break;
		
		case "rocur_44":
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaKamushki"))
			{
            	dialog.text = "Güzel iş çıkardın, "+pchar.name+"! Payı bölüşme zamanı. Zaten hesapladım. Sandıkta neredeyse 2000 mücevher vardı: 1560 zümrüt, 1032 opal ve 363 ateş opali. Senin payın üçte bir: 350 zümrüt, 244 opal ve 63 ateş opali. Al, bunlar senin.";
            }
            else
           	{
           	dialog.text = "Güzel iş çıkardın, "+pchar.name+"! Payı bölüşme zamanı. Sayıları zaten çıkardım. Sandıkta neredeyse 2.000 mücevher vardı: 1.050 zümrüt, 732 opal ve 189 ateş opali. Senin payın üçte bir: 350 zümrüt, 244 opal ve 63 ateş opali. Al, bunlar senin.";
           	}
			link.l1 = "Güzel!";
			link.l1.go = "rocur_45";
		break;
		
		case "rocur_45":
			PlaySound("interface\important_item.wav");
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaKamushki"))
			{
				TakeNItems(pchar, "jewelry4", 520);
				TakeNItems(pchar, "jewelry16", 334);
				TakeNItems(pchar, "jewelry14", 121);
			}
			else
			{
				TakeNItems(pchar, "jewelry4", 350);
				TakeNItems(pchar, "jewelry16", 244);
				TakeNItems(pchar, "jewelry14", 63);
			}
            dialog.text = "Şimdi beni kurtardığın için sana olan borcumdan bahsedelim. Biliyorum, bu işte epey masrafın oldu. Sence adil bir karşılık ne olurdu? Mücevherlerden bana düşen paydan ödeyeceğim.";
			link.l1 = "Payını üçüncüye bölmek yeterli olacak. Senin de paraya ihtiyacın var – bir gemi almak, donatmak, tayfanı ödemek için...";
			link.l1.go = "rocur_46";
		break;
		
		case "rocur_46":
			PlaySound("interface\important_item.wav");
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaKamushki"))
			{
				TakeNItems(pchar, "jewelry4", 173);
				TakeNItems(pchar, "jewelry16", 111);
				TakeNItems(pchar, "jewelry14", 40);
			}
			else
			{
				TakeNItems(pchar, "jewelry4", 116);
				TakeNItems(pchar, "jewelry16", 81);
				TakeNItems(pchar, "jewelry14", 21);
			}
            dialog.text = "Teşekkür ederim, dostum! Yarıdan azına razı olmayacağını sanmıştım. Şu anda gerçekten paraya ihtiyacım var. Al, mücevherleri senin olsun.";
			link.l1 = "Ne baskındı ama, Jean! Hadi Hispaniola'ya, Tyrex'e gidelim.";
			link.l1.go = "rocur_47";
		break;
		
		case "rocur_47":
            DialogExit();
			chrDisableReloadToLocation = false;
			pchar.questTemp.Mtraxx = "merida_gohome";
			AddQuestRecord("Roger_5", "18");
			sld = characterFromId("Mrt_Rocur");
			LAi_SetWarriorType(sld);
			LAi_CharacterDisableDialog(sld); // релиз-правка
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			sld = characterFromId("Lepricon");
			LAi_SetWarriorType(sld);
			LAi_CharacterDisableDialog(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "mtraxx_40";
			pchar.quest.mtraxx_merida_lavega.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_lavega.win_condition.l1.location = "Hispaniola1";
			pchar.quest.mtraxx_merida_lavega.function = "Mtraxx_IgnasioKitty";
			// таймер на доплыть домой 40 дней
			SetFunctionTimerCondition("Mtraxx_MeridaReturnLate", 0, 0, 40, false);
			DeleteAttribute(pchar, "GenQuest.HunterLongPause");
		break;
		
		case "rocur_48":
            dialog.text = "Ah, ne güzel bir karşılaşma! Sizi görmek büyük bir zevk, "+pchar.name+". Nasılsın?";
			link.l1 = "Fena değil. Kısa süre önce Kızıl Kurt'un hazinesini buldum. Şimdi Martinique'e, ortak bir dostumuzla buluşmaya gidiyorum. Tyrex'i görmek ister misin?";
			link.l1.go = "rocur_49";
		break;
		
		case "rocur_49":
            dialog.text = "Evet. Onunla Pasquale Lavoisier hakkında konuşmak istiyorum. Marcus beni o yarı haydut, yarı tüccara gönderdi. İstediğini yaptım, karşılığında bana bir avuç saçmalık verdi, bunun harika bir ödeme olduğunu iddia etti. Oracıkta gebertirdim o herifi, ama Marcus ona saygılı davranmamı istedi... şimdi bu pisliği temizlemek ona kaldı.";
			link.l1 = "Üzgünüm, ama Marcus hiçbir şey yapmayacak. Dört göz onunla iş yapıyor.";
			link.l1.go = "rocur_50";
		break;
		
		case "rocur_50":
            dialog.text = "Ne oluyor lan?";
			link.l1 = "Evet, ama sana bundan bahsetmedim, tamam mı? Lavoisier de kısa süre önce bana kazık attı. Tyrex benden de yardım istedi, tıpkı senden istediği gibi. Isla Tesoro'da bana dört gözle uğraşmanın Marcus'la uğraşmakla aynı şey olduğu söylendi. Bu yüzden sana tavsiyem, bunu unut. Bu işte ne ilk ne de son sensin.";
			link.l1.go = "rocur_51";
		break;
		
		case "rocur_51":
            dialog.text = "Anladım. O ikisi seni de kandırdı mı?";
			link.l1 = "Evet, aslında ben de o dört gözle biraz uğraşmayı düşünüyordum, ama onu daha iyi tanıyınca vazgeçtim. Değmezmiş.";
			link.l1.go = "rocur_52";
		break;
		
		case "rocur_52":
            dialog.text = "Eğer kimsenin asla öğrenmeyeceğini bilseydin, o herifi geri ödemeye çalışır mıydın?";
			link.l1 = "Ha! Tabii ki isterim! Ama nasıl yapacağımı bilmiyorum. Lavoisier’in adamlarına saldır, bir gün gelir, tayfaların sarhoş olup her şeyi anlatır. Nasıl işlediğini bilmiyor musun?";
			link.l1.go = "rocur_53";
		break;
		
		case "rocur_53":
            dialog.text = "Şimdi Martinique'e mi gidiyorsun? La Vega'ya tekrar ne zaman varırsın?";
			link.l1 = "Marcus bana üç hafta verdi.";
			link.l1.go = "rocur_54";
		break;
		
		case "rocur_54":
            dialog.text = "İki güne yetiştirmeye çalış. Düşünüp karar vereceğim... 14 gün sonra beni Gonaïves Körfezi'nde bul. Doğrudan oraya git, La Vega'ya uğrama.";
			link.l1 = "Bir şeyler peşinde olduğunu görebiliyorum, ha-ha. Peki. Deneyeceğim.";
			link.l1.go = "rocur_55";
		break;
		
		case "rocur_55":
            dialog.text = "Bunu yapsan iyi olur. Görüşürüz!";
			link.l1 = "...";
			link.l1.go = "rocur_56";
		break;
		
		case "rocur_56":
            DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3", "none", "", "", "", 10.0);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			ReOpenQuestHeader("Roger_4");
			AddQuestRecord("Roger_4", "11");
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.hour  = 1.0;
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 14);
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 14);
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 14);
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l2 = "location";
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l2.location = "Shore34";
			pchar.quest.mtraxx_pasq_gonaiv.function = "Mtraxx_PasqualeJanGonaiv";
			SetFunctionTimerCondition("Mtraxx_PasqualeJanTimer", 0, 0, 10, false); // правки прогона 3
			SetFunctionTimerCondition("Mtraxx_PasqualeJanTimeOver", 0, 0, 15, false);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			pchar.questTemp.Mtraxx.Pasquale.Grabbing = "true";
		break;
		
		case "rocur_57":
			if (pchar.location.from_sea != "Shore34")
			{
				dialog.text = RandSwear()+"Gemicin nerede? Buraya La Vega'dan mı geldin? Merde! Sana buraya gizlice ve kimseye görünmeden gelmeni söylemiştim. Planım mahvoldu şimdi. Kahretsin!..";
				link.l1 = "Hm...";
				link.l1.go = "rocur_58";
			}
			if (GetOfficersQuantity(pchar) > 0)
			{
				dialog.text = "İşte buradasın, "+pchar.name+". İyi ki buradasın. Adamlarını gemiye geri gönder. Bu özel bir konuşma.";
				link.l1 = "Pekâlâ.";
				link.l1.go = "rocur_59";
			}
			else
			{
				dialog.text = "İşte buradasın, "+pchar.name+". İyi ki buradasın.  Sana bir iş teklifi yapacağım. Dinlemeye hazır mısın?";
				link.l1 = "Tabii!";
				link.l1.go = "rocur_61";
			}
		break;
		
		case "rocur_58":
            DialogExit();
			Group_DelCharacter("RocurSeaGroup", "Mrt_Rocur");
			Group_DeleteGroup("RocurSeaGroup");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 10.0);
			AddQuestRecord("Roger_4", "14");
			CloseQuestHeader("Roger_4");
		break;
		
		case "rocur_59":
            DialogExit();
			LAi_SetStayType(npchar);
			npchar.dialog.currentnode = "rocur_60";
		break;
		
		case "rocur_60":
            if (GetOfficersQuantity(pchar) > 0)
			{
				dialog.text = "Sana zaten söyledim - subaylarını dışarı gönder!";
				link.l1 = "Evet, evet, anladım.";
				link.l1.go = "rocur_59";
			}
			else
			{
				dialog.text = "Harika. Şimdi rahatça konuşabiliriz. Sana bir iş teklifim var. Dinlemeye hazır mısın?";
				link.l1 = "Tabii!";
				link.l1.go = "rocur_61";
			}
		break;
		
		case "rocur_61":
            dialog.text = "La Vega'yı iyi tanır mısın?";
			link.l1 = "Pekâlâ... Sanırım biliyorum. Neden soruyorsun?";
			link.l1.go = "rocur_62";
			npchar.greeting = "";
		break;
		
		case "rocur_62":
            dialog.text = "Hiç yerel dükkânın sağındaki ambarı fark ettin mi? Kulübelerin arasında tek büyük ev odur.";
			link.l1 = "Her zaman kapalı olan mı? Evet, gördüm onu. Neden soruyorsun?";
			link.l1.go = "rocur_63";
		break;
		
		case "rocur_63":
            dialog.text = "Güzel fark ettin - burası her zaman kapalıdır. Sen Martinique'teki görevinle meşgulken, ortak dostumuz Lavoisier burada Marcus Tyrex'in misafiri olarak üç gün kaldı. Bu evde rom içip eğlendiler.";
			link.l1 = "Hm...";
			link.l1.go = "rocur_64";
		break;
		
		case "rocur_64":
            dialog.text = "Sonra Lavoisier'nin adamları bazı sandıkları ve paketleri eve taşıdı. Ardından o ayrıldı. Marcus'a gelince, o her gün orada birkaç saat kalıyor.";
			link.l1 = "Bir önerin var mı?";
			link.l1.go = "rocur_65";
		break;
		
		case "rocur_65":
            dialog.text = "Hangi öneriler? Eminim bu ev, La Vega'daki Lavoisier'nin üssü olmalı. Pencereden pek bir şey göremedim ama içeride mallar depolanmış. Sanırım o dört göz, bize borcunu ödeyecek güce sahip.";
			link.l1 = "Pekala, pekala... İçeri mi girmek istiyorsun? Peki ya kapalı kapı? Ağır ve sağlam, sessizce içeri girmemizin imkanı yok.";
			link.l1.go = "rocur_66";
		break;
		
		case "rocur_66":
            dialog.text = ""+pchar.name+", beni aptal mı sanıyorsun? Ben çoktan hallettim. Kilidin balmumu kalıbını çıkarıp anahtarı yaptırdım. Bana epey pahalıya patladı ama o benim sorunum.";
			link.l1 = "Heh! O zaman neden beni bekliyorsun?";
			link.l1.go = "rocur_67";
		break;
		
		case "rocur_67":
            dialog.text = "Böylesi daha güvenli olacak, hem de sana güvenebileceğim tek kişi sensin. Bir kafa iyidir, iki kafa daha iyidir, dört göz ise iki gözden daha iyidir.";
			link.l1 = "Evet, Lavoisier’i alt etmek için onun kadar çok göze ihtiyacımız olacak, ha-ha-ha! Ama ya Tyrex? Biz Pasquale’in eşyalarını karıştırırken eve girerse ne olacak?";
			link.l1.go = "rocur_68";
		break;
		
		case "rocur_68":
            dialog.text = "O yapmaz. Her zaman gece yarısında kendi evine döner. Yarın gece La Vega'ya gitmeye hazır mısın? Kimlerin onları mahvettiğini asla anlamayacaklar: sen hâlâ Martinique'tesin ve ben La Vega'dan bir hafta önce ayrıldım.";
			link.l1 = "Şu dört gözlü herifi bir güzel becermek isterdim. Ama söyle bana Jean, fıçıları ve sandıkları evden nasıl taşıyacağız?";
			link.l1.go = "rocur_69";
		break;
		
		case "rocur_69":
            dialog.text = "Eminim orada sandıklardan ve variller dolusu mallardan daha değerli eşyalar bulacağız, hem de çok daha hafif olacaklar. Peki, var mısın?";
			link.l1 = "Tabii ki öyleyim!";
			link.l1.go = "rocur_70";
		break;
		
		case "rocur_70":
            dialog.text = "Harika, yanılmadığıma sevindim. Şimdi dinlenelim, gece yarısı La Vega'ya gidiyoruz.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNight");
		break;
		
		case "rocur_71":
            dialog.text = "Gitme vakti. Şu herifi soyalım ve gün doğmadan buradan defolup gidelim.";
			link.l1 = "İleri!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightMarch");
			SetLocationCapturedState("LaVega_town", true);
			LAi_LoginInCaptureTown(npchar, true);
		break;
		
		case "rocur_72":
            dialog.text = "Sessiz ol... Şimdi Pasquale'nin evine sessizce ilerle. Beni takip et.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightToHouse");
		break;
		
		case "rocur_73":
            dialog.text = "Şuna bak - etrafta ne kadar çok eşya var. Hadi başlayalım. Kapının yanındaki sandığı kontrol et, sonra yukarı çıkıp bir odayla ilgilen. Ben burada kalacağım: Değerli şeyleri hurda arasında saklamanın yollarını bilirim. Gözünü ve kulağını açık tut, pencerelerden uzak dur.";
			link.l1 = "Pekala...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightInHouse");
		break;
		
		case "rocur_74":
            dialog.text = ""+pchar.name+", neyin var? İlginç bir şey var mı?";
			link.l1 = "Gel ve bak. Bu bir şey.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeJanSeeGirl");
		break;
		
		case "rocur_75":
            dialog.text = "Lanet olsun! Şimdi Tyrex'in neden her gün buraya geldiğini anlıyorum. Burası sadece dört gözün deposu değil, aynı zamanda bir genelevmiş.";
			link.l1 = "Burada köle gibi görünüyor.";
			link.l1.go = "rocur_76";
		break;
		
		case "rocur_76":
            dialog.text = "Tabii. Şuna bir bak - belli ki liman fahişesi... Kötü şans bizim için. Onu öldürmemiz gerek.";
			link.l1 = "Gerçekten mi?";
			link.l1.go = "rocur_77";
		break;
		
		case "rocur_77":
            dialog.text = "Yüzlerimizi gördü ve senin adını duydu. Tyrex'e her şeyi anlatacak.";
			link.l1 = "Hm...";
			link.l1.go = "rocur_78";
		break;
		
		case "rocur_78":
            dialog.text = "Karar senin. Onun hayatı sana kendi hayatına mal olabilir.";
			link.l1 = "";
			link.l1.go = "rocur_79";
		break;
		
		case "rocur_79":
            DialogExit();
			sld = characterFromId("Mirabella");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_80":
            dialog.text = "Bu fahişeye güvenmeyi aklından bile geçirme. Yarın Tyrex her şeyi öğrenecek. Kara işaret almak ister misin?";
			link.l1 = "Hayır, bilmiyorum. Ve o kadını öldürmek istemiyorum – ona ihtiyacım var. Benimle geliyor.";
			link.l1.go = "rocur_81";
		break;
		
		case "rocur_81":
            dialog.text = "Aptal olma! Fırsatını bulur bulmaz kaçar. Alnına bak, damgayı görüyor musun? O bir hırsız.";
			link.l1 = "Hm. Muhtemelen haklısın, Jean. Peki, işini bitir ve buradan gidelim.";
			link.l1.go = "rocur_82";
			link.l2 = "Onu gemimde tutmayı düşünmüyorum. Onun için asla kaçamayacağı bir yerim var, çığlıklarını da kimse duyamaz. Orada da işini yapmaya devam edecek... Kişisel fahişem olacak, hem de bedavaya, he-he!";
			link.l2.go = "rocur_84";
		break;
		
		case "rocur_82":
            DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto6", "", 5);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto7", "Mtraxx_PasqualeJanKillGirl", 5);
		break;
		
		case "rocur_83":
			ChangeCharacterComplexReputation(pchar, "nobility", -10);
            dialog.text = "Bu kadar, artık Marcus'a hiçbir şey söylemez...";
			link.l1 = "Zavallı kız... hah, ne derler bilirsin, Şans Hanım tam bir kaltak...";
			link.l1.go = "rocur_86";
		break;
		
		case "rocur_84":
            DialogExit();
			sld = characterFromId("Mirabella");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_85":
            dialog.text = "Sen iyi bir adamsın, "+pchar.name+" . Neden onunla uğraşmak istiyorsun? Neyse, senin kararın. Ayrılırken sessiz olmasını sağla.";
			link.l1 = "Eğer olmayacaksa - o zaman ölmüştür.";
			link.l1.go = "rocur_86";
		break;
		
		case "rocur_86":
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Pasquale.Grabbing.Chest")) sTemp = "A bit. A chest full of doubloons, a handful of rubies, a map of Hispaniola and some rum.";
			else sTemp = "Nothing of value.";
            dialog.text = "Ne buldun?";
			link.l1 = sTemp;
			link.l1.go = "rocur_87";
		break;
		
		case "rocur_87":
			Log_Info("You have received two treasure collections.");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "icollection", 2);
            dialog.text = "Şans yine benden yana. Al, bu da senin payın. Bunca şeyi tek başıma karaya taşıyamazdım zaten. Dört göz bize tam parasını verdi.";
			link.l1 = "Harika! Aferin, Jean!";
			link.l1.go = "rocur_88";
		break;
		
		case "rocur_88":
            dialog.text = "Şimdi git!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightOutHouse");
		break;
		
		case "rocur_89":
			PlaySound("VOICE\English\LE\Rocur\Rocur_04.wav");
            dialog.text = "Harika. İş bitti. Güzel ve sessizce hallettik. Şimdi, hadi gemilere geri dönelim.";
			link.l1 = "Hah, iyi fikir.";
			link.l1.go = "rocur_89_1";
			//AddDialogExitQuestFunction("Mtraxx_PasqualeNightGulf");
		break;
		
		case "rocur_89_1":
			DialogExit();
			DoFunctionReloadToLocation("shore34", "goto", "goto13", "Mtraxx_PasqualeFinal");
		break;
		
		case "rocur_90":
			PlaySound("VOICE\English\LE\Rocur\Rocur_05.wav");
            dialog.text = "Pekala, "+pchar.name+". Artık yollarımızı ayırmanın zamanı geldi. Bir daha karşılaşır mıyız bilmiyorum, ama bil ki seni tanımak büyük bir zevkti, dostum.";
			link.l1 = "Ah, hadi bakalım, La Vega'da sık sık görüşeceğiz.";
			link.l1.go = "rocur_91";
			SetLocationCapturedState("LaVega_town", false);
			LAi_LoginInCaptureTown(npchar, false);
		break;
		
		case "rocur_91":
            dialog.text = "Hayır. Tyrex ile işim bitti. Lavoisier ile yaşanan bu karmaşa bardağı taşıran son damla oldu.";
			link.l1 = "Hmm... Anladım, boşver gitsin. Hakkımız olanı aldık zaten. Tyrex iyi ipuçları veriyor, değil mi? Geçen sefer Kızıl Kurt'un hazinesinden yarım milyondan fazla kazandım.";
			link.l1.go = "rocur_92";
		break;
		
		case "rocur_92":
            dialog.text = "Söylesene, onu bulmak için çok mu uğraştın?";
			link.l1 = "Pekala... Kolay olmadı. Çok düşündüm, yolculuk ettim, savaştım. Buna değdi sanırım.";
			link.l1.go = "rocur_93";
		break;
		
		case "rocur_93":
            dialog.text = "Tyrex'e ne kadar ödedin?";
			link.l1 = "Üçüncüsü.";
			link.l1.go = "rocur_94";
		break;
		
		case "rocur_94":
            dialog.text = "Bu işte onun payı neydi? Marcus tam olarak ne yaptı?";
			link.l1 = "Hm... Bana Kızıl Kurt'un günlüğünü verdi...";
			link.l1.go = "rocur_95";
		break;
		
		case "rocur_95":
            dialog.text = "Hepsi bu mu? Doğru mu?";
			link.l1 = "Pekâlâ... Yoksa Kaptan Wulfric hakkında asla bir şey öğrenemezdim...";
			link.l1.go = "rocur_96";
		break;
		
		case "rocur_96":
            dialog.text = ""+pchar.name+", Tyrex’in pis işlerini başkalarına yaptırdığını görmüyor musun? Gerçekten o hazineyi bulma işini sana verirdi, eğer kendisi yapabilseydi? Tabii ki hayır! Eminim önce kendisi denedi, işi berbat edince de seni çağırdı ki işi sen bitir diye. Sen haftalarca denizde kafa patlatıp, dövüşüp, kendi hayatını riske atarken, o alçak ve iğrenç dört gözlü arkadaşı La Vega’daki fahişeyle oyalanıyordu. Üstelik bunun için de çeyrek milyon peso aldı. Hem de öylece\nSence köpeği Leprechaun’u Merida baskınında bize yardım etsin diye mi gönderdi? Hayır, sadece kendi çıkarlarının korunduğundan emin olmak istedi. Marcus’un kendi başına yapabileceği her şeyi ya tek başına ya da Cutlass’lar, Kel’ler, Leprechaun’lar ve ona üç kuruşa çalışan diğer aptallarla birlikte yapar. Senin ve benim gibi insanlar ise, Marcus’un kendi başına altından kalkamayacağı işleri üstleniriz\nOnun için yaptığın işleri hatırla. Bir düşün, senden ne kadar para kazandı. Ben bu işten bıktım artık. Şimdi param var, güzel bir korvetim ve sadık bir tayfam... Bundan sonra serbestim. Jamaika’ya gidiyorum—belki orada bana bir korsanlık beratı verirler.";
			link.l1 = "Tyrex hakkında pek haklı olduğunu düşünmüyorum... Ama sana bol şans, Jean! Umarım Jamaika'da başarıya ulaşırsın.";
			link.l1.go = "rocur_97";
		break;
		
		case "rocur_97":
            dialog.text = "I will. Best of luck to you too, and think about what I've said. Being Marcus' lackey is not the best role for you; I know you are capable of much more. Well... farewell, brother! Godspeed!";
			link.l1 = "İyi avlar, Jean!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeAddComplete");
		break;
		
		case "rocur_98":
            dialog.text = ""+pchar.name+", söyle bakalım, nasıl oldu da bu kadar zamanı ormanda harcadık? Şimdi bütün planım mahvoldu. Eh... Hoşça kal, dostum...";
			link.l1 = "Heh...";
			link.l1.go = "rocur_99";
		break;
		
		case "rocur_99":
            DialogExit();
		    LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 10.0);
			sld.lifeday = 0;
			Group_DeleteGroup("RocurSeaGroup");
			AddQuestRecord("Roger_4", "18");
			CloseQuestHeader("Roger_4");
		break;
		
		case "rocur_100":
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaZloVariant"))
			{
				dialog.text = "Gitme vakti, çocuklar. Vay canına Prens, beni şaşırttın. Bütün bir şehri yaktın ama iş ciddiye binince elini kirletmekten kaçındın.";
				link.l1 = "Şehrin yakılmasını emretmedim!";
				link.l1.go = "rocur_101";
			}
			else
			{
				dialog.text = "Ayrılma vakti, çocuklar. Lucas, sen kaçırdın. Prens işi harika halletti – üstüne güzel de kazanç sağladı!";
				link.l1 = "Şehir ne olacak, yakışıklı?! Söz verdim!";
				link.l1.go = "rocur_102";
			}
			sld = CharacterFromID("Lepricon");
			CharacterTurnToLoc(sld, "reload", "reload3");
		break;
		
		case "rocur_101":
            dialog.text = "En azından onu kurtarmaya çalışmadın. Yoksa adamlarımız önce seni doğrardı. Onlar için zor bir gündü. Biraz rahatlamayı hak ettiler. Buna alışacaksın. Sende bunun tüm özellikleri var.";
			link.l1 = "Uyarın için sağ ol, ama ben senden bir tavsiye istemedim. Hadi gidelim.";
			link.l1.go = "rocur_103";
		break;
		
		case "rocur_102":
            dialog.text = " Şaka yapıyorsun sandım. Neyse... fazla acele ettin. Şehir bitti artık. Kıyı Kardeşliği işe koyuldu mu hep böyle olur. Alışırsın.";
			link.l1 = "Emin değilim, ama peki, gidelim.";
			link.l1.go = "rocur_103";
		break;
		
		case "rocur_103":
            DialogExit();
			LAi_SetPlayerType(pchar);
			DeleteAttribute(pchar, "questTemp.lockedMusic");
			EndQuestMovie();
			locCameraTarget(PChar);
			locCameraFollow();
			sld = characterFromId("Tagofa");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			Mtraxx_MeridaCheckOurWarriors();
			AddQuestRecord("Roger_5", "12");
		break;
		
		case "rocur_104":
            dialog.text = "Dostum... az önce neydi o?";
			link.l1 = "Ne, anlamadın mı? Seni satın aldım. Bir keresinde İspanyollara ulaşabildiğimi söylemiştin, ben de bunu kullandım.";
			link.l1.go = "rocur_105";
		break;
		
		case "rocur_105":
            dialog.text = "Anladım - aptal değilim. Ama başka bir plan üzerinde çalışmıyor muyduk?";
			link.l1 = "Bak, Cutlass'la ben düşündük ki, bir isyan ya da kovalamaca sırasında ölmen içimize sinmezdi, bu yüzden seni doğrudan satın almaya karar verdik.";
			link.l1.go = "rocur_106";
		break;
		
		case "rocur_106":
            dialog.text = "Hah, bana hakaret etme. Sonuçta ben Terrax'ın kaptanlarından biriyim. Kılıç kullanmayı iyi bilirim.";
			link.l1 = "Buna hiç şüphem yok, ama özgür olduğun için gerçekten üzgün müsün?";
			link.l1.go = "rocur_107";
		break;
		
		case "rocur_107":
            dialog.text = "Hayır, hayır - minnettarım. Sadece... bunca altını harcamak biraz fazla olmadı mı? Düşündükçe midem bulanıyor. Öte yandan, plantasyon sahibi cilalanmış gümüş bir tepsi gibi parlıyordu.";
			link.l1 = "Evet, 'Yüzyılın Anlaşması', gerçekten de öyle. Biraz can yakıyor, elbette. Ama zaman altından daha değerli, Jean. Hepiniz için tabanca ve ilaç aramak...";
			link.l1.go = "rocur_108";
		break;
		
		case "rocur_108":
            dialog.text = " Minnettarım, ama dostum, kusura bakma, sen de biraz safmışsın. Adamlarımın kılıçla pek arası yok dedim ya. Ama tetiği herkes çekebilir. Herhangi bir tabanca ve ilaç getirebilirdin ambarından, pala ve balta gibi - seçici değiller.";
			link.l1 = "Hmm, açıkçası, bunu düşünmemiştim... Neyse, hadi gidelim – Cutlass muhtemelen sabırsızlanıyordur.";
			link.l1.go = "rocur_109";
		break;
		
		case "rocur_109":
			DialogExit();
			DoFunctionReloadToLocation("Shore37", "goto", "goto6", "Mtraxx_PlantPlantVykup_3");
		break;
		
		// Люк Лепрекон
		case "lepricon":
            dialog.text = "Selamlar, kaptan "+GetFullName(pchar)+" . Hizmetinizdeyim, Cüce Luke! Güney Main'in ormanlarına gideceğimiz söylendi bana.";
			link.l1 = "Kesinlikle. Sandallara binin, hemen ayrılıyoruz.";
			link.l1.go = "lepricon_1";
		break;
		
		case "lepricon_1":
            dialog.text = "Eski bir korsan olarak sana bir tavsiye vereyim, kaptan. Selva'ya doğru gidiyoruz, kesinlikle yerlilerle karşılaşacağız. Onlara hediye götürmeyi unutma. Yerlilerin savaşçıları güzel tabancalara, özellikle düello tabancalarına bayılır. Ayrıca pusula ve dürbün gibi eşyaları da büyülü şeyler olarak görürler, çok hoşlarına gider.\nKadınları ise ucuz takılara, aynalara ve tarak gibi süslü ıvır zıvırlara ilgi duyar. Eğer onlarla çatışırsak, kartuşlu tüfekler ve arkebüzler kullan; saçma atışı, zırh giymeyen düşmanlara karşı çok etkilidir. Yerleşime gelince, kağıt kartuşla ateş edebilen silahlar kullanmanı öneririm.";
			link.l1 = "Çok iyi, Luke. Sözlerin aklımda. Gemimize hoş geldin.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_MeridaSail");
		break;
		
		case "lepricon_2":
            dialog.text = "See the chieftain as soon as we reach the village. And bring gifts, it's pointless otherwise. Make sure to ask if anyone among his people knows about secret passages in the jungles ahead, and ask for those who have no fear of travelling. I am coming with you; address me if you face any difficulties.";
			link.l1 = "Hadi gidelim! Jean, Luc - beni takip edin!";
			link.l1.go = "exit";
			npchar.greeting = "Lepricon_02";
			AddDialogExitQuestFunction("Mtraxx_MeridaSeekVillage");
		break;
		
		case "lepricon_3":
            dialog.text = "Bir sorunuz var mı, kaptan?";
			link.l1 = "Şimdilik yok, Luke.";
			link.l1.go = "lepricon_3x";
			if (pchar.questTemp.Mtraxx == "merida_advice")
			{
				link.l1 = "Evet! Şefleriyle konuştum, ona hediyeler verdim, sonra da halkını bir toplantıya çağırdı. Bazıları Merida'ya nasıl gidileceğini biliyor, ama hiçbiri gitmek istemiyor—Caponglar denen başka bir kabileden korkuyorlar. O Caponglar yerel halkı ödleri patlayana kadar korkutuyor. O herif, yolu kendi başımıza bulmamızın imkânsız olduğunu ve tutabileceğimiz bir rehber olmadığını söylüyor. Şimdi ne yapacağız, ha?!";
				link.l1.go = "lepricon_4";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Potion") && GetCharacterItem(pchar, "potion3") >= 12)
			{
				link.l2 = "Yanımda panzehirler var.";
				if (GetCharacterItem(pchar, "potion3") > 42) link.l2.go = "lepricon_7";
				else link.l2.go = "lepricon_6";
			}
		break;
		
		case "lepricon_3x":
           DialogExit();
		   npchar.dialog.currentnode = "lepricon_3";
		break;
		
		case "lepricon_4":
            dialog.text = "Hmm, anlıyorum... Kaptan, bilmelisiniz ki korkaklık çoğu zaman açgözlülükle yenilir. O kadar cömert bir ödül vaat edin ki, adam işi kabul etsin... Aslında biliyor musunuz? Daha kurnazca bir yol deneyin – kadınlarını kullanın. Onlara hediyeler verin ve adamları hakkında sorular sorun, büyük ihtimalle aradığımız rehberi bulursunuz. Kocasının yardımı karşılığında ona boncuklar ve aynalar yığınları vaat edin. Cömert olun ve bol bol söz verin, onları ikna edin.";
			link.l1 = "Heh! Eh, en azından denemeye çalışırım, ama işe yarar mı emin değilim...";
			link.l1.go = "lepricon_5_1";
			DelLandQuestMark(npchar);
		break;
		
		case "lepricon_5_1":
            dialog.text = "Aslında başka bir seçenek daha var... Ama pek iyi bir seçenek sayılmaz, ne demek istediğimi anlıyorsan.";
			link.l1 = "Başka bir seçenek mi var? Anlat bakalım! Hintli kadınların yanına gidip kocalarını bize katılmaya ikna etmeleri için yalvarmak pek içime sinmiyor.";
			link.l1.go = "lepricon_5_2";
		break;
		
		case "lepricon_5_2":
            dialog.text = "Bu seçenek kadar eski bir şey yok. Onlara Kaponglardan çok senden korkmaları gerektiğini göster. Biliyorsun... Şefe korsanlarının köydeki tüm kadınlara, özellikle de karısına ve kızlarına neler yapabileceğini anlatabilirsin. Hatta işkenceyle tehdit etmeyi bile ekleyebilirsin.\nNeyse, bu Kızılderililere senden korkmaları için bir yol bulacağına eminim. Açıkçası, ben bu yolu pek sevmiyorum, bunun da sebepleri var.";
			link.l1 = "Nedenler mi? Mesela ne gibi? Bana sorarsan, bu oldukça etkili ve doğrudan bir çözüm gibi görünüyor.";
			link.l1.go = "lepricon_5_3";
		break;
		
		case "lepricon_5_3":
            dialog.text = "Her şeyden önce, bu olaydan sonra kasabanın gözdesi olmayacağız. Bir tuzağa ya da başka tatsız bir duruma düşebiliriz. Ve ayrıca... bu bana doğru gelmiyor. Silahlı düşmanlarla savaşmak başka, kadınlara tehdit savurmak bambaşka bir şey. Yerlilerle daha... diplomatik bir yol bulmamızı öneririm.";
			link.l1 = "Anladım, düşüneceğim. Belki birkaç boncukla bir hanımı tavlamayı denerim... Ya da belki de şefin kızlarını biraz yaratıcı yollarla kızdırmanın bir yolunu bulurum, haha!";
			link.l1.go = "lepricon_5";
		break;
		
		case "lepricon_5":
            dialog.text = "Bir şey daha, Kaptan, reisin dediğine göre ormanda düşmanca bir Kızılderili kabilesiyle karşılaşabiliriz. Büyük ihtimalle bunlar sadece küçük bir yamyam grubu, ama tedbiri elden bırakmamakta fayda var. Eğer savaşçı bir kabileyse, silahlarını zehirleyeceklerdir, bu yüzden adamlarınıza panzehir temin ettiğinizden emin olun.   Ben ve adamlarım yanımızda bolca iksir taşırız. Korsanlarınıza gelince... Panzehirleri bana getirin, ben de adamlarınız arasında dağıtılmasını sağlarım. Bunun için en az bir düzine iksire ihtiyacım var. Kendin ve subayların için de mutlaka birkaç tane getir.";
			link.l1 = "Pekala. Panzehirleri getireceğim.";
			link.l1.go = "lepricon_5x";
		break;
		
		case "lepricon_5x":
           DialogExit();
		   npchar.dialog.currentnode = "lepricon_3";
		   pchar.questTemp.Mtraxx = "merida_advice2";
		   pchar.questTemp.Mtraxx.Merida.Women = "true";
		   pchar.questTemp.Mtraxx.Merida.Potion = "true";
		   AddQuestRecord("Roger_5", "8");
		   sld = characterFromId("Hayamee");
		   LAi_CharacterEnableDialog(sld);
		   AddLandQuestMark(sld, "questmarkmain");
		  // LocatorReloadEnterDisable("Shore_ship3", "boat", false); 
		   bQuestDisableMapEnter = false;
		   DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");// выпустим в море
		   SetFunctionTimerCondition("Mtraxx_MeridaPotionLate", 0, 0, 10, false); // таймер, чтобы не ходил долго
		break;
		
		case "lepricon_6":
			i = GetCharacterItem(pchar, "potion3");
			RemoveItems(pchar, "potion3", i);
			pchar.questTemp.Mtraxx.Merida.Antidote = i;
            dialog.text = "Pekala. Onları bana ver. Gerisini ben hallederim.";
			link.l1 = "Orada...";
			link.l1.go = "lepricon_8";
		break;
		
		case "lepricon_7":
			RemoveItems(pchar, "potion3", 42);
			pchar.questTemp.Mtraxx.Merida.Antidote = 42;
            dialog.text = "Kırk iki iksir yeterli olacak. Geri kalanını kendine saklamalısın.";
			link.l1 = "Pekala...";
			link.l1.go = "lepricon_8";
		break;
		
		case "lepricon_8":
            DialogExit();
		    npchar.dialog.currentnode = "lepricon_3";
			DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Potion");
		break;
		
		case "lepricon_9":
            dialog.text = "Kaptan, yerlileriniz - Hayami ve Tagofa - onlara söz verdiğiniz hediyeleri getirmekte geciktiğiniz için fazla beklediler ve başka bir köye gidip kasheeri içip dans etmeye başladılar. Sizin iş yapma tarzınızın bize bir faydası olmayacak gibi hissediyorum. Üzgünüm, ama artık bu işte yoksunuz. Picard sefere liderlik edecek.";
			link.l1 = "Hepinizin canı cehenneme o zaman!";
			link.l1.go = "exit";
			AddQuestRecord("Roger_5", "19");
			AddDialogExitQuestFunction("Mtraxx_MeridaHayameeFail");
		break;
		
		case "lepricon_10":
            dialog.text = "Kaptan, bu da neyin nesi? Hiçbir şey için çok fazla zaman harcadık! Senin iş yapış tarzının bize faydası olmayacağına dair bir his var içimde. Üzgünüm, ama artık bu işte yoksun. Picard seferi yönetecek.";
			link.l1 = "Hepinizin canı cehenneme o zaman!";
			link.l1.go = "exit";
			AddQuestRecord("Roger_5", "20");
			AddDialogExitQuestFunction("Mtraxx_MeridaHayameeFail");
		break;
		
		case "lepricon_11":
            dialog.text = "Kaptan, ne oluyor? Deri ve tahta bulmak için on günün vardı. Şurada, çok uzakta olmayan Maracaibo kasabası var! Senin iş yapma tarzının bize hiç faydası olmayacak gibi hissediyorum. Üzgünüm ama artık bu işte yoksun. Seferi Picard yönetecek.";
			link.l1 = "Hepinizin canı cehenneme o zaman!";
			link.l1.go = "exit";
			AddQuestRecord("Roger_5", "20");
			AddDialogExitQuestFunction("Mtraxx_MeridaHayameeFail");
		break;
		
		case "lepricon_12":
            dialog.text = "Captain, I'm sorry, but I was supposed to be in La Vega long ago, as were you, actually. You must have forgotten about Marcus and me. Anyway, I'm leaving. You should keep doing whatever it is you're doing, and I'll explain everything to Marcus. Farewell, it's a pity; I thought better of you.";
			link.l1 = "Hıh...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_MeridaReturnFail");
		break;
		
		case "lepricon_13":
			PlaySound("VOICE\English\LE\Leprikon\Lepricon_03.wav");
            dialog.text = "Yani, anladığım kadarıyla aranızda bir kavga çıkmış. Ganimeti paylaşamamışsınız, değil mi Charlie Prince?";
			link.l1 = "Leprechaun? Buradasın... Gerçi pek şaşırmadım. Evet, o açgözlü herifler Kodeks'e tükürdüler ve beni öldürmeye kalktılar.";
			link.l1.go = "lepricon_14";
			QuestPointerDelLoc("Judgement_dungeon_05", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_04", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_03", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_02", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_01", "quest", "lepricon");
		break;
		
		case "lepricon_14":
            dialog.text = "Evet, seni fena benzetmişler Prens. Sırılsıklam bok gibi görünüyorsun\nKod hakkında ne demiştin? Sana bir açıklayayım: Bu Kod'un sözde koruyucusu Marcus'la çalıştım ben. O kadar çok adamın buna tükürdüğünü gördüm ki, saymaya kalkışmam bile. Bazıları bunun bedelini ağır ödedi. Bazılarıysa hiç ödemedi\nİstediğini yapabilirsin, yeter ki ödül buna değsin. Hele bir de kimse bakmıyorsa.";
			link.l1 = "Yani... sen de hazine için mi buradasın?";
			link.l1.go = "lepricon_15";
		break;
		
		case "lepricon_15":
            dialog.text = "Böyle aptalca bir soru. Burada, anavatanım Hispaniola'dan bu kadar uzakta başka ne yapıyor olabilirim ki? Gerçi, sonuçta, hepinizden daha akıllıyım: Sizin çürümüş korsan doğanızı biliyorum. Sadece bekledim, siz sıçanların birbirinizi parçalayarak geride yalnızca bir düşman bırakmasını sağladım, ama o da yaralı ve yorgun.";
			link.l1 = "Düşman mı? Hamini̇ni̇n Yasası'na böyle mi uyuyorsun?! Bunun için insanları öldürüyor!";
			link.l1.go = "lepricon_16";
		break;
		
		case "lepricon_16":
            dialog.text = "Ben Code Prince'e tabi değilim, korsan da değilim. Bir gemim bile yok – buraya gelmek için bir tekne kiralamak zorunda kaldım. Kısacası ben sadece bir bucaneerim. Avcıyım, bizon avlarım ve buccan yaparım. Biz Fransız bucaneerlerin geçimlerini mahvettiğimizi iddia eden lanet İspanyollar yüzünden Marcus'tan destek ve koruma aradım. Bazen onun işlerinde ona bu yüzden yardım ediyorum.\nHer ne kadar korsan olmasam da, adamlarım ve ben iyi dövüşürüz, bizi iş başında gördün.";
			link.l1 = "Birlikte baskın yaptık ve savaştık, Leprechaun. Birbirimizin arkasını kolladık, hayatımızı riske atıp birbirimizi kurtardık. Bunların senin için hiçbir anlamı yok mu?";
			link.l1.go = "lepricon_17";
		break;
		
		case "lepricon_17":
			PlaySound("VOICE\English\LE\Leprikon\Lepricon_04.wav");
            dialog.text = "Sana karşı dürüst olacağım, Prens: Seni hiç sevmedim. Sen bir ukalasın. Saygısız bir gençsin, içkiyi ve düşmüş kadınları seven, Tyrex için birkaç kârlı iş yapıp kendini büyük bir korsan sanan biri.\nÜstelik, doğuştan bir cellatsın. Cartagena'nın sana Kardeşlik içinde daha fazla ağırlık kazandırdığını mı sanıyorsun? Ha-ha, yok artık, ancak senin gibi canavarların arasında.";
			link.l1 = "Ah, bu gerçekten komik! Ha-ha-ha, bunu söyleyen tam bir melekmiş gibi! Seni yaşlı herif!";
			link.l1.go = "lepricon_18";
		break;
		
		case "lepricon_18":
            dialog.text = "Bence artık her şeyi hallettik. Bu maskaralığa son vermenin vakti geldi. Cehennemdeki şeytanlar seni beklemekten fazlasıyla yoruldular.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionLepriconFight");
		break;
		
		case "lepricon_19":
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaZapugivanieIndeets"))
			{
				dialog.text = "Beğendin mi, hmm?";
				link.l1 = "Uzak dur!";
				link.l1.go = "lepricon_20";
			}
			else
			{
				dialog.text = "Peki, ne düşünüyorsun?";
				link.l1 = "Bu komik değil, Leprechaun. Ne oluyor böyle?! Katliam emri vermedim ben! Sence de bu fazla değil mi?! Terrax bundan hiç memnun olmayacak!";
				link.l1.go = "lepricon_24";
			}
		break;
		
		case "lepricon_20":
            dialog.text = "O zaman neden suçlu gibi bakıyorsun? Hoşuna gitmiyor mu? Söyleyeyim sana – işler daha da kötüleşecek. Bugünkü katliam sırf öyle bir gün diye mi oldu sanıyorsun? Hah, tabii. Bu onlar için sıradan bir şey. Picard'ın yüzü bile kıpırdamadı. Onlar için bu, sadece sevdikleri işi yaparken geçen bir gün daha.";
			link.l1 = "Peki ya sen? Sadece uğrayıp mı geçiyorsun?";
			link.l1.go = "lepricon_21";
		break;
		
		case "lepricon_21":
            dialog.text = "Ben korsan değilim. Ve bugünkü olayların bir parçası olmayı da istemezdim. Ve... eğer Merida'nın kararmış topraklarında kadın bedenlerini görmek seni bu kadar rahatsız ettiyse, neden Kızılderililere karşı öyle davrandın, Prens?";
			link.l1 = "Ne yapmamı bekliyordun? Her şeyi bırakıp Marcus'un önüne diz çöküp özür mü dilemeliydim?";
			link.l1.go = "lepricon_22";
		break;
		
		case "lepricon_22":
            dialog.text = "Ben de senin bunu tamamen benimsediğini, artık Tirax'ın kaptanları gibi düşünmeye ve davranmaya başladığını sanmıştım. Ama yok, ha! Sen bu işlere fazla yumuşaksın. En iyisi payını Marcus'a verip kuyruğunu kıstırıp gitmek olur. Bu iş sana göre değil.";
			link.l1 = "Benim adıma karar vermek sana düşmez, Leprechaun. Ve beni aşağılamaya da hiç hakkın yok. Payımdan kimseye vazgeçmem. Onu Terrax'la adilce paylaşacağım.";
			link.l1.go = "lepricon_23";
		break;
		
		case "lepricon_23":
            dialog.text = "Tabii. Ama bayılmadan önce gitsek iyi olur.";
			link.l1 = "Bu komik değil, kahretsin.";
			link.l1.go = "lepricon_30";
		break;
		
		case "lepricon_24":
            dialog.text = "O halde onu pek iyi tanımıyorsun. Yine de, bugünkü olaylar seni mutlu etmediyse, sana sunacaklarımı dinle.";
			link.l1 = "Bundan sonra daha ne sunabilirsin ki?!";
			link.l1.go = "lepricon_25";
		break;
		
		case "lepricon_25":
            dialog.text = "Dinlemeye biraz özen göstersen iyi olur, çocuk.";
			link.l1 = "Hmm, Lucas, üslubunu beğenmedim ama peki, devam et.";
			link.l1.go = "lepricon_26";
		break;
		
		case "lepricon_26":
            dialog.text = "Bunu karşılayabilirim - senden daha uzun yaşadım, Prens. Yani sadece nişan almakta değil, gözlemde de iyiyim. Ne fark ettiğimi bilmek ister misin?";
			link.l1 = "Sadece söyle!";
			link.l1.go = "lepricon_27";
		break;
		
		case "lepricon_27":
            dialog.text = "Buraya ait değilsin. Evet, iyisin. İlerleme kaydediyorsun. Ama bu sadece güçlü bir kaptan olduğun için, yoksa burası gerçekten senin yerin olduğu için değil. Terrax'a nasıl yöneldin, nedenini de bilmiyorum, ama bana güven, burası senin yolun değil.";
			link.l1 = "Bir amacım var... Ne olduğunu sana söyleyemem.";
			link.l1.go = "lepricon_28";
		break;
		
		case "lepricon_28":
            dialog.text = "Ve ona biraz daha yaklaştın mı?";
			link.l1 = "Henüz değil.";
			link.l1.go = "lepricon_29";
		break;
		
		case "lepricon_29":
            dialog.text = "Eh, bugün bile seni yaklaştıramadıysa, burada daha fazla kazanacak bir şey yok. İyi bir adamsın, Prens. Yerlilere insan gibi davrandın. Sonunda kendini bizimle burada bulman ironik. Benim tavsiyem: payını Terrax'a ver, başını belaya sokma, ve bütün bu işlerden uzak dur – ruhunu kurtarabilecekken kurtar.";
			link.l1 = "Düşüneceğim.";
			link.l1.go = "lepricon_30";
		break;
		
		case "lepricon_30":
			DialogExit();
			locCameraFromToPos(21.35, 1.54, 0.05, true, 25.55, 0.46, -0.91);
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaZloVariant"))
			{
				PlaySound("People Fight\PistolShot.wav");
				DoQuestFunctionDelay("Mtraxx_MeridaGorit_5", 2.0);
			}
			else
			{
				DoQuestFunctionDelay("Mtraxx_MeridaGorit_5", 0.5);
			}
		break;
		
		// Тагофа - проводник к Мериде
		case "tagofa":
            dialog.text = "Tagofa seni selamlıyor, denizin oğlu. Dağlardaki İspanyol yerleşimine giden yolu sana göstermemi ister misin?";
			link.l1 = "Doğru. Senin bizim dilimize hakim olduğunu görüyorum, diğer insanlarının aksine.";
			link.l1.go = "tagofa_1";
		break;
		
		case "tagofa_1":
            dialog.text = "Tagofa sık sık Yalanaui ile iş yapardı... Yolculuğumuzun büyük kısmında nehirden gideceğiz. Uzun teknelere ihtiyacın olacak. Onların var mı?";
			link.l1 = "Öyle mi? Bir süreliğine ödünç alabiliriz onları...";
			link.l1.go = "tagofa_2";
		break;
		
		case "tagofa_2":
            dialog.text = "Köyümüz küçük, çok az sandalımız var ve hepsi sadece balıkçılık için işe yarıyor. Şimdi ise, uzun bir yolculuğa dayanacak sağlam sandallara ihtiyacımız var, tıpkı sizin gemilerinizdeki gibi.";
			link.l1 = "Hmm... O zaman altı sandal gerekecek. Gemide o kadar yok.";
			link.l1.go = "tagofa_3";
		break;
		
		case "tagofa_3":
            dialog.text = "O zaman yapın onları. Siz beyazlar, koca gemilerinizi karada onarabiliyorsanız, birkaç sandal da yapabilirsiniz herhalde.";
			link.l1 = "Heh, galiba haklısın, Tagofa. Bizi nehre götür, umarım buradan çok uzakta değildir?";
			link.l1.go = "tagofa_4";
		break;
		
		case "tagofa_4":
            dialog.text = "Değil. Beni takip et.";
			link.l1 = "...";
			link.l1.go = "tagofa_5";
		break;
		
		case "tagofa_5":
           DialogExit();
		   chrDisableReloadToLocation = true;
		   npchar.dialog.currentnode = "tagofa_6";
		   LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Mtraxx_MeridaGotoRiver", 5.0);
		break;
		
		case "tagofa_6":
            dialog.text = "İşte sana bahsettiğim nehir burası. Yolculuğumuza buradan başlayacağız. Sen tekneleri inşa et, sonra da yola koyulacağız.";
			link.l1 = "Anladım, Tagofa. Bitince sana haber vereceğim.";
			link.l1.go = "tagofa_7";
		break;
		
		case "tagofa_7":
            DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.dialog.currentnode = "tagofa_8";
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.questTemp.Mtraxx = "merida_boats";
			pchar.questTemp.Mtraxx.Boats = "true";
			chrDisableReloadToLocation = false;
			DoQuestCheckDelay("TalkSelf_Quest", 2.0);
			// Лепрекона - гулять
			sld = characterFromId("Lepricon");
			sld.dialog.currentnode = "lepricon_3";
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, true);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			SetFunctionTimerCondition("Mtraxx_MeridaBoatLate", 0, 0, 10, false); // таймер, чтобы не ходил долго
		break;
		
		case "tagofa_8":
            dialog.text = "Kayıklar hazır mı, beyaz reis?";
			link.l1 = "Evet. Adamlarım onları birazdan gemiye alacak.";
			link.l1.go = "tagofa_9";
		break;
		
		case "tagofa_9":
            dialog.text = "Çok iyi. Benimle birlikte ilkine bin. Tagofa yolu gösterecek.";
			link.l1 = "";
			link.l1.go = "tagofa_10";
		break;
		
		case "tagofa_10":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "Mtraxx_MeridaRiverTrip", -1);
			chrDisableReloadToLocation = true;
		break;
		
		case "tagofa_11":
            dialog.text = "Nehir kısmı bitti. Buradan İspanyol yerleşimine çok uzak değiliz. İşte patika, ona sadık kalırsak kaybolmayız. Capong avcılarıyla dolu bir ormanı dolanmayı başardık, ama burası da onların toprağı. Dikkatli olmalıyız.";
			link.l1 = "Endişelenme. O pis suratlarını gösterdikleri anda hepsini yok edeceğiz.";
			link.l1.go = "tagofa_12";
		break;
		
		case "tagofa_12":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.mtraxx_merida_warning.win_condition.l1 = "locator";
			pchar.quest.mtraxx_merida_warning.win_condition.l1.location = "Serpentine2";
			pchar.quest.mtraxx_merida_warning.win_condition.l1.locator_group = "quest";
			pchar.quest.mtraxx_merida_warning.win_condition.l1.locator = "detector1";
			pchar.quest.mtraxx_merida_warning.function = "Mtraxx_MeridaWarning";
			chrDisableReloadToLocation = false;
		break;
		
		case "tagofa_13":
			StartQuestMovie(true, false, true);
            dialog.text = "";
			link.l1 = "Hey! Tagofa! Bak! Şu da ne... yolun ortasında? Bir Kızılderili şeyi gibi.";
			link.l1.go = "tagofa_14";
			locCameraFromToPos(7.63, 9.07, 11.73, true, 2.97, 9.02, 7.70);
			CharacterTurnToLoc(pchar, "quest", "quest1");
		break;
		
		case "tagofa_14":
            DialogExit();
			LAi_SetActorType(pchar);
			LAi_FadeLong("Mtraxx_MeridaWarningCutscene", "");
			locCameraSleep(true);
		break;
		
		case "tagofa_15":
            dialog.text = "Bu, Capongların işareti. Bir uyarı. Durmamızı ve daha ileri gitmememizi söylüyor. Caponglar bizi çoktan fark etti.";
			link.l1 = "Ya peki daha ileri gidersek? Bize saldırırlar mı?";
			link.l1.go = "tagofa_16";
		break;
		
		case "tagofa_16":
            dialog.text = "Evet, beyaz reis. Onlara tehditkâr görünüyorsun galiba, henüz bize saldırmadılar. Ama senin için bir işaret dikmişler.";
			link.l1 = "Tabelayı boş verin. İlerliyoruz... Herkes dikkat! Silah başına! Hazır olun! Tetikte kalın! Eğer bu vahşiler suratlarını gösterirse, hepsini öldüreceğiz!";
			link.l1.go = "tagofa_17";
		break;
		
		case "tagofa_17":
            DialogExit();
			EndQuestMovie();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.mtraxx_merida_capong.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_capong.win_condition.l1.location = "Merida_jungle_01";
			pchar.quest.mtraxx_merida_capong.function = "Mtraxx_MeridaPrepareCapongAttack";
		break;
		
		case "tagofa_18":
            dialog.text = "Beyaz reis ve adamları capongaları ezdi, Tagofa etkilendi. İspanyol şehri yakın. Bir şelale göreceğin bir vadi var. Tagofa İspanyollara gitmeyecek. Seni şelalenin yakınında bekleyeceğim.";
			link.l1 = "Pekâlâ. Devam edelim!";
			link.l1.go = "tagofa_19";
		break;
		
		case "tagofa_19":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			chrDisableReloadToLocation = false;
			pchar.quest.mtraxx_merida_exittown.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_exittown.win_condition.l1.location = "Merida_ExitTown";
			pchar.quest.mtraxx_merida_exittown.function = "Mtraxx_MeridaExitTown";
			Mtraxx_MeridaCheckOurWarriors();
			AddQuestRecord("Roger_5", "15");
		break;
		
		case "tagofa_20":
            dialog.text = "Geri döndük, beyaz reis. Tagofa sözünü tuttu.";
			link.l1 = "Teşekkür ederim, Tagofa. İyi iş çıkardın.";
			link.l1.go = "tagofa_21";
		break;
		
		case "tagofa_21":
            dialog.text = "Tagofa gitmeli. Hayami beni bekliyor. Elveda, denizin oğlu.";
			link.l1 = "İyi şanslar, ormanın oğlu. Eşine selamlarımı ilet. Ve bize yardım ettiğin için teşekkür ederim.";
			link.l1.go = "tagofa_22";
		break;
		
		case "tagofa_22":
            DialogExit();
			chrDisableReloadToLocation = false;
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.mtraxx_merida_final.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_final.win_condition.l1.location = "Shore_ship3";
			pchar.quest.mtraxx_merida_final.function = "Mtraxx_MeridaFinal";
			ChangeIndianRelation(7.0);
		break;
		
		// дозорный у Мериды
		case "merida_guard":
            dialog.text = "Hey! Sen kimsin ve ne istiyorsun?";
			link.l1 = "Merida'ya gitmemiz ve valinizle ya da onun yerine kimi koyduysanız onunla konuşmamız gerekiyor...";
			link.l1.go = "merida_guard_1";
		break;
		
		case "merida_guard_1":
            dialog.text = "Yabancıları Merida'ya almıyoruz. Defol!";
			link.l1 = "Dostum, iki gündür var gücümüzle kürek çektik, sonra da bir sürü Kızılderiliyle savaştık, öylece çekip gitmek için değil. Tekrar ediyorum, köyünüzün reisiyle konuşmak istiyorum! Ona bir... iş teklifimiz var, evet! Eğer hepimiz anlaşabilirsek, köyünüz zarar görmeden kalacak.";
			link.l1.go = "merida_guard_2";
		break;
		
		case "merida_guard_2":
            dialog.text = "Bana tehdit mi savuruyorsun, hırsız?";
			link.l1 = "Bunu nasıl anladın? Evet, doğru, tehdit ediyorum. Buraya ne için geldiysek ya huzur içinde alırız ya da zorla, ve köyünün kaderine karar verme onuru sana ait.";
			link.l1.go = "merida_guard_3";
		break;
		
		case "merida_guard_3":
            dialog.text = "Merida'ya asla giremeyeceksin, seni lanet korsan! Alarm! Düşman kapıda!";
			link.l1 = "Böylesine mantıksız bir centilmen...";
			link.l1.go = "merida_guard_4";
		break;
		
		case "merida_guard_4":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "", 10.0);
			DoQuestFunctionDelay("Mtraxx_MeridaHouseGuards", 5.0);
		break;
		
		// мэр Мериды
		case "merida_head":
            dialog.text = "Lanet olası haydutlar! Bizden ne istiyorsunuz?! Burası küçük, mütevazı bir yerleşim. Ne altınımız var ne de gümüşümüz! Bizi nasıl buldunuz ki?";
			link.l1 = "Ah, masum ve hiçbir şeyden haberi yokmuş gibi davranmayın, Ekselansları. Tüm dünya zaten opallerinizle ilgili dedikodularla çalkalanıyor.";
			link.l1.go = "merida_head_1";
		break;
		
		case "merida_head_1":
            dialog.text = "Ve sen bu tanrısız katliama... söylentiler yüzünden mi sebep oldun?! Kimseyi esirgemedin! Canavarlar... Bilmiş ol ki: madenler buradan çok uzakta. Burada kazanacak hiçbir şeyin yok. Git.";
			link.l1 = "Bu tanrısız katliamı sen başlattın. Siviller askerlerinle birlikte savaştı. Birkaç çıplak duvarı korumak için böyle anlamsız bir kahramanlığa asla inanmayacağım.";
			link.l1.go = "merida_head_2";
		break;
		
		case "merida_head_2":
            dialog.text = "Bu duvarları inşa etmek için ne kadar emek harcandığını biliyor musun? Dışarıdan usta tutmadık—her bir tuğlayı kendimiz koyduk. Buranın her sakini. Ben bile, şu ellerimle.";
			link.l1 = "Ne dokunaklı bir hikaye... Peki ya mobilyalar? Onları da kendiniz mi yaptınız? Ne güzel oyulmuş bir sandalye. Ve masa. Ve dolaplar. Bu lekeli meşe mi? Yoksa abanoz mu? 'Mütevazı bir yerleşim' için biraz fazla lüks değil mi, sizce de?";
			link.l1.go = "merida_head_3";
		break;
		
		case "merida_head_3":
            dialog.text = "Açgözlülük zihnini bulandırmış, hırsız.";
			link.l1 = "İşleri karmaşıklaştırmaya gerek yok, Sayın Vali. Yoksa pişman olursunuz.";
			link.l1.go = "merida_head_4";
		break;
		
		case "merida_head_4":
            dialog.text = "Beni işkenceyle mi korkutacaksın, lanet olası korsan? Yazık sana – ben Yüce Tanrı'ya inanırım. Haddini aşarsan, şehit olarak yükselirim.";
			link.l1 = "Hm-m...";
			link.l1.go = "merida_head_5";
		break;

		case "merida_head_5":
			StartInstantDialog("Mrt_Rocur", "merida_head_6", "Quest\Roger.c");
		break;
		
		case "merida_head_6":
            dialog.text = "Arkadaşım, o böyle konuşmayacak. Bunu bana bırak.";
			link.l1 = "Ha?";
			link.l1.go = "merida_head_7";
		break;
		
		case "merida_head_7":
            dialog.text = "O lanetli plantasyonda o kendini beğenmiş İspanyolların bana yaptıklarını hâlâ unutmadım. Sana da göstermekten memnuniyet duyarım, Prens. Hem birkaç hikaye de anlatırım. Sıkılmazsın.";
			link.l1 = "Ya kendini kaptırırsan ne olacak?";
			link.l1.go = "merida_head_8";
		break;
		
	case "merida_head_8":
            dialog.text = "Kibarca konuşmayacak. Onun gibilerini bilirim.";
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) >= 50 && GetSummonSkillFromName(pchar, SKILL_Leadership) >= 50)
			{
				link.l1 = "(Güvenilir) (Onur) (Liderlik) Bugünlük bu kadar kan yeter, Jean. Bunu kendim halledeceğim.";
				link.l1.go = "merida_head_dobro_1";
				Notification_Perk(true, "Trustworthy");
				Notification_Reputation(true, 50, "low");
				notification("Skill Check Passed", SKILL_Leadership);
			}
			else
			{
				if (!IsCharacterPerkOn(pchar, "Trustworthy")) Notification_Perk(false, "Trustworthy");
				if (sti(pchar.reputation.nobility) < 50) Notification_Reputation(false, 50, "low");
				if (GetCharacterSkill(pchar, SKILL_LEADERSHIP) < 50) notification("Skill Check Failed (50)", SKILL_LEADERSHIP);
			}
			link.l2 = "Yap. Ben karışmıyorum. İzlemeye de niyetim yok.";
			link.l2.go = "merida_head_zlo_1";
		break;
		
		case "merida_head_zlo_1":
            dialog.text = "Eğer sana borçlu olmasaydım, sana birkaç lafım olurdu... Kahretsin. Hadi git. Şimdi asıl işe koyulma zamanı.";
			link.l1 = "Kendini fazla yorma.";
			link.l1.go = "rocur_42";
		break;
		
		case "merida_head_dobro_1":
            dialog.text = "Dediğin gibi olsun, dostum. İzlemesi eğlenceli olacak.";
			link.l1 = "Henüz gülümsemeye kalkma.";
			link.l1.go = "merida_head_dobro_2";
		break;
		
		case "merida_head_dobro_2":
			StartInstantDialog("Merida_Head", "merida_head_dobro_3", "Quest\Roger.c");
		break;
		
		case "merida_head_dobro_3":
            dialog.text = "Bunu kendi başına, kan dökmeden halledeceğini mi söylüyorsun, lanet olası hırsız? Havadan taş yaratacak bir lafın yok ki!";
			link.l1 = "En iyisi ortaya çıksınlar, Vali. Yoksa şehri yerle bir eder, senden başkasını sağ bırakmayız. Bu çözümü hiç istemem, ama davam için onurumu feda etmeye hazırım. Senin görevin ise Merida'nın sivillerini, hayatta kalan askerlerini ve işçilerini korumak. Yoksa onların acısı pahasına 'şehit olup yücelmeyi' mi tercih edersin? Bana pek de ilahi gelmiyor bu.";
			link.l1.go = "merida_head_dobro_4";
		break;
		
		case "merida_head_dobro_4":
            dialog.text = "Lanet olsun sana...\nSandıkta... Orada. Yalnızca kasaba halkını bağışla!";
			if (GetSummonSkillFromName(pchar, SKILL_Sneak) >= 50)
			{
				link.l1 = "(Gizlice) Sandığın içindeki her şey tamam mı?";
				link.l1.go = "merida_head_dobro_vnimatelnost_1";
				notification("Skill Check Passed", SKILL_Sneak);
			}
			else
			{
				link.l1 = "Sözümde dururum. Elveda, Vali.";
				link.l1.go = "merida_head_dobro_5";
				notification("Skill Check Failed (50)", SKILL_SNEAK);
			}
		break;
		
		case "merida_head_dobro_vnimatelnost_1":
            dialog.text = "Cehenneme kadar yolun var!\nSandığın da sahte bir tabanı varmış. Her şeyi al!!";
			link.l1 = "...";
			link.l1.go = "merida_head_dobro_vnimatelnost_2";
			pchar.questTemp.Mtraxx_MeridaKamushki = true;
		break;
		
		case "merida_head_dobro_vnimatelnost_2":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto2", "Mtraxx_MeridaOpenChest", -1);
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
		break;
		
		case "merida_head_dobro_vnimatelnost_3":
            dialog.text = "Güzel iş, Prens. Seni küçümsediğim için üzgünüm.";
			link.l1 = "Memnun musun?";
			link.l1.go = "merida_head_dobro_7";
		break;
		
		case "merida_head_dobro_5":
			StartInstantDialog("Mrt_Rocur", "merida_head_dobro_6", "Quest\Roger.c");
		break;
		
		case "merida_head_dobro_6":
            dialog.text = "Güzel, Prens.";
			link.l1 = "Memnun musun?";
			link.l1.go = "merida_head_dobro_7";
		break;
		
		case "merida_head_dobro_7":
            dialog.text = "More than. But... you'll see for yourself. You go ahead; I'll dig around a little more.";
			link.l1 = "...";
			link.l1.go = "rocur_43";
		break;
		
		/*case "merida_head_99999":
            DialogExit();
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto2", "Mtraxx_MeridaGiveJewelry", -1);
		break;*/
		
		case "merida_head_sleep":
            dialog.text = "Taşları aldıktan sonra kasabadan ayrılacağına söz vermiştin... Şimdi taşlar sende ve adamların evlerimizi ateşe verdi! Sen yalancı ve alçak bir korsansın! Umarım cehennemin alevleri de senin için bu kadar yakıcı olur!!!";
			link.l1 = "";
			link.l1.go = "exit";
			locCameraFromToPos(19.18, 1.28, -0.28, true, 24.88, 1.62, -1.19);
			AddDialogExitQuest("Mtraxx_RetributionSleep2");
		break;
		
		// капитан пинаса Китти
		case "kittycap":
            dialog.text = TimeGreeting()+", iyi beyefendi. Sizi buraya getiren nedir?";
			link.l1 = "Ben Tyrex'ten geliyorum. Geminizi Bridgetown'a kadar eşlik etmem söylendi. Hazır mısınız?";
			link.l1.go = "kittycap_1";
		break;
		
		case "kittycap_1":
            dialog.text = "Nihayet! Evet, mürettebatım hemen yelken açmaya hazır!";
			link.l1 = "Harika. Yelkenleri hazırlayın, kaptan. Harekete geçiyoruz!";
			link.l1.go = "kittycap_2";
		break;
		
		case "kittycap_2":
		    DialogExit();
            LAi_CharacterDisableDialog(npchar);
			Group_DelCharacter("Mtr_Kitty", "Mtr_KittyCap");
			SetCharacterRemovable(npchar, false);
			npchar.CompanionEnemyEnable = false; //всегда друзья
			LAi_SetImmortal(npchar, false);
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = MAX_LOYALITY;
		    pchar.quest.mtraxx_ignasio_sail.win_condition.l1 = "location";
			pchar.quest.mtraxx_ignasio_sail.win_condition.l1.location = "Bridgetown_town";
			pchar.quest.mtraxx_ignasio_sail.function = "Mtraxx_IgnasioArrive";
			SetFunctionTimerCondition("Mtraxx_IgnasioTimeOver", 0, 0, 30, false);
			pchar.quest.mtraxx_ignasio_sinkkitty.win_condition.l1 = "NPC_Death";
			pchar.quest.mtraxx_ignasio_sinkkitty.win_condition.l1.character = "Mtr_KittyCap";
			pchar.quest.mtraxx_ignasio_sinkkitty.function = "Mtraxx_IgnasioKittySink";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		case "kittycap_3":
            dialog.text = "Bana yardım ettiğiniz için teşekkür ederim, kaptan! Sizin yanınızda kendimi kalenin duvarlarının ardında gibi güvende hissettim.";
			link.l1 = "Hah, lafı bile olmaz dostum! Her şey Marcus'a ait. Sana bol şans, dostum!";
			link.l1.go = "kittycap_4";
		break;
		
		case "kittycap_4":
            DialogExit();
			npchar.lifeday = 0;
			RemoveCharacterCompanion(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 30.0);
			Mtraxx_IgnasioCreateMarko();
			AddCharacterExpToSkill(pchar, "Sailing", 200);
		break;
		
		// Игнасио Марко
		case "ignasio":
            PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_01.wav");
			dialog.text = "Kahraman kaptana selamlar! Kendimi tanıtmama izin verin – Torero gemisinin Ignacio Marco’su, İngiltere adına çalışan bir korsanım.";
			link.l1 = TimeGreeting()+", dostum. Kaptan "+GetFullName(pchar)+" hizmetinizdeyim. Size nasıl yardımcı olabilirim?";
			link.l1.go = "ignasio_1";
		break;
		
		case "ignasio_1":
            PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_02.wav");
			dialog.text = "Ah, seni tanıyorum! Mösyö "+GetFullName(pchar)+"! Kaynaklarınız ve destekçilerinizle ilgili söylentiler tüm Takımadalar boyunca kulağıma geliyor. Sanırım teklifim sizin için oldukça ilgi çekici olacak.";
			link.l1 = "Ne teklifi?";
			link.l1.go = "ignasio_2";
		break;
		
		case "ignasio_2":
            dialog.text = "Bir içki içmek için bir meyhaneye gidelim. Sana her şeyi anlatacağım. Bu, sokakta konuşulacak bir mesele değil.";
			link.l1 = "Pekala... Hadi gidelim!";
			link.l1.go = "ignasio_3";
		break;
		
		case "ignasio_3":
            DialogExit();
			FreeSitLocator("Bridgetown_tavern", "sit_front2");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "Bridgetown_tavern", "sit", "sit_front2", "Mtraxx_IgnasioInTavern", -1);
		break;
		
		case "ignasio_4":
			LAi_SetSitType(pchar);
            dialog.text = "Bir tur ister misiniz, kaptan?";
			link.l1 = "Tabii ki!";
			link.l1.go = "ignasio_5";
		break;
		
		case "ignasio_5":
			LAi_Fade("", "");
            dialog.text = "Heh, burada gerçekten romu suyla karıştırmıyorlar...";
			link.l1 = "Ve müşterilere çürük balık satma, tamam mı. Peki, mesele ne?";
			link.l1.go = "ignasio_6";
		break;
		
		case "ignasio_6":
            dialog.text = "Doğrudanlığınızı beğendim, monsieur. Söyleyin, İngilizler ile Hollandalılar arasındaki ticaret savaşının farkında mısınız?";
			link.l1 = "Benim. Ona katılma zevkini yaşadım.";
			link.l1.go = "ignasio_7";
		break;
		
		case "ignasio_7":
            PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_02.wav");
			dialog.text = "O halde açıklamaya gerek yok. Bir İngiliz korsanı olarak, bu savaşı onların tarafında sürdürüyorum. Sen ise çoğunlukla serbest çalışıyorsun, bu da hangi tarafa karşı savaşacağın konusunda seni kayıtsız kılıyor...";
			link.l1 = "Neredeyse. Fransa'yı geçmem, üzgünüm.";
			link.l1.go = "ignasio_8";
		break;
		
		case "ignasio_8":
            dialog.text = "Elbette, kaptan! O zaman, lafı dolandırmadan söyleyeyim: Curacao ile Trinidad arasında, haritalarda olmayan küçük bir yerleşimli ada var... Çok yakın zamanda, hatta diyebilirim ki en yakın zamanda, Hollandalılar burayı geçici bir ikmal ve tamir noktası olarak kullanmaya başladılar. Görünüşe göre sadece kendilerinin bu adadan haberi olduğunu sanıyorlar. Yanılıyorlar. He-he\nBirkaç gün önce, bir gümüş kervanı bir... fırtınaya yakalandı ve şimdi Hollandalılar gemilerini bu adada tamir ediyorlar. Amiral gemisi direğini kaybetti, bu yüzden tamir biraz zaman alacak. Hollandalılar tamirle meşgul, mürettebatın çoğu ise adanın dört bir yanına dağılmış durumda...";
			link.l1 = "Ve sonra birdenbire ortaya çıkıp günü mü kurtarıyoruz?";
			link.l1.go = "ignasio_9";
		break;
		
		case "ignasio_9":
            dialog.text = "Kesinlikle, kaptan. Bunu tek başıma yapamam, ama sizinle birlikte - bu bambaşka bir hikaye. Risk alır mısınız? Güzel bir gemim var, mürettebat harika, ayrıca epeyce tecrübem de var. Sizin yetenekleriniz de... takdire şayan.";
			link.l1 = "Ne kadar vaktimiz var?";
			link.l1.go = "ignasio_10";
		break;
		
		case "ignasio_10":
            dialog.text = "Yeterince var, eğer boşa harcamaz ve hemen yola çıkarsak.";
			link.l1 = "O halde mühimmat ve silahlarımızı tazeleyelim, Kaptan Ignacio Marco, ve yelken açalım. Adanın tam koordinatları nedir?";
			link.l1.go = "ignasio_11";
		break;
		
		case "ignasio_11":
            dialog.text = "12°40 Kuzey, 64°11 Batı. Anladın mı?";
			if (CheckAttribute(pchar, "questTemp.HWIC.Isladecoche")) link.l1 = "Ha! Déjà vu... Anladım.";
			else link.l1 = "Anladım.";
			link.l1.go = "ignasio_12";
		break;
		
		case "ignasio_12":
            dialog.text = "'Torero'ya gidiyorum. Seni bekliyor olacağım, kaptan!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioAddMarko");
		break;
		
		case "ignasio_13":
            PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_03.wav");
			dialog.text = "Ne dövüştük ama, değil mi kaptan? Şimdi işin güzel kısmına geçelim: payımızı bölelim. Yarısı bana ve adamlarıma.";
			link.l1 = "Pekala, hadi yapalım...";
			link.l1.go = "ignasio_14";
		break;
		
		case "ignasio_14":
			LAi_Fade("", "");
			WaitDate("", 0, 0, 0, 3, 10); 
			pchar.questTemp.Mtraxx.Silver = GetSquadronGoods(pchar, GOOD_SILVER)-sti(pchar.questTemp.Mtraxx.Silver);
			pchar.questTemp.Mtraxx.Mahogany = GetSquadronGoods(pchar, GOOD_MAHOGANY)-sti(pchar.questTemp.Mtraxx.Mahogany);
			if (sti(pchar.questTemp.Mtraxx.Silver) < 100)
			{
				dialog.text = "Kaptan, ne oldu? Gümüşümüz nerede? Ödülümüzü batırdın mı?";
				if (sti(pchar.questTemp.Mtraxx.Mahogany) < 200) 
				{
					link.l1 = "Hm...";
					link.l1.go = "ignasio_15_1";
				}
				else
				{
					link.l1 = "Bir şekilde gümüş boşa gitti, ama biraz kızılçam alabildik. Hadi paylaşalım.";
					link.l1.go = "ignasio_15_11";
				}
				break;
			}
			if (sti(pchar.questTemp.Mtraxx.Silver) < 300 && sti(pchar.questTemp.Mtraxx.Silver) > 100)
			{
				dialog.text = "Hm... Bu çok zayıf. Daha fazlası olur sanmıştım.";
				link.l1 = "Ne varsa elimizde, o kadar.";
				link.l1.go = "ignasio_15_2";
				break;
			}
			if (sti(pchar.questTemp.Mtraxx.Silver) < 700 && sti(pchar.questTemp.Mtraxx.Silver) > 300)
			{
				dialog.text = "Fena değil, fena değil. Yine de, daha fazlası olur sanmıştım.";
				link.l1 = "Ne varsa elimizde, o kadar.";
				link.l1.go = "ignasio_15_3";
				break;
			}
            dialog.text = "Güzel iş çıkardınız, Mösyö. Bu gerçekten değerli bir ganimet...";
			link.l1 = "Bu konuda sana katılmamak elde değil, kaptan.";
			link.l1.go = "ignasio_15_4";
		break;
		
		case "ignasio_15_1":
			dialog.text = "Kafandan ciddi bir sorun var gibi görünüyor. Gidiyoruz! Çocuklar!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_11":
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
			dialog.text = "En azından bundan bir şey elde ediyoruz... Çocuklar! Hadi gidelim!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_2":
			RemoveCharacterGoods(pchar, GOOD_SILVER, makeint(sti(pchar.questTemp.Mtraxx.Silver)/2));
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
            dialog.text = "Hiç yoktan iyidir. Herkes kendi yoluna gitsin.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_3":
            RemoveCharacterGoods(pchar, GOOD_SILVER, makeint(sti(pchar.questTemp.Mtraxx.Silver)/2));
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
            dialog.text = "Hiç yoktan iyidir. Artık yollarımızı ayıralım. Sonuçta başardık, heh!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_4":
			RemoveCharacterGoods(pchar, GOOD_SILVER, makeint(sti(pchar.questTemp.Mtraxx.Silver)/2));
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
            dialog.text = "Çok kârlı bir görüşme yaptık. Belki de bu, birlikte iş yaptığımız son sefer olmayacak, kaptan!";
			link.l1 = "Bana yine böyle tombul tüccarlar bulursan haber et, he-he!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_boarding":
			PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_04.wav");
            dialog.text = "Bunun bir tesadüf olmadığını varsayıyorum, Kaptan?";
			link.l1 = "Bunu görmeseydin akıllı olmazdın. Kurduğum düzen için bana borçlusun. Neden bahsettiğimi biliyorsun. Ayrıca, arkadaşım Jean Picard'ı tuzağa düşürdüğüm için de bana borçlusun. Senin planından sonra onu bir plantasyona sattılar... Ignacio'yu kaybettin. Seni asacağım, ama cezanı hafifletebilirsin...";
			link.l1.go = "ignasio_boarding_1";
		break;
		
		case "ignasio_boarding_1":
            dialog.text = "Şunu bile merak ediyorum – seni bana acıman için ne yapabilirim?";
			link.l1 = "Bilgiye ihtiyacım var. Seni ambarıma alacağım, orada Havana'daki işini konuşacağız...";
			link.l1.go = "ignasio_boarding_2";
		break;
		
		case "ignasio_boarding_2":
            dialog.text = RandSwear()+" Bunu hiç beklemiyordum! Sakın aklından bile geçirme. Barbazon ihaneti mi hemen öğrenir. Ona ihanet edenlere neler yaptığını bilmek istemezsin. Ben gördüm.";
			link.l1 = "Peki, asılmak daha iyi bir seçenek mi?";
			link.l1.go = "ignasio_boarding_3";
		break;
		
		case "ignasio_boarding_3":
            dialog.text = "Savaşta ölmeyi tercih ederim!";
			link.l1 = "...";
			link.l1.go = "ignasio_boarding_4";
		break;
		
		case "ignasio_boarding_4":
            DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "spy_sailor":
            dialog.text = "Kaptan! Kaptan! Çabuk olun! İspanyol askeri filosu peşimizde!";
			link.l1 = RandSwear()+"Bunu bekliyordum... Aynısı Picard'ın da başına geldi. Dışarıda kaç tanesinin olduğunu gördün mü?";
			link.l1.go = "spy_sailor_1";
		break;
		
		case "spy_sailor_1":
            dialog.text = "Evet, kaptan. Üç gemi var. Amiral gemileri bir kalyon, şimdiye kadar gördüğüm en büyüklerinden, hem de hızlı ilerliyor. Diğer ikisi ise bir korvet ve bir şebek.";
			link.l1 = "Herkes güverteye. Hâlâ kaçma şansımız olabilir.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioOurEscape");
		break;
		
		// индей-кариб в гроте Порто-Белло
		case "grot_canib":
            dialog.text = "Haya! Lanet olası yalanaui, ormanımıza girmiş! Öldürün onu! Haya!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekGrotFight");
		break;
		
		// бандит у пещеры Панамы
		case "cave_bandit":
            dialog.text = "Hey! Ne halt ediyorsun burada? A-ah, başkalarının eşyalarını mı çalıyorsun? Eh, yandın şimdi!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekCaveFight");
		break;
		
		case "carpenter":
            dialog.text = "Hey! Hepiniz orada kalın! Yoksa hepinizi bir saçma atışıyla yere sererim! "+RandSwear()+"";
			link.l1 = "Şu anda hiçbir yere gitmiyoruz. Ama dinle dostum – hiçbir şekilde hepimizi tek seferde öldüremezsin. Sen silahını doldururken bazılarımız seni paramparça eder. En iyisi şimdi konuşalım.";
			link.l1.go = "carpenter_1";
			locCameraFromToPos(-71.57, 14.57, -130.20, true, -63.78, 11.36, -125.50);
		break;
		
		case "carpenter_1":
            dialog.text = "Burada yetkili sen misin? Cevap ver bana!";
			link.l1 = "Ben kaptanım "+GetFullName(pchar)+". Ve Red Wolf burada yokken onun sağ kolu olmalısın, değil mi?";
			link.l1.go = "carpenter_2";
		break;
		
		case "carpenter_2":
            dialog.text = "Burada ne yapıyorsun, kaptan "+GetFullName(pchar)+"? Biz burada misafir kabul etmeyiz!";
			link.l1 = "Adın ne? Kiminle konuştuğumu bilmek istiyorum.";
			link.l1.go = "carpenter_3";
		break;
		
		case "carpenter_3":
            dialog.text = "Adım Rodgar Janssen.";
			link.l1 = "Bakıyorum, burada bayağı karanlıktasınız. Artık bir kaptanınız yok. Korvetiniz de gitti. 'Freyja', Hispaniola yakınlarında İspanyollar tarafından cehenneme çevrildi. Mürettebatının sonuna kadar hepsi öldürüldü...";
			link.l1.go = "carpenter_4";
		break;
		
		case "carpenter_4":
            dialog.text = RandSwear()+" Wulfric... Aahhh-ghhhhh!!! ... Ama bana gerçeği söylediğini nasıl bilebilirim?";
			link.l1 = "Eski kaptanınızın günlüğü elimde! Freyja'nın enkazından birkaç eşya bulduk. Günlük sayesinde bu adayı ve... sizin bu hazinenizi buldum.";
			link.l1.go = "carpenter_5";
		break;
		
		case "carpenter_5":
            dialog.text = "Heh! Bana hâlâ bir cevap borçlusun: Neden bu bilinmeyen topraklardasın?";
			link.l1 = "I'm not going to lie, pal. They say Red Wolf possessed quite a fortune. I'm here to find it, since no such treasure was found on his ship. I believe it should belong to good people; it has no use for Wulfric now, anyway.";
			link.l1.go = "carpenter_6";
		break;
		
		case "carpenter_6":
            dialog.text = "Ha! Dostum, seni hayal kırıklığına uğratacağım: ne ben ne de mürettebattan başka biri Wolf'un hazinelerini hiç görmedi. Ona bunu sormak bile çok riskliydi.";
			link.l1 = "O zaman onları köyünde aramam gerekecek. Silahını indirecek misin, yoksa köye baskın mı yapayım? Hiç şansın yok, Rodgar. Gerekirse daha fazla adam ve silah getiririm.";
			link.l1.go = "carpenter_7";
		break;
		
		case "carpenter_7":
            dialog.text = "Ölmeden önce, birçoğunuzu cehenneme götüreceğiz! Belki seni de!";
			link.l1 = "Emin misin? Ne kaptanın var, ne gemin, ne de seni kurtarmaya gelecek biri. Ben şimdi gitsem bile, hepiniz kısa sürede açlıktan öleceksiniz!";
			link.l1.go = "carpenter_8";
		break;
		
		case "carpenter_8":
            dialog.text = "Hmm... bir önerin var mı?";
			link.l1 = "Evet, biliyorum. Silahından uzak dur ve adamlarını kontrol altında tut. Sana ya da adamlarına zarar vermeyeceğime yemin ederim. İstersen ekibime katılabilirsin, yoksa seni medeniyete götüreceğiz.";
			link.l1.go = "carpenter_9";
		break;
		
		case "carpenter_9":
            dialog.text = "Adamlarının önünde, yüksek sesle ve açıkça yemin et!";
			link.l1 = "Yemin ederim! Söz veriyorum: senin ve adamlarının kılına bile zarar gelmeyecek.";
			link.l1.go = "carpenter_10";
		break;
		
		case "carpenter_10":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_11";
			LAi_SetActorType(npchar);
			LAi_ActorDialog(npchar, pchar, "", -1, 0);
			for (i=1; i<=2; i++) // 
			{
				sld = CharacterFromID("Islamona_fort_pirate_"+i);
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
		break;
		
		case "carpenter_11":
            dialog.text = "Umarım sözünüzü tutarsınız, kaptan.";
			link.l1 = "Her zaman yaparım. Kaç kişi kaldınız?";
			link.l1.go = "carpenter_12";
		break;
		
		case "carpenter_12":
            dialog.text = "Hepimizi görüyorsun. Üç kişiyiz. Diğerleri sana saldırırken ormanda öldü. Onlara yapmamalarını söyledim, ama dinlemediler...";
			link.l1 = "Anladım...";
			link.l1.go = "carpenter_13";
		break;
		
		case "carpenter_13":
            dialog.text = "Yiyecekler tükeniyordu. Papağan avlamaya başladık. 'Freyja' çok uzun süredir ortalarda yoktu. Şüphelerimiz vardı ve haklı çıktık.";
			link.l1 = "İyi ki hazine avına çıkmaya karar verdim. Sence onları nereye saklamış?";
			link.l1.go = "carpenter_14";
		break;
		
		case "carpenter_14":
            dialog.text = "Sana zaten söyledim: onları kimse hiç görmedi. Wulfric payına dikkat ederdi, hiçbir şeyini boşa harcamazdı. Bize karşı adildi, ama sakladığı şeyi bulmaya çalışan herkes kayboldu. İstersen köyü arayabilirsin.";
			link.l1 = "Planım bu. Kızıl Kurt'un evi nerede?";
			link.l1.go = "carpenter_15";
		break;
		
		case "carpenter_15":
            dialog.text = "Burada sahip olduğumuz tek iki katlı bina.";
			link.l1 = "Güzel. Bu arada, mesleğiniz nedir?";
			link.l1.go = "carpenter_16";
		break;
		
		case "carpenter_16":
			worldMap.labels.islamona.icon = 5;
			worldMap.labels.islamona.text = GetIslandNameByID("IslaMona");
            dialog.text = "Ben marangozum, bu ikisi de yardımcılarım. Daha önce 'Freyja'yı tamir edip bakıma alıyorduk. Mürettebatınızda işe yarayabiliriz.";
			link.l1 = "Anladım. Pekala, kabul edildin, ayrıntıları sonra konuşuruz. Girişten şu silahı al. Ve Rodgar, ben gizli yeri ararken köyden ayrılma.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekInFort");
		break;
		
		case "carpenter_17":
            dialog.text = "Emirleriniz nedir, kaptan?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.WolfreekGord"))
			{
				link.l1 = "Evet. Kaptanının hazineleri bulundu. Onları iyi saklamış ama ben ondan daha kurnaz çıktım!";
				link.l1.go = "carpenter_18";
				break;
			}
			// Jason Исла Мона -->
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "start")
			{
				link.l1 = "Rodgar, sence bu üs ile başka ne yapabiliriz?";
				link.l1.go = "IslaMona";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "get_tools")
			{
				link.l1 = "Rodgar, aletleri getirdim. Onlar sana çoktan teslim edilmiş olmalı.";
				link.l1.go = "IslaMona_8";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "himenes")
			{
				link.l1 = "Hoş geldiniz! Bu, Cadiz'den gelen küçük ama çok çalışkan bir topluluğun lideri Rodrigo Jimenez. Señor Jimenez, geçici olarak topraklarımızda kalmayı ve inşaat işlerimizde bize yardımcı olmayı nazikçe kabul etti.";
				link.l1.go = "IslaMona_12";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "nextday")
			{
				link.l1 = "Rodgar, nasılsın? Bana iyi bir tavsiyen var mı?";
				link.l1.go = "IslaMona_18";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "stalk")
			{
				link.l1 = "Rodgar, senden bir iyilik isteyeceğim.";
				link.l1.go = "IslaMona_20";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "dublon_wait" && PCharDublonsTotal() >=600)
			{
				link.l1 = "Senin için doblonları getirdim, ama hepsini hemen içkiye harcama sakın.";
				link.l1.go = "IslaMona_24";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "storage" && !CheckAttribute(pchar, "questTemp.IslaMona.Food") && IslaMona_CheckFood())
			{
				link.l1 = "Rodgar, depoyu kontrol et. İlaçları ve erzakları getirdim.";
				link.l1.go = "IslaMona_30";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "village")
			{
				link.l1 = "Merhaba Rodgar, yeni yerleşimde işler nasıl gidiyor?";
				link.l1.go = "IslaMona_32";
				break;
			}
			if (!CheckAttribute(npchar, "quest.stalk")) // ремонт кораблей
			{
				link.l2 = "Rodgar, gemim tamire ihtiyaç duyuyor. Sen ve adamların hazır mısınız?";
				link.l2.go = "repair";
			}
			link.l3 = "Rodgar, gemilerimden birini burada bırakmak istiyorum.";
			if (CheckAttribute(npchar, "portman.info")) link.l3.go = "shipstock";
			else link.l3.go = "shipstock_info";
			if (CheckAttribute(npchar, "portman") && sti(npchar.portman > 0))
			{
				link.l4 = "Rodgar, gemilerimden birini geri almak istiyorum.";
				link.l4.go = "shipstockreturn";
			}
			if (!CheckAttribute(npchar, "storadge"))
			{
				link.l5 = "Bak, depo olarak kullanabileceğim boş bir bina var mı?";
				link.l5.go = "storadge";
			}
			if (CheckAttribute(npchar, "storadge"))
			{
				link.l5 = "Rodgar, ambarı görmek istiyorum.";
				link.l5.go = "storadge_3";
			}
			if (CheckAttribute(npchar, "crew"))
			{
				link.l6 = "Rodgar, ekibin bir kısmını adada bırakmak istiyorum.";
				link.l6.go = "crew";
			}
			if (CheckAttribute(npchar, "crew") && sti(npchar.crew.qty) > 0)
			{
				link.l7 = "Rodgar, denize tekrar açılırken denizcilerimi yanıma almak istiyorum.";
				link.l7.go = "crew_3";
			}// <-- Исла Мона
			link.l99 = "Henüz bir şey yok...";
			link.l99.go = "carpenter_exit";
		break;
		
		case "Crew":
			DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			LaunchHireCrew();
		break;
		
		case "carpenter_exit":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
		break;
		
		case "carpenter_18":
            dialog.text = "Tebrikler, Kaptan. Şimdi ne yapıyoruz? Gidiyor muyuz?";
			link.l1 = "Uzun zamandır burada mısın?";
			link.l1.go = "carpenter_19";
		break;
		
		case "carpenter_19":
            dialog.text = "Çok uzun zamandır. Wulfric beni buraya sorumlu atayalı bir yıl oldu.";
			link.l1 = "Bu gizli üssün boşa harcanamayacak kadar değerli olduğuna karar verdim. Köy artık benim. İstersen seni ve adamlarını burada bırakabilirim. Rom, erzak, ilaç - hepsi sizin.";
			link.l1.go = "carpenter_20";
		break;
		
		case "carpenter_20":
            dialog.text = "Harika olurdu, kaptan. Bu sahilde, bu adada yaşamaya alıştım.";
			link.l1 = "Harika. Bu arada, adanın adı ne?";
			link.l1.go = "carpenter_21";
		break;
		
		case "carpenter_21":
            dialog.text = "Isla Mona.";
			link.l1 = "Isla Mona... Belki bir gün burada daha fazla ev ve yapı inşa ederiz... Ama o zaman sonra gelecek. Şimdilik, burada aynı görevi sürdüreceksin, fakat artık yeni bir kaptanın emrinde.";
			link.l1.go = "carpenter_22";
		break;
		
		case "carpenter_22":
            dialog.text = "Anlaştık. Kendine dikkat et kaptan, bir de bizi erzak konusunda unutma.";
			link.l1 = "Tabii Rodgar. Bol şans, benim La Vega'ya yelken açmam gerek.";
			link.l1.go = "carpenter_exit";
			npchar.portman = 0;
			AddDialogExitQuestFunction("Mtraxx_WolfreekComplete");
		break;
		//------------------------------------------------------------ Исла Мона ------------------------------------
		case "IslaMona":
			sTemp = "";
			if (GetCharacterIndex("Mirabella") != -1) sTemp = ", not accounting for your woman";
            dialog.text = "Bunu söylemek zor, Kaptan. Merhum Wulfric burada hiçbir zaman iki düzineden fazla insan bırakmadı. Şu anda ise sadece üç kişiyiz."+sTemp+". Yapabileceğimiz pek bir şey yok.";
			link.l1 = "Yani, burada daha fazla insan yaşasaydı, burayı tam teşekküllü bir yerleşim yerine dönüştürebileceğini mi söylüyorsun?";
			link.l1.go = "IslaMona_1";
		break;
		
		case "IslaMona_1":
            dialog.text = "Ada küçük, bu yüzden burada bir koloni kuramazsın, ama bir yerleşim yeri kurmak gayet mümkün! Balık tutabilir, kuş ve keçi avlayabilir, meyve toplayabilirsin. Kendi kendimize yetebiliriz, ama bundan zengin olmayız.\nAma bir şeyi pek anlamadım, Kaptan. Bunu neden istiyorsun?";
			link.l1 = "Burası benim evim, toprağım, halkım. Onlara sahip çıkmazsam ben kim olurum?";
			link.l1.go = "IslaMona_2_1";
			link.l2 = "Paraya değer bir işe yatırım yapmak istiyorum.";
			link.l2.go = "IslaMona_2_2";
			link.l3 = "Bu küçük ada, bu bölgenin tam kalbinde yer alıyor. Onu tam teşekküllü ve gizli bir askeri üsse dönüştürmek akıllıca olurdu.";
			link.l3.go = "IslaMona_2_3";
			link.l4 = "Senin için endişeleniyorum Rodgar, artık hepiniz tamamen kontrolden çıktınız.";
			link.l4.go = "IslaMona_2_4";
		break;
		
		case "IslaMona_2_1":
            dialog.text = "Garip birisin. Neyse, en azından yapacak bir şey olur...";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
			AddCharacterExpToSkill(pchar, "Defence", 2000);//защита
		break;
		
		case "IslaMona_2_2":
            dialog.text = "Garip birisin. Neyse, en azından yapacak bir şey olacak...";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
			AddCharacterExpToSkill(pchar, "Commerce", 1500);//торговля
		break;
		
		case "IslaMona_2_3":
            dialog.text = "Sen de tuhafsın. Neyse, boşver. En azından oyalanacak bir şey olacak...";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
			AddComplexSelfExpToScill(250, 250, 250, 250);//оружие
		break;
		
		case "IslaMona_2_4":
            dialog.text = "Garip birisin. Neyse, en azından yapacak bir şey olacak...";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
			AddCharacterExpToSkill(pchar, "Leadership", 1000);//авторитет
		break;
		
		case "IslaMona_3":
            dialog.text = "Her şeyden önce, buraya taşınmaya ve dış dünyadan tamamen izole bir şekilde yıllarca yaşamaya, çalışmaya ikna edilebilecek çok özel insanları bulman gerekecek. Araman gereken kişiler işte böyle olağanüstü insanlar olmalı. Üstelik, umarım birden fazlasını bulursun. Sonuçta, en azından şimdilik, tayfanı burada yerleşmeye zorlayamazsın. Kolonistler ise kurulu düzenlerini ve güvenli işlerini bırakmak istemezler. Ve elbette, buraya başıboşları ya da toplumdan dışlanmışları da istemiyoruz.\nAyrıca, bu adanın gizliliği meselesi her zaman bir sorun olarak kalacak. Eğer birine anlatırsan, hemen ardından burayı araştırmaya gelecek avcılar tehdidi ortaya çıkar.";
			link.l1 = "Anladım, önerin var mı?";
			link.l1.go = "IslaMona_4";
		break;
		
		case "IslaMona_4":
            dialog.text = "Hayır, Kaptan. Burada fazlasıyla uzun kaldım ve medenî hayatla tamamen bağımı kaybettim.";
			link.l1 = "Harika, bu çok yardımcı oldu!";
			link.l1.go = "IslaMona_5";
		break;
		
		case "IslaMona_5":
            dialog.text = "Ben ahşapla çalışırım, insanlarla değil. Ve bundan gayet memnunum, ha-ha! Bu arada, insanlardan başka, buraya kaliteli bir dövme ve inşaat aletleri takımı da getirmen gerekecek. Bu aletler sadece eski Avrupa'da yapılıyor, yani sana pahalıya patlayacaklar. Büyük tersanelerin sahiplerine sor.";
			link.l1 = "Her şey açık. Özetleyelim: Eğer bu üssü daha büyük bir şeye dönüştürmek istiyorsam, buraya daha fazla yerleşimci ve alet getirmem gerekiyor, değil mi?";
			link.l1.go = "IslaMona_6";
		break;
		
		case "IslaMona_6":
            dialog.text = "Doğru söylüyorsun!";
			link.l1 = "Ne yapabileceğime bakacağım.";
			link.l1.go = "IslaMona_7";
		break;
		
		case "IslaMona_7":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			AddQuestRecord("IslaMona", "1");
			pchar.questTemp.IslaMona = "tools";
			IslaMona_SelectShipyard();
		break;
		
		case "IslaMona_8":
            dialog.text = "Emredersiniz, Kaptan! Harika bir ekipman, koloni kurmaya hazırız! Pahalıya mı patladı?";
			link.l1 = "Bir servete mal oldu, umarım değmiştir!";
			link.l1.go = "IslaMona_9_1";
			link.l2 = "Birkaç yıl önce, çok pahalı derdim. Ama şimdi... Bilmiyorum bile.";
			link.l2.go = "IslaMona_9_2";
		break;
		
		case "IslaMona_9_1":
			AddCharacterExpToSkill(pchar, "Commerce", 600);
            dialog.text = "Elindekilerle yetinmeyi başaramadın, değil mi? Her halükarda, masraflarının sadece artacağını bilmelisin. Yerleşimcilerle ilgili meseleyi hallettin mi?";
			link.l1 = "Hayır, Rodgar. Onları nerede bulacağımı henüz çözemedim. Sonuçta, bu sularda yerleşim kurma hakkım yok.";
			link.l1.go = "IslaMona_10";
		break;
		
		case "IslaMona_9_2":
			AddCharacterExpToSkill(pchar, "Leadership", 300);
            dialog.text = "Elindekilerle yetinmedin, değil mi? Her durumda, masraflarının sadece artacağını bil. Yerleşimcilerle ilgili meseleyi hallettin mi?";
			link.l1 = "Hayır, Rodgar. Onları nerede bulacağımı henüz çözemedim. Sonuçta, bu sularda yerleşim kurma hakkım yok.";
			link.l1.go = "IslaMona_10";
		break;
		
		case "IslaMona_10":
            dialog.text = "Bu sularda, Kaptan, her gün kaos hüküm sürüyor. İnsanların ne dediğine kulak ver, belki gizli bir fırsat yakalarsın. Şimdilik aletlerle ben ilgilenirim.";
			link.l1 = "Pekala, bu tür bilgiler için gözümü açık tutacağım.";
			link.l1.go = "IslaMona_11";
		break;
		
		case "IslaMona_11":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			AddQuestRecord("IslaMona", "3");
			RemoveItems(pchar, "islamona_toolbox", 1);
			pchar.questTemp.IslaMona = "rumours";
			AddRumor("They say some criminals have been cast out to one of the uninhabited islands! It seems they're such fierce monsters that even the executioner and the holy fathers wouldn't want to deal with them! But why do they always bring such people to us?!", 1, "all", "none", 0, (2022 - STARTGAME_YEAR) * 365, "IslaMona_TerksRumour", "none");
		break;
		
		case "IslaMona_12":
            dialog.text = "İspanyollar mı? Şaka yapıyorsun herhalde, Kaptan. Le Francois’dan aylaklar getirirsin sanmıştım, bunları değil...";
			link.l1 = "";
			link.l1.go = "IslaMona_13";
		break;
		
		case "IslaMona_13":
            DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_18";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "IslaMona_14":
            dialog.text = "Avrupa'dan mı geldin? Hehe, anlamak zor değil. Merak etme, alışırsın.";
			link.l1 = "Jimenez, bir süreliğine benim evimde kalacaksın. Orada bir bodrum var, bolca yer mevcut. Rodgar, aletleri ve yerleşimcileri de getirdim. Sırada ne var?";
			link.l1.go = "IslaMona_15";
		break;
		
		case "IslaMona_15":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_20";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "IslaMona_16":
            dialog.text = "Yarın görüşürüz, Kaptan. Bu... yerleşimciler hazineleriyle yerleşene kadar bir gün bekleyelim, sonra konuşuruz.";
			link.l1 = "Pekala,   yarın devam ederiz.";
			link.l1.go = "IslaMona_17";
		break;
		
		case "IslaMona_17":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			LAi_SetWarriorType(npchar);
			IslaMona_HimenesWait();
		break;
		
		case "IslaMona_18":
            dialog.text = "Kaptan, İspanyol ile konuş. Zaten işine tamamen dalmış durumda.";
			link.l1 = "Anlaşıldı, hallederim.";
			link.l1.go = "IslaMona_19";
			link.l2 = "Bir sorun mu var?";
			link.l2.go = "IslaMona_18_1";
		break;
		
		case "IslaMona_18_1":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
            dialog.text = "Kaptan, burada çocuklarla birkaç yıldır oyalanıyorum. Artık İspanyolların bu telaşlı hareketliliği sinirlerimi bozuyor.";
			link.l1 = "Hiçbir çatışma olmayacak! Ve seninle adamlarının onların kadınlarına bakmasını bile yasaklıyorum! En azından, şimdilik... Eğer işler kızışırsa, bir kayık alıp birkaç günlüğüne balık tutmaya gidin.";
			link.l1.go = "IslaMona_18_2";
		break;
		
		case "IslaMona_18_2":
            dialog.text = "Emredersiniz, efendim!";
			link.l1 = "Mükemmel. Peki, gidip neyle meşgul olduğuna bakacağım.";
			link.l1.go = "IslaMona_19";
		break;
		
		case "IslaMona_19":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			IslaMona_SetHimenesNextDay();
		break;
		
		case "IslaMona_20":
            dialog.text = "Zaten biliyorum, Kaptan. İspanyol bizden adayı keşfetmemizi mi istiyor? Bir grup aptal gibi haritayla kayaların üstünde zıplayalım mı yani?";
			link.l1 = "Doğru söylüyorsun, Rodgar.";
			link.l1.go = "IslaMona_21";
		break;
		
		case "IslaMona_21":
            dialog.text = "Altı yüz dublon ve işi hallederim.";
			link.l1 = "Sen deli misin? Yoksa buranın bir örümceği ya da zehirli bir yılanı mı ısırdı seni? Issız bir adada bir sandık altınla ne yapacaksın? Gömecek misin?";
			link.l1.go = "IslaMona_22";
		break;
		
		case "IslaMona_22":
            dialog.text = "Hadi ama, Kaptan. Bir gün buradan gideceğiz, peki büyük dünyada paramız olmadan kime lazım olacağız? Tabii, ufak bir birikimimiz var, ama asla yeterli değil. Wulfric, son maceralarında bana ve adamlara olan borcunu hiç ödemedi.\nAylarca sahilde pinekleyip, altı ayda bir filonuza bakmak başka bir şey. Ama her gün karada sıkı çalışmak, lanetli bir korsan gibi yaşamak bambaşka! O iş, ve işler karşılığında para alınır. Mürettebatınıza ödeme yapıyorsunuz, değil mi Kaptan?";
			link.l1 = "Makul görünüyor. Sana 600 dublon getireceğim. Umarım peşin ödeme beklemiyorsundur, değil mi?";
			link.l1.go = "IslaMona_23";
			link.l2 = "Başka bir teklifim var. Sen karada çalışıyorsun, denizde gemilerin gövdesinden midye kazımakla uğraşmıyorsun. Şu anda, tam da böyle bir işe çok ihtiyacımız var.";
			link.l2.go = "IslaMona_25";
		break;
		
		case "IslaMona_23":
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			AddQuestRecord("IslaMona", "7");
            dialog.text = "Kaptan, hemen şimdi başlayabilirim, ama adamlarım ellerinde birkaç doblon gördüklerinde çok daha sıkı çalışacaklar. Söz veriyorum, bu adada keşfedilmemiş tek bir toprak parçası bile bırakmayacağız.";
			if (PCharDublonsTotal() >= 600)
			{
				link.l1 = "Pekala. Al altınlarını. Sadece hemen gidip içkiye harcama.";
				link.l1.go = "IslaMona_24";
			}
			else
			{
				link.l1 = "Pekala, sana altınlarını getireceğim.";
				link.l1.go = "IslaMona_24_1";
			}
		break;
		
		case "IslaMona_24_1":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			pchar.questTemp.IslaMona = "dublon_wait";
		break;
		
		case "IslaMona_24":
			RemoveDublonsFromPCharTotal(600);
			Log_Info("You gave away 600 doubloons");
			PlaySound("interface\important_item.wav");
            dialog.text = "Ha-ha! Haklısınız Kaptan! Ah, neredeyse unutuyordum. Artık burada epey insan yaşıyor ve onların da yiyeceğe ihtiyacı var. Şu hanımları gördünüz mü? Doğada hayatta kalmaya alışık değiller. Pek bir faydaları dokunmaz.";
			link.l1 = "Sadece bana daha fazla korsan bulmam gerekeceğini söyleme yeter.";
			link.l1.go = "IslaMona_26";
		break;
		
		case "IslaMona_25":
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			pchar.questTemp.IslaMona.Nodublon = "true"; // дублоны не заплатил
			AddQuestRecord("IslaMona", "8");
            dialog.text = "Emredersiniz, Kaptan! Karada çalışmaya hazırız! Ah, bir şey daha, az kalsın unutuyordum. Artık burada epey insan yaşıyor ve onların da yiyeceğe ihtiyacı var. Şu hanımları gördünüz mü? Toprakla uğraşıp geçinmeye alışkın değiller. Pek yardımcı olamazlar.";
			link.l1 = "Bana da yardım etmen için korsan aramaya çıkmam gerekecek deme sakın...";
			link.l1.go = "IslaMona_26";
		break;
		
		case "IslaMona_26":
            dialog.text = "Hayır, neden yapalım ki? Aralarından en yeteneklilerini eğitip geçimlerini sağlayacak hale getireceğiz. Ama o güzel an gelene kadar, bize yiyecek sağlaman gerekecek. Birkaç bin gemi erzağı yeterli olur. Bir de geleceğe yönelik yüz okka ilaç. Bunların hepsini gemilerden indirip adadaki depomuza bırak.";
			link.l1 = "Olur. Keşif görevi için ne kadar zamana ihtiyacın var?";
			link.l1.go = "IslaMona_27";
		break;
		
		case "IslaMona_27":
            dialog.text = "İki ya da üç güne bitiririz, şimdiden ilginç şeyler bulduk.";
			link.l1 = "Harika!";
			link.l1.go = "IslaMona_28";
		break;
		
		case "IslaMona_28":
            dialog.text = "İşimiz biter bitmez, doğruca o gülen İspanyolun yanına git. O deli adam, yaptıklarımızdan bir sonuç çıkarmalı.";
			link.l1 = "Bakıyorum, neredeyse arkadaş olmuşsunuz bile. O halde üç gün sonra onu ziyaret edeceğim. Neyse, işimize bakalım. Hepimize bol şans!";
			link.l1.go = "IslaMona_29";
		break;
		
		case "IslaMona_29":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			npchar.quest.stalk = "true";
			AddQuestRecord("IslaMona", "9");
			pchar.questTemp.IslaMona = "storage";
			SetFunctionTimerCondition("IslaMona_StalkFin", 0, 0, 3, false);
		break;
		
		case "IslaMona_30":
            dialog.text = "Vay canına! Teşekkürler, Kaptan. Şimdi hanımları bu çılgın hayata hazırlamak için zamanımız var.";
			link.l1 = "Onları korsana çevirmemeye dikkat et! Teşekkürler, Rodgar";
			link.l1.go = "IslaMona_31";
		break;
		
		case "IslaMona_31":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			pchar.questTemp.IslaMona.Food = "true";
			AddQuestRecord("IslaMona", "10");
			IslaMona_RemoveFood();
		break;
		
		case "IslaMona_32":
            dialog.text = "Kaptan! Burada yaşamaktan artık kendimi pek rahat hissetmediğimi söylemeliyim.";
			link.l1 = "Neden böyle, Rodgar? Yoksulluk ve yıkımın cazibesini mi özledin?";
			link.l1.go = "IslaMona_33";
		break;
		
		case "IslaMona_33":
            dialog.text = "Öyle denebilir. Artık medeniyet buraya kadar ulaşıyor. Ve benim gibi insanların bu dünyada yeri yok.";
			link.l1 = "Kendine bir jabot ve baston al. Hemen ortama uyum sağlarsın.";
			link.l1.go = "IslaMona_34";
		break;
		
		case "IslaMona_34":
            dialog.text = "Öyleyse, hadi gidip İspanyolunu bulalım ve keşif sonuçlarını konuşalım. Bir çılgın fikrim daha var...";
			link.l1 = "Az önce onunla konuştum! Peki, hadi gidelim, Rodgar.";
			link.l1.go = "IslaMona_37";
			link.l2 = "Onunla çalışmaktan keyif alıyor musun?";
			link.l2.go = "IslaMona_35";
		break;
		
		case "IslaMona_35":
            dialog.text = "Çok eğitimli ve çalışkan insanlar! Jimenez ise gerçekten usta biri. Eskiden böyle insanlar için iyi bir miktar altın alınabilirdi. Kızları da çok güzel...";
			link.l1 = "Hiçbirini duymak istemiyorum, Rodgar! Hadi gidelim ve şu efendimizle konuşalım";
			link.l1.go = "IslaMona_36_1";
			link.l2 = "Eğer işi beceremezlerse, onları satarız. Ama kızlar kalsın, ha-ha! Hadi ustanın yanına gidelim... ";
			link.l2.go = "IslaMona_36_2";
		break;
		
		case "IslaMona_36_1":
			ChangeCharacterComplexReputation(pchar, "nobility", 6);
            dialog.text = "Cidden mi, Kaptan? Sadece şaka yapıyordum, hadi gidelim...";
			link.l1 = "";
			link.l1.go = "IslaMona_37";
		break;
		
		case "IslaMona_36_2":
			ChangeCharacterComplexReputation(pchar, "nobility", -6);
            dialog.text = "Beni destekleyeceğini biliyordum, Kaptan! Hadi gidelim...";
			link.l1 = "";
			link.l1.go = "IslaMona_37";
		break;
		
		case "IslaMona_37":
            DialogExit();
			DoQuestReloadToLocation("IslaMona_TwoFloorHouse", "goto", "goto5", "IslaMona_HouseDialog");
		break;
		
		case "IslaMona_38":
            dialog.text = "Gülmüyor, Kaptan...";
			link.l1 = "";
			link.l1.go = "IslaMona_39";
		break;
		
		case "IslaMona_39":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_48";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_40":
            dialog.text = "O da, Kaptan. Onu sonra konuşuruz...";
			link.l1 = "";
			link.l1.go = "IslaMona_41";
		break;
		
		case "IslaMona_41":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_52";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_42":
            dialog.text = "Beyefendinin dediği doğru, Kaptan. Hiçbirimiz ormanda canımızı dişe takmayacağız. İş pis olabilir, ama buradan başka türlü bir şey çıkaramazsınız; burası en fazla bir korsan yuvası olur.";
			link.l1 = "";
			link.l1.go = "IslaMona_43";
		break;
		
		case "IslaMona_43":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_58";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_44":
            dialog.text = "Captain, when you build the factory, the slaves will need protection. My guys will take care of that. One of them even shoots like Thor with lightning. Nothing motivates work like a hunting scope. We already have one gun; now we need a second. Any musket will do.";
			link.l1 = "";
			link.l1.go = "IslaMona_45";
		break;
		
		case "IslaMona_45":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_60";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_46":
            dialog.text = "Ve adamlarım da aynı miktarda altın ve bir düzine daha iyi rom isteyecek.";
			link.l1 = "Her partide ne kadar odun sağlayabilirsin? Ve altına neden ihtiyacın var?";
			link.l1.go = "IslaMona_47";
		break;
		
		case "IslaMona_47":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_62";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_48":
            dialog.text = "Her şeyden önce, eğlence olmadan hayatın hiçbir anlamı yoktur, yakında o dindar Katolikler bile, hehe, duvarlara tırmanmaya başlar. İkincisi, adada bir meyhane varsa, mürettebatın bir kısmını burada beklemede bırakabilirsin. Bak, insanları koca bir yıl boyunca sahildeki kulübelerde bedavaya vahşi gibi yaşamaya ikna etmek pek kolay değil. Ama yakınlarda bir meyhane, sıcak yemek, müzik ve eğlence olan bir yerleşim varsa... Bir denizcinin karada izindeyken başka neye ihtiyacı olur ki?";
			link.l1 = "Orospular?";
			link.l1.go = "IslaMona_49";
			link.l2 = "Bir şeyler içer misin?";
			link.l2.go = "IslaMona_49";
		break;
		
		case "IslaMona_49":
            dialog.text = "Haklısın, ama sorunları birer birer çözelim. Önce evini yeniden inşa edeceğiz...";
			link.l1 = "...";
			link.l1.go = "IslaMona_50";
		break;
		
		case "IslaMona_50":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_65";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_51":
            dialog.text = "Bunu aklına bile getirmedi, Kaptan.";
			link.l1 = "Teşekkür ederim, Rodgar. Artık bu küçük koyda daha fazla gemiye hizmet edebileceğimi anlıyorum, değil mi?";
			link.l1.go = "IslaMona_52";
		break;
		
		case "IslaMona_52":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_harbour_4";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_53":
            dialog.text = "Selam, Kaptan! İş hakkında konuşmaya mı geldiniz?";
			link.l1 = "Hayır, hiç de değil. Sadece kuzeyli yüz hatlarını özlemişim.";
			link.l1.go = "IslaMona_54";
		break;
		
		case "IslaMona_54":
            dialog.text = "Yürüyelim mi? Fabrikanı sana göstereceğim.";
			link.l1 = "Önden buyur.";
			link.l1.go = "IslaMona_55";
		break;
		
		case "IslaMona_55":
            DialogExit();
			IslaMona_PlantationGo();
		break;
		
		case "IslaMona_56":
            dialog.text = "H-hıç! Kaptan, kutlama yapıyoruz!";
			link.l1 = "Rodgar! Rodrigo! Lanet olsun!";
			link.l1.go = "IslaMona_57";
		break;
		
		case "IslaMona_57":
            dialog.text = "Ne oldu, k-k-kaptan? Duvarların rengini beğenmediniz mi?";
			link.l1 = "Şimdi fark ettim ki ikinizin de adı aynı! Ha-ha-ha! Bir İspanyol ve bir korsan, aynı isme sahip, ıssız bir adada bir meyhane kurmuş ve Hint tanrıları herkesi yutacak, güneş doğana kadar dünya sona erecekmiş gibi birlikte içiyorlar! Ha-ha! Ben de sizinleyim!";
			link.l1.go = "IslaMona_58";
		break;
		
		case "IslaMona_58":
            dialog.text = "Ha-ha-ha! Gerçekten öyle! Şerefe!";
			link.l1 = "Şerefe!";
			link.l1.go = "IslaMona_59";
		break;
		
		case "IslaMona_59":
            DialogExit();
			npchar.dialog.currentnode = "IslaMona_60";
			IslaMona_ReloadTavern();
		break;
		
		case "IslaMona_60":
            dialog.text = "Bir içki ister misin, Kaptan?";
			link.l1 = "Rodgar, meyhaneci mi oluyorsun?";
			link.l1.go = "IslaMona_61";
		break;
		
		case "IslaMona_61":
            dialog.text = "Geçici olarak! Özellikle İspanyollar, bir korsanın barı işletmesini çok ilginç buluyorlar - onlar için tam bir egzotizm ve macera. Ama genel olarak, burada olmak keyifli. Mürettebatından birini bu yerleşimde yedekte bırakmak istersen, bana haber ver - ben hallederim.";
			link.l1 = "Peki, nerede yaşayacaklar?";
			link.l1.go = "IslaMona_62";
		break;
		
		case "IslaMona_62":
            dialog.text = "Basit - sahilde birkaç kulübe inşa edeceğiz. Böylece, meyhaneden sahile koşup duracaklar. Yalnızca hatırlatmak isterim, bu ada üç yüz kişiden fazlasını barındıramaz, bunu aklında tut gelecekte. Bazen senden rom ve şarap getirmeni isteyeceğiz, bu yüzden, Kaptan, malları önceden depoya koyarsan harika olur.";
			link.l1 = "Bunu unutmayacağım. Peki öyleyse, dostum. İspanyolları eğlendir ve biraz dinlen. Ama ne olur, o kadar çok içme ki bütün köy yanıp kül olsun – bunu görmek istemem!";
			link.l1.go = "IslaMona_63";
		break;
		
		case "IslaMona_63":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			//LocatorReloadEnterDisable("IslaMona_TwoFloorHouse", "reload1", false);
			//LocatorReloadEnterDisable("IslaMona_TwoFloorHouse", "reload3", false);
			npchar.crew = "true"; // можно оставлять матросов
			npchar.crew.qty = 0;
			pchar.questTemp.IslaMona.Tavern = "done"; // флаг - таверна построена и сдана
			// belamour обнулим матросов-->
			ref rTown = GetColonyByIndex(FindColony(loadedLocation.fastreload));
			rTown.Ship.crew.quantity = 0;
			rTown.Ship.crew.morale = 0;
			rTown.Ship.Crew.Exp.Sailors   = 0;
			rTown.Ship.Crew.Exp.Cannoners = 0;
			rTown.Ship.Crew.Exp.Soldiers  = 0;
			ChangeCrewExp(rTown, "Sailors", 0);  // приведение к 1-100
			ChangeCrewExp(rTown, "Cannoners", 0);
			ChangeCrewExp(rTown, "Soldiers", 0);
			
		break;
		
		case "IslaMona_64":
            dialog.text = "Kaptan! Sizi gördüğüme gerçekten çok sevindim! Freyja'ya şükür, tam zamanında geldiniz!";
			link.l1 = "Yine güzel bir belaya bulaştık. Hola, Rodrigo!";
			link.l1.go = "IslaMona_65";
		break;
		
		case "IslaMona_65":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_13";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_66":
            dialog.text = "Hiç kayıp yok. Hayatta kalan İspanyollar önce bize ulaştı, daha fazla misafirle karşılaşma ihtimalimiz olduğunu bildirdiler ve bölgedeki neredeyse tüm erzak ve ekipmanı yerleşkeye taşımayı başardık. Kölelerle ilgili durum ise elbette pek iyi olmadı.";
			link.l1 = "";
			link.l1.go = "IslaMona_67";
		break;
		
		case "IslaMona_67":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_16";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_68":
            dialog.text = "Ya bizi açık bir saldırıya sürüklerlerse?";
			link.l1 = "O zaman silahsız çalışırız. Bir geçit törenindeymişiz gibi birlikte kapılara yürür, sonra arkadan saldırırız. Sen kapıları tutup destek sağlarsın. Hepsi bu, bize bol şans!";
			link.l1.go = "IslaMona_69";
		break;
		
		case "IslaMona_69":
            DialogExit();
			AddQuestRecord("IslaMona", "21");
			pchar.quest.islamona_def_jungle1.win_condition.l1 = "locator";
			pchar.quest.islamona_def_jungle1.win_condition.l1.location = "IslaMona_jungle_01";
			pchar.quest.islamona_def_jungle1.win_condition.l1.locator_group = "encdetector";
			pchar.quest.islamona_def_jungle1.win_condition.l1.locator = "enc04";
			pchar.quest.islamona_def_jungle1.function = "IslaMona_DefSoldiersInJungle"; // встреча с французами
			LAi_LocationFightDisable(&Locations[FindLocation("IslaMona_jungle_01")], true);//запретить драться
		break;
		
		case "IslaMona_70":
            dialog.text = "Yaşasın, Kaptan!";
			link.l1 = "Anlaştık! Harikaydı, ben de kendimi yere atmak istedim. Çocuklar, oraya ne doldurdunuz?";
			link.l1.go = "IslaMona_71";
		break;
		
		case "IslaMona_71":
            dialog.text = "Çifte doldur, Kaptan. Tek bir atışla savaşma heveslerini kırmış olalım!";
			link.l1 = "Silahın bu kadar hassas kullanımdan patlayacağından hiç endişelenmedin mi?";
			link.l1.go = "IslaMona_72";
		break;
		
		case "IslaMona_72":
            dialog.text = "Wulfric’in bana bıraktığı özel bir tılsımım var. Anavatanımız Danimarka’dan bir hatıra. Hep birlikte meyhaneye gidelim mi, Kaptan? Bugün hepimiz yorulduk.";
			link.l1 = "Evet, harika olurdu. Hadi biraz kart oynayalım – mucizevi tılsımına bahse gireceğiz.";
			link.l1.go = "IslaMona_73";
		break;
		
		case "IslaMona_73":
            dialog.text = "Ha-ha, bugün sergilediğiniz o harika gösteriden sonra, Kaptan, belki o seçeneği bile düşünebilirim!";
			link.l1 = "";
			link.l1.go = "IslaMona_74";
		break;
		
		case "IslaMona_74":
            DialogExit();
			sld = characterFromId("IM_fraofficer");
			sld.dialog.currentnode = "FraOfficer_18";
			LAi_CharacterEnableDialog(sld);
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_75":
            dialog.text = "Kaptan, bunu duydunuz mu? Hâlâ kulaklarımda çınlama var. Bu kederli ses kime ait?";
			link.l1 = "Bu, Rodgar, hâlâ çözülememiş bir mesele. Onu fabrikaya götür, zincire vur ve sonraki talimatları bekle.";
			link.l1.go = "IslaMona_76";
		break;
		
		case "IslaMona_76":
            dialog.text = "Baş üstüne, kaptan!";
			link.l1 = "";
			link.l1.go = "IslaMona_77";
		break;
		
		case "IslaMona_77":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			sld = characterFromId("IM_fraofficer");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			for (i=1; i<=5; i++) 
			{
				sld = characterFromId("IM_soldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			}
			for(i=4; i<=7; i++)
			{
				sld = characterFromId("IM_fra_sailor_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			}
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_20";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "IslaMona_78":
            dialog.text = "Kaptan, mahkumla ilgili meseleyi çözmeye mi geldiniz? Burada nöbet tutmaktan yoruldum.";
			link.l1 = "Onu öldürmek zorundayız. Risk çok büyük, başka seçeneğimiz yok. Yoksa Fransız kolonilerinde yüzümü göstermemem en iyisi olur.";
			link.l1.go = "IslaMona_79";
			link.l2 = "Onu serbest bırakamam, yoksa Fransız kolonilerinde yüzümü göstermesem iyi olur. Zincire vurun ve fabrikada çalıştırın. Onu öldürmekten iyidir.";
			link.l2.go = "IslaMona_80";
		break;
		
		case "IslaMona_79":
            dialog.text = "Anlaşıldı! Hızlıca halledelim. Devam et, Kaptan. Yarın görüşürüz.";
			link.l1 = "";
			link.l1.go = "IslaMona_81";
		break;
		
		case "IslaMona_80":
            dialog.text = "Vay canına. Gerçekten tam bir şeytani dehasın. Senin düşmanın olmak istemezdim. O halde, önce ona biraz açıklama yapmamız gerekecek. Devam et Kaptan. Yarın görüşürüz.";
			link.l1 = "";
			link.l1.go = "IslaMona_81";
			pchar.questTemp.IslaMona.Fraprisoner = "true";
		break;
		
		case "IslaMona_81":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "IslaMona_DefFraPrisonerFin", 10.0); /// идёт внутрь фактории - УСТАНОВИТЬ ЛОКАТОР
		break;
		
		case "IslaMona_82":
            dialog.text = "Ne kıyım oldu! Topu ateşleyemedik belki ama doğrudan pusuya koştular – görülmeye değerdi!";
			link.l1 = "Evet, bu topraklarda çok kan döktük. Ama anlaşılan, bu dünyada bir yuva kurmanın başka yolu yok.";
			link.l1.go = "IslaMona_83";
		break;
		
		case "IslaMona_83":
            dialog.text = "Çok fazla kafana takma, Kaptan. Onları Isla Mona'ya getiren bizzat kaderin ta kendisiydi. Ve sana söyleyeyim, kader bazen tam bir baş belası olabiliyor!";
			link.l1 = "Kader mi, yoksa ada mı?";
			link.l1.go = "IslaMona_84";
		break;
		
		case "IslaMona_84":
            dialog.text = "İkisi de üzerine düşeni yaptı.";
			link.l1 = "Haha! İkisi de güzel! Pekâlâ, cesur Viking. Kupaları topla ve şu cesetleri kaldır. Onları layıkıyla göm. Sonuçta onlar da bizim insanımız...";
			link.l1.go = "IslaMona_85";
		break;
		
		case "IslaMona_85":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_20a";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "IslaMona_86":
            dialog.text = "Evet, Kaptan. Doğru! Rodrigo öyle güzel söyledi ki gözlerim doldu. Kutsal babaların neden onun kıçını kazığa oturtmak istediği şimdi çok açık!";
			link.l1 = "";
			link.l1.go = "IslaMona_87";
			locCameraFromToPos(1.36, 1.32, 0.31, true, 3.44, 0.20, -0.50);
		break;
		
		case "IslaMona_87":
            DialogExit();
			if (GetCharacterIndex("Mirabella") != -1)
			{
				sld = characterFromId("Mirabella");
				sld.dialog.currentnode = "mirabelle_46";
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 0.0);
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && CheckPassengerInCharacter(pchar, "Mary"))
				{
					sld = characterFromId("Mary");
					sld.dialog.currentnode = "IslaMona_2";
					LAi_SetActorType(sld);
					LAi_ActorDialogDelay(sld, pchar, "", 0.0);
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena"))
					{
						sld = characterFromId("Helena");
						sld.dialog.currentnode = "IslaMona_2";
						LAi_SetActorType(sld);
						LAi_ActorDialogDelay(sld, pchar, "", 0.0);
					}
					else
					{
						sld = characterFromId("Himenes_companion_1");
						sld.dialog.currentnode = "island_man_2";
						LAi_SetActorType(sld);
						LAi_ActorDialogDelay(sld, pchar, "", 0.0);
					}
				}
			}
		break;
		
		case "IslaMona_88":
            dialog.text = "Rodrigo, ve burada tam da buduarın içinde bizim piskoposla karşılaştım... Ve sana söyleyeyim, Santiago'daki en iyi mekân burası!";
			link.l1 = "Papazlardan da hoşlanıyorsan en iyi yer burası.";
			link.l1.go = "IslaMona_89";
		break
		
		case "IslaMona_89":
            DialogExit();
			sld = characterFromId("Himenes");
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_90":
            dialog.text = "Evet, o alçak ve kafir Rodrigo'yu gerçekten tam bir korsana çevirdim, hem de nasıl.";
			link.l1 = "Bu arada, beni aydınlat, Rodgar. Neden bu kadar az İspanyol korsan var?";
			link.l1.go = "IslaMona_91";
		break;
		
		case "IslaMona_91":
            dialog.text = "Why so few? Ah, you mean pirate captains? Well, there are plenty of them; they just mostly operate under the Casa de Contratación in Seville. It's like military intelligence, but for some reason they call it a trading house...";
			link.l1 = "";
			link.l1.go = "IslaMona_92";
		break;
		
		case "IslaMona_92":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_77";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_93":
            dialog.text = "Evet, neden onlara bir mesaj gönderip davet etmeyelim ki. Hepsinin patentleri var, üstelik oldukça da idealistler. Genellikle kendi türlerinden çalmazlar, ancak baskın başarısız olursa işler değişir, ha-ha! Sadece Puerto Principe'ye uğrarlar ve sürekli Papaz'la çatışırlar.\nSon zamanlarda biri öne çıktı... Diego de Montoya. En son Wulfric'le sefere çıktığımda, onun maceralarını çokça duydum. Senin de onunla ortak bir yanın var, kaptan. Ama aynı zamanda birbirinizden çok farklısınız... Neyse, ne anlatıyorum ben? Hadi bir tur daha içelim ve biraz da kart oynayalım.";
			link.l1 = "Hiç paran yok. Dublonlarla kumar oynamıyorsun, değil mi?";
			link.l1.go = "IslaMona_94";
		break;
		
		case "IslaMona_94":
            dialog.text = "Her birimiz bir peso ortaya koyuyoruz. Yirmiye kadar oynayalım mı? Hymenes, sen de var mısın?";
			link.l1 = "";
			link.l1.go = "IslaMona_95";
		break;
		
		case "IslaMona_95":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_79";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_96":
            dialog.text = "Oynayalım mı, kaptan?";
			if (sti(pchar.money) >= 20)
			{
				link.l1 = "Başlat!";
				link.l1.go = "IslaMona_97";
			}
			link.l2 = "Ben de pas geçiyorum, Rodgar. Peso olsa da olmasa da, insanlar böyle gemilerini kaybediyor. Hem de adalarıyla birlikte. Sen burada eğlen, ben biraz daha etrafa bakacağım.";
			link.l2.go = "IslaMona_98";
		break;
		
		case "IslaMona_97": // игра в карты
            DialogExit();
			pchar.questTemp.GoldenGirl.Game.IslaMona = "true"; // атрибут квестовой игры
			npchar.money = 20;
			pchar.questTemp.IslaMona.Money = sti(pchar.money);
			pchar.money = 20;
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 1; // ставка
			LaunchCardsGame();
		break;
		
		case "IslaMona_98": // выход из-за стола
            DialogExit();
			IslaMona_ChurchTavernStandUp();
		break;
		
		case "IslaMona_99":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				dialog.text = "Pes! Peki, peki, artık seninle oynamıyorum! Eminim hile yaptın, Kaptan! Ve bir hilekârı öylece bırakmak doğru olmaz!";
				link.l1 = "Dinliyorum, Rodgar.";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Fail"))
				{
					dialog.text = "Ben kazandım, Kaptan. Ama seni böyle eli boş gönderecek değilim, haha!";
					link.l1 = "Pekâlâ, seni alçak. Bu bana ders olsun...";
				}
				else
				{
					dialog.text = "Ben kazandım, Kaptan. Ama seni böyle eli boş göndermeye gönlüm razı olmaz, haha!";
					link.l1 = "Pekâlâ, seni alçak. Bu bana ders olsun...";
				}
			}
			link.l1.go = "IslaMona_100";
		break;
		
		case "IslaMona_100":
            dialog.text = "Ah, hadi ama! Sen bana ve tayfama daracık kamaralardan, bayat sudan ve kafama bir kıymık saplanma riskinden uzak, gerçek bir hayat şansı verdin. Al bak, bu tılsımı Wulfric uzak Danimarka'dan getirmişti, sonra da bana verdi ki... hani, bodrumunda fazla oyalanmayayım diye. Artık bana lazım değil, ama sana - bak gör, çok işine yarayacak.";
			link.l1 = "Teşekkür ederim, Rodgar. Gerçekten de işe yarar bir eşya. Üstelik çok da güzel...";
			link.l1.go = "IslaMona_101_1";
			link.l2 = "Bunu sakla, Rodgar. Sensiz burası var olmazdı. Memleketini hatırlatan bir anı olarak kalsın.";
			link.l2.go = "IslaMona_101_2";
		break;
		
		case "IslaMona_101_1":
			GiveItem2Character(pchar, "talisman3");
			Log_Info("You received 'Thor's Hammer'");
			PlaySound("interface\important_item.wav");
            dialog.text = "Beğendiğinize sevindim, Kaptan. Bir tur daha ister misiniz?";
			link.l1 = "Siz burada biraz dinlenin, ben etrafa bir kez daha bakacağım.";
			link.l1.go = "IslaMona_102";
		break;
		
		case "IslaMona_101_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			AddCharacterExpToSkill(pchar, "Fortune", 2000);
            dialog.text = "Dediğin gibi olsun! O zaman birini de Şans Tanrıçası'na kaldırıyorum, haha! Bir tur daha?";
			link.l1 = "Siz burada kalın, ben etrafa bir kez daha bakacağım.";
			link.l1.go = "IslaMona_102";
		break;
		
		case "IslaMona_102":
            DialogExit();
			DeleteAttribute(pchar, "questTemp.GoldenGirl.Game");
			DeleteAttribute(pchar, "GenQuest.Cards");
			pchar.money = sti(pchar.money)+sti(pchar.questTemp.IslaMona.Money);
			DeleteAttribute(pchar, "questTemp.IslaMona.Money");
			IslaMona_ChurchTavernStandUp();
		break;
		
		case "IslaMona_103":
            dialog.text = "Pekâlâ, Kaptan. İspanyol'la işini hallettin, kutlamamızı yaptık ve baş ağrım da biraz geçti. Hayat güzel!";
			link.l1 = "Ne yapıyorsun, Rodgar?";
			link.l1.go = "IslaMona_104";
		break;
		
		case "IslaMona_104":
			sTemp = "";
            if (CheckAttribute(pchar, "questTemp.IslaMona.MiraRodgar")) sTemp = "I'll get along with the woman. ";
			dialog.text = "Her zamanki gibi avlanacağım, gözüm... bizim meyhanemizde olacak, plantasyondaki kölelere göz kulak olacağım. Mükemmel bir emeklilik.";
			link.l1 = "Sen benden sadece beş yaş büyüksün, Rodgar. Peki ya sen, Rodrigo? Nasıl gidiyor?";
			link.l1.go = "IslaMona_105";
		break;
		
		case "IslaMona_105":
            DialogExit();
			sld = characterFromId("Himenes");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		// <-- Исла Мона
		
		case "repair":
			if (CheckSelfRepairConditions())
			{
				dialog.text = "Elbette kaptan! Tek ihtiyacımız olan kalaslar ve yelken bezi. Çıkış noktanıza gidin ve mürettebata malzemeleri hazırlamalarını emredin.";
				link.l1 = "Yoldayım. Hızlı ol.";
				link.l1.go = "repair_1";
			}
			else
			{
				dialog.text = "Elbette, kaptan, ama gördüğüm kadarıyla geminizin şu anda tamire ihtiyacı yok.";
				link.l1 = "Sadece sordum...";
				link.l1.go = "carpenter_exit";
			}
		break;
		
		case "repair_1":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			chrDisableReloadToLocation = true;
			DoQuestReloadToLocation(Pchar.location.from_sea, "reload", "sea", "Mtraxx_WolfreekRepairShore");
		break;
		
		case "shipstock_info":
			npchar.portman.info = "true";
            dialog.text = "Mümkün, kaptan. Ama birkaç kısıtlama var: Bu adada bunun için uygun sadece iki yer var. Ayrıca, burada her gemi için yalnızca bir subay bırakabilirsin, başkasını bırakamazsın. Mürettebatı burada tutacak kadar kaynağımız yok. Henüz. Son olarak, birinci sınıf gemiler için yer yok.";
			link.l1 = "Anladım. Gemiyi burada bırakmaya hazırım.";
			link.l1.go = "shipstock";
			link.l2 = "Pekâlâ, onu hazırlayacağım.";
			link.l2.go = "carpenter_exit";
		break;
		
		case "shipstock":
			if(CheckAttribute(pchar,"questTemp.IslaMona.Harbour") && pchar.questTemp.IslaMona.Harbour == "done")
			{
				if(sti(npchar.portman) == 3)
				{
					dialog.text = "Kaptan, rıhtımda zaten üç geminiz demirlemiş durumda. Başka yer kalmadı.";
					link.l1 = "Haklısın, unuttum.";
					link.l1.go = "carpenter_exit";
					break;
				}
				else
				{
					if(CheckAttribute(npchar,"FstClassInHarbour") && sti(npchar.portman) > 0)
					{
						dialog.text = "Kaptan, iskelede zaten birinci sınıf bir gemi demirlemiş durumda. Başka yer kalmadı.";
						link.l1 = "Haklısın, unuttum.";
						link.l1.go = "carpenter_exit";
						break;
					}
				}
			}
			else
			{
				if (sti(npchar.portman) == 2)
				{
					dialog.text = "Kaptan, iki geminiz zaten iskeleye demirlemiş durumda. Başka yer kalmadı.";
					link.l1 = "Haklısın, unuttum.";
					link.l1.go = "carpenter_exit";
					break;
				}
			}
			if (GetCompanionQuantity(pchar) < 2)
			{
				dialog.text = "Kaptan, sadece bir geminiz var.";
				link.l1 = "Hm... Daha az içmeliyim...";
				link.l1.go = "carpenter_exit";
				break;
			}
            dialog.text = "Burada bırakmak istediğin gemi hangisi?";
			for(i=1; i<COMPANION_MAX; i++)
			{
				int cn = GetCompanionIndex(PChar, i);
				if( cn > 0 )
				{
					ref chref = GetCharacter(cn);
					if (!GetRemovable(chref)) continue;

					attrL = "l"+i;
					Link.(attrL) = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
					Link.(attrL).go = "ShipStockMan_" + i;
				}
			}
			Link.l9 = "Bekle, fikrimi değiştirdim.";
			Link.l9.go = "carpenter_exit";
		break;
		
		case "ShipStockMan_1":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 1);
			dialog.text = "Bakalım...";
			Link.l1 = "Çok iyi.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Bekle, fikrimi değiştirdim.";
			Link.l2.go = "carpenter_exit";
		break;

		case "ShipStockMan_2":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 2);
			dialog.text = "Bakalım...";
			Link.l1 = "Çok iyi.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Bekle, fikrimi değiştirdim.";
			Link.l2.go = "carpenter_exit";
		break;

		case "ShipStockMan_3":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 3);
			dialog.text = "Bakalım...";
			Link.l1 = "Çok iyi.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Bekle, fikrimi değiştirdim.";
			Link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStockMan_4":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 4);
			dialog.text = "Bakalım...";
			Link.l1 = "Çok iyi.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Bekle, fikrimi değiştirdim.";
			Link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStock_2":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			if(CheckAttribute(pchar,"questTemp.IslaMona.Harbour") && pchar.questTemp.IslaMona.Harbour == "done")
			{
				if(sti(RealShips[sti(chref.Ship.Type)].Class) < 2 && sti(npchar.portman) > 0)
				{
					dialog.text = "Kaptan, daha önce de söylemiştim, limanımızda sadece birinci sınıf bir gemi barındırabiliriz. Mevcut alan bu kadar büyük bir gemi için yetersiz.";
					Link.l1 = "Haklısın, unuttum.";
					Link.l1.go = "carpenter_exit";
					break;
				}
			}
			else
			{
				if (sti(RealShips[sti(chref.Ship.Type)].Class) < 2)
				{
					dialog.text = "Kaptan, birinci sınıf gemiler kıyılarımız için fazla büyük. Bunu sana zaten söylemiştim.";
					Link.l1 = "Haklısın, unuttum.";
					Link.l1.go = "carpenter_exit";
					break;
				}
			}
			if (sti(chref.Ship.Crew.Quantity) > 0 && !CheckAttributeEqualTo(pchar, "questTemp.IslaMona.Tavern", "complete"))
			{
				dialog.text = "Kaptan, bir subay hariç tüm mürettebatını amiral gemine al.";
				Link.l1 = "Ah, doğru! Bunu yapacağım!";
				Link.l1.go = "carpenter_exit";
				break;
			}
			dialog.Text = "Yani, burada kalacağız mı"+XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName+"Acc")+" named '"+chref.Ship.Name+"'. Doğru mu?";
			Link.l1 = "Pekala.";
			Link.l1.go = "ShipStock_3";
			Link.l2 = "Bekle, fikrimi değiştirdim.";
			Link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStock_3":
            LeaveShipIslaMona(&NPChar);
			dialog.text = "Pekâlâ, onu güvenli bir limana ulaştıracağız.";
			Link.l1 = "Mükemmel!";
			Link.l1.go = "carpenter_exit";
		break;
		
		case "shipstockreturn":
            if (GetCompanionQuantity(pchar) < COMPANION_MAX)
			{
				dialog.text = "Hangi gemiyi alacaksınız, kaptan?";
				cn = 1;
				for (i=1; i<MAX_CHARACTERS; i++)
				{
					makeref(chref, Characters[i]);
					if (CheckAttribute(chref, "ShipInStockMan"))
					{
						if (chref.ShipInStockMan == NPChar.id)
						{
							attrL = "l"+cn;
							Link.(attrL)    = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
							Link.(attrL).go = "ShipStockManBack_" + i;
							cn++;
						}
					}
				}
				link.l9 = "Bekle, fikrimi değiştirdim.";
				link.l9.go = "carpenter_exit";
			}
			else
			{
				dialog.text = "Kaptan, filonuzda bir gemi daha için yer yok.";
				link.l1 = "Hm. Görünüşe göre haklısın.";
				link.l1.go = "carpenter_exit";
			}
		break;
		
		 case "ShipStockManBack":
			if (AttributeIsTrue(NPChar, "StoreWithOff") && FindFreeRandomOfficer() < 1 ) {
				dialog.text = "Kaptan, mürettebatında başka bir subay için yer yok gibi görünüyor.";
				link.l1 = "Haklı olabilirsin. Sonra uğrarım—bu arada, burada gözünü dört aç ki, yeni bir sahip gemime el koymasın.";
				link.l1.go = "exit";
				break;
			}
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			dialog.Text = "Onu götürüyor musun?";
			link.l1 = "Evet.";
			link.l1.go = "ShipStockManBack2";
			link.l2 = "Bekle, fikrimi değiştirdim.";
			link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStockManBack2":
			DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			if(CheckAttribute(npchar,"FstClassInHarbour")) DeleteAttribute(npchar,"FstClassInHarbour");
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			DeleteAttribute(chref, "ShipInStockMan");
			SetCompanionIndex(pchar, -1, sti(NPChar.ShipToStoreIdx));
			npchar.portman = sti(npchar.portman)-1;
            pchar.ShipInStock = sti(pchar.ShipInStock)-1;
		break;
		
		case "storadge":
            dialog.text = "Burada mı? Hayır. Ama Wulfric, buradan çok uzakta olmayan bir yerde büyük bir ambar inşa etti. Sağlam bir bina, palmiye yaprakları ve katranlı yelken beziyle güzelce örtülmüş. Kilidi var ve bir düzine ticaret gemisini dolduracak kadar yük odası mevcut\nŞu anda boş, ama istersen bakabilmen için anahtarı bende var. Ne dersin, bakalım mı?";
			link.l1 = "Elbette! Bu arada, bu adada fareler var mı? Ambarımdaki mallarıma zarar verirler mi?";
			link.l1.go = "storadge_1";
		break;
		
		case "storadge_1":
            dialog.text = "Wolf da işi halletti: anakaradan buraya iki kedi getirdi. Ama erkekleri unuttu, bu yüzden bu çılgın dişi kediler her kızgınlık döneminde ortalığı birbirine katıyor. Yine de fareleri ve sıçanları iyi avlıyorlar. Merak etmeyin kaptan, mallarınız haşerelerden ve rüzgârdan güvende olacak.";
			link.l1 = "Harika! Bunu iyi değerlendireceğim. Anahtarını kendinde tut ve bana şu ambarı göster.";
			link.l1.go = "storadge_2";
		break;
		
		case "storadge_2":
			DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			npchar.city = "islamona";
			npchar.Storage.Activate = true;
			SaveCurrentNpcQuestDateParam(npchar, "Storage.Date");
			npchar.MoneyForStorage = 0;
			npchar.storadge = true;
			LaunchStorage(29);
		break;
		
		case "storadge_3":
            dialog.text = "Beni takip et, kaptan.";
			link.l1 = "...";
			link.l1.go = "storadge_4";
		break;
		
		case "storadge_4":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			LaunchStorage(29);
		break;
		
		// Мирабель
		case "mirabelle":
			PlaySound("Voice\English\Girl_Q.wav");
            dialog.text = "Ah...";
			link.l1 = "Şimdi bak sen... Bir kız... Sen burada ne yapıyorsun?";
			link.l1.go = "mirabelle_1";
		break;
		
		case "mirabelle_1":
			PlaySound("Voice\English\Girl_Q.wav");
            dialog.text = "Ah...";
			link.l1 = "...";
			link.l1.go = "mirabelle_2";
		break;
		
		case "mirabelle_2":
            DialogExit();
			npchar.dialog.currentnode = "mirabelle_3";
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_74";
			ChangeCharacterAddressGroup(sld, "LaVega_TwoFloorHouse", "goto", "goto8");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
		break;
		
		case "mirabelle_3":
			PlaySound("Voice\English\LE\Mirabel\Mirabel_01.wav");
            dialog.text = "Señor! Señor "+pchar.name+" Beni öldürme lütfen! Sana yalvarıyorum! Tyrex'e hiçbir şey söylemeyeceğim! O canavardan nefret ediyorum! Ne olur, yalvarırım, por favor!";
			link.l1 = "...";
			link.l1.go = "mirabelle_4";
		break;
		
		case "mirabelle_4":
			DialogExit();
            npchar.dialog.currentnode = "mirabelle_5";
			npchar.greeting = "mirabella_goodgirl";
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_80";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "mirabelle_5":
            dialog.text = "";
			link.l1 = "Hey, kız! Duydun mu? Benimle geleceksin, yoksa bu herif seni öldürür.";
			link.l1.go = "mirabelle_6";
		break;
		
		case "mirabelle_6":
            dialog.text = "Sizinle geleceğim, señor, beni nereye götürüyorsanız!";
			link.l1 = "Pekâlâ, o zaman. Çeneni kapalı tut, yoksa bağırmaya ya da Tyrex'i çağırmaya kalkarsan seni öldürürüm. Adın ne?";
			link.l1.go = "mirabelle_7";
		break;
		
		case "mirabelle_7":
            dialog.text = "Mirabelle...";
			link.l1 = "Kendini düzgün tut, Mirabelle, o zaman bu senin için iyi bitecek. Yanımda kal ve sakın sesini çıkarma.";
			link.l1.go = "mirabelle_8";
		break;
		
		case "mirabelle_8":
            dialog.text = "Söz veriyorum, yapmayacağım, señor.";
			link.l1 = "...";
			link.l1.go = "mirabelle_9";
		break;
		
		case "mirabelle_9":
            DialogExit();
            npchar.dialog.currentnode = "mirabelle_10";
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_85";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
			pchar.questTemp.Mtraxx.Mirabella = "true";
		break;
		
		case "mirabelle_10":
            dialog.text = "Señor?";
			link.l1 = "İyi iş çıkardın kızım, bu yüzden seni sevdim. Şimdi gemime gidiyoruz, orada bir süre küçük bir kamarada kalacaksın. Üzgünüm ama Tyrex'e gidip ona bir şey anlatmanı istemiyorum.";
			link.l1.go = "mirabelle_11";
		break;
		
		case "mirabelle_11":
            dialog.text = "Olmaz, señor! Tyrex'e asla gitmem, o bastardo'ya! Ondan nefret ediyorum! Lo odio!!!";
			link.l1 = "Vay canına! Sana ne yaptı?";
			link.l1.go = "mirabelle_12";
		break;
		
		case "mirabelle_12":
            dialog.text = "Çok... Ondan nefret ediyorum, nefret ediyorum!";
			link.l1 = "Anladım. Vardığımızda, oldukça şık bir evde yaşayacaksın. Yalnız başına. Beni memnun edersen, kimse sana zarar vermez. Şimdi sandalına git... Mirabelle.";
			link.l1.go = "mirabelle_13";
		break;
		
		case "mirabelle_13":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 20.0);
			pchar.quest.mtraxx_pasq_mirabella.win_condition.l1 = "location";
			pchar.quest.mtraxx_pasq_mirabella.win_condition.l1.location = "Shore75";
			pchar.quest.mtraxx_pasq_mirabella.function = "Mtraxx_PasqualeMirabella";
			pchar.quest.mtraxx_pasq_mirabella1.win_condition.l1 = "location";
			pchar.quest.mtraxx_pasq_mirabella1.win_condition.l1.location = "Shore77";
			pchar.quest.mtraxx_pasq_mirabella1.function = "Mtraxx_PasqualeMirabella";
			AddPassenger(pchar, npchar, false);//добавить пассажира
			SetCharacterRemovable(npchar, false);
			SetFunctionTimerCondition("Mtraxx_MirabellaSailOver", 0, 0, 30, false); // месяц на доплыть до Исла Моны
		break;
		
		case "mirabelle_14":
            dialog.text = "Vardık mı, señor?";
			link.l1 = "Evet, tatlım. Burası benim köyüm ve evim. Bu yer bana ait. Ama burada nadiren bulunuyorum, dışarıda yapılacak çok iş var. Burada yaşarken evimi temiz tutmayı unutma, yoksa seni Rodgar ve marangozlarına veririm. Adayı dilediğin gibi gezebilirsin, gerçekten çok güzel, ama zaten buradan kaçış yok.";
			link.l1.go = "mirabelle_15";
			// belamour legendary edition -->
			link.l2 = "Pekala, işte buradayız. Burası benim evim. Bu adadaki her şey bana ait. Sık sık gelmem – sonuçta gemide yaşıyorum – ama yine de birinin eve göz kulak olması gerek. Rodgar, bu onurlu görevi sana devretmeyi büyük bir incelikle kabul etti. İstediğin kadar dolaşabilirsin, ister ormanda ister sahilde, ama yanında mutlaka biri olsun – hâlâ vahşi hayvanlar var. Ayrıca, burada bir gemin olmadan ayrılman da mümkün değil.";
			link.l2.go = "mirabelle_15a";
		break;
		
		case "mirabelle_15a":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
            dialog.text = "Kaçacak hiçbir yerim yok, señor "+pchar.name+". Kimsem yok, kimsenin de bana ihtiyacı yok. Beni bir geneleve satmadığın sürece...";
			link.l1 = "By the hearth, there's a hatch that leads underground. Do not go there; you'll fall into the cave and break your bones, or you won't be able to get back and might die of hunger. And then it would be a pity that I saved you for nothing.";
			link.l1.go = "mirabelle_16";
		break;
		
		case "mirabelle_15":
			ChangeCharacterComplexReputation(pchar,"nobility", -10);
			// <-- legendary edition
            dialog.text = "Gidecek hiçbir yerim yok, señor "+pchar.name+". Artık ailem yok, bir amacım da kalmadı. Yine bir geneleve düşebilirim.";
			link.l1 = "Mağaraya açılan bir kapak var, ondan uzak dur. Aşağısı karanlık ve tehlikeli.";
			link.l1.go = "mirabelle_16";
		break;
		
		case "mirabelle_16":
            dialog.text = "Uzak duracağım, señor.";
			link.l1 = "Yukarıda bir yatak odası daha var. Beni takip et.";
			link.l1.go = "mirabelle_17";
		break;
		
		case "mirabelle_17":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			pchar.quest.mtraxx_islamona_mirabella1.win_condition.l1 = "location";
			pchar.quest.mtraxx_islamona_mirabella1.win_condition.l1.location = "IslaMona_TwoFloorRoom";
			pchar.quest.mtraxx_islamona_mirabella1.function = "Mtraxx_PasqualeMirabellaRoom";
		break;
		
		case "mirabelle_18":
            dialog.text = "";
			link.l1 = "İşte. Sana bütün evi gösterdim. Daha önce kaldığın Tyrex’in yeri kadar kötü değil. Umarım beğenirsin.";
			link.l1.go = "mirabelle_19";
		break;
		
		case "mirabelle_19":
            dialog.text = "Evet, señor. Güzel bir eviniz var. Yokluğunuzda ona iyi bakacağıma söz veriyorum.";
			link.l1 = "Benimle bu kadar işbirlikçi olmandan memnunum. Umarım dürüstsündür. Benimle dürüst ol, yoksa pişman olursun. İyi bir kız ol ve beni üzme, ben de sana iyi davranırım. Charlie Prince sözünün arkasında durur!";
			link.l1.go = "mirabelle_20";
			// belamour legendary edition -->
			link.l2 = "Sana inanıyorum, canım. Burada, Tyrex’in seni tuttuğu o karanlık depoda bağlı kalmandan daha güvende olacaksın bence.";
			link.l2.go = "mirabelle_20a";
		break;
		
		case "mirabelle_20a":
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
            dialog.text = "Teşekkür ederim señor "+pchar.name+". Beni... compañero'nuzun öldürmesine izin vermediğiniz için teşekkür ederim. Bana karşı çok naziksiniz...";
			link.l1 = "Heh, sen de eğlencelisin... Yüzün de güzelmiş, alnındaki damgaya rağmen. Umarım diğer her şey de yerindedir... Hadi bakalım, şimdi kaptanına neler yapabildiğini göster. Denizin sallantısından sonra birkaç saat rahatlayalım.";
			link.l1.go = "mirabelle_21";
			link.l2 = "Pekala. Tamamdır, yapacak çok işim var. Sen de yerleş, Rodgar ve çocuklarla tanış. Döndüğümde biraz daha sohbet ederiz.";
			link.l2.go = "mirabelle_21a";
		break;
		
		case "mirabelle_20":
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			// <-- legendary edition
            dialog.text = "Teşekkür ederim señor "+pchar.name+". Beni öldürmesine izin vermediğin için... compañero’na teşekkür ederim. Çok naziksin.";
			link.l1 = "Heh, sen de ne komik bir tatlısın... Yüzün de güzelmiş, izine rağmen. Umarım geri kalanı da yerindedir... Şimdi kaptanına neler yapabildiğini göster bakalım.";
			link.l1.go = "mirabelle_21";
			// belamour legendary edition -->
			link.l2 = "Pekâlâ. Bu kadar, yapacak çok işim var. Sen de yerleş, Rodgar ve çocuklarla tanış. Döndüğümde biraz daha sohbet ederiz.";
			link.l2.go = "mirabelle_21a";
		break;
		
		case "mirabelle_21a":
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Fortune", 400);
			pchar.questTemp.Mtraxx.MirabellaFirstTimeSex = true;
            DialogExit();
			npchar.InOurHouse = true;
		    npchar.dialog.currentnode = "mirabelle_26";
		    chrDisableReloadToLocation = false;
			pchar.quest.mtraxx_mirabella_setlife.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_mirabella_setlife.function = "Mtraxx_MirabellaSetLife";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		case "mirabelle_21":
			DialogExit();
			
			pchar.questTemp.Mtraxx.MirabellaFirstTimeKiss = true;
			sld = characterFromId("Mirabella");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("IslaMona_MirabelleKiss", "");
		break;
		
		case "mirabelle_22":
			PlaySound("Voice\English\LE\Mirabel\Mirabel_07.wav");
            dialog.text = "Señor "+pchar.name+" sen ne kadar tatlısın... Gerçekten centilmen birisin. Avrupa'dan daha yeni gelmiş olmalısın.";
			link.l1 = "Bana yağ çekme, küçük yalancı, yutmuyorum bunu. Heh, iyisin sen, Mirabelle! Tyrex'in zevki yerinde, heh-heh...";
			link.l1.go = "mirabelle_23";
			locCameraFromToPos(0.55, 1.64, -1.09, true, 0.63, -0.30, -3.12);
		break;
		
		case "mirabelle_23":
            dialog.text = "Ben değilim. Siz bir centilmensiniz. Ama nedense kaba davranıyormuş gibi yapıyorsunuz. Hımm... Bu çok hoşuma gitti. Sizi tekrar görmeyi bekleyeceğim...";
			link.l1 = "Ah evet, bir centilmen... talihli bir centilmen, ha-ha! Pekâlâ, tatlım, şimdilik burada otur bakalım.";
			link.l1.go = "mirabelle_24";
		break;
		
		case "mirabelle_24":
            dialog.text = "Hoşça kal, señor.";
			link.l1 = "...";
			// belamour legendary edition -->
			if(CheckAttribute(pchar,"questTemp.Mtraxx.MirabellaFirstTimeSex"))
			{
				link.l1.go = "mirabelle_28";
				DeleteAttribute(pchar,"questTemp.Mtraxx.MirabellaFirstTimeSex");
			}
			else link.l1.go = "mirabelle_25";
			// <-- legendary edition
		break;
		
		case "mirabelle_25":
            DialogExit();
			npchar.InOurHouse = true;
		    npchar.dialog.currentnode = "mirabelle_26";
			LAi_SetStayType(npchar);
		    chrDisableReloadToLocation = false;
			pchar.quest.mtraxx_mirabella_setlife.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_mirabella_setlife.function = "Mtraxx_MirabellaSetLife";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		case "mirabelle_26":
            dialog.text = TimeGreeting()+", señor "+pchar.name+"!   Seni gördüğüme çok sevindim. Nasılsın?";
			link.l1 = RandSwear()+""+RandPhraseSimple("Vay canına, vay ruhum!","Oh, cesurca dalgalandırdığım siyah bayrağın altında yaşamak ve ölmek daha iyi!")+" Charlie Prince iyi, tatlım.";
			link.l1.go = "mirabelle_26x";
			if (!CheckAttribute(pchar, "questTemp.MirabelleBlock")) {
				if (!CheckAttribute(npchar, "sex_date") || GetNpcQuestPastDayParam(npchar, "sex_date") >= 1)
				{
					link.l2 = "Tatlım, bir kaptanı biraz daha mutlu etmeye ne dersin?";
					link.l2.go = "mirabelle_sex";
				}
			}
		break;
		
		case "mirabelle_26x":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_26";
		break;
		
		case "mirabelle_sex":
            dialog.text = "Sizin için her şey, señor!";
			link.l1 = RandPhraseSimple("Kancaları hazırlayın!","Saldırın!");
			link.l1.go = "mirabelle_sex_1";
		break;
		
		case "mirabelle_sex_1":
            DialogExit();
			
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("", "");
			
			LAi_SetActorType(npchar);
			// belamour legendary edition -->
			if(CheckAttribute(pchar,"questTemp.Mtraxx.MirabellaFirstTimeSex")) npchar.dialog.currentnode = "mirabelle_22";
		    else npchar.dialog.currentnode = "mirabelle_27";
			// <-- legendary edition
			if (pchar.location == "IslaMona_TwoFloorRoom") DoQuestCheckDelay("IslaMona_MirabelleKiss", 0.5);
			else DoQuestReloadToLocation("IslaMona_TwoFloorRoom", "goto", "goto2", "IslaMona_MirabelleKiss");
		break;
		
		case "mirabelle_27":
            dialog.text = "Mhm... Señor, siz tam bir sihirbazsınız! Umarım siz de keyif aldınız? Ben elimden gelenin en iyisini yaptım.";
			link.l1 = "Harika iş çıkardın, tatlım.";
			link.l1.go = "mirabelle_28";
			locCameraFromToPos(0.55, 1.64, -1.09, true, 0.63, -0.30, -3.12);
		break;
		
		case "mirabelle_28":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_26";
			LAi_SetStayType(npchar);
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
		break;
		
		case "mirabelle_sleep":
            dialog.text = "Bu doğru değil, doğru değil! Señor "+pchar.name+" iyi ve nazik biri! O sadece kötü bir korsan rolü yapıyor! Asıl kötü olan sensin, señor "+pchar.name+"?";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep6_1");
		break;
		
		case "mirabelle_29":
            dialog.text = TimeGreeting()+", señor "+pchar.name+"! Seni gördüğüme çok sevindim. Nasılsın? Neden bu kadar üzgün görünüyorsun?";
			link.l1 = "Merhaba, Mirabelle. Sence neden üzgünüm?";
			link.l1.go = "mirabelle_30";
		break;
		
		case "mirabelle_30":
            dialog.text = "Bak, bunu görebiliyorum. Her zamanki gibi değilsin. Seni neşelendirmemi ister misin? Hadi ama! Ormandan çok tatlı meyveler topladım, Rodgar ve adamlarının dün yakaladığı balık da kızartıldı ve hâlâ sıcak.";
			link.l1 = "Bekle. Seninle konuşmak istiyorum.";
			link.l1.go = "mirabelle_31";
		break;
		
		case "mirabelle_31":
            dialog.text = "Elbette, señor, ne derseniz deyin. Sizi dinliyorum";
			link.l1 = "Bana anlat, Tyrex'in eline nasıl düştün ve neden alnında bir hırsız işareti var? Korkma, sana asla zarar vermem. Sadece hikayeni duymak istiyorum.";
			link.l1.go = "mirabelle_32";
		break;
		
		case "mirabelle_32":
            dialog.text = "Ah, señor! My story is brief and dull. I was born in Puerto Rico; my father was a white gentleman, my mother an Indian. I've never seen my pa. When I was a child, I was a servant, and when I grew up, I made the foolish mistake of stealing my master's jewellery. I had never had any of my own, and I wanted some so badly, just to try wearing it for a day. Of course, they found out everything\nThere was a trial, I was whipped, branded, and put in the jail of San Juan. I didn't stay there for too long: one of the officers made a deal with the chief, and I was sold to a brothel in Philipsburg for a handful of golden doubloons\nI spent about a year there. One unfortunate day, we were paid a visit by Tyrex and his wretched friend with glasses.";
			link.l1 = "Pasquale Lavoisier...";
			link.l1.go = "mirabelle_33";
		break;
		
		case "mirabelle_33":
            dialog.text = "Evet-evet, adı señor Pasquale Lavoisier'di. Onlar bende ne buldular hiçbir fikrim yok, ama ziyaretlerinden kısa bir süre sonra Tyrex beni Madame Johanna'dan satın aldı ve beni sandıklar ve mallarla dolu kilitli bir eve kapattı. Hayatımın en kötü zamanlarıydı, San Juan hapishanesinde geçirdiğim günlerden bile daha kötü. Tyrex denizde olmadığı sürece her gün yanıma gelirdi, o zamanlar biraz nefes alabiliyordum, ama señor Lavoisier her geldiğinde ben... ben... Her şeyin en kötüsüydü. Señor "+pchar.name+", lütfen, bundan bahsetmesem olur mu?\nOrada ne kadar kaldığımı bilmiyorum. Sonra sen geldin ve beni o korkunç evden aldın. Senin bu kadar iyi kalpli olman benim için büyük bir şanstı.";
			link.l1 = "İyi mi? Mirabelle, ama ben de sana aynısını yaptım: Seni bir adaya götürdüm ve bir evin içine kilitledim.";
			link.l1.go = "mirabelle_34";
		break;
		
		case "mirabelle_34":
            dialog.text = "Hayır, señor, bu doğru değil. Burada kilitli miyim? Her gün adada dolaşıyorum. Burası harika ve huzurlu bir yer. Çok fazla ev işi yapmak zorunda mıyım? Hiç bile, zaten alıştım artık. Ve sen Tyrex gibi değilsin, onun tüccar arkadaşı gibi de değilsin. Seni gördüğüme her zaman seviniyorum, çok genç ve yakışıklısın. Üstelik bir centilmen...";
			link.l1 = "Mirabelle, seni istediğin bir şehre götürmemi ister misin? Sana yeterince para vereceğim. Nereye gitmek istersin? Herhangi bir koloniyi seçebilirsin.";
			link.l1.go = "mirabelle_35";
		break;
		
		case "mirabelle_35":
            dialog.text = "Señor, beni kovmak mı istiyorsunuz? Lütfen yapmayın, yalvarırım size!";
			link.l1 = "Şey... Normal hayatına dönmek isteyeceğini düşünmüştüm...";
			link.l1.go = "mirabelle_36";
		break;
		
		case "mirabelle_36":
            dialog.text = "Ah, señor "+pchar.name+", and what is there for me? How will I ever marry, being a marked half-blood? I'll be sold to a brothel again. Please, don't send me away. I like it here; I've never felt so peaceful and safe anywhere else. Rodgar and his boys are good men, we're friends, and they've never hurt me—each of them would risk his life for me. I enjoy spending time with them, it's always fun! Sometimes we make a fire on the beach and I dance samba. Please, señor, I'll do anything for you, just let me stay!";
			link.l1 = "Peki, Mirabelle, eğer burayı bu kadar seviyorsan burada kal. Ama bil ki burada tutsak değilsin, istersen her zaman seni buradan götürmemi isteyebilirsin.";
			link.l1.go = "mirabelle_37";
		break;
		
		case "mirabelle_37":
            dialog.text = "Sevgili iyi señorum, teşekkür ederim! Teşekkür ederim! Teşekkür ederim! Bir daha senden böyle bir şey asla istemeyeceğim - bu adanın mahkûmu olarak kalmak istiyorum... ve senin mahkûmun, hihi... Çok naziksin ama bugün çok üzgünsün! Her zamanki gibi şarkı söyleyip küfretmiyorsun.";
			link.l1 = "Belki şarkı söylerim, ama artık küfür yok, Mirabelle. Ve... sana kaba davrandıysam özür dilerim.";
			link.l1.go = "mirabelle_38";
		break;
		
		case "mirabelle_38":
            dialog.text = "İngiliz bir lord gibi sert ve disiplinli mi olacaksın?.. Ah... señor, bu gece senin için dans edip şarkı söylememi ister misin? Sadece senin için. Şimdi benimle gel! Üzüntüye en iyi çare aşktır. Seni o kadar çok özledim ki.";
			link.l1 = "Hah! Güzel bir nokta, sevgili kızım... Hadi gidelim.";
			link.l1.go = "mirabelle_39";
		break;
		
		case "mirabelle_39":
            DialogExit();
			LAi_SetActorType(npchar);
		    npchar.dialog.currentnode = "mirabelle_40";
			if (pchar.location == "IslaMona_TwoFloorRoom") DoQuestCheckDelay("IslaMona_MirabelleKiss", 0.5);
			else DoQuestReloadToLocation("IslaMona_TwoFloorRoom", "goto", "goto2", "IslaMona_MirabelleKiss");
		break;
		
		case "mirabelle_40":
			PlaySound("Voice\English\LE\Mirabel\Mirabel_07.wav");
            dialog.text = "Ah, señor "+pchar.name+", bugün çok naziktin, mhm... Benden memnun musun, sevgili kaptanım?";
			link.l1 = "Her şey harikaydı, Mirabelle.";
			link.l1.go = "mirabelle_41";
			locCameraFromToPos(0.55, 1.64, -1.09, true, 0.63, -0.30, -3.12);
		break;
		
		case "mirabelle_41":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
			LAi_SetStayType(npchar);
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
		break;
		
		case "mirabelle_42":
			bool bMary = GetCharacterIndex("Mary") != -1 && CheckAttribute(pchar, "questTemp.LSC.Mary_officer");
			bool bHelena = GetCharacterIndex("Helena") != -1 && CheckAttribute(pchar, "questTemp.Saga.Helena_officer");
            dialog.text = TimeGreeting()+", señor "+pchar.name+"!  Seni gördüğüme çok sevindim! Nasılsın?";
			link.l1 = ""+LinkRandPhrase("Seni görmek de güzel, kızım.","Merhaba, Mirabelle. Sen her zaman aynısın – neşeli ve güzel, ne hoş bir manzara.","Merhaba, güzelim. Harika görünüyorsun!")+"Ben gayet iyiyim. Umarım sen de iyisindir.";
			link.l1.go = "mirabelle_42x";
			if (!bMary && !bHelena && !CheckAttribute(npchar,"quest.rodgar")) // прогона 3
			{
				if (!CheckAttribute(npchar, "sex_date") || GetNpcQuestPastDayParam(npchar, "sex_date") >= 1)
				{
					link.l2 = "Mirabelle, seni ve gelincik dostunu şimdiden özledim. Deniz kurdunu öper misin?";
					link.l2.go = "mirabelle_43";
				}
			}
		break;
		
		case "mirabelle_42x":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
		break;
		
		case "mirabelle_43":
            dialog.text = "Ah, tatlı kaptanım, ben de seni özledim! Hadi, sabırsızlanıyorum!";
			link.l1 = "...";
			link.l1.go = "mirabelle_39";
		break;
		
		// Jason Исла Мона
		case "mirabelle_44":
			dialog.text = "Señor Kaptan! Kaptan "+pchar.name+"! Çok mutluyum! Bizi kurtaracaksın!";
			link.l1 = "Ben de seni gördüğüme sevindim, Mirabelle. Peki, kayıplar ne durumda?";
			link.l1.go = "mirabelle_45";
		break;
		
		case "mirabelle_45":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_66";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "mirabelle_46":
			dialog.text = "Kaptan, Kaptan, teşekkür ederim! Siz en iyisisiniz, en merhametlisiniz! Beni sadece canavarlardan kurtarmadınız, aynı zamanda bana yeni bir hayat da verdiniz! Hepimize!";
			link.l1 = "";
			link.l1.go = "mirabelle_47";
			locCameraFromToPos(1.25, 1.28, 0.71, false, 2.28, -0.20, 1.91);
		break;
		
		case "mirabelle_47":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && CheckPassengerInCharacter(pchar, "Mary"))
			{
				sld = characterFromId("Mary");
				sld.dialog.currentnode = "IslaMona_2";
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 0.0);
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena"))
				{
					sld = characterFromId("Helena");
					sld.dialog.currentnode = "IslaMona_2";
					LAi_SetActorType(sld);
					LAi_ActorDialogDelay(sld, pchar, "", 0.0);
				}
				else
				{
					sld = characterFromId("Himenes_companion_1");
					sld.dialog.currentnode = "island_man_2";
					LAi_SetActorType(sld);
					LAi_ActorDialogDelay(sld, pchar, "", 0.0);
				}
			}
		break;
		
		case "mirabelle_48":
			dialog.text = "Señor Kaptan!";
			link.l1 = "Sana da merhaba, güzelim. Sıkılmadın, değil mi?";
			link.l1.go = "mirabelle_49";
		break;
		
		case "mirabelle_49":
			dialog.text = "Ah, Kaptan! O korkunç evden beni kurtardığınızdan beri hayatım renklendi ve neşeyle doldu.";
			link.l1 = "Mutlu musun?";
			link.l1.go = "mirabelle_50";
		break;
		
		case "mirabelle_50":
			dialog.text = "Elbette! Ve bu mutluluğu seninle paylaşmak isterim... Yukarıda, odanda seni bekliyor olacağım.";
			link.l1 = "Ne kadın ama...";
			link.l1.go = "mirabelle_51";
		break;
		
		case "mirabelle_51":
			DialogExit();
			LAi_SetActorType(npchar);
		    npchar.dialog.currentnode = "mirabelle_40";
			DoQuestFunctionDelay("IslaMona_ChurchReloadToRoom", 0.5);
			pchar.questTemp.IslaMona.Mirabelle = "true";
		break;
		
		case "mirabelle_52":
			dialog.text = "Señor Kaptan!";
			link.l1 = "Sana da merhaba, güzelim. Sıkılmadın ya?";
			link.l1.go = "mirabelle_53";
		break;
		
		case "mirabelle_53":
			dialog.text = "Ah, Kaptan! O korkunç evden beni kurtardığınızdan beri hayatım renk ve neşeyle doldu.";
			link.l1 = "Mutlu musun?";
			link.l1.go = "mirabelle_54";
		break;
		
		case "mirabelle_54":
			dialog.text = "Çok! Sadece...";
			link.l1 = "Anladım, bana bir şey sormak ister misin?";
			link.l1.go = "mirabelle_55";
		break;
		
		case "mirabelle_55":
			dialog.text = "Evet, Kaptan! Ben... mutluluğumu belli bir adamla paylaşmak istiyorum...";
			link.l1 = "Rahatsız olur mu?";
			link.l1.go = "mirabelle_56";
		break;
		
		case "mirabelle_56":
			dialog.text = "Hayır, hayır, Kaptan. Birlikte çok mutlu olurduk, bundan eminim. Sadece... buna izin verir misin?";
			link.l1 = "Bunu herkesten çok sen hak ediyorsun. Ama ikinizi evlendirecek olan ben değilim, o yüzden sorma bile!";
			link.l1.go = "mirabelle_57";
		break;
		
		case "mirabelle_57":
			dialog.text = "Ha-ha! İyi kalpli efendim! Teşekkür ederim, Señor Kaptan. Dışarıda sizin hakkınızda ne derler bilmem ama, ben sizi her zaman en nazik ve en onurlu insan olarak gördüm.";
			link.l1 = "İyi şanslar, Mirabelle.";
			link.l1.go = "mirabelle_58";
		break;
		
		case "mirabelle_58":
			DialogExit();
			npchar.quest.rodgar = true;
		    npchar.dialog.currentnode = "mirabelle_42";
		break;
		
		// губернатор Картахены
		case "CartahenaMayor":
            dialog.text = "Lanet olası hırsızlar! Her neyse, bizim ulak zaten Porto Bello'ya doğru yolda. Yakında filomuz gelecek ve...";
			link.l1 = TimeGreeting()+", Majesteleri. Sizi böyle güzel bir malikanede görmek büyük bir zevk. Umarım biz gittikten sonra da burada kalırsınız. Yerinizde olsam filoya güvenmezdim, ayrıca biz de burada üç günden fazla kalmayacağız. Eminim Porto Bello'nun soylu beyefendileri size hemen yardıma gelmeyeceklerini anlıyorsunuzdur. O halde lafı uzatmadan asıl meseleye geçelim, ne dersiniz?";
			link.l1.go = "CartahenaMayor_1";
		break;
		
		case "CartahenaMayor_1":
            dialog.text = "Şimdiden iş konuşmaya mı başladın? Pencereden dışarı bak! Adamlarının sokaklarda ve evlerde neler yaptıklarına bir bak!";
			link.l1 = "Oh, majesteleri, eğer yeterince işbirliği yapmazsanız onların neler yapabileceğinin yanında bu hiçbir şey. Umarım bu adamların kim olduğunu anlıyorsunuz...";
			link.l1.go = "CartahenaMayor_2";
		break;
		
		case "CartahenaMayor_2":
            dialog.text = "O korsan Charlie Prince’in ne kadar azılı bir kötülüğe sahip olduğunu biliyorum! Patronunun kim olduğunu da biliyorum! Zamanı gelince, Hispaniola’daki haydut ininizi yerle bir edeceğiz! Ne kadar?";
			link.l1 = "Lafı uzatma, sevgili Valim. En iyisi bana 250.000 peso bul.";
			link.l1.go = "CartahenaMayor_3";
		break;
		
		case "CartahenaMayor_3":
            dialog.text = "Ne?! Senin küstahlığın sınır tanımıyor! Bu bir soygun!";
			link.l1 = "Tabii ki bu soygun. Başka ne olabilir ki? Elitlerini, tüccarlarını ve tacirlerini topla, altınları büyük bir sandıkta biriktir, yoksa... Sana ve halkına çok daha kötü şeyler yaparım.";
			link.l1.go = "CartahenaMayor_4";
		break;
		
		case "CartahenaMayor_4":
            dialog.text = "Lanet olası korsan! Bastardo! Kafir! Defol git buradan!";
			link.l1 = "Senin o pis dilin yüzünden, fidyeyi 300.000’e çıkarıyorum.";
			link.l1.go = "CartahenaMayor_5";
		break;
		
		case "CartahenaMayor_5":
            dialog.text = "CEHENNEMDE YAN, OROSPU ÇOCUĞU!!!";
			link.l1 = "350.000. Devam etmek istiyor musun?";
			link.l1.go = "CartahenaMayor_6";
		break;
		
		case "CartahenaMayor_6":
            dialog.text = "Şehirde böyle bir para yok!";
			link.l1 = "Yalan söylüyorsun. Bu mümkün değil. Burada en az bir milyon toplayabilirdik ama ne yazık ki bunun için yeterli vaktimiz yok. Bu yüzden cömert ve anlayışlı olacağım. Meblağı biliyorsun. Git ve getir.";
			link.l1.go = "CartahenaMayor_7";
		break;
		
		case "CartahenaMayor_7":
            dialog.text = "Sana tekrar söylüyorum, Charlie Prince: Cartagena'da öyle bir para yok!";
			link.l1 = "Ah... nasıl bu kadar anlayışsız olabiliyorsun. Pala! Etrafı araştır ve bulduğun herkesi buraya getir. İyice araştır! Ve biz de şimdilik burada bekleyeceğiz, efendim...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CartahenaInResidence");
		break;
		
		case "CartahenaMayor_8":
            dialog.text = "";
			link.l1 = "Hey, señor 'İnatçı'! Cartagena'nın güzel şehrinde para toplamaktan vazgeçmedin mi hâlâ?... Ne oldu, neden birden bu kadar ciddileştin?! İyi misin? Sana biraz su getireyim mi?";
			link.l1.go = "CartahenaMayor_9";
		break;
		
		case "CartahenaMayor_9":
            dialog.text = "";
			link.l1 = "Anladığım kadarıyla, bu iki hanımefendi eşiniz ve kızınız, doğru mu? Üçüncü kız hizmetçi gibi duruyor, ona pek önem vermiyorsunuz anlaşılan, o yüzden ona zarar vermeyeceğiz. Ama şu iki güzel hanım, silah arkadaşım señor Cutlass'ın ilgisini çekebilir. Onlardan hoşlanmış gibi görünüyor, señor. Peki ne olacak? Fidye işini halledecek misiniz?";
			link.l1.go = "CartahenaMayor_10";
		break;
		
		case "CartahenaMayor_10":
            dialog.text = "Benim... Benim zamana ihtiyacım olacak.";
			link.l1 = "Aha! Şimdi konuşuyorsun! Peki burada kim bastardo? Adamlarım senin vatandaşlarını korkuturken umurunda bile olmadı ama iki kadının olunca işler değişti, öyle mi? Benimle pazarlık etmeye cüret mi ettin, seni dangalak? Sana Charlie Prince'e bulaşmanın ne demek olduğunu göstereceğim!";
			link.l1.go = "CartahenaMayor_10x";
		break;
		
		case "CartahenaMayor_10x":
            dialog.text = "";
			link.l1 = "Git ve lanet fidyeyi topla. 350.000 ve bir peso bile eksik olmasın. Bir günün var. Biz burada kalıp biraz şarap içeceğiz ve bu güzel kadınlarla sohbet edeceğiz... Acele et, amigo, yoksa buradaki dostum señor Cutlass'la birlikte güzellerine aşık olabiliriz, o zaman onları da kurtarmak zorunda kalırsın. Hadi! Yürü!";
			link.l1.go = "CartahenaMayor_11";
		break;
		
		case "CartahenaMayor_11":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Mtraxx_CartahenaResidenceWait", 5.0);
		break;
		
		case "CartahenaMayor_12":
			AddMoneyToCharacter(pchar, 350000);
            dialog.text = "Al kanını al, Charlie Prince!";
			link.l1 = "Fidye parasını topladın mı? Harika! Ama bir saat geciktin, sevgili valim. Bu fazladan saat bana ve Cutlass’a, hayatımızın bu güzeller olmadan fazlasıyla sıkıcı olacağını gösterdi. Ne de olsa bizimle ne kadar nazik ve sohbetliydiler...";
			link.l1.go = "CartahenaMayor_13";
		break;
		
		case "CartahenaMayor_13":
            dialog.text = "Sen... sen!";
			link.l1 = "Ah, işinden dolayı çok gerginsin dostum. Şaka yapıyordum... Kılıcını al! Hadi, gidiyoruz!";
			link.l1.go = "CartahenaMayor_14";
		break;
		
		case "CartahenaMayor_14":
            DialogExit();
			AddQuestRecord("Roger_9", "7");
			AddDialogExitQuestFunction("Mtraxx_CartahenaToFort");
		break;
		
		// Камилла
		case "camilla":
			PlaySound("Voice\English\hambit\Girls_3.wav");
            dialog.text = "Demek bu, ünlü korsan Charlie Prince, İspanyol Güney Ana Karası'nın korkulu rüyası!";
			link.l1 = RandSwear()+"Heh, Tortuga'da bu kadar popüler olduğumu bilmiyordum. Senin adın ne, güzel kız?";
			link.l1.go = "camilla_1";
		break;
		
		case "camilla_1":
            dialog.text = "Benim adım Camilla.";
			link.l1 = "Camilla... Bir zamanlar Fransa'da bu isme sahip bir kızı tanımıştım. Ne kadar da uzun zaman geçti!";
			link.l1.go = "camilla_2";
		break;
		
		case "camilla_2":
			PlaySound("ambient\tavern\orijka_003.wav");
            dialog.text = "";
			link.l1 = "(kusarak) ... kahretsin... Özür dilerim, prenses, ama Prens bu gece biraz fazla içmiş. Yani... ee... neden bana geldin?";
			link.l1.go = "camilla_3";
		break;
		
		case "camilla_3":
            dialog.text = "Çeşitli nedenlerle. Ya da belki hiçbir neden olmadan.";
			link.l1 = "Tanrım, bu iş çok karmaşık. Sen tam bir muamma gibisin, kızım.";
			link.l1.go = "camilla_4";
		break;
		
		case "camilla_4":
            dialog.text = "Her genç kızın bir sırrı olmalı.";
			link.l1 = "Görünüşe göre bu gizemi çözmemi istiyorsun. Öyle mi? Hanımefendilerin sırlarını çözmekte ustayım, yemin ederim! Bir meyhaneye gidip biraz şarap içelim mi? Sana en güzel ikramı ben yapacağım!";
			link.l1.go = "camilla_5";
		break;
		
		case "camilla_5":
            dialog.text = "Mmm... Sert adamları severim. Ama aşağıda sarhoş ayak takımıyla şarap içmem. Bize bir oda ayarla, orada içer konuşuruz.";
			link.l1 = RandSwear()+"Çekicisin! Beni takip et!";
			link.l1.go = "camilla_6";
		break;
		
		case "camilla_6":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1 = "locator";
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1.location = "Tortuga_town";
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1.locator_group = "reload";
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1.locator = "reload4_back";
			pchar.quest.mtraxx_retribution_tavern.function = "Mtraxx_RetributionToTavern";
		break;
		
		case "camilla_7":
			PlaySound("Voice\English\hambit\Gr_officiant_1.wav");
            dialog.text = "Hadi ama... Dök gitsin, hanımefendiyi bekletme!";
			link.l1 = "Elbette, canım!";
			link.l1.go = "camilla_8";
		break;
		
		case "camilla_8":
			LAi_Fade("", "");
			PlaySound("ambient\tavern\krujki_005.wav");
			PlaySound("ambient\tavern\naliv_003.wav");
			PlaySound("ambient\tavern\glotok_001.wav");
			WaitDate("", 0, 0, 0, 1, 5);
            dialog.text = "Mmm... Düşünsene, burada tek başıma Charlie Prince ile birlikteyim, harika bir şarap içiyorum...";
			link.l1 = "Bu yolculuktan benimle birlikte çok keyif alacaksın, söz veriyorum! Charlie Prince, kendini ona teslim eden hanımefendilere nazik ve şefkatlidir. Teslim olacak mısın, prenses?";
			link.l1.go = "camilla_9";
		break;
		
		case "camilla_9":
            dialog.text = "Hihi... Tabii ki, tatlım! Sözlerin o kadar cazip geliyor ki, biliyor musun...";
			link.l1 = "O halde, vakit kaybetmeyelim, güzelim?";
			link.l1.go = "camilla_10";
		break;
		
		case "camilla_10":
            dialog.text = "Ah! Bayıldım! Gerçek adamlar!..";
			link.l1 = "...";
			link.l1.go = "camilla_11";
		break;
		
		case "camilla_11":
            DialogExit();
			pchar.GenQuest.FrameLockEsc = true;
			bDisableCharacterMenu = true;
			ResetSound();
			WaitDate("", 0, 0, 0, 2, 30);
			SetLaunchFrameFormParam("", "", 0, 5.1);
			SetLaunchFrameFormPic("loading\inside\censored1.tga");
			if(bSFW) PlayStereoSound("sex\sex_sfw.wav");
			else PlayStereoSound("sex\sex2.wav");
			LaunchFrameForm();
			if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	
			{
				AddCharacterHealth(pchar, 6);
				AddCharacterMaxHealth(pchar, 1.0);
			}
			else AddCharacterHealth(pchar, 3);
			LAi_SetCurHPMax(pchar);
			DoQuestCheckDelay("Mtraxx_RetributionRoomSex", 5.1);
		break;
		
		case "camilla_12":
            dialog.text = "Mmm...";
			link.l1 = "Beğendin mi, prensesim?";
			link.l1.go = "camilla_13";
		break;
		
		case "camilla_13":
            dialog.text = "Elbette! Umarım sen de benden hoşlanmışsındır.";
			link.l1 = "Heh! Şimdi kafam bile pırıl pırıl oldu!";
			link.l1.go = "camilla_14";
		break;
		
		case "camilla_14":
            dialog.text = "Prensim, sizden bir ricam var. Bana yardım eder misiniz?";
			link.l1 = "Senin için gökyüzünden bir yıldız bile getirirdim, ha-ha! Devam et.";
			link.l1.go = "camilla_15";
		break;
		
		case "camilla_15":
            dialog.text = "La Vega'ya gitmem lazım, Tyrex'i görmem gerek. Ondan korkuyorum, ama siz birlikte iş yapıyorsunuz. Lütfen beni ona götürün.";
			link.l1 = "Şuna bak! Böyle tatlı, narin bir kız neden Kodeksin Koruyucusu'nu görmek ister ki?";
			link.l1.go = "camilla_16";
		break;
		
		case "camilla_16":
            dialog.text = "Bu tatlı, narin kız biraz para kazanmak istiyor. Merhum babam ve kardeşlerim bana pek para bırakmadı. Tyrex bunu düzeltebilir.";
			link.l1 = "Gerçekten mi? Nasıl yani? Bir İspanyol gemisinin peşine mi düştün? Ha-ha!";
			link.l1.go = "camilla_17";
		break;
		
		case "camilla_17":
            dialog.text = " Kervanları ve şehirleri yağmalamak zorlu adamların işi, tıpkı senin gibi, tatlım. Marcus için başka bir işim var. O bilgi alıp satıyor, değil mi? Bende bir şey var... Kendim kullanamam, ama o kullanabilir. Bana küçük bir pay kalması bile yeter.";
			link.l1 = "İlginç! Devamını anlat.";
			link.l1.go = "camilla_18";
		break;
		
		case "camilla_18":
            dialog.text = "Hm... Bilmiyorum...";
			link.l1 = "Ah, hadi ama. Kendimi Tyrex'in sağ kolu olarak görebilirsin, şimdiye kadar onun için epey araştırma yaptım, bana güven. Eğer verdiğin bilgi buna değerliyse – onu bizzat ben satın alırım.";
			link.l1.go = "camilla_19";
		break;
		
		case "camilla_19":
            dialog.text = "Pekala. Sana daha fazlasını anlatacağım, ama parayı almadan ayrıntı yok. Anlaştık mı, tatlım?";
			link.l1 = "Tabii güzelim. Charlie Prince ortaklarını yarı yolda bırakmaz... ne demek istediğimi anladın, ha-ha-ha! Devam et, seni dinliyorum.";
			link.l1.go = "camilla_20";
		break;
		
		case "camilla_20":
            dialog.text = "... Babam bir ticaret şilebinde kaptandı. Bir gün, bir şekilde Main'in ormanlarının derinliklerinde yatan eski bir İspanyol maden yerleşimini öğrendi. Yirmi yıl önce bir depremle yıkılmış. Madenciler orayı terk etmiş ve gizli geçitler unutulmuş. Bir tanesi hariç. Babam onu buldu\nKardeşlerimi ve bir rehberi yanına alıp oraya gitti, yıllar önce çıkarılıp eritilmiş altınla dolu bir yer buldular. Çok fazla altın. En az bir milyon peso. Babam altını taşımak için adam getirmek üzere gemiye döndü ama döndüğünde geminin gitmiş olduğunu görünce şok oldu. Görünüşe göre birinci zabiti isyan başlatmış ve onu kardeşlerimle birlikte ıssız kıyılarda bırakmışlar\nBir sandal yapıp kıyı boyunca yelken açmışlar, çaresizce yerleşim aramışlar ama... (ağlar) bir fırtına yakalamış onları ve (ağlar) kardeşlerim ölmüş. Babam sağ kurtulmuş ama eve döndükten sonra fazla yaşamamış – kardeşlerimin ölümü onu her gün yavaş yavaş öldürüyordu. Ölmeden önce bir harita yaptı ve bana verdi\nBana, evlendiğimde kocamın oraya gidip altını alması gerektiğini ve hayatımızı krallar gibi yaşamamız gerektiğini söyledi. Elbette öyle yapacağız, ama adamımın o lanetli ormanlara bir daha girmesine asla izin vermem! Bir milyon peso, dedi babam, ama bu bana göre değil. Böyle bir ödülü ancak en iyi ve en dayanıklı adamlar alabilir – Marcus Tyrex gibi adamlar. Bu yüzden onunla buluşmaya gidiyorum.";
			link.l1 = "Harita için ne kadar istiyorsun?";
			link.l1.go = "camilla_21";
		break;
		
		case "camilla_21":
            dialog.text = "İki yüz altın doblon. Ödülle kıyaslanınca hiçbir şey. Tyrex buna razı olur, eminim. Crassus kadar zengin o.";
			link.l1 = "Heh! Ya bu her şey bir oyun ise?";
			link.l1.go = "camilla_22";
		break;
		
		case "camilla_22":
            dialog.text = "İntihar etmek mi istiyorum sanıyorsun? Tyrex'e kafa tutmak mı? Tatlım, hiç yaşamamaktansa yoksulluk içinde yaşamak daha iyidir. Peki, beni oraya götürecek misin? Lütfen...";
			link.l1 = "Harita nerede? Bana gösterecek misin?";
			link.l1.go = "camilla_23";
		break;
		
		case "camilla_23":
            dialog.text = "Rahibim onu güvende tutuyor. Sana gösterebilirim, ama 200 doblon isterim.";
			link.l1 = "Pekala! Satın alıyorum. Hanlarda yabancılar bazen değersiz şeyler için çok daha fazlasını isterler.";
			link.l1.go = "camilla_24";
		break;
		
		case "camilla_24":
            dialog.text = "Gerçekten mi? Doğru mu bu, sevgilim? La Vega'ya gitmeyeceğim için öyle mutluyum ki! Açıkçası, Marcus'tan korkuyorum. Bu arada, senden de korkuyorum... ama biraz daha az.";
			link.l1 = "Böylesine tatlı bir küçük kızın benden korkmasına gerek yok. Parayı nereye getirmemi istersin?";
			link.l1.go = "camilla_25";
		break;
		
		case "camilla_25":
            dialog.text = "Bir anlaşma yapalım: beni herhangi bir gün sabah saat ondan öğleden sonra bire kadar kilisemizde bul. Bu kutsal yerin koruması altında kendimi çok daha güvende hissedeceğim. Anlaşmamızı orada tamamlarız.";
			link.l1 = "Hâlâ benden korkuyor musun? Ha-ha! Merak etme Camilla, sana ihanet etmeyeceğim. Charlie Prince iki yüz doblon için bu kadar alçalmaz, hem sana yardım etmek istiyorum.";
			link.l1.go = "camilla_26";
		break;
		
		case "camilla_26":
            dialog.text = "Harika. Pekâlâ, yakışıklı, seni bekliyor olacağım... Bu gece birlikte geçirdiğimiz harika zaman için teşekkür ederim! Tanıştığımıza çok memnun oldum!";
			link.l1 = "Yakında görüşürüz, güzelim.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionOutRoom");
		break;
		
		case "camilla_27":
			PlaySound("Voice\English\hambit\Girls_3.wav");
            dialog.text = "Peki? Parayı getirdin mi, canım?";
			if (PCharDublonsTotal() >= 200) // belamour legendary edition
			{
				link.l1 = "Evet. İşte altının, şimdi haritayı ver.";
				link.l1.go = "camilla_28";
			}
			else
			{
				link.l1 = "Tam arkasındayım.";
				link.l1.go = "camilla_27x";
			}
		break;
		
		case "camilla_27x":
            DialogExit();
			npchar.dialog.currentnode = "camilla_27";
		break;
		
		case "camilla_28":
			RemoveDublonsFromPCharTotal(200); // belamour legendary edition
			GiveItem2Character(pchar, "mapEnrico"); 
            dialog.text = "Teşekkür ederim, canım... Al, bu senin. Babamın hatırası üzerine yemin ederim – bu harita sahte değil, seni tam gitmen gereken yere götürecek...";
			link.l1 = "Güzel, tatlım. Anlaşmamızı tıpkı geçen seferki gibi kutlamaya ne dersin?";
			link.l1.go = "camilla_29";
		break;
		
		case "camilla_29":
            dialog.text = "İsterdim Prens, ama şu anda günah çıkarmadan önce kendimi hazırlıyorum, bu yüzden her türlü cazibeden uzak durmam gerekiyor. Bunu bir dahaki sefere yapalım.";
			link.l1 = "Ah, benimle dalga geçiyorsun, kızım. Peki! Kaybedecek vaktimiz yok: az sonra denize açılıyoruz. Yemin ederim, eğer babanın haritası gerçekten beni altına götürürse, ödülünü iki katına çıkaracağım.";
			link.l1.go = "camilla_30";
		break;
		
		case "camilla_30":
            dialog.text = "Çok cömertsin, canım. İyi yolculuklar!";
			link.l1 = "Yo-ho-ho!";
			link.l1.go = "camilla_31";
		break;
		
		case "camilla_31":
            DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Roger_10", "2");
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.quest.mtraxx_retribution_carataska.win_condition.l1 = "location";
			pchar.quest.mtraxx_retribution_carataska.win_condition.l1.location = "shore10";
			pchar.quest.mtraxx_retribution_carataska.function = "Mtraxx_RetributionCarataska";
			pchar.questTemp.Mtraxx.Retribution = "carataska";
		break;
		
		case "camilla_sleep":
            dialog.text = "Sizin alçaklarım babamı ve kardeşlerimi öldürdü. Cartagena'ya yaptığınız saldırı oradaki her aileye acı getirdi. Umarım şimdi korkuyorsunuzdur, tıpkı bizim, Cartagena halkının, sizin vahşileriniz sokaklarda ve evlerde eğlenirken hissettiğimiz korku gibi. Cehennemde yanacaksın, Charlie Prince.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep4");
		break;
		
		// дон Энрико - народный мститель
		case "enrico":
			PlaySound("Voice\English\LE\Zorro\Don_Enriko_01.wav");
            dialog.text = "Bu dünyada bana, kutudaki farelerin birbirini parçalamasını izlemek kadar keyif veren çok az şey var!\nSadece en güçlü ve en iğrenç fare hayatta kalır. Sonra yapman gereken tek şey, onu sıkıca yakalamak...";
			link.l1 = "Argh! Sen de kimsin?!";
			link.l1.go = "enrico_1";
		break;
		
		case "enrico_1":
			PlaySound("Voice\English\LE\Zorro\Don_Enriko_02.wav");
            dialog.text = "I am Don Enrico. The English scum call me Fox, the Dutch call me Vos, the French call me Renaud. But I prefer my Spanish nickname - Zorro. I punish the wicked who torment and terrorise the common folk, the most vulnerable among the people.\nThis trial today will judge four pirates of Marcus Tyrex: Bold Jeffry, Pelly the Cutlass, Luke the Leprechaun, and Charlie Prince - these bandits are responsible for the massacres in Merida and Cartagena. The last bastard, called Handsome Jean, didn't show up here; he must be the cleverest of your lot.";
			link.l1 = "Ne?!";
			link.l1.go = "enrico_2";
		break;
		
		case "enrico_2":
            dialog.text = "Sen tam bir alçaksın, Charlie Prince, ama aptal değilsin. Sanırım bunu çoktan anladım. Bu, sahte haritalar, belgeler, sözler ve altınla gümüş vaadiyle sana kurduğum bir tuzaktı. Hepinizi buraya, bu zindanlara çektim ve siz de birbirinizi yok ettiniz; sizi buna sürükleyen ise o iğrenç huylarınız oldu: kıskançlık, açgözlülük, kötülük ve vicdansızlık. Gerçekten de bu, tam anlamıyla bir ilahi adaletti!";
			link.l1 = "Camilla... O kızda bir gariplik olduğunu baştan anlamalıydım!";
			link.l1.go = "enrico_3";
		break;
		
		case "enrico_3":
            dialog.text = "Camilla adında bir kız, Cartagena'da babası ve kardeşleriyle huzurlu bir hayat sürüyordu. Tam evlenmek üzereyken sen ve şeytanların şehre saldırdınız. Korsanların, ona en yakın herkesi öldürdü, bu yüzden onları ne pahasına olursa olsun intikamını almaya yemin etti. Bu, onun için çok ağır bir roldü. Ailesinin ölümünden sorumlu o alçağın yatağına bile girmek zorunda kaldı. O an ne hissettiğini düşünmek bile istemiyorum.\nZavallı kız, günlerce kilisede af dilemek için dua etti. Ona verdiğin kanlı doblonları, saldırından en çok zarar görenlere bağışladı. Şimdi bir manastırda, yazık. Hayatını mahvettin, pislik! Düşünsene! Kaç Camilla, Isabela, Rosita'ya tecavüz edip dul bıraktın! Kaç Juan, Carlos, Pedro'yu öldürdünüz, işkence ettiniz!\nMerida'yı hatırla! Kasabanın başına söz verip yakmayacağına dair yemin ettin, sonra da tüm yeri yerle bir edip ateşe verdin!";
			link.l1 = "Bunu asla yapmak istemedim! Konaktan çıktığımda, yangın her yeri sarmıştı zaten. Ben böyle bir şey emretmedim...";
			link.l1.go = "enrico_4";
		break;
		
		case "enrico_4":
            dialog.text = "Korsanlarının yaptıklarından sen sorumlusun. Boynunda asılı ölü adamlar var ve yakında seni de cehenneme sürükleyecekler!";
			link.l1 = "Hadi o zaman! Ha? Benimle dövüş! Bunu istiyorsun, değil mi?! O zaman yapalım!";
			link.l1.go = "enrico_5";
		break;
		
		case "enrico_5":
            PlaySound("Voice\English\LE\Zorro\Don_Enriko_03.wav");
            if (CharacterIsAlive("Tonzag") && CheckPassengerInCharacter(pchar, "Tonzag"))
			{
				dialog.text = "No, Charlie Prince. Don't reach for your weapon, it's pointless... I could kill you easily, but a quick death is not enough for a bastard like you. You will stay in this dungeon forever. The door you used to enter is blocked by a stone outside, and the door behind me will be blocked too; besides, there are sturdy bars protecting it. That's it, there is no way out except for these two doors\nWhat the... I locked all the doors!";
				link.l1 = "Ne oluyor...";
				link.l1.go = "exit";
				AddDialogExitQuest("Mtraxx_RetributionEnricoAndTonzag");
			}
			else
			{
				dialog.text = "No, Charlie Prince. Don't reach for your weapon, it's pointless... I could kill you easily, but a quick death is not enough for a bastard like you. You will stay in this dungeon forever. The door you used to enter is blocked by a stone outside, and the door behind me will be blocked as well; besides, there are sturdy bars protecting it. That's it, there is no way out except for these two doors\nThere is water below, so you'll have enough time to reflect on your deeds. All alone here, in the darkness, perhaps you will repent for what you have done before you starve to death or go insane\nOne last thing - the treasure below is a fake. The gold ingots are nothing but coloured lead. The doubloons are real, though, but there are only a few of them, just enough to cover the rocks inside the chests. A fitting end for pirates, eh? You killed each other for a fake treasure, Prince. Farewell now. Pray for your sinful soul, Charlie Prince, if you still remember how...";
		// belamour legendary edition -->
				link.l1 = "Marcus Tyrex’in öncüsünün tamamını tek başıma öldürdüm! Bu paslı parmaklıkların beni durduracağını mı sanıyorsun?! Kafanı kullanıp hepsini kırarım!";
				link.l1.go = "enrico_5a";
				link.l2 = "Belki de bunu hak ettim. Ama pes etmeyeceğim, duyuyor musun?! Bir yolunu bulacağım, her zaman bulurum!";
				link.l2.go = "enrico_5b";
			}
		break;
		
		case "enrico_5a":
			AddCharacterHealth(pchar, 5);
			AddCharacterExpToSkill(pchar, "FencingL", 400);
			AddCharacterExpToSkill(pchar, "FencingS", 400);
			AddCharacterExpToSkill(pchar, "FencingH", 400);
			AddCharacterExpToSkill(pchar, "Pistol", 400);
            DialogExit();
			AddDialogExitQuestFunction("Mtraxx_RetributionEnricoGo");
		break;
		
		case "enrico_5b":
			AddCharacterExpToSkill(pchar, "Leadership", 1200);
			ChangeCharacterComplexReputation(pchar, "nobility", 15);
            DialogExit();
			AddDialogExitQuestFunction("Mtraxx_RetributionEnricoGo");
		break;
		// <-- legendary edition
		
		case "enrico_Tonzag_1":
			dialog.text = "Haklısın, kapı eski olsa da güvenilir. Kapıyı indirmediğin için sağ ol—beni geciktirirdi. Ama uzun sürmezdi.";
			link.l1 = "Hercule Tonzag, Kel Gaston! Senin gibi birinin Prens ve onun tayfasıyla işbirliği yapacağını tahmin etmeliydim. Seni burada da görmek ne büyük şans.";
			link.l1.go = "enrico_Tonzag_2";
			sld = CharacterFromID("Zorro");
			CharacterTurnToLoc(sld, "quest", "door");
		break;
		
		case "enrico_Tonzag_2":
			dialog.text = "Şanslı mı diyorsun? Ölmek için acele ediyorsan... Gerçi, onunla yüzleşmek yerine açlığa terk ettiğine göre, pek de öyle olmadığını düşünmüştüm.";
			link.l1 = "Beni korkaklıkla mı suçluyorsun? Ne kadar da aptalca. Prense de söylediğim gibi, ölüm onun için fazla kolay bir ceza. O bana rakip olamaz.";
			link.l1.go = "enrico_Tonzag_3";
		break;
		
		case "enrico_Tonzag_3":
			dialog.text = "Ve sen bana rakip olamazsın, Don.";
			link.l1 = "On yıl önce mi? Kesinlikle. Şimdi mi? Pek sayılmaz. Üstelik...";
			link.l1.go = "enrico_Tonzag_4";
		break;
		
		case "enrico_Tonzag_4":
			dialog.text = "Dahası ne? Bu dramatik duraklama da neyin nesi? Gerçi, şu karnaval maskeni düşününce... Beni hemen saf dışı bırakmak için erken değil mi?";
			link.l1 = "Kapıyı kırdın, ama kaba kuvvet bana yetmez. Reflekslerin nasıl? Görüşün? Sadece bir gözle. Benim ikisi de yerinde.";
			link.l1.go = "enrico_Tonzag_5";
		break;
		
		case "enrico_Tonzag_5":
			dialog.text = "Şimdilik, en azından. Heh-heh.";
			link.l1 = "Porto Bello için, Prens'ten daha beter bir sonu hak ediyorsun!";
			link.l1.go = "enrico_Tonzag_6";
		break;
		
		case "enrico_Tonzag_6":
			dialog.text = "Ha, demek yaptıklarımı duydun? Sanırım senin tayfan arasında bunun dedikodusu bir süre daha sürecek. O zaman başımdan neler geçtiğini de biliyorsun.";
			link.l1 = "Yaşlandın, Tonzag, ve bu sefer kibirin sonun olacak. Evet, sadece duymadım – Cartagena ve Merida senin işin. Tıpkı Porto Bello gibi.";
			link.l1.go = "enrico_Tonzag_7";
		break;
		
		case "enrico_Tonzag_7":
			dialog.text = "Bunu iltifat olarak alabilirdim, ama hayır, benim işim değil. Uzaktan bakınca benziyor olabilir. Fazla acemice. Gerçi, Porto Bello'da bile... bazı olaylar olmuştu.";
			link.l1 = "Olaylar mı?! O gün bir kişi öldü... Ve o katliamı sen başlattığın için, herkesi bizzat öldürmemiş olsan da, hâlâ seni suçluyorum. Her 'olay'dan seni sorumlu tutuyorum.";
			link.l1.go = "enrico_Tonzag_8";
		break;
		
		case "enrico_Tonzag_8":
			dialog.text = "Bir kişi mi diyorsun... O gün birçok kişi öldü. Daha açık ol.";
			link.l1 = "Gerçekten, bunu söyleyebiliyorsan kalbin yok demektir! Ama cevap vereceğim: Öldürmemen gereken kişi. Babam, Don de la Vega. O hayatta olsaydı, asla bu yola sapmazdım ve sizler de hâlâ yaşıyor olurdunuz.";
			link.l1.go = "enrico_Tonzag_9";
		break;
		
		case "enrico_Tonzag_9":
			dialog.text = "Kes sesini, velet. Sevgili karım da... orada öldü.";
			link.l1 = "Taziye mi bekliyorsun? Boşuna. Bu senin için Tanrı'nın cezası. Demek bir kalbin varmış – küçücük ve kapkara. Onu kılıcımla bulacağım.";
			link.l1.go = "enrico_Tonzag_10";
		break;
		
		case "enrico_Tonzag_10":
			dialog.text = "Ah, kalbimle ilgili bu tantanalar... Benim gördüklerimden daha kötüsünü gördüğünü sanıyorsan, yanılıyorsun.";
			link.l1 = "Beni sadece para savuran şımarık bir zengin çocuğu mu sanıyorsun? Şunu bil: Kumar ya da kadınlar için tek bir altın harcamadım! Hepsini senin gibilerle mücadeleye yatırdım ve hayatımı buna adadım!";
			link.l1.go = "enrico_Tonzag_11";
		break;
		
		case "enrico_Tonzag_11":
			dialog.text = "Ve ne için? Pek başarılı görünmüyor. Ticaret yolları hâlâ korsanlarla dolup taşıyor. Bu savaşta yalnızsın. Onlarsa koca bir ordu.";
			link.l1 = "Birinin yapması gerek. En azından birinin. Belki de sadece bir korsan kaptanını öldürerek birkaç hayat kurtarabilirim.";
			link.l1.go = "enrico_Tonzag_12";
		break;
		
		case "enrico_Tonzag_12":
			dialog.text = " Aptalca. İdealistçe. Ve... bir bakıma soyluca, diyebilirim, yöntemlerin olmasa. Düşmanca, tıpkı düşmanların gibi. Sonunda... senden bir farkları yok.";
			link.l1 = "Bana vaaz verme! Onur, onun kurallarına uyanlar içindir. Seni anlıyorum. Senin gibi düşünüyorum. Ve cezalandırıyorum.";
			link.l1.go = "enrico_Tonzag_13";
		break;
		
		case "enrico_Tonzag_13":
			dialog.text = "Haklısın. Sana bir şey öğretmek anlamsız. O halde, barışçıl yollarla ayrılmayacağız. Ama umurumda değilsin Don Enrico. Zamanımı harcamaya bile değmezsin.";
			link.l1 = "Ne demek iste...";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionEnricoAndTonzag2");
		break;
		
		case "enrico_Tonzag_14": // после выстрела в Зорро в подземелье
            dialog.text = "İyi misiniz, Kaptan? Dikkatli olmanız için sizi uyarmıştım. Keşke içgüdülerimi dinleseydiniz.";
			link.l1 = "Evet, iyiyim. Teşekkürler, Hercule. Sadece biraz...";
			link.l1.go = "enrico_Tonzag_15";
		break;
		
		case "enrico_Tonzag_15":
            dialog.text = "...şok oldun mu? Bunu itiraf etmekten korkma - senin yaşında ve böyle bir durumda bu gayet normal. Ayrıca, o Don tam bir düzenbaz.";
			link.l1 = "Hı-hı. Ama senden korkmuş gibiydi. Bu beni şaşırttı. Ama aynı zamanda kendime gelmemi sağladı. Bu arada, hâlâ hayatta mı? Öyle görünüyor. Ona arkanı dönerek durmamalısın.";
			link.l1.go = "enrico_Tonzag_16";
		break;
		
		case "enrico_Tonzag_16":
            dialog.text = "Hayatta, ama sersemlemiş. Kendine gelmeye başlıyor. Gövdeye değil, kafasına nişan almalıy­dık – meğerse soylu hidalgomuz ceketinin altında hafif ama sağlam bir zırh giymiş. Heh, Fleetwood bile sade bir yelekle yetinirdi. Yoksa burada çoktan bir kan gölü olurdu.";
			link.l1 = "Peki sen buraya nasıl geldin? Onunla aynı yerde mi buldun kendini?";
			link.l1.go = "enrico_Tonzag_17";
		break;
		
		case "enrico_Tonzag_17":
            dialog.text = "Şimdi bunun için zaman yok. Yakında tekrar ayağa kalkacak. Şimdilik, şu kapıyı kaldıralım.";
			link.l1 = "Biz... ne?? Elbette, belki Herkül olabilirsin, ama...";
			link.l1.go = "enrico_Tonzag_18";
		break;
		
		case "enrico_Tonzag_18":
            dialog.text = "Gençliğimdeki adamlar sağlam olurdu. Bu menteşelerin pimleri kısa. Hadi, yardım et bana Kaptan - Herkül olabilirim ama yaşım ilerliyor artık.";
			link.l1 = "Pekala, üçte! Ve kaldır!";
			link.l1.go = "enrico_Tonzag_19";
		break;
		
		case "enrico_Tonzag_19":
            DialogExit();
			locCameraSleep(true);
			LAi_FadeLong("Mtraxx_RetributionEnricoAndTonzag6", "");
		break;
		
		case "enrico_Tonzag_20": // окружили Зорро
            dialog.text = "Tüm planlarımı alt üst edip kazandığını mı sanıyorsun? Bu elbette beklenmedikti, ama hâlâ birçok şeyi hesaba kattım!";
			link.l1 = "Kıyafetinin altındaki o hafif zırhı beğendim. Neden tam bir zırh giymiyorsun da sadece onu seçtin? Sırf ceketini göstermek için mi?";
			link.l1.go = "enrico_Tonzag_21";
		break;
		
		case "enrico_Tonzag_21":
            dialog.text = "Ben bir genç kız değilim, Prens. Sebeplerim tamamen pratik – tam bir zırh hareketlerimi fazlasıyla kısıtlıyor. Herkesin kendi yöntemi var.";
			link.l1 = "Ve işte buradayım, bir Fransız olarak, bir İspanyol'dan farklı olarak zırh giymeye çoktan alışmışım. Ne ironik. Peki şimdi ne olacak? Bizi tuzağa düşüremedin. Her şeye hazırlıklısın... Planlarında bir düello var mıydı? Yoksa kılıç – ve hatta zırh – gerçek dövüşler dışında her şey için mi?";
			link.l1.go = "enrico_Tonzag_22";
		break;
		
		case "enrico_Tonzag_22":
            dialog.text = "Bana da korkak mı demeye çalışıyorsun? Söyledim ya, senin hak ettiğin şey uzun bir azap, düelloda ölüm değil. Ruhların burada, dünyada, tüm günahlarının acısını çekip anlamaya vakti olmayacaksa, bunun ne anlamı var?";
			link.l1 = "Cehenneme giden yolun iyi niyetlerle döşendiğini söylerler... Peki ya kurbanlarına işkence etmek, kendi ruhunu kirletmez mi?";
			link.l1.go = "enrico_Tonzag_23";
		break;
		
		case "enrico_Tonzag_23":
            dialog.text = "Asla. Hiçbir zaman. Çünkü kendime ve ilkelerime sadık kalırım.";
			link.l1 = "Aha, bizden farklısın yani. Bizim onursuz, aşağılık pislikler olduğumuzu defalarca söyledin, öyleyse... beklentilerini boşa çıkarmayalım. Seninle kendimiz ilgileneceğiz. Hem de birlikte.";
			link.l1.go = "enrico_Tonzag_24";
			link.l2 = "Sana bir teklifim var, Don Enrico. Seni burada ve şimdi düelloya davet ediyorum. Bir asilzade diğerine meydan okuyor.";
			link.l2.go = "enrico_Tonzag_26";
		break;
		
		case "enrico_Tonzag_24":
            dialog.text = "Hm-m. Yoksa hiç şansın olmazdı. Tabii, Tonzag biraz zor olacak... O yüzden önce seninle ilgileneceğim.";
			link.l1 = "Sanki sana bunu yapmasına izin verecekmiş gibi.";
			link.l1.go = "enrico_Tonzag_25";
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		
		case "enrico_Tonzag_25":
            DialogExit();
			EndQuestMovie();
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Tonzag");
			LAi_SetImmortal(sld, false);
			LAi_SetCheckMinHP(sld, 1, true, "TonzagRanen");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = CharacterFromID("Zorro");
			LAi_SetImmortal(sld, false);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "Mtraxx_RetributionEnricoAndTonzag7");
		break;
		
		case "enrico_Tonzag_26":
            dialog.text = "Sen mi? Soylu musun? Belki bir “prens” olabilirsin, ama sende zerre kadar soylu kanı olduğundan şüpheliyim.";
			link.l1 = "Bana gerçek adını açıkladın. Ben de kendi adımı açıklayacağım. Ben Charles de Maure. Ve birbirimizin onurunu yeterince incittik, artık ikimizin de hesaplaşma hakkı var. Kendini savun, Don Enrico.";
			link.l1.go = "enrico_Tonzag_27";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;
		
		case "enrico_Tonzag_27":
            dialog.text = "Ama sonra kararından pişman olma.";
			link.l1 = "Hayatımda birçok kararım için pişman oldum, ama bu onlardan biri olmayacak. Silahını hazırla!";
			link.l1.go = "enrico_Tonzag_28";
		break;
		
		case "enrico_Tonzag_28":
			DialogExit();
			EndQuestMovie();
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Tonzag");
			LAi_SetImmortal(sld, true);
			LAi_SetActorType(sld);
			
			sld = CharacterFromID("Zorro");
			LAi_SetImmortal(sld, false);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "Mtraxx_RetributionEnricoAndTonzag7");
		break;
		
		case "enrico_Tonzag_29": // после победы над Зорро
            dialog.text = "İyi misiniz, Kaptan? Soylu hidalgomuz sadece zırh giymemiş, kılıcını da zehirlemiş. Alın, bunu alın. Ormanda yürürken yanımda her zaman birkaç tane taşırım – ne zaman bir yılan ısırır ya da bir yerliden zehirli ok gelir, belli olmaz.";
			link.l1 = "Teşekkür ederim, Hercule. İyiyim. Zamanında gelmen sayesinde kendimi toparladım.";
			link.l1.go = "enrico_Tonzag_30";
			GiveItem2Character(PChar, "potion3");
			LAi_UseAtidoteBottle(pchar);
			LAi_UseAtidoteBottle(npchar);
		break;
		
		case "enrico_Tonzag_30":
            dialog.text = "Önemli değil. Hadi gidelim, seni buradan çıkaracağım – girişin önünü taşlarla kapattığını söyledi. Başka bir geçit buldum, kestirme bir yol.";
			link.l1 = "Bana anlat Hercule... Porto Bello'da tam olarak ne oldu? Ve ne zaman?";
			link.l1.go = "enrico_Tonzag_31";
		break;
		
		case "enrico_Tonzag_31":
            dialog.text = "Bugün bunu konuşacak havada değilim. Ama belki bir gün, bir kadeh şarap ya da daha sert bir şey eşliğinde anlatırım. Şimdi ise buradan gidelim - velet haklıydı, yaşlanıyorum galiba. Gemide dinlenmek istiyorum.";
			link.l1 = "O halde yolu sen göster.";
			link.l1.go = "enrico_Tonzag_32";
		break;
		
		case "enrico_Tonzag_32":
            DoQuestReloadToLocation("Shore10", "goto", "goto2", "Mtraxx_RetributionEnricoAndTonzag8");
		break;
		
		case "mishelle_sleep":
            dialog.text = "Söyle bana, kardeşim - nasıl böyle bir rezilliğe dönüştün? Sana korsanlarla tanış dedim ama şehirleri yak, masum insanları öldür, kadınlara işkence et demedim. Savaş bile onur ve haysiyetle yapılabilir\nAilemize yüz karası oldun. İyi ki babamız burada değil: Oğlunun bir korsan ve haydut olduğunu bilseydi utancından ölürdü!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep5");
		break;
		
		case "mishelle_sleep_1":
            dialog.text = "Kardeşim! Kardeşim!\nBeni duyabiliyor musun?\nİki kapıdan birinin arkasında bir geçit var. Kapı açılabiliyor. Anahtar hemen yanında!\nMerdivenlerde bul onu. Merdivenlerde!..";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep7");
		break;
		
		case "terrax_sleep":
            dialog.text = "Ha-ha-ha, selam sana, cesur haydutum! Neden bu kadar üzgünsün? Deniz, altın, rom ve kadınlar - başka neye ihtiyacın var? İlk karşılaşmamızı hatırlıyor musun? O zaman da söylemiştim sana - barut kokusundan korkmayan, kanlı nehirleri kurutmaya çekinmeyen adamlara ihtiyacım var demiştim. Tüm beklentilerimi aştın! Gerçek bir korsan oldun, Charlie Prince! Ha-ha-ha!";
			link.l1 = "";
			link.l1.go = "terrax_sleep_1";
			locCameraSleep(false);
		break;
		
		case "terrax_sleep_1":
            dialog.text = "Gerçekten kanlı bir korsan! Ah-ah-ha-ha!";
			link.l1 = "";
			link.l1.go = "terrax_sleep_2";
		break;
		
		case "terrax_sleep_2":
			Mtraxx_RetributionSleepSkeletons();
            dialog.text = "Ua-ha-ha-ha-ha-ha!!!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep6");
		break;

		// belamour legendary edition -->
		case "SlavesTrader":
            dialog.text = "Sen kimsin? Burada ne yapıyorsun? Çabuk cevap ver!";
			link.l1 = "Fadey'den geliyorum, bir parti siyah kemik için geldim. Seni uyarmalıydı.";
			link.l1.go = "SlavesTrader_1";
		break;
		
		case "SlavesTrader_1":
            dialog.text = "Hah! Don't worry about appearances, friend. We recognised you; the Muscovite gave a very detailed description. He also asked that you not take offence at the price. So, taking into account the advance payment, you owe 10,000 silver. Or, if you pay in gold, then only 50 doubloons. Well, what have you decided? Don't drag it out!";
			if(PCharDublonsTotal() >= 50)
			{
				link.l1 = "50 dublon ödeyeceğim. Bu daha kârlı.";
				link.l1.go = "SlavesTrader_Dub";
			}
			if(sti(Pchar.money) >= 10000)
			{
				link.l2 = "10.000 peso ödeyeceğim.";
				link.l2.go = "SlavesTrader_P";
			}
			link.l3 = "Üzgünüm, ama şu anda köle alacak durumda değilim.";
			link.l3.go = "SlavesTrader_X";
		break;
		
		case "SlavesTrader_Dub":
			RemoveDublonsFromPCharTotal(50);
            dialog.text = "Harika. Adamlarına malları almalarını işaret et.";
			link.l1 = "Elbette.";
			link.l1.go = "SlavesTrader_End";
		break;
		
		case "SlavesTrader_P":
			AddMoneyToCharacter(pchar, -10000);
            dialog.text = "Harika. Adamlarına malları almalarını işaret et.";
			link.l1 = "Elbette.";
			link.l1.go = "SlavesTrader_End";
		break;
		
		case "SlavesTrader_End":
			DialogExit();
			AddQuestRecord("Roger_3", "25");
            pchar.questTemp.Mtraxx.GiveMeSlaves = "Deal";
			SetCharacterGoods(pchar, GOOD_SLAVES, (GetCargoGoods(pchar, GOOD_SLAVES) + 50));
			Log_Info("Fifty slaves shipped to "+PChar.Ship.Name);
			for(i=1; i<=3; i++)
			{
				sld = characterFromId("Mtraxx_SlavesSeller"+i);
				ChangeCharacterAddressGroup(sld, "none", "", "");
				sld.lifeday = 0;
			}
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Shore29")], false); 
			DeleteAttribute(&locations[FindLocation("Shore29")],"DisableEncounters"); //энкаунтеры открыть
		break;
		
		case "SlavesTrader_X":
            dialog.text = "Peki, nasıl istersen. Bu malın her zaman bir alıcısı bulunur. Görüşürüz, dostum.";
			link.l1 = "Hoşça kal.";
			link.l1.go = "SlavesTrader_EndX";
		break;
		
		case "SlavesTrader_EndX":
			DialogExit();
			AddQuestRecord("Roger_3", "26");
			pchar.questTemp.Mtraxx.GiveMeSlaves = "WithoutSlaves";
			for(i=1; i<=3; i++)
			{
				sld = characterFromId("Mtraxx_SlavesSeller"+i);
				ChangeCharacterAddressGroup(sld, "none", "", "");
				sld.lifeday = 0;
			}
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Shore29")], false); 
			DeleteAttribute(&locations[FindLocation("Shore29")],"DisableEncounters"); //энкаунтеры открыть
		break;
		// диалог Гаспара Златозубого Xenon
		case "GasparGold_meeting":
            dialog.text = "Selamlar, Kaptan. Yanılmıyorsam siz Charlie Prince'siniz? Merak etmeyin, duvarlarımın kulağı yoktur. Açıkçası, adınızın ne olduğu umurumda değil. Önemli olan, bana sizi tavsiye etmiş olmaları; bu da demektir ki, iş yapabiliriz.";
			link.l1 = "Sana da selam, Gaspard ‘Altındiş.’ Gerçi, nasıl çağrıldığın umurumda değil. Birkaç ıvır zıvır almak isteyebileceğini duydum?";
			link.l1.go = "GasparGold_meeting_01";
		break;
		
		// ---> andre39966, Фриплейный Гаспарито
		case "GasparGold_meeting_sandbox":
			dialog.text = "Selamlar. Benim adım Gaspar Parmentier. Size nasıl yardımcı olabilirim?";
			link.l1 = "Sana da selam, Gaspar. Ben kaptan " + GetFullName(pchar) + ". Buradaki meyhaneciden geliyorum. Duyduğuma göre bazı ıvır zıvırları satın alıyormuşsun?";
			link.l1.go = "GasparGold_meeting_01";
			link.l2 = "Merhaba Altın Diş. Parlayan her şeyi satın aldığını duydum. Gök gürlesin, seninle iyi anlaşacağız.";
			link.l2.go = "GasparGold_meeting_wrong";
		break;

		case "GasparGold_meeting_wrong":
			dialog.text = "Bayım, beni biriyle karıştırıyor olmalısınız. Muhafızları çağırmadan önce lütfen burayı terk edin.";
			link.l1 = "Argh... Pekâlâ...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gaspar_sandbox_repeat";
		break;

		case "Gaspar_sandbox_repeat":
			dialog.text = RandPhraseSimple("Sanırım sizden burayı terk etmenizi istemiştim.", "Boş muhabbetler için vaktim yok. Lütfen beni yalnız bırakın.", "Ne kadar terbiyesizsiniz. Beni rahatsız etmeye devam mı edeceksiniz?");
			link.l1 = "Sakin ol dostum. Meyhaneciden geliyorum.";
			link.l1.go = "Gaspar_Alternative";
			link.l2 = "Beni kandırmayı bırak! Mücevher aldığını biliyorum!";
			link.l2.go = "Gaspar_Angry";
		break;

		case "Gaspar_Angry":
			dialog.text = "Böyle bir işle uğraşmadığımı söyledim. Kovulmadan önce buradan gidin.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gaspar_sandbox_repeat";
		break;

		case "Gaspar_Alternative":
			dialog.text = "Bu işi tamamen değiştiriyor, kaptan. Doğru yere geldiniz. Demek bazı mücevherleri satmak istiyorsunuz?";
			link.l1 = "Şey, 'benim' demek belki biraz aceleci oldu. He he.";
			link.l1.go = "GasparGold_01";
			NextDiag.TempNode = "GasparGold";
		break;
		// <--- andre39966, Фриплейный Гаспарито
		
		case "GasparGold_meeting_01":
            dialog.text = "Doğru. Sana benden daha iyi bir fiyat kimse veremez. Belki tefeciler hariç, ama onlar da fazla bir şey almaz. Ne sunarsan sun, almaya hazırım. Değerli eşyalarını bana bizzat getirmen bile gerekmez: gizli bir iskeleye açılan arka kapım var. Gemindeki sandıklarda sakladığın bütün ıvır zıvırı bana satabilirsin, çekinme.";
			link.l1 = "Harika, bu! Sizinle tanıştığıma memnun oldum.";
			link.l1.go = "GasparGold";
		break;
		
		case "GasparGold_story":
			npchar.mtraxx.story = true;
            dialog.text = "Bu benim kişisel meselem. Lütfen buna burnunu sokma. Sadece şunu söyleyeyim, her şey kontrolüm altında, yani benimle gönül rahatlığıyla ticaret yapabilirsin. Gerisi seni ilgilendirmez.";
			link.l1 = "Risk almamak en önemlisi! Bir de başka bir şey sormak istiyordum...";
			link.l1.go = "GasparGold";
		break;
		
		case "GasparGold":
			NextDiag.TempNode = "GasparGold";
            dialog.text = "Size nasıl yardımcı olabilirim? Elinizde fazladan inci ya da değerli taş mı var? Belki altın, gümüş, mücevher? Hepsini satın alırım.";
			if(!CheckAttribute(npchar,"mtraxx.story"))
			{
				link.l1 = "Söylesene, çalıntı mal alıcısı olmak nasıl bir şey? Hiç mi yetkililerden korkmuyorsun?";
				link.l1.go = "GasparGold_story";
			}
			link.l2 = "Burada bir şeyim var... Bunu biraz nakit parayla takas etmek istiyorum.";
			link.l2.go = "GasparGold_01";
		break;
		
		case "GasparGold_01":
            dialog.text = "Pekala, değiş tokuşu yapalım. Dublon mu, peso mu?";
			link.l1 = "Pesoyla gidelim - doblona gerek yok. Normal para her yerde geçer.";
			link.l1.go = "GasparGold_peso";
			link.l2 = "Doğru tahmin ettin - özellikle dubloonlara ihtiyacım var. O yüzden sadece onlarla satış yapacağım.";
			link.l2.go = "GasparGold_dub";
			link.l3 = "Şu anda satacak bir şeyim yok. Sadece değerli eşyalarım olduğunda almaya hazır olup olmadığını görmek istedim. Bir dahaki sefere kadar!";
			link.l3.go = "exit";
		break;
		
		// окно торговли
		case "GasparGold_peso":
            Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
		break;
		
		case "GasparGold_dub":
            Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 1);
		break;
		
		// Диалоги после угроз вождю индейцев Кумване
		case "MeridaObsuzhdenie_Bad_1":
            dialog.text = "Hâlâ gözdağı mı veriyorsun, Kaptan? Tehditlerini dışarıdan bile duydum.";
			link.l1 = "Bana başka seçenek bırakmadılar. Yardımını almak için bu Tagofa'nın karısına hediyeler sundum. Beni dinlemedi bile. Şimdi bırak reis onlarla konuşsun. Eğer bu inatçı adamları yola getiremezse, onun kalbini kendi ellerimle göğsünden söküp alırım. Bu arada, Yahahu kim?";
			link.l1.go = "MeridaObsuzhdenie_Bad_2";
			ChangeShowIntarface();
		break;
		
		case "MeridaObsuzhdenie_Bad_2":
            dialog.text = " Kızılderililerle arayı bozman iyi olmadı. Biz korsanların yanında sadece kılıçlarımız ve gemilerimiz var. Ama bu senin kararınsa, öyle olsun. Ve Yahahu kötü bir iblis. Onun hakkında başka hiçbir şey bilmiyorum.";
			link.l1 = "...";
			link.l1.go = "MeridaObsuzhdenie_Bad_3";
		break;
		
		case "MeridaObsuzhdenie_Bad_3":
            StartInstantDialog("Mrt_Rocur", "MeridaObsuzhdenie_Bad_4", "Quest\Roger.c");
		break;
		
		case "MeridaObsuzhdenie_Bad_4":
            dialog.text = "İkna için vakit harcamak akıllıca değil, Leprechaun. Yoksa zengin ganimetten vazgeçip Kızılderililerle iyi ilişkiler kurmayı mı tercih edersin?";
			link.l1 = "...";
			link.l1.go = "MeridaObsuzhdenie_Bad_5";
		break;
		
		case "MeridaObsuzhdenie_Bad_5":
            StartInstantDialog("Lepricon", "MeridaObsuzhdenie_Bad_6", "Quest\Roger.c");
		break;
		
		case "MeridaObsuzhdenie_Bad_6":
            dialog.text = "İkisini de almayı tercih ederim.";
			link.l1 = "İki tarafa da oynamak bu sefer işe yaramaz. Artık tartışmanın anlamı yok, her şey zaten yapıldı. Yarın reis bize Tagofa'nın kararını bildirecek, umarım beni hayal kırıklığına uğratmaz. Yoksa... aşırı önlemler almak zorunda kalacağım. Tabii ki bunu istemem.";
			link.l1.go = "MeridaObsuzhdenie_Bad_7";
		break;
		
		case "MeridaObsuzhdenie_Bad_7":
			DialogExit();
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.CannotWait"); //разрешить отдыхать
			ChangeShowIntarface();
			
            sld = characterFromId("Lepricon");
			sld.dialog.Filename = "Quest\Roger.c";
			sld.dialog.currentnode = "lepricon_3";
			LAi_SetWarriorType(sld);
			
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
		case "MeridaObsuzhdenie_Good_1":
            dialog.text = "Peki, işler nasıl gidiyor? Bir rehberimiz olacak mı?";
			link.l1 = "Hayır, Jean, yapamayacağız. Şef ve bütün kabile Kaponglardan, şeytanın tütsüden korktuğu gibi korkuyor. Görünüşe göre planımızdan vazgeçmek zorunda kalacağız.";
			link.l1.go = "MeridaObsuzhdenie_Good_2";
			ChangeShowIntarface();
		break;
		
		case "MeridaObsuzhdenie_Good_2":
            StartInstantDialog("Lepricon", "MeridaObsuzhdenie_Good_3", "Quest\Roger.c");
		break;
		
		case "MeridaObsuzhdenie_Good_3":
            dialog.text = "Terrax bu olayların böyle gelişmesinden memnun kalmayacak.";
			link.l1 = "Sence işlerin bu hale gelmesine çok mu sevindim sanıyorsun? Korkak Lokonolar Kaponglarla uğraşmak istemiyor. Ne ikna ne de ödül onları cezbetmiyor.";
			link.l1.go = "MeridaObsuzhdenie_Good_4";
		break;
		
		case "MeridaObsuzhdenie_Good_4":
            StartInstantDialog("Mrt_Rocur", "MeridaObsuzhdenie_Good_5", "Quest\Roger.c");
		break;
		
		case "MeridaObsuzhdenie_Good_5":
            dialog.text = "O zaman tehditlere başvuracağız. Onlara köylerini yerle bir edeceğini ve hayatta kalanları biri bizi götürmeye razı olana kadar işkence edeceğini söyle.";
			link.l1 = "Jean, aklını tamamen mi kaçırdın? Masum insanların evlerini yakacak değilim. Ve elbette onlara işkence de yapmam.";
			link.l1.go = "MeridaObsuzhdenie_Good_6";
		break;
		
		case "MeridaObsuzhdenie_Good_6":
            dialog.text = "Charles Prince örnek bir hayırseverdir. Senden böyle bir şefkat patlaması beklemezdim.";
			link.l1 = "Bu şefkat değil, Yakışıklı. Şimdi, bir Kızılderiliyi yarı ölü hale gelene kadar işkence edeceğiz. O da intikam için bizi doğruca Kapongların eline götürecek, sonra da sadece kendisinin bildiği yollardan kaybolacak. Halkımın hayatını böyle bir riske atmam.";
			link.l1.go = "MeridaObsuzhdenie_Good_7";
		break;
		
		case "MeridaObsuzhdenie_Good_7":
            dialog.text = "Öyleyse, Leprechaun ve ben gidiyoruz. Beni Maracaibo plantasyonlarından kurtardığın için sana elli bin gümüş veriyorum. Aslında bu parayı yeni bir gemi almak için biriktiriyordum. Sana bir tavsiye: bir süre Marcus'un gözüne görünme. Hoşça kal, Charles Prince.";
			link.l1 = "Hoşça kal, Jean.";
			link.l1.go = "MeridaObsuzhdenie_Good_8";
			AddMoneyToCharacter(pchar, 50000);
		break;
		
		case "MeridaObsuzhdenie_Good_8":
            DialogExit();
			chrDisableReloadToLocation = false;
			ChangeShowIntarface();
			AddQuestRecord("Roger_5", "8b");
			CloseQuestHeader("Roger_5");
			
			sld = characterFromId("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			sld.location = "None";
			RemovePassenger(pchar, sld);
			
			sld = characterFromId("Mrt_Rocur");
			LAi_type_actor_Reset(sld);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			sld.location = "None";
			RemovePassenger(pchar, sld);
			
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "First time";
		break;
		
		// Немезида. Диалоги с офицерами после взрыва бочонков с порохом
		// Тонзаг
		case "Nemezida_Tonzag_1":
            dialog.text = "Şimdi buraya herkes akın edecek! O ağaçları havaya uçurmak iyi bir fikir miydi, Kaptan?";
			link.l1 = "Kahretsin! Belki herkes baltalarla çalışsaydı daha iyi olurdu... Ama artık bunun için çok geç.";
			link.l1.go = "Nemezida_Tonzag_2";
		break;
		
		case "Nemezida_Tonzag_2":
            dialog.text = "Doğru. Elimizdekilerle idare edeceğiz. Hazırlan.";
			link.l1 = "Sen de, Hercule.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Tonzag_3":
            dialog.text = "Hâlâ bu tarafa geliyorlar. Peki, bunlarla da ilgilenelim mi?";
			link.l1 = "Ya bitmezlerse ne olacak? Biz böyle belalara bulaşmak için burada değiliz.";
			link.l1.go = "Nemezida_Tonzag_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Tonzag_4":
            dialog.text = "Pekâlâ, her şeyin bir sonu var... Ama haklısın. Geri çekilelim. Hem de hemen.";
			link.l1 = "Hadi acele edelim!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Tonzag_5":
            dialog.text = "Çok acımasızlar, bize yetiştiler. Burada bir patika var, içeri girelim mi? Savunmak daha kolay olur.";
			link.l1 = "Bekle, Hercule. Duyuyor musun? İçeride zaten birileri var. Sen ve adamların burada kalın, işleri halledin. Ben içeri gireceğim, hazineyi almadan önce – kimsenin oraya tesadüfen girdiğine inanmıyorum.";
			link.l1.go = "Nemezida_Tonzag_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Tonzag_6":
            dialog.text = "Peki. Ama dikkatli ol, içime kötü bir his doğdu.";
			link.l1 = "Sen de! Ben oraya gidiyorum.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		case "Nemezida_Tonzag_7": // на берегу
            dialog.text = "Bir şey mi söylemek istiyorsunuz, Kaptan? Gemimize yürürken başından beri dalgınsınız.";
			link.l1 = "Evet, doğru. Son zamanlarda yaptıklarımı düşünüyorum. Terrax'ı ve... beni nereye getirdiğini. Kardeşimi kurtarmaya bir adım daha yaklaştım mı? Ya da eve dönmeye?..";
			link.l1.go = "Nemezida_Tonzag_8";
		break;
		
		case "Nemezida_Tonzag_8":
            dialog.text = "Hm-m. Güzel sorular. Peki, senin cevapların ne?";
			link.l1 = "Sadece bir soru daha. Eğer önceden anlamsızdıysa, yine mi anlamsız olacak? Terrax bana yardım etmeyecek. Ne kardeşim için, ne de Tortuga için.";
			link.l1.go = "Nemezida_Tonzag_9";
		break;
		
		case "Nemezida_Tonzag_9":
            dialog.text = "Muhtemelen hayır. Ona bunun bir faydası yok. Bunu ancak şimdi fark etmiş olman şaşırtıcı. Peki, sıradaki sorunun ne?";
			link.l1 = "Ben neden bütün bu zaman boyunca Terrax'ın peşinden bir köpek gibi koştum, onun için ateşten kestane çıkardım?!";
			link.l1.go = "Nemezida_Tonzag_10";
		break;
		
		case "Nemezida_Tonzag_10":
            dialog.text = "Şimdi, bu güzel bir soru. Gerçekten yerinde. Bu sefer bir cevabın var mı?";
			link.l1 = "Daha çok bir karar gibi. Bugün şanslıydım. Ama bir daha şansım yaver gidecek mi? Ne zaman duracağını bilmek önemli. Ve... kendine saygı duymak da. Yeterince yaşadım.";
			link.l1.go = "Nemezida_Tonzag_11";
		break;
		
		case "Nemezida_Tonzag_11":
            dialog.text = "Terrax ile ortaklığını bitirmeye mi karar verdin?";
			link.l1 = "Evet. Yapmam gereken daha önemli şeyler var. Ailem, arkadaşlarım. Onlarla birlikte hedeflerime ulaşacağım. Ama bu şekilde değil. Ve eğer bir gün yaparsam... Marcus'la olmayacak. Kendi efendim olacağım. Kendi kararlarımı kendim vereceğim.";
			link.l1.go = "Nemezida_Tonzag_12";
		break;
		
		case "Nemezida_Tonzag_12":
            dialog.text = "Bir zamanlar peşinden gittiğim adam yine konuşuyor. Yine yanlış insanlarla bulaşma. Bir zamanlar beni etkileyen potansiyelini boşa harcama.";
			link.l1 = "Anladım, Hercule. Ve tekrar teşekkür ederim. Bu sefer, bana bunu gerçekten fark ettirdiğin için. Artık Prens'in uşağı değilim. Ben Charles de Maure, gururlu bir soyluyum. Hadi gemiye çıkalım - ikimiz de yorgunuz.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Tonzag");
		break;
		
		// Книппель
		case "Nemezida_Knippel_1":
            dialog.text = "Bu gerçekten müthiş bir patlamaydı, efendim – kıç tarafıma knippel geldi! Valkyrie'nin borda ateşi gibi ses çıkardı. Ama korkarım, şuradaki adamlar da bunu fark etti...";
			link.l1 = "Eğer fark ettilerse, bu onların sorunu. Kimse onları buraya çağırmadı. Onlara bir ders vermeye hazır mısın, Charlie?";
			link.l1.go = "Nemezida_Knippel_2";
		break;
		
		case "Nemezida_Knippel_2":
            dialog.text = "Her zaman hazırım, efendim!";
			link.l1 = "Mükemmel. Hadi başlayalım.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Knippel_3":
            dialog.text = "Korkarım birazdan daha fazla misafirimiz olacak, Kaptan. Emirleriniz nedir?";
			link.l1 = "Ormanın derinliklerine ilerleyip saklanacağız - hepsiyle başa çıkmamız mümkün değil, zaten bunun için burada değiliz.";
			link.l1.go = "Nemezida_Knippel_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Knippel_4":
			PlaySound("VOICE\English\hambit\Charlie Knippel-05.wav");
            dialog.text = "Emredersiniz, efendim.";
			link.l1 = "O zaman hadi gidelim!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Knippel_5":
            dialog.text = "Bizi buldular, Kaptan! Ama burada saklanabiliriz – bu yol bir yere çıkıyor gibi görünüyor, gerçi sanırım orada zaten birisi var.";
			link.l1 = "Sığınmıyoruz! Görünen o ki, hazineyi başkaları da duymuş. Plan şöyle: Ben gidip neler olup bittiğine bakacağım, onlar her şeyi kapmadan önce, sen de burada adamlarla onları oyalayacaksın!";
			link.l1.go = "Nemezida_Knippel_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Knippel_6":
			PlaySound("VOICE\English\hambit\Charlie Knippel-05.wav");
            dialog.text = "Evet, efendim.";
			link.l1 = "Mükemmel. Şimdi aşağı iniyorum! Burada her şeyi halledeceğine güveniyorum.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		case "Nemezida_Knippel_7": // на берегу
            dialog.text = "Khe-khe... İyi misiniz, efendim?";
			link.l1 = "Charlie! Benim için endişelenmek için harika bir zaman seçtin. Nefesini boşa harcama. Dayanabiliyor musun? Seni gemide bırakıp yerine daha fazla adam getirmeliydim...";
			link.l1.go = "Nemezida_Knippel_8";
		break;
		
		case "Nemezida_Knippel_8":
            dialog.text = "Ah, sadece bir sıyrık, efendim. Biraz yorgunum. Hayatımda böyle bir dövüş görmedim, gençliğimde bile! Ama onlara öyle bir ders verdim ki, sonsuza dek kartuş sesleri kulaklarından gitmeyecek!";
			link.l1 = "Kraliyet Donanması, eski usul! Görünen o ki, aslanlar gibi dövüştün Charlie. Ama yine de ayakta zor duruyorsun. Rol yapma – yaran ne kadar kötü?";
			link.l1.go = "Nemezida_Knippel_9";
		break;
		
		case "Nemezida_Knippel_9":
            dialog.text = "Önemli bir şey değil, Kaptan, sadece yorgunluk. Arkandaki giriş neredeyse hemen çöktü ve biz de o adamların saldırılarını saatlerce savuşturduk. Sonunda yalnız kaldım, yaralıydım. Bu yüzden buraya gelip yolu açmaya ve biraz ilk yardım almaya çalıştım.";
			link.l1 = "Anladım. Bugün sen üstüne düşeni yaptın. Bana gelince... Ben başaramadım. Hepimiz kandırıldık ve birbirimize düşman edildik, birinin keyfi için—ortada hazine bile yokmuş. Ve oradaki tek enayi de ben değildim.";
			link.l1.go = "Nemezida_Knippel_10";
		break;
		
		case "Nemezida_Knippel_10":
            dialog.text = "Başaramadınız mı?.. Ama hayattasınız, efendim. Ne oldu? Kaçmayı mı başardınız?";
			link.l1 = "Hayır, ama yine de biraz koşuşturma oldu. Üzgünüm dostum, ama orada olanları kimseye anlatmayacağım – en yakın arkadaşlarıma bile. Yine de, gerekli sonuçları çıkardım.";
			link.l1.go = "Nemezida_Knippel_11";
		break;
		
		case "Nemezida_Knippel_11":
            dialog.text = "Ne tür sonuçlar, efendim? Sizin mantığınızı her zaman anlayamıyorum. Benim felsefem basit – iyi bir culverin ve direğe zincirli gülle.";
			link.l1 = "Bana söyle, sen de daha önce İspanyolları öldürmüşsündür, tıpkı benim yakın zamanda yaptığım gibi. Kraliyet Donanmasındayken. Sonra da Fleetwood'la birlikteyken.";
			link.l1.go = "Nemezida_Knippel_12";
		break;
		
		case "Nemezida_Knippel_12":
            dialog.text = "Yaptım. İspanyollar, Hollandalılar—başka birçokları da. Dick'in bir keresinde dediği gibi, bizim işimiz tehlikeli ve zorlu. Ama neden soruyorsun? Ne demek istiyorsun?";
			link.l1 = "Açıklayacağım. Ama önce, başka bir soru. Hiç yaptıklarından ve neden yaptığından şüphe ettin mi, Charlie?";
			link.l1.go = "Nemezida_Knippel_13";
		break;
		
		case "Nemezida_Knippel_13":
            dialog.text = "Hm-m. Kendime hep, Taç için en iyisini yaptığımı söyledim. Emirleri düşünmek nankör bir iş – sonuçta yine de uymak zorundasın.";
			link.l1 = "Taç... Eh, senin kendince sebeplerin vardı. Benimse öyle bir sebebim bile yoktu – Michel bana Terrax'a yakın olmamı söyledi. Ama bunca fedakârlığa değdi mi? Bu bana ya da ona bir fayda sağladı mı? Evet, evet, donlardan hoşlanmıyoruz... ama nihayetinde hepimiz insanız.";
			link.l1.go = "Nemezida_Knippel_14";
		break;
		
		case "Nemezida_Knippel_14":
            dialog.text = "Sanırım ne demek istediğinizi anlamaya başlıyorum, efendim.";
			link.l1 = "Güzel. Söylesene, Fleetwood ayrıldığında artık Hollandalı tüccarlara ateş etmek zorunda kalmadığına sevindin mi? Onların bazıları dürüst insanlardı.";
			link.l1.go = "Nemezida_Knippel_15";
		break;
		
		case "Nemezida_Knippel_15":
            dialog.text = "Hiç düşünmemiştim, Kaptan. Ama şunu söyleyeyim - sizinle hizmet etmekten her zaman keyif aldım, efendim. Eğer yalan söylüyorsam, boynuma bir knippel dolansın, lanet olsun!";
			link.l1 = "Ha-ha-ha, peki. Ama şunu söyle bana – sence hangimiz daha kötüydü? Sen, emirleri yerine getiren mi? Yoksa ben mi, kimse bana zorla yaptırmadı yaptıklarımı?";
			link.l1.go = "Nemezida_Knippel_16";
		break;
		
		case "Nemezida_Knippel_16":
            dialog.text = " Bilmiyorum, efendim... ";
			link.l1 = "Ben de bilmiyorum. Ama bunun bir önemi yok. Önemli olan, artık Terrax'la hiçbir alakam olsun istemiyorum. Yeter artık. Charlie Prince yok. Sadece Charles de Maure.";
			link.l1.go = "Nemezida_Knippel_17";
		break;
		
		case "Nemezida_Knippel_17":
            dialog.text = "Ama bu, kardeşini kurtarma planının bir parçası değil miydi?";
			link.l1 = "Öyleydi. Ama sonunda bana hiç yardımcı olmadı. Bu yüzden eğer bir daha böyle bir şey yapmam gerekirse - bu sadece benim kararım olacak. Ve ancak gerçekten beni hedefime yaklaştırıyorsa yapacağım.";
			link.l1.go = "Nemezida_Knippel_18";
		break;
		
		case "Nemezida_Knippel_18":
            dialog.text = "Umarım ne yaptığını biliyorsundur, Kaptan. Ve Terrax gibi ya da darağacında bitirmezsin işi.";
			link.l1 = "Ben de öyle umuyorum. Ama artık emin olduğum bir şey var, o da bundan sonra kendi hedeflerim ve çıkarlarımın öncelikli olacağı. Şimdi, yaralarına bakalım.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;
		
		// Лонгвэй
		case "Nemezida_Longway_1":
            dialog.text = "Patlamanız dikkat çekti, Lord Kaptan. Bir düşman birliği bize doğru yaklaşıyor gibi görünüyor.";
			link.l1 = "Lanet olsun! ...Sence o ağaçlarla başa çıkmanın daha iyi bir yolu var mıydı? Peki, sen ne yapardın?";
			link.l1.go = "Nemezida_Longway_2";
		break;
		
		case "Nemezida_Longway_2":
            dialog.text = " Bilmiyorum. Ama şimdi ne yapmam gerektiğini biliyorum – şu insanlarla ilgilenmek.";
			link.l1 = "Pekâlâ, adil olsun. Sanırım tam da bunu yapacağız.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Longway_3":
            dialog.text = "Yeni insanlar geldi, Kaptanım.";
			link.l1 = "Evet, fark ettim, teşekkürler Longway. Ama bunlarla uğraşacak vaktimiz yok, ormana çekilelim – belki peşimizi kaybederler.";
			link.l1.go = "Nemezida_Longway_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Longway_4":
            dialog.text = "Hmm, tabii ki onlarla baş edebiliriz, ama dediğin gibi.";
			link.l1 = "Bu kavgaya gerek yok, hadi gidelim.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Longway_5":
            dialog.text = "Bizi bırakmayacaklar ve yakalayacaklar, Kaptanım! Size söylemiştim, onları daha önce öldürmeliydik. O mağarada pusu mu kursak? Gerçi orada zaten birileri var gibi görünüyor.";
			link.l1 = "Burada adamlarla pusu kurmak en iyisi! O hazineyi kaçıracak değilim. Görünen o ki, birileri daha ganimetin kokusunu almış... O yüzden gidip kendim bakacağım.";
			link.l1.go = "Nemezida_Longway_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Longway_6":
            dialog.text = "Dikkatli olun, Kaptanım. Unutmayın, bir zamanlar büyük bir ejderha bile altın yığınlarının tepesinde can vermiştir.";
			link.l1 = "Bunu aklımda tutacağım, Longway. Bugün hepimiz hayatta kalmaya çalışalım.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		case "Nemezida_Longway_7": // на берегу
            dialog.text = "Lord Kaptan, oradan kaçmayı başarmışsınız gibi görünüyor.";
			link.l1 = "Şaşırdın mı, Longway? Gerçi ben de biraz şaşkınım doğrusu. Görünen o ki, hayatta kalan tek kişi sensin. Ama bunu nasıl başardın?";
			link.l1.go = "Nemezida_Longway_8";
		break;
		
		case "Nemezida_Longway_8":
            dialog.text = "Bir avuç serseri kedi bir kaplanı alt edemez. Bir yılan yuvası bir ejderhayı yere seremez. Beyaz adamlar arasında, bana layık rakip pek azdır.";
			link.l1 = "Ama unutma Longway, bir grup köpek bir aslanı parçalayabilir.";
			link.l1.go = "Nemezida_Longway_9";
		break;
		
		case "Nemezida_Longway_9":
            dialog.text = "Şimdi Lord Kaptan, Longway'e akıl mı veriyor? Keşke tavsiyemi daha önce dinleseydin.";
			link.l1 = "Altın dağındaki ejderha mı? Doğru, neredeyse ben de birine dönüştüm – hatta ölümden döndüm. Ama öyle bir altın dağı yoktu, hiç olmadı. Onun yerine bulduğum şey ise bambaşka, ama en az onun kadar önemliydi.";
			link.l1.go = "Nemezida_Longway_10";
		break;
		
		case "Nemezida_Longway_10":
            dialog.text = "Bir dahaki sefere, 'neredeyse' yetmeyebilir. Ne buldunuz, Kaptanım?";
			link.l1 = "Evet, şimdi bunu anlıyorum. Bulduğum şey... bilgelikti. Tecrübeydi. Anlayıştı. Bir karardı. Söylesene Longway, biz son zamanlarda neyle meşguldük?";
			link.l1.go = "Nemezida_Longway_11";
		break;
		
		case "Nemezida_Longway_11":
            dialog.text = "Biz korsanlarız. Yeni efendin Lord Terrax için çalışıyoruz. Kaçakçılık yapıyoruz, kasabaları yağmalıyoruz, öldürüyoruz, kurtarıyoruz ve onun halkına yardım ediyoruz.";
			link.l1 = "O benim efendim değil, biliyorsun. Ama kahretsin, her şeyi öyle güzel anlattın ki! Gururumu, özsaygımı unuttum ve peşinden bir köpek gibi sürüklendim.";
			link.l1.go = "Nemezida_Longway_12";
		break;
		
		case "Nemezida_Longway_12":
            dialog.text = "Longway sizi anlıyor, Lord Kaptan. Ben de van Merden ve Rodenburg için çalıştım; onurlu, gururlu ve saygılı olmayı bir kenara bırakıp, değer verdiğim bir hedef uğruna her şeyi unuttum.";
			link.l1 = "Bana söyle, bunun için kendini suçluyor musun? Kendinden nefret ediyor musun?";
			link.l1.go = "Nemezida_Longway_13";
		break;
		
		case "Nemezida_Longway_13":
            dialog.text = "Kınamak mı? Bazen. Nefret etmek mi? Hayır. Kim olduğumu biliyorum ve unutmuyorum. Amacımı, bana yol gösteren yıldızımı hatırlıyorum. Hayatta bundan daha önemli bir şey yok. Peki senin bir amacın var mı?";
			link.l1 = "Senin gibi yol gösterici bir yıldız değil belki, ama yine de önemli bir amaçtı – kardeşimi kurtarmak. Ama o hedeften saptım. Ve bunu bir daha yapmaya hakkım yok.";
			link.l1.go = "Nemezida_Longway_14";
		break;
		
		case "Nemezida_Longway_14":
            dialog.text = "Sana Göksel İmparatorluk'tan bir bilgelik daha paylaşayım. Tamamen iyi ya da tamamen kötü insanlar yoktur. Her insan hem Yin'i — karanlığı ve cehaleti — hem de Yang'ı — ışığı ve bilgeliği — taşır. Bu denge herkesin içinde değişir.";
			link.l1 = "Yani, benim Yang’ım Charles de Maure. Ve Yin’im Charlie Prince. Ama belki bir gün Charles de Maure bile karanlık ve zor kararlar almak zorunda kalacak.";
			link.l1.go = "Nemezida_Longway_15";
		break;
		
		case "Nemezida_Longway_15":
            dialog.text = "Hayat böyle, Kaptanım. Her insan hem karanlık hem de aydınlık seçimler yapmak zorunda kalır.";
			link.l1 = "Yine de Prens'in maskesi neredeyse benimle bütünleşmişti. Ama onu çıkaracağım. Charles de Mort bir soyludur, ayak işlerine koşan biri değil. Bundan böyle böyle olacak. Gururumu ve onurumu geri alıyorum. Artık kendi efendimim.";
			link.l1.go = "Nemezida_Longway_16";
		break;
		
		case "Nemezida_Longway_16":
            dialog.text = "Longway kararınızı onaylıyor, Kaptanım.";
			link.l1 = "Teşekkür ederim, Longway. Bu arada, hiç özgür bir kaptan olmadığın için pişmanlık duyuyor musun? Bana hizmet etmek, dediğin gibi, 'efendin' olmak?";
			link.l1.go = "Nemezida_Longway_17";
		break;
		
		case "Nemezida_Longway_17":
            dialog.text = "Hm-m. Longway kendi gemisini yönetmeyi özlüyor. Ama seni tanıyorum. Bana tipik beyaz barbarlar gibi davranmayıp saygı ve akıl gösterdiğin için seni takdir ediyorum. Belki farklı bir hayat isterdim. Ama sana yardım ettiğim için pişman değilim.";
			link.l1 = "Bunu duyduğuma sevindim, Longway. Şimdi... buradan ve Yin'in yolundan ayrılalım. Hayatımıza daha fazla Yang katalım. Doğru mu anladım?";
			link.l1.go = "Nemezida_Longway_18";
		break;
		
		case "Nemezida_Longway_18":
            dialog.text = "Evet, doğru. Umarım bundan sonra çok daha iyi bir yol izlersin.";
			link.l1 = "Dao?";
			link.l1.go = "Nemezida_Longway_19";
		break;
		
		case "Nemezida_Longway_19":
            dialog.text = "Yol, Kaptanım. Ya da Öz. Ama bizim durumumuzda – Yol.";
			link.l1 = "Gelecekte yolumda ne olursa olsun, artık gerçekten önemli olandan sapmayacağım. Hadi buradan gidelim, Longway.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;
		
		// Тичингиту
		case "Nemezida_Tichingitu_1":
            dialog.text = "Kaptan Charles, buraya doğru birçok kişi geliyor. Duman işaretin onları buraya çekti. Ve belli ki dostlarımız değiller.";
			link.l1 = "Ah, keşke senin dediğin gibi sadece bir 'duman sinyali' olsaydı – tüm ormanda yankılandı. Başka çare yok – kendimizi savunacağız. Bütün bir ekibin arkamızdan saldırmasına hiç gerek yok.";
			link.l1.go = "Nemezida_Tichingitu_2";
		break;
		
		case "Nemezida_Tichingitu_2":
            dialog.text = "Evet, Kaptan Charles. Önce saldır!";
			link.l1 = "Saldırın! Mermileri esirgemeyin!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Tichingitu_3":
            dialog.text = "Daha fazlası geliyor! Daha da fazla insan.";
			link.l1 = "Ormana çekilelim, Tichingitu! Saklanıp bekleyeceğiz. Ben buraya hazine için geldim, kavga için değil!";
			link.l1.go = "Nemezida_Tichingitu_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Tichingitu_4":
            dialog.text = "Gerekirse, ormanda bir pusu kurabiliriz.";
			link.l1 = "Doğru söylüyorsun. Şimdi, hadi gidelim – hızlı ama sessizce.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Tichingitu_5":
            dialog.text = "Kaptan Charles, bak! İleride bir geçit var. Oradan ayak sesleri ve konuşmalar geliyor.";
			link.l1 = "Başka biri de hazineyi öğrendi mi? Kahretsin! Sen de arkadan gelen o sesi duyuyor musun? Görünüşe göre yetiştiler. Tichingitu! Ben ileride ne var bakmaya gidiyorum. Sen çocuklarla onları oyalamaya bak!";
			link.l1.go = "Nemezida_Tichingitu_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Tichingitu_6":
            dialog.text = "Deneyeceğiz! Sen git!";
			link.l1 = "Sana güveniyorum!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
			
		case "Nemezida_Tichingitu_7": // на берегу
            dialog.text = "Kaptan Charles! Hayatta kaldınız! Tichingitu buna çok sevinecek.";
			link.l1 = "Teşekkür ederim, dostum. Ben de mutluyum. Hayatta kaldığıma ve senin de iyi olmana sevindim. Görünen o ki, tüm ekipten geriye bir tek sen kaldın. Çoklar mıydı? Onlara gerçekten iyi karşı koymuşsun.";
			link.l1.go = "Nemezida_Tichingitu_8";
		break;
		
		case "Nemezida_Tichingitu_8":
            dialog.text = "Birçok kişi var. Ama benimki Maskog köyümüzün en iyi savaşçılarından biri. Orada sana ne oldu? Aradığın hazineyi bulabildin mi?";
			link.l1 = "Hayır, Tichingitu. Kandırıldık – hazine falan yokmuş. Söylesene, son zamanlarda yaptıklarımız hakkında ne düşünüyorsun?";
			link.l1.go = "Nemezida_Tichingitu_9";
		break;
		
		case "Nemezida_Tichingitu_9":
            dialog.text = "Ne yaptık biz, Kaptan Charles? Seyrettik. Düşmanlarını yendik.";
			link.l1 = "Beni anlamadığın anlaşılıyor. Söylesene, kabileden sürülmene üzülüyor musun? Geri dönmek ister misin, kardeşlerini özlüyor musun?";
			link.l1.go = "Nemezida_Tichingitu_10";
		break;
		
		case "Nemezida_Tichingitu_10":
            dialog.text = "Elbette, arkadaşlarımı ve ailemi özlüyorum. Ama geri dönmek mi? Onsuz... evim artık yok. Üstelik o şeytani çakal, şaman da var!";
			link.l1 = "Üzgünüm, bunu gündeme getmek istememiştim. Biliyor musun, yakın zamanda bir kabileye katıldım, tabiri caizse. Benim gibi kaptanlardan oluşan bir kabile. Ama sonunda anladım ki, hepsi kendini deniz kurdu sanan bir grup çakaldan ibaretmiş...";
			link.l1.go = "Nemezida_Tichingitu_11";
		break;
		
		case "Nemezida_Tichingitu_11":
            dialog.text = " Peki ne oldu? Şimdi ne yapacağız? ";
			link.l1 = "İyi soru. O çakallar arasında ben de neredeyse bir çakala dönüşüyordum. Yani, bu bana yeter. Arkadaşlarım ve tayfam - işte benim 'kabilem' onlar.";
			link.l1.go = "Nemezida_Tichingitu_12";
		break;
		
		case "Nemezida_Tichingitu_12":
            dialog.text = "Tichingitu, kendi kabileini bulduğuna sevindi, Kaptan Charles.";
			link.l1 = "Teşekkür ederim, dostum. Bunu söylemem gerekiyordu. Sen de ben de kendi yolumuzun ve kabilemizin lideriyiz. Ve şimdi, gerçekten önemli meselelere dönme vakti.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;
		
		// Айронс
		case "Nemezida_Irons_1":
            dialog.text = "Birisi geliyor! Ve sesinden anladığım kadarıyla, buraya Şükran Günü'nü kutlamak için gelmiyor.";
			link.l1 = "Lanet kökler! Tamam, şimdi bu alçaklarla uğraşmamız gerekecek – hazineyi gemiye taşırken başımıza gelmesindense şimdi olsun.";
			link.l1.go = "Nemezida_Irons_2";
		break;
		
		case "Nemezida_Irons_2":
            dialog.text = "Doğru bildin. Hazır mısın?";
			link.l1 = "Sormana gerek yoktu. Sanki başka bir seçeneğimiz varmış gibi.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Irons_3":
            dialog.text = "Her yerdeler, Londra'nın kenar mahallelerindeki fareler gibi, Sayın Yargıcım! Ne yapacağız - burada kalıp adamlarla çatışmaya mı girelim?";
			link.l1 = "Şimdi değil, geri çekilin! Biz buraya hazine için geldik, kavga etmek için değil!";
			link.l1.go = "Nemezida_Irons_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Irons_4":
            dialog.text = "Heh, burada bir itirazım yok.";
			link.l1 = "O zaman hızlan!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Irons_5":
            dialog.text = "Hey, Kaptan, bak - bu yol bir yere gidiyor gibi görünüyor. Ve seslere bakılırsa orası epey hareketli!";
			link.l1 = "Yoksa hazineyi başkası mı öğrendi? Tommy, duyuyor musun? Bizi yakaladılar. Tamam, ben öne geçiyorum, siz de burada onlara güzel bir karşılama yapın!";
			link.l1.go = "Nemezida_Irons_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Irons_6":
            dialog.text = "Şimdi duyuyorum! Kim olurlarsa olsunlar, acele etsen iyi olur, heh-heh. Yoksa, bunca yolu buraya kadar boşuna mı geldik?!";
			link.l1 = "Ah, öyle olmasını hiç istemem.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		case "Nemezida_Irons_7": // на берегу
            dialog.text = "Ah, demek sensin, kaptan! Hayatta kaldın ha. Yalan söylemeyeceğim - beklemiyordum doğrusu. Ama sevindim, yanlış anlama, heh-heh.";
			link.l1 = "Ben de beklemiyordum, yalan söylemeyeceğim. Ama hayatta kalmana hiç şaşırmadım. Kaçtın mı?";
			link.l1.go = "Nemezida_Irons_8";
		break;
		
		case "Nemezida_Irons_8":
            dialog.text = "Bana haksızlık ediyorsun! Tommy Irons asla kaçmaz! Sadece takviye almak için geri döner. Ama gerek kalmadı – adamlarımla birlikte işin üstesinden geldik, gerçi yine de hayatta kalan bir tek ben oldum, heh...";
			link.l1 = "Belki bu sefer takviye çağırmalıydın. Ama ben... ben kaçtım.";
			link.l1.go = "Nemezida_Irons_9";
		break;
		
		case "Nemezida_Irons_9":
            dialog.text = "Kaçtın mı? Heh, yine beni şaşırttın. Ama aslında işim biter bitmez sana koşmak istedim! Her türlü takviyeden daha iyiyim, biliyorsun. Sadece...";
			link.l1 = "Ne oldu, Tom?";
			link.l1.go = "Nemezida_Irons_10";
		break;
		
		case "Nemezida_Irons_10":
            dialog.text = "Lanet olsun, ben oyalanırken, arkanızdaki giriş kayalarla kapandı. Geçemedim. Orayı temizlemem bu kadar uzun sürdüğü ve sana yardım edemediğim için gerçekten utanıyorum. Yolu bulmaya çalışırken kendi başıma biraz kayboldum, adamları almak ve kayaları kaldırmaya yardım etmek için geri dönmeye çalışıyordum... Döndüğümde ise sen zaten geri dönmüştün.";
			link.l1 = "Evet, belki de bugün başıma gelenleri itiraf etmeye utanacağım.";
			link.l1.go = "Nemezida_Irons_11";
		break;
		
		case "Nemezida_Irons_11":
            dialog.text = "Ne oldu peki? Korkma, anlat bana. Ama komik bir şeyse, baştan söyleyeyim, gülerim. Başka nasıl olmalı? Bir dost omzunu uzatır, sonra da gülerek dirseğiyle dürter.";
			link.l1 = "Sen gerçekten teselli etmeyi biliyorsun. Söylesene Tommy, korsanlığı sevdiğini söylemiştin. Benimle tekrar bu işe dönmekten memnun oldun mu?";
			link.l1.go = "Nemezida_Irons_12";
		break;
		
		case "Nemezida_Irons_12":
            dialog.text = "Şöyle söyleyeyim. Korsan olup olmamam fark etmez, benim her zaman lanet olasıca sevdiğim şey macera! Cevabım seni tatmin etmedi sanırım. Böyle şeyler, bu büyük meseleler, aslında pek umurumda değil.";
			link.l1 = "Beni tatmin etmediğinden değil. Ama konuşmak istediğim konu bu değildi. Biliyor musun... Tiraqs yüzünden, hedeflerimden tamamen uzaklaştığımı fark ettim. Ayrıca... Charlie Prince de cesur bir korsan kaptan değil, bir çeşit uşakmış, anlıyor musun Tom? Bu bana yeter.";
			link.l1.go = "Nemezida_Irons_13";
		break;
		
		case "Nemezida_Irons_13":
            dialog.text = "Anlıyorum. Bu yüzden Terrax'ın seni böyle kontrol etmesine izin vermene şaşırdım. Hiç sana benzemiyordu.";
			link.l1 = "Belki o zamanlar gerçekten Charlie Prince bendim. Ama korsanlığa geri dönüp dönmeyeceğimize ben karar veririm! Ve sadece gerçekten işime yararsa ve beni amacımda daha ileriye götürürse!";
			link.l1.go = "Nemezida_Irons_14";
		break;
		
		case "Nemezida_Irons_14":
            dialog.text = "İşte bu başka! Ama şunu söylemek isterim, ister Charlie Prince ol ister Charles de Maure – sonuçta yine sensin. Seninle her zaman lanet olası derecede ilginçti!";
			link.l1 = "Bunu duyduğuma sevindim, Tommy.";
			link.l1.go = "Nemezida_Irons_15";
		break;
		
		case "Nemezida_Irons_15":
            dialog.text = "Unutma, neredeyse kimse sana yardım etmeyecek, kendinden başka. Başkalarının senin adına karar vermesine izin vermektense, sevdiğin şeyi tek başına yapmak daha iyidir!";
			link.l1 = "Doğru. Terrax'la da tam olarak böyle hissetmiştim. Birinin peşinden tekrar gidersem, bu ancak gerçekten değerli bir sebep için olur, öyle lanet bir ayakçı gibi değil!";
			link.l1.go = "Nemezida_Irons_16";
		break;
		
		case "Nemezida_Irons_16":
            dialog.text = "Haklısın! Şimdi buradan çıkalım - bacaklarım zaten titriyor.";
			link.l1 = "Hey, ben de tam bunu söyleyecektim, ha-ha. Ama haklısın, hadi gidelim. Önümüzde çok önemli işler var, Tom. Böyle şeylerle oyalanamayız.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;
		
		// Алонсо
		case "Nemezida_Alonso_1":
            dialog.text = "Kaptan, galiba misafirlerimiz var! Burada yalnız değiliz.";
			link.l1 = "Tam da ihtiyacımız olan şey... Peki, şimdi onlarla ilgilenelim. Sonra daha fazla başımıza iş açacaklar.";
			link.l1.go = "Nemezida_Alonso_2";
		break;
		
		case "Nemezida_Alonso_2":
            dialog.text = "Emredersiniz, Kaptan.";
			link.l1 = "Hazır ol!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Alonso_3":
            dialog.text = "Onlardan giderek daha fazlası geliyor!";
			link.l1 = "O zaman devam etmenin anlamı yok! Geri çekilin! Onları atlatıp doğrudan hazineye gideceğiz!";
			link.l1.go = "Nemezida_Alonso_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Alonso_4":
            dialog.text = "Emredersiniz, Kaptan!";
			link.l1 = "Çekil, çekil!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Alonso_5":
            dialog.text = "Kaptan, burada bir giriş var gibi görünüyor! Ve içeride biri zaten var.";
			link.l1 = "Dikkatle dinleyin - peşimize takılmışlar. Ben içeri girip bir bakacağım, siz burada kalın. Beni koruyun, çocuklar!";
			link.l1.go = "Nemezida_Alonso_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Alonso_6":
            dialog.text = "Emredersiniz, Kaptan!";
			link.l1 = "Yerini koru. Sana da, hepimize de bol şans!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Sen "+GetSexPhrase("Bir hırsız, görüyorum! Muhafızlar, yakalayın onu","Bir hırsız, demek! Muhafızlar, onu yakalayın")+"!!!","İnanamıyorum! Bir an için arkamı döndüm - ve sen eşyalarımı karıştırıyorsun! Dur, hırsız!!!","Gardiyanlar! Soygun! Hırsızı durdurun!!!");
			link.l1 = "Aaaah, şeytan!!!";
			link.l1.go = "fight";
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//<-- блок реагирования на попытку залезть в сундук
		
		// <-- legendary edition
	}
}
