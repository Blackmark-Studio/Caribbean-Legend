void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Ne istiyorsun?";
			link.l1 = "Hiçbir şey.";
			link.l1.go = "exit";
		break;

		case "Naemnik":
			dialog.text = "İyisin"+GetSexPhrase("","ess")+"... lanet olası iyi"+GetSexPhrase("","ess")+". Ama işi bitirmeden önce, beni bir dinle. Söyleyeceklerimin ilgini çekeceğinden eminim.";
			link.l1 = "Sanırım ölmeden önce son sözlerini söyleyebilirsin. Ama fazla umutlanma. Bu mağaradan çıkamayacaksın.";
			link.l1.go = "Naemnik_2";
		break;

		case "Naemnik_2":
			dialog.text = "Liman şefi, ha? Kafamı almaya mı gönderdi seni?";
			link.l1 = "Her zamanki gibi zekisin.";
			link.l1.go = "Naemnik_3";
		break;

		case "Naemnik_3":
			dialog.text = "Seni beni öldürmen için gönderdi, değil mi? Bulman için değil, yakalaman için değil — öldürmen için.";
			link.l1 = "Doğru. Ee, ne olmuş yani?";
			link.l1.go = "Naemnik_4";
		break;

		case "Naemnik_4":
			dialog.text = "Ha... sen gerçekten bir "+GetSexPhrase("ahmak","küçük aptal")+" . Hiç düşündün mü, neden onun için benim hücrede çürümemden ziyade ölmem bu kadar önemliydi? Hayır mı? Kimi kurtarmaya çalıştığından haberin yok. O liman tarafındaki örümcek bütün bu yere yalanlardan bir ağ ördü, ve sen, "+GetSexPhrase("oğlan","sevgilim")+", işin tam ortasında kaldınız.\nOnun dürüst bir memur olduğunu mu sanıyorsun? Ha! Dürüstlüğü ancak rüyasında görür. Korsanlara ve Hollandalılara bilgi satar. Güvenenleri sırtından vurur. Onun gibi bir haşere toprağın altında olmalı!";
			link.l1 = "Ve kim çizmeleriyle biraz toprak çiğnememiş ki. Sen de pek rahip gibi görünmüyorsun.";
			link.l1.go = "Naemnik_5";
		break;

		case "Naemnik_5":
			dialog.text = "Ben bir keşiş değilim, öyleymiş gibi de yapmam. Kılıcım asla yalan söylemez. Bir bakışım yeter, adam ölümün geldiğini anlar. Avıma gülümsemem, elini sıkmam; zaten sonunun geldiğini bilirim. Hayır. Niyetim bellidir. O bürokrat mı?\nGüvenen herkesi sırtından vurur, yardım ediyor gibi görünürken. Şimdiye kadar mezara gönderdiğim heriflerin en rezilinden bile daha beter.";
			link.l1 = "Diyelim ki doğruyu söylüyorsun. Seni kim tuttu?";
			link.l1.go = "Naemnik_6";
		break;

		case "Naemnik_6":
			dialog.text = "Sana bir isim vermeyeceğim – zaten bilmiyorum. Ama o, o pislikten zarar görmüş biri. Adalet arayan... ya da intikam peşinde bir adam. Nasıl istersen öyle de. O çürük memurun kellesi için beş yüz dublon! Bana yardım et, parayı paylaşırız.";
			link.l1 = "Yeter artık bu lafların! Canını kurtarmak için her şeyi söylersin. Konuşmana izin verdim, şimdi ölme zamanı.";
			link.l1.go = "Naemnik_7";
			link.l2 = "Güzel hikaye. Ama sana öylece inanacak değilim. Sözünden başka bir şeyin var mı? Kanıt, şahitler? Yoksa bu da ölümden kaçmak için başka bir numara mı?";
			link.l2.go = "Naemnik_8";
		break;
		
		case "Naemnik_7":
			DialogExit();
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("GS_Naemnik");
			LAi_SetImmortal(sld, false);
			LAi_SetCurHPMax(sld);
			LAi_GetCharacterMaxEnergy(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheckFunction("EnemyFight", "GS_UbivaemNaemnika");
		break;
		
		case "Naemnik_8":
			dialog.text = "Bu parşömenler, hamimin düelloda alt ettiği bir korsanın kamarasında bulundu. O alçak, istihbaratını bizzat Liman Şefi’nden almış. Burada gemi rotaları, kalkış saatleri ve taşıdıkları yükler titizlikle kaydedilmiş. Aynı gemiler daha sonra yağmalanmış, mürettebatı ya katledilmiş ya da sonsuz mavilikte kaybolmuş\nİyi dikkat et - bu notlardaki kalem izleriyle resmi kayıtlardaki tamamen aynı. Bu kanıt, hainin maskesini düşürecek. Hamim, bu belgelerin cesedinin yanında bulunmasını istiyor. Bir yargıç kürsüsü yetmezdi\nBu alçak, sayısız yozlaşmış yandaşıyla birlikte, çok fazla nüfuza sahip. Mahkemeye çıkarılsa bile adaletin elinden kayıp kurtulurdu. Böyle bir haşereye Tanrı’nın yarattığı canlılar arasında yer yok. Bu ihanete yakışan tek son, sonsuz bir rezaletle ölüm.";
			link.l1 = "Alçak köpek! Adamlar ona servetlerini emanet ediyor, o ise hayatlarını cellatlara ve haydutlara satıyor! Bu işte beni de müttefikin say. Böyle bir yaratığın Tanrı'nın göğü altında yeri yok.";
			link.l1.go = "Naemnik_9";
			GiveItem2Character(PChar, "GS_letters");
			AddQuestRecordInfo("GS_Letters", "1");
		break;

		case "Naemnik_9":
			dialog.text = "Ona ait konağın anahtarını, o görkemli malikanede mobilyaları tamir eden marangozdan edindim. Her şey planladığım gibi gidiyordu, ta ki odalarını başkasıyla paylaştığını öğrenene kadar. Adaleti sağlamak için içeri girdiğimde, yanında eşi de vardı\nOnun beklenmedik varlığı beni duraksattı. Onun kanı için bir ödül yoktu ve taç adına çalışanlar, saygın bir kadını öldürenin peşine çok daha büyük bir hırsla düşerdi. Bu yüzden planımı değiştirdim ve onu gümrük binasının yakınında beklemeye karar verdim.";
			link.l1 = "Lanet olsun! Bütün kasaba şimdi tetikte - artık eskisi gibi açıktan hareket edemeyiz. Şimdi ne yapacağız?";
			link.l1.go = "Naemnik_10";
		break;

		case "Naemnik_10":
			dialog.text = "I've kept watch over the town, biding my time until the commotion subsided. After my attempt, that cowardly rat hurried to hide away his wife. With my own eyes I saw her board a vessel and leave the harbor\nNow he remains alone - the perfect time to finish what we started. Under cover of darkness, you can slip into his lair and end this business. Then leave these damning papers where they cannot be missed, so all may know the foul corruption that festered within his heart\nBut for me, the town gates are barred. You, however... you can succeed where I cannot. No guard searches for your face; you'll pass their watch with ease. His house is near the city prison. Five hundred doubloons! Half this bounty will be yours when the traitor lies dead.";
			link.l1 = "O halde öyle olsun. Bu alçağı kendi elimle haklayıp öte tarafa göndereceğim. Bu belgeler onun evinde kalacak ki herkes ihanetinin gerçeğini görebilsin. Dönüşümü bekle. Adalet yerini bulduğunda geri döneceğim.";
			link.l1.go = "Naemnik_11";
		break;
		
		case "Naemnik_11":
			DialogExit();
			chrDisableReloadToLocation = false;
			locations[FindLocation("Beliz_Cave")].DisableEncounters = false;
			AddQuestRecord("GS", "5");
			AddQuestUserData("GS", "sSex", GetSexPhrase("","а"));
			
			sld = CharacterFromID("GS_Naemnik");
			LAi_SetWarriorType(sld);
			LAi_SetCurHPMax(sld);
			LAi_GetCharacterMaxEnergy(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
			NextDiag.CurrentNode = "Naemnik_12";
			
			sld = &Locations[FindLocation("Beliz_town")];
			sld.reload.l11.open_for_night = 1;
			sld = &Locations[FindLocation("Beliz_houseS5_room2")];
			sld.locators_radius.item.button01 = 1.0;
			
			pchar.quest.GS_SoldatyDoma.win_condition.l1 = "Hour";
			pchar.quest.GS_SoldatyDoma.win_condition.l1.start.hour = 0.00;
			pchar.quest.GS_SoldatyDoma.win_condition.l1.finish.hour = 5.00;
			PChar.quest.GS_SoldatyDoma.win_condition.l2 = "location";
			PChar.quest.GS_SoldatyDoma.win_condition.l2.location = "Beliz_houseS5";
			PChar.quest.GS_SoldatyDoma.function = "GS_SoldatyDoma";
		break;
		
		case "Naemnik_12":
			dialog.text = "Neden orada öylece donup kaldın, sanki ayakların sönmüş kirece saplanmış gibi?";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Naemnik_12";
		break;

		case "Portman_1":
			dialog.text = "Sen mi? Ne oluyor? Buraya nasıl girdin?";
			link.l1 = "Buraya nasıl geldiğimin hiçbir önemi yok. Ve bence, derinlerde bir yerde neden geldiğimi sen de anlıyorsun.";
			link.l1.go = "Portman_2";
			DelLandQuestMark(npchar);
		break;

		case "Portman_2":
			dialog.text = "Hayır, anlamıyorum! Eğer ödül için buradaysan, yarın idareye gel, sana her şeyi vereceğim.";
			link.l1 = "Masum numarası yapmayı bırak! Her şeyi biliyorum. Müşterilerinin gemileriyle ilgili bilgileri korsanlara sattın. Böyle alçak biri böyle bir mevkide olmamalı. Dahası, dürüst insanların arasında yaşamayı da hak etmiyorsun. Bayım, senin yerin kendi türünün arasında - cehennemde.";
			link.l1.go = "Portman_3";
		break;

		case "Portman_3":
			dialog.text = "Ah, hayır-hayır-hayır! Hayır! Yanlış anladınız! Onlar beni zorladılar... Geldiler ve eğer yardım etmezsem aileme zarar vereceklerini söylediler... Anlamıyorsunuz...";
			link.l1 = "Senin zavallı bahanelerinden bıktım artık! Bahşişlerden payını istediğin notlar elime geçti! İkiyüzlülüğün midemi bulandırıyor ve artık buna tahammül etmeyeceğim. Eğer cesaretin varsa silahını çek ve kendini savun!";
			link.l1.go = "Portman_4";
		break;
		
		case "Portman_4":
			DialogExit();
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Beliz_portman_clone");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheckFunction("EnemyFight", "GS_PortmanDead");
		break;
		
		case "Naemnik_21":
			dialog.text = "O halde, ne haber? İşimiz bitti mi?";
			link.l1 = "Benden şüphelendin mi? O sefil adam, dudaklarından zavallı bir bahane koparmak için kendini paraladı ama nafile. Suçlayıcı belgeleri, tam da anlaştığımız gibi, gözden kaçmayacak bir yere bıraktım.";
			link.l1.go = "Naemnik_22";
		break;

		case "Naemnik_22":
			dialog.text = "Böylesine korkak alçaklar, Adaletin kılıcından sahte sözler ve birkaç akçeyle kurtulabileceklerine hep inanır.";
			link.l1 = "Artık düşünceleri onu rahatsız etmiyor. Ödememi verin, ben de yoluma gideyim.";
			link.l1.go = "Naemnik_23";
		break;

		case "Naemnik_23":
			dialog.text = "İşte hak ettiğin doblonlar. Güzel iş çıkardın, bunu kabul ediyorum. Ama iyi dinle beni – eğer kılıcım o ilk karşılaşmamızda daha sert olsaydı, işler bambaşka sonuçlanabilirdi... ve senin için hiç de iyi olmazdı. O daracık odalarda, doğru düzgün bir silah sallanmaz; ben de sadece şu zavallı kürdanı aldım elime, seni çabucak alt ederim diye düşündüm.\nAma işlerin böyle gelişeceğini bilseydim, kendime bu mettle yakışır bir kılıç alırdım.";
			link.l1 = "Ha! Bizim merhum dostumuz, seni Roncesvalles geçidinde Roland gibi silahlı olduğunu iddia etmişti! Ne büyük bir şövalye olduğunu kanıtladın.";
			link.l1.go = "Naemnik_24";
			AddItems(pchar, "gold_dublon", 250);
		break;

		case "Naemnik_24":
			dialog.text = "Heh. Korku ne büyük gölgeler düşürür, değil mi? Kendi gözlerinle gördün, neredeyse atan kalbini delip geçecek o zavallı yemek bıçağını.";
			link.l1 = "Elinde daha ağır bir çelik olsaydı, bana layık bir rakip olabileceğini mi söylüyorsun?";
			link.l1.go = "Naemnik_25";
		break;

		case "Naemnik_25":
			dialog.text = "Orta ağırlıktaki kılıçlarda ustalığımın üstüne kimse yoktur – hayatım pahasına yemin ederim buna. Şüphe mi ediyorsun? Pekâlâ. Sayısız tehlikeden sağ çıkmamı sağlayan bazı ustalıklı hamleleri sana öğreteceğim. İyi dinle – bunlar öyle boş övünmeler değil, bir gün seni erken bir mezardan kurtarabilecek gerçek bilgiler. Böyle gizli bilgiler ancak en layık öğrencilere verilir.";
			link.l1 = "...";
			link.l1.go = "Naemnik_26";
		break;
		
		case "Naemnik_26":
			DialogExit();
			SetLaunchFrameFormParam("An hour passes...", "Run_Function", 0, 4.0);
			SetLaunchFrameRunFunctionParam("GS_Spravedlivost_2", 0.0);
			LaunchFrameForm();
		break;

		case "Naemnik_27":
			dialog.text = "...";
			link.l1 = "Gerçekten işinizde usta olduğunuzu görüyorum. Öğrettikleriniz için size teşekkür ederim. Ama işlerimiz bittiyse, artık yoluma devam etmeliyim.";
			link.l1.go = "Naemnik_28";
			AddComplexSelfExpToScill(0, 500, 0, 0);
		break;

		case "Naemnik_28":
			dialog.text = "Hoşça kal, "+GetSexPhrase("Kaptan","güzel hanımefendi")+". Umarım bir daha kılıçlarımızı karşı karşıya getirmeyiz. Seni yaratıcına göndermek beni üzerdi. Ha-ha.";
			link.l1 = "Senin zerre kadar şansın olmazdı, ben sarhoş olup tek ayak üstünde dursam bile! Elveda, paralı asker.";
			link.l1.go = "Naemnik_29";
		break;
		
		case "Naemnik_29":
			DialogExit();
			AddDialogExitQuestFunction("Naemnik_29");
			
			AddSimpleRumourCity("Word has it the Port Chief was found dead in his own home. Documents were discovered on his body proving his involvement in the disappearance of ships. Just imagine—what a disgrace for our town...", "Beliz", 30, 1, "");
			AddSimpleRumourCity("Have you heard the news? Someone snuck into the Port Chief’s house, killed the guards, and took him out. They found notes on the body with routes of missing ships—written in his own hand! A servant of the Crown, yet a traitor in truth! Got what he deserved! And where was the Governor all these years?", "Beliz", 30, 1, "");
			AddSimpleRumourCity("The Port Master is dead! Killed right in his own home! The guards were slaughtered, and among his possessions were notes mapping routes of vanished ships. No doubt about it—he was behind the disappearances! Justice has finally caught up with the scoundrel.", "Beliz", 30, 1, "");
			break;
	}
}