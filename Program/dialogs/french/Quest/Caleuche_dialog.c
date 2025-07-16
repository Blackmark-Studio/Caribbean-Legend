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
			dialog.text = "C'est certainement un bug. Pouvez-vous informer Jason de quand et comment cela est arrivé.";
			link.l1 = "Je m'en occuperai.";
			link.l1.go = "exit";
		break;
		
		// шаман карибов Туттуатхапак
		case "Tuttuat":
			dialog.text = "Pourquoi es-tu venu dans ma hutte, homme blanc ? Tuttuathapak ne pense pas que tu sois son cher invité.";
			if (GetCharacterFreeItem(pchar, "mushket1") || GetCharacterFreeItem(pchar, "mushket2") || GetCharacterFreeItem(pchar, "mushket7"))
			{
				link.l1 = "Salut à toi, grand chaman Tuttuathapak. Je suis venu te demander ton aide et tes conseils.  Je t'offre ce mousquet en gage de ma bonne volonté.";
				link.l1.go = "Tuttuat_1";
			}
			else
			{
				link.l1 = "Salut à toi, grand chaman Tuttuathapak. Je suis venu te demander aide et conseil.";
				link.l1.go = "Tuttuat_exit";
			}
		break;
		
		case "Tuttuat_exit":
			dialog.text = "Tuttuathapak n'aide pas l'homme blanc. Les hommes blancs sont de mauvais hommes. Ils tuent et conquièrent les Indiens, font des Indiens des esclaves. Tuttuathapak ne donne aucun conseil à l'homme blanc. Vous partez maintenant.";
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
			dialog.text = "Toi savoir quoi donner à Tuttuathapak, homme blanc. Tuttuathapak accepte ton cadeau. Il parlera. Quel conseil cherches-tu de moi ?";
			link.l1 = "J'ai entendu dire que vous veniez d'un endroit lointain au sud. J'ai un amulette indienne, et un homme savant m'a dit que vous pourriez savoir comment elle peut être utilisée.";
			link.l1.go = "Tuttuat_2";
			DelLandQuestMark(npchar);
			DelMapQuestMarkIsland("Dominica");
		break;
		
		case "Tuttuat_2":
			dialog.text = "Montre l'amulette.";
			link.l1 = "Voici, grand chaman.";
			link.l1.go = "Tuttuat_3";
		break;
		
		case "Tuttuat_3":
			PlaySound("interface\important_item.wav");
			dialog.text = "(regardant l'amulette)... Ton ami dit la vérité, homme blanc. Cet amulette appartient à mon peuple, les grands Indiens, Chavin était leur nom. Un bâtard impie et maudit au visage pâle a profané le sanctuaire et l'a emportée ici. Tuttuathapak a puni ce chien.";
			link.l1 = "Tu l'as privé de son esprit, je suppose ?";
			link.l1.go = "Tuttuat_4";
		break;
		
		case "Tuttuat_4":
			dialog.text = "L'homme blanc surprend Tuttuathapak avec son savoir. Oui, je dévore l'esprit de ce chien galeux. Lui et son homme immonde obtiennent ce qu'ils méritent.";
			link.l1 = "Je vois... Dis-moi, chaman, à quoi sert cet amulette ? Peut-être peut-elle protéger quelqu'un au combat ou éloigner la magie maléfique ?";
			link.l1.go = "Tuttuat_5";
		break;
		
		case "Tuttuat_5":
			dialog.text = "Cet amulette ne te sert à rien, capitaine blanc. Tu ne peux en utiliser le pouvoir. Seuls les grands chamans de notre tribu savent comment l'éveiller.";
			link.l1 = "Hmm... Alors, il s'avère que j'ai fait un si long voyage en vain. Mais, peut-être, pouvez-vous éveiller le pouvoir de cet amulette, grand chaman ? Certainement nous pourrions parvenir à un accord...";
			link.l1.go = "Tuttuat_6";
		break;
		
		case "Tuttuat_6":
			dialog.text = "Même si je réveille l'amulette, tu ne pourras pas tenir son pouvoir longtemps. Mais je te propose un marché, homme blanc.";
			link.l1 = "Quel genre d'accord ?";
			link.l1.go = "Tuttuat_7";
		break;
		
		case "Tuttuat_7":
			dialog.text = "Trois amulettes comme celle-ci ont été prises de notre sanctuaire. Elles ont des pouvoirs différents, mais si elles sont réunies, elles seront très très puissantes. Trouve les trois amulettes et apporte-les moi, et je te récompenserai. Je te donnerai un pouvoir que tu pourras garder pour toujours.";
			link.l1 = "Je ne comprends pas très bien... De quelle sorte de pouvoir parlez-vous ?";
			link.l1.go = "Tuttuat_8";
		break;
		
		case "Tuttuat_8":
			dialog.text = "Tu sauras tout en temps voulu. Trouve et apporte-moi les trois amulettes. Elles sont dans les Caraïbes. Cherche et trouve. Tu les reconnaîtras facilement - elles se ressemblent. Va, homme blanc. Tuttuathapak attend et demande aux esprits de t'aider.";
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
				dialog.text = "Va, homme blanc. Trouve deux autres amulettes.";
				link.l1 = "Je les ai déjà trouvés, grand chaman. Tenez, regardez.";
				link.l1.go = "Tuttuat_33";
			}
			else
			{
				dialog.text = "Va, homme blanc. Trouve les deux autres amulettes.";
				link.l1 = "D'accord.";
				link.l1.go = "Tuttuat_10_1";
			}
		break;
		
		case "Tuttuat_10_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_10";
		break;
		
		case "Tuttuat_11":
			dialog.text = "Toi ici encore, homme blanc ? On dirait que tu as rencontré un jaguar féroce dans la jungle.";
			link.l1 = "Bien pire, grand chaman. Lorsque j'ai mis le pied dans la mer, une tempête massive est apparue de nulle part et j'ai été attaqué par un navire dirigé par des morts-vivants ! Leur capitaine était totalement invincible. D'abord, il m'a pris l'amulette et a failli me tuer - j'ai à peine survécu. Et ensuite, ils ont presque coulé mon navire, seulement une poignée de mon équipage a survécu.";
			link.l1.go = "Tuttuat_12";
			DelLandQuestMark(npchar);
		break;
		
		case "Tuttuat_12":
			dialog.text = "Mauvaises nouvelles, homme blanc. Le Caleuche part à nouveau pour tuer.";
			link.l1 = "Le Caleuche ? Ce capitaine mort-vivant appelait son navire le Coeur Volant. Alors, tu savais pour le navire fantôme et tu ne m'en as pas averti ? Si j'avais su que ce cauchemar marin chassait l'amulette, je n'aurais jamais...";
			link.l1.go = "Tuttuat_13";
		break;
		
		case "Tuttuat_13":
			dialog.text = "Tuttuathapak voit que le capitaine blanc est contrarié. Le capitaine blanc doit se calmer.";
			link.l1 = "Me calmer ?! Tu es fou, comment puis-je même survivre contre une telle chose !";
			link.l1.go = "Tuttuat_14";
		break;
		
		case "Tuttuat_14":
			dialog.text = "Oui. Calmez-vous et ne criez pas. Dites-moi - vous voulez toujours recevoir de grands pouvoirs de moi, qui resteront avec vous pour toujours ?";
			link.l1 = "Eh bien, bien sûr que je le fais. Mais je n'ai plus l'amulette.";
			link.l1.go = "Tuttuat_15";
		break;
		
		case "Tuttuat_15":
			dialog.text = "Je t'apprends comment prendre l'amulette du capitaine du Caleuche. Ce ne sera pas facile. Mais si tu y parviens, tu prendras son navire comme ton prix, trouveras un trésor précieux, gagneras la gloire auprès de ton peuple et recevras une récompense de ma part.";
			link.l1 = "Nom de Dieu! Je détruirais volontiers ce monstre ratatiné ! Mais comment puis-je le vaincre, s'il ne peut être blessé ni par l'épée, ni par la balle ?!";
			link.l1.go = "Tuttuat_16";
		break;
		
		case "Tuttuat_16":
			dialog.text = "Tu es prêt à m'écouter, capitaine blanc ?";
			link.l1 = "Oui, je le suis, grand chaman.";
			link.l1.go = "Tuttuat_17";
		break;
		
		case "Tuttuat_17":
			dialog.text = "Quand mon père était un jeune guerrier, les hommes blancs arrivèrent sur ma terre à bord du navire le Cœur Volant. Ils allèrent vers les montagnes. La légende dit qu'un sanctuaire de nos ancêtres y est caché. Sanctuaire des guerriers jaguar. Les hommes blancs trouvèrent le sanctuaire et l'or et profanèrent une chose sacrée ancienne. Ils emportèrent un grand trésor des Chavins - le crâne de jade de Yum Cimil, dieu de la mort et patron des hommes jaguar.\nLes hommes blancs retournèrent à leur navire. Ils décidèrent de revenir pour prendre plus d'or, mais dès que leur homme posa le pied sur la terre ferme, il mourut dans une douleur horrible. Yum Cimil maudit le capitaine et son équipage. Ils devinrent immortels, mais ils ne pouvaient plus poser pied à terre. Ils naviguèrent de nombreux hivers, un demi-siècle selon votre calendrier. C'est ainsi que le Caleuche vit le jour.\nLeurs corps dépérissent, leur chair pourrit, mais ils vivent toujours. Si vous leur tranchez un bras ou une jambe, cela repousse. Si vous les découpez, ils redeviennent un. Si leur navire fait naufrage, ils le réparent sous l'eau, et il navigue à nouveau.";
			link.l1 = "Juste fantastique...";
			link.l1.go = "Tuttuat_18";
		break;
		
		case "Tuttuat_18":
			dialog.text = " Le Caleuche terrorise les marins. Il attaque sans raison et promet un destin funeste. Il n'est pas un invité fréquent dans les Caraïbes. Il aime naviguer sur les côtes de ma patrie. Je crois qu'il veut lever la malédiction. Mais il ne la lèvera jamais.";
			link.l1 = "Pourquoi ? Que faut-il faire pour lever la malédiction ?";
			link.l1.go = "Tuttuat_19";
		break;
		
		case "Tuttuat_19":
			dialog.text = "Crâne de jade. Il doit retourner au sanctuaire de Yum Cimil, temple des guerriers jaguars. Il y a plusieurs temples. Les anciens de ma tribu disent qu'il y en a un sur une petite île dans les Caraïbes. C'est pourquoi le Caleuche y a navigué. Une fois le crâne au temple, le sort de Yum Cimil se brise, et ils deviennent mortels et ne guérissent plus leurs blessures.";
			link.l1 = "Ha ! Plus probablement, ils ne vont pas rendre le crâne ! Pourquoi le feraient-ils, s'ils sont immortels et invincibles ? Et puis, ils ne peuvent tout simplement pas le ramener, s'ils ne sont pas autorisés à poser le pied sur terre, n'est-ce pas ?";
			link.l1.go = "Tuttuat_20";
		break;
		
		case "Tuttuat_20":
			dialog.text = "Ils n'ont pas de crâne. Le capitaine l'a jeté sur la terre de mes ancêtres, quand il est revenu du sanctuaire des hommes jaguar. Le jade n'est pas de l'or, l'homme blanc n'en a pas besoin, il ne pouvait pas prendre la belle gemme verte dans les yeux du crâne. Et il l'a jeté. Un marin l'a ramassé, et il n'a pas été touché par la malédiction\nQuand le marin a vu ce que l'équipage du Caleuche était devenu, il s'est enfui. Il est venu dans notre village. Mon père a vu ce marin et le crâne de Yum Cimil. Et puis l'homme blanc est allé vers le Nord le long de la côte et a pris le crâne avec lui.";
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				if (CheckAttribute(pchar, "questTemp.Caleuche.SolomonSkul"))
				{
					link.l1 = "Un crâne de jade avec des pierres vertes dans les orbites oculaires ? Je l'avais entre mes mains, peux-tu imaginer ? Je l'ai donné à Salomon moi-même. Mais il est parti pour l'Europe avec sa fille, et il semble qu'il ait emporté le crâne avec lui.";
				}
				else
				{
					link.l1 = "Un crâne de jade avec des gemmes vertes dans les orbites ? Nom d'un chien... J... Je l'ai tenu de mes propres mains ! Et je l'ai vendu à un Portugais... Merriman, ou quelque chose comme ça... Oui, c'est ce qu'il a dit - le crâne de Yum Cimil ! Il le voulait vraiment ! Il a payé un demi-million de pesos pour ça !";
				}
				link.l1.go = "Tuttuat_21_1";
			}
			else
			{
				link.l1 = "Un crâne de jade avec des gemmes vertes dans les orbites ? Alors c'est ça que je dois trouver ? Mais ce marin pourrait être mort dans la selva il y a cinquante ans, et le crâne pourrait être perdu à jamais !";
				link.l1.go = "Tuttuat_21_2";
			}
		break;
		
		case "Tuttuat_21_1":
			dialog.text = "Moi savoir que le crâne est aux Caraïbes. Le Caleuche être ici pas par hasard. Depuis les six dernières lunes, il souvent vu à l'île. Autrefois, il être pas là pour beaucoup d'hivers. Capitaine du Caleuche peut sentir l'artefact des hommes jaguar. C'est ainsi qu'il te trouver et ton navire.";
			link.l1 = "Alors, ai-je bien compris que je dois retrouver ce crâne encore une fois ? Et ensuite, que dois-je en faire ?";
			link.l1.go = "Tuttuat_22";
		break;
		
		case "Tuttuat_21_2":
			dialog.text = "Le Crâne doit être ici, dans les Caraïbes. Le Caleuche ne se trouve pas ici par hasard. Depuis les six dernières lunes, il a souvent été aperçu près de l'île. Avant cela, il n'y était pas pendant de nombreux hivers. Le capitaine du Caleuche peut ressentir l'artéfact des hommes-jaguars. C'est ainsi qu'il t'a trouvé, toi et ton navire.";
			link.l1 = "Alors, est-ce que je comprends bien que je dois retrouver ce crâne encore une fois ? Et ensuite, qu'est-ce que je devrais en faire ?";
			link.l1.go = "Tuttuat_22";
		break;
		
		case "Tuttuat_22":
			dialog.text = "Tout d'abord, tu dois trouver les deux amulettes dont nous avons parlé. Sans elles, tu ne peux rien faire. Les amulettes te donnent le pouvoir de tenir tête aux hommes-jaguars et à tout ennemi que tu rencontreras.";
			link.l1 = "Se dresser contre des hommes jaguars ? De quoi parles-tu ?";
			link.l1.go = "Tuttuat_23";
		break;
		
		case "Tuttuat_23":
			dialog.text = "Le temple où vous devez apporter le crâne de jade est sur une île déserte des Caraïbes. Il est gardé par des hommes jaguars. Ils sont tous morts mais vivants maintenant. Sans amulette, vous ne les passerez pas. Les hommes jaguars étaient de féroces guerriers de leur vivant, et après la mort, ils deviennent presque invincibles. Ils reçoivent leur force de Yum Cimil lui-même.";
			link.l1 = "Des morts-vivants ? Encore ? Quelle chance j'ai...";
			link.l1.go = "Tuttuat_24";
		break;
		
		case "Tuttuat_24":
			dialog.text = "Pourquoi si surpris, capitaine blanc ? Yum Cimil est un dieu de la mort, le crâne de jade donne le pouvoir sur les morts et les vivants. Caraïbes. Il est gardé par des hommes jaguars. Sans amulette, tu ne les passeras pas. Avec l'amulette, tu peux entrer dans le temple et survivre, tu laisses le crâne là, puis trouves le Caleuche, défaites son capitaine et reprends l'amulette qu'il t'a prise.";
			link.l1 = "Et pourquoi le capitaine du Caleuche a-t-il besoin de ces amulettes ?";
			link.l1.go = "Tuttuat_25";
		break;
		
		case "Tuttuat_25":
			dialog.text = "Il me semble qu'il veut aller au temple des hommes jaguar et il pense que l'amulette l'aidera. Mais je peux me tromper. Pourtant, le Caleuche est toujours attiré par les artefacts de ma terre. Elle a navigué près de l'île où se trouve le temple des hommes jaguar, et elle a navigué sur les côtes de ma patrie.";
			link.l1 = "Et où se trouve cette île ?";
			link.l1.go = "Tuttuat_26";
		break;
		
		case "Tuttuat_26":
			dialog.text = "Premièrement, tu trouves le crâne de Yum Cimil et les amulettes. Ensuite, nous parlerons de l'île.";
			link.l1 = "Très bien. Peux-tu me donner un indice sur où chercher le crâne de jade ?";
			link.l1.go = "Tuttuat_27";
		break;
		
		case "Tuttuat_27":
			dialog.text = "Moi pas savoir. Mais c'est ici, aux Caraïbes. Et des amulettes aussi. Demande. Cherche. Trouve.";
			link.l1 = "Heh... D'accord, je vais essayer.";
			link.l1.go = "Tuttuat_28";
		break;
		
		case "Tuttuat_28":
			dialog.text = "Sois prudent, capitaine blanc. Le Caleuche ressent les objets Chavins. Quand tu auras l'amulette, elle te cherchera. Si elle te trouve, fuis vite. Si elle t'attrape, t'es un homme mort.";
			link.l1 = "Ce navire maudit est incroyablement rapide ! Il est environ deux fois plus rapide que tout navire que j'ai jamais vu. Mais j'ai remarqué qu'il peine à naviguer contre le vent.";
			link.l1.go = "Tuttuat_29";
		break;
		
		case "Tuttuat_29":
			dialog.text = "La Caleuche est maudite - c'est pourquoi elle est si rapide. Difficile de s'échapper. Vous devez avoir un navire capable de distancer la Caleuche. Ou vous finirez mort. Lorsque vous trouverez l'amulette, apportez-la-moi. Ne gardez pas l'amulette sur le navire.";
			link.l1 = "Je l'ai déjà. Merci pour ton conte, grand chaman. Il est temps pour moi de partir maintenant.";
			link.l1.go = "Tuttuat_31";
		break;
		
		case "Tuttuat_31":
			dialog.text = "Je vais demander aux esprits de vous aider et de vous sauver du Caleuche.";
			link.l1 = "...";
			link.l1.go = "Tuttuat_32";
		break;
		
		case "Tuttuat_32":
			DialogExit();
			LocatorReloadEnterDisable("Shore27", "boat", false);
			npchar.dialog.currentnode = "Tuttuat_10";
			pchar.questTemp.Caleuche = "mayak"; 
			AddQuestRecord("Caleuche", "6");
		break;
		
		case "Tuttuat_33":
			if (CheckCharacterItem(pchar, "kaleuche_amulet2")) RemoveItems(pchar, "kaleuche_amulet2", 1);
			else RemoveItems(pchar, "kaleuche_amulet3", 1);
			Log_Info("You have given the amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "(regardant) Oui, c'est celui-là. Deuxième amulette de Chavins. Tu es bon. Tu dois encore trouver une autre amulette.";
			link.l1 = "Je m'en souviens, chaman. Bientôt, tu l'auras.";
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
				dialog.text = "Va, homme blanc. Trouve un autre amulette.";
				link.l1 = "Je l'ai déjà, grand chaman. Tenez, regardez.";
				link.l1.go = "Tuttuat_36";
			}
			else
			{
				dialog.text = "Va, homme blanc. Trouve encore un amulette.";
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
			dialog.text = "(regardant) Oui, c'est celui-là. Troisième amulette des Chavins. Tu es doué. Tu as trouvé toutes les amulettes pour passer les guerriers jaguars morts, serviteurs de Yum Cimil.";
			link.l1 = "Maintenant, si je comprends bien, j'aurai besoin du crâne de jade ?";
			link.l1.go = "Tuttuat_37";
			DelLandQuestMark(npchar);
			DelMapQuestMarkIsland("Dominica");
		break;
		
		case "Tuttuat_37":
			dialog.text = "Tu dis vrai. Crâne de jade de Yum Cimil. Tu dois l'apporter au temple de Chavins. Alors le Caleuche perdra son pouvoir pour de bon.";
			link.l1 = " Tuttuathapak, s'il te plaît, dis-moi, où chercher ? Des idées ?";
			link.l1.go = "Tuttuat_38";
		break;
		
		case "Tuttuat_38":
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				dialog.text = "Non. Pensez à l'endroit où vous avez vu le crâne de jade pour la dernière fois. À qui vous l'avez donné. Commencez à chercher là-bas.";
				link.l1 = "D'accord, grand chaman. Je ferai tout ce que je peux.";
				link.l1.go = "Tuttuat_39";
			}
			else
			{
				dialog.text = "Un sorcier blanc intéressé par le crâne de Yum Cimil. Il le cherche. Il est même venu dans notre village. J'ai entendu dire que le sorcier vit dans une maison sur l'île hollandaise. Cherchez le sorcier sur l'île hollandaise, et vous pourriez apprendre quelque chose.";
				link.l1 = "D'accord, grand chaman. Je ferai tout ce que je peux.";
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
			dialog.text = "Va, homme blanc. Trouve le crâne de jade de Yum Cimil.";
			if (pchar.questTemp.Caleuche == "island")
			{
				link.l1 = "Je l'ai ici, grand chaman, jetez un oeil.";
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
			dialog.text = "Va, homme blanc. Trouve le crâne de jade de Yum Cimil.";
			link.l1 = "Je crains de ne pouvoir le faire. J'ai trouvé le sorcier, mais au dernier moment, il s'est échappé avec le crâne. Je n'ai absolument aucune idée d'où il peut être maintenant.";
			link.l1.go = "Tuttuat_42";
		break;
		
		case "Tuttuat_42":
			dialog.text = "C'est très mauvais, homme blanc. Maintenant, tu ne passeras pas le temple et ne vaincras pas le Caleuche. Je ne te donnerai pas de cadeau. Maintenant, pars.";
			link.l1 = "...";
			link.l1.go = "Tuttuat_43";
		break;
		
		case "Tuttuat_43":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_44";
		break;
		
		case "Tuttuat_44":
			dialog.text = "Tu pars maintenant, homme blanc.";
			link.l1 = "...";
			link.l1.go = "Tuttuat_44_1";
		break;
		
		case "Tuttuat_44_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_40";
		break;
		
		case "Tuttuat_45":
			dialog.text = " (regardant) Oui, c'est celui-là. Très belle. Et très effrayante.";
			link.l1 = "Bien sûr... Mais ce qui est plus intéressant - j'ai traversé toute la mer des Caraïbes de Cuba à la Dominique, et le Caleuche n'a jamais essayé de m'attaquer, quand j'avais ce crâne, je ne l'ai même pas vu. Et quand je transportais des amulettes pour toi, il me traquait constamment dès que je mettais les voiles, il me retrouvait en quelques heures.";
			link.l1.go = "Tuttuat_46a";
		break;
		
		case "Tuttuat_46a":
			dialog.text = "Il me semble que le Caleuche a peur du crâne ou qu'il ne peut pas le sentir. Je n'ai pas d'autre explication. Peut-être que Yum Cimil rend le crâne de jade très dangereux pour le Caleuche - en plus de la malédiction. Peut-être est-ce pour cela que le capitaine tenait tant à prendre les trois amulettes de mon peuple. Pour acquérir la sagesse de contrôler le sort de Yum Cimil.";
			link.l1 = "Alors, tant que j'ai le crâne de jade à bord de mon navire, je n'ai rien à craindre des attaques du Caleuche ?";
			link.l1.go = "Tuttuat_46b";
		break;
		
		case "Tuttuat_46b":
			dialog.text = "Exactement, visage pâle. Tu le vois par toi-même.";
			link.l1 = "Très bien ! Alors, je peux prendre le commandement d'un grand navire, engager un équipage décent et préparer un bel accueil pour ce mort-vivant, quand le sort sera levé de lui, sans craindre qu'il ne m'intercepte plus tôt...";
			link.l1.go = "Tuttuat_46c";
		break;
		
		case "Tuttuat_46c":
			dialog.text = "";
			link.l1 = "...a propos de ce sort, d'ailleurs - où dois-je emmener le crâne de jade ?";
			link.l1.go = "Tuttuat_46";
		break;
		
		case "Tuttuat_46":
			dialog.text = "Tu dois l'apporter au temple de Chavins et terminer ton voyage. Je veux te raconter une histoire. Tu es prêt à écouter, homme blanc ?";
			link.l1 = "Mes oreilles sont toujours ouvertes à ta sagesse, Tuttuathapak.";
			link.l1.go = "Tuttuat_47";
		break;
		
		case "Tuttuat_47":
			dialog.text = "Comme le disent les légendes de mes ancêtres, il y a longtemps, lorsque les hommes au visage pâle n'étaient pas encore venus sur notre terre, le grand chef des Chavins a construit un canoë très, très grand et l'a envoyé avec un groupe de guerriers vers la terre de nombreuses îles. Le fils du grand chef les a menés, et il y avait aussi l'un des hauts chamans. Dans la terre de nombreuses îles, ils ont trouvé une terre déserte et ont fondé une colonie et construit un grand temple pour Yum Cimil, que seuls nos grands ancêtres pouvaient édifier\nLes messagers sont revenus avec de bonnes nouvelles, mais personne n'a vu ni le fils du chef, ni le chaman, ni les guerriers depuis lors. La légende dit qu'ils sont restés là pour vivre, mais les plus sages des chamans ont parlé aux esprits et ont dit qu'il n'y avait plus d'hommes là-bas, et que Yum Cimil régnait sur cette terre\nLa terre de nombreuses îles, c'est les Caraïbes, homme blanc. Le temple de Yum Cimil est sur une île où ni hommes blancs ni Indiens ne vivent. Seuls les serviteurs de Yum Cimil, les Chavinavi, gardent encore les corridors du temple.";
			link.l1 = "Où se trouve cette île ?";
			link.l1.go = "Tuttuat_48";
		break;
		
		case "Tuttuat_48":
			dialog.text = "Je suppose qu'elle est petite et au nord du village quelque part dans cette vaste étendue d'eau que vous appelez océan, ce n'est pas loin.";
			link.l1 = "Hmm... Au nord de la Dominique à la frontière de l'océan peut-être ? Nom de Dieu - c'est une très vaste zone en mer ! Comment suis-je censé trouver une petite île là-bas, si personne n'en a entendu parler ?";
			link.l1.go = "Tuttuat_49";
		break;
		
		case "Tuttuat_49":
			dialog.text = "Je ne puis mieux dire. Mais je connais encore une autre histoire. Vous pourriez l'entendre de vos frères. Il y a environ vingt hivers, l'homme blanc trouve cette île. Avec une femme et un vieil homme, il entre dans le temple de Yum Cimil et emporte un artefact puissant - l'orbe du soleil levant. Aux rivages de l'île, le capitaine au visage pâle est attaqué par le Caleuche. Le visage pâle est malin. Il aveugle le capitaine et l'équipage du Caleuche avec le soleil levant. La malédiction du Caleuche s'affaiblit, et le capitaine le coule, mais l'orbe du soleil levant se dissout. Si vous trouvez cet homme au visage pâle, il vous dira où se trouve l'île.";
			if (CheckAttribute(pchar, "questTemp.NatanStory")) link.l1 = "Ha ! Je pense que je connais cet 'homme au visage pâle'... Les histoires se ressemblent trop. Alors, le Caleuche a été coulé ?";
			else link.l1 = "Hmm... Alors, le Caleuche a été coulé ?";
			link.l1.go = "Tuttuat_50";
		break;
		
		case "Tuttuat_50":
			dialog.text = "Oui, mais la malédiction les protège de la mort. Ils l'ont réparée et ont continué leur voyage éternel.";
			link.l1 = "D'accord, compris. Mais que dois-je faire dans le temple ? Où dois-je mettre le crâne ? Comment puis-je vaincre les guerriers jaguars qui le gardent ? S'ils sont les Chavinavi comme ceux invoqués par ce sorcier Merriman, il serait insensé d'y aller seul - chacun d'eux est aussi fort que dix soldats.";
			link.l1.go = "Tuttuat_51";
		break;
		
		case "Tuttuat_51":
			dialog.text = "Ils ne le sont pas. Les Chavinavi invoqués par le sorcier blanc avec le crâne sont faibles. Bien plus faibles que ceux invoqués par Yum Cimil lui-même. Tu ne leur fais jamais de mal, et ils te tuent d'un seul coup de leur arme.";
			link.l1 = "Attends - et comment cet 'homme au visage pâle' a-t-il réussi à entrer dans le temple et voler l'artefact ?";
			link.l1.go = "Tuttuat_52";
		break;
		
		case "Tuttuat_52":
			dialog.text = "Avant que ce premier visage pâle n'entre dans le temple, il était gardé par les esprits des ancêtres morts. Le visage pâle était un guerrier fort et il les a vaincus. Quand il a volé l'orbe du soleil levant, Yum Cimil était furieux. Il a envoyé feu et soufre sur l'homme au visage pâle et a presque détruit le temple, mais il s'est enfui avec l'artefact. Maintenant Yum Cimil a convoqué des guerriers jaguars invincibles pour garder le temple.";
			link.l1 = "Glorieux ! Et comment vais-je m'infiltrer, alors ?";
			link.l1.go = "Tuttuat_53";
		break;
		
		case "Tuttuat_53":
			dialog.text = "Je t'aide, homme blanc. Je te donne deux amulettes Chavins que tu m'apportes. Je parle aux esprits des ancêtres et je renforce l'amulette. Quand tu en as une avec toi, tu peux combattre les guerriers jaguars comme des soldats ordinaires, tu seras comme l'un d'eux, mais très fort. L'amulette te protège et te donne le pouvoir d'arme pour nuire au Chavinavi du temple.";
			link.l1 = "Es-tu sûr que les amulettes aideront ?";
			link.l1.go = "Tuttuat_54";
		break;
		
		case "Tuttuat_54":
			dialog.text = "Moi savoir. Moi parler aux ancêtres. Moi grand chaman. Toi me faire confiance. Toi prendre deux amulettes. Une protège. Autre renforce arme. Une amulette toi devoir utiliser. Laquelle - toi choisir. Si toi pas porter amulette, toi périr face aux guerriers jaguars\nEt toi te souvenir qu'à minuit Yum Cimil ramène à la vie tous les guerriers que toi tuer. Toi devoir trouver le moment pour ne pas les combattre deux fois, ou bien le faire, les esprits me dire que toi pourrais.";
			link.l1 = "Je vois.";
			link.l1.go = "Tuttuat_55";
		break;
		
		case "Tuttuat_55":
			dialog.text = "Tu prends des amulettes. Les voici. Tu te souviens, leur pouvoir a des limites. Il s'affaiblit en une lune. Tu te souviens que je t'ai dit que tu ne peux pas retenir leur pouvoir ? Seul le grand chaman de notre tribu peut le retenir.";
			link.l1 = "Je me souviens. Alors, je n'ai qu'une lune ? Un mois ?";
			link.l1.go = "Tuttuat_56";
		break;
		
		case "Tuttuat_56":
			dialog.text = "Oui. Quand tu arrives au temple Yum Cimil, tu dois trouver le sanctuaire et une grande statue du Condor à l'intérieur. C'est la partie la plus importante du temple. Ici, tu places le crâne de jade de Yum Cimil, et la malédiction sera levée du Caleuche. Quand il t'attaque à nouveau, tu le bats comme un homme ordinaire. Ensuite, tu m'apportes l'amulette qu'il t'a prise.";
			link.l1 = "Condor ? Qu'est-ce que c'est ?";
			link.l1.go = "Tuttuat_57";
		break;
		
		case "Tuttuat_57":
			dialog.text = "Le condor est un grand oiseau qui vit dans les montagnes de ma patrie. En mémoire de chez nous, les ancêtres ont construit une statue du condor près du sanctuaire.";
			link.l1 = "Très bien, je vais le chercher...";
			link.l1.go = "Tuttuat_58";
		break;
		
		case "Tuttuat_58":
			dialog.text = "Fais attention. De nombreux dangers rôdent dans le temple à côté des guerriers jaguars.";
			link.l1 = "Quels dangers ?";
			link.l1.go = "Tuttuat_59";
		break;
		
		case "Tuttuat_59":
			dialog.text = "Je ne sais pas vraiment. Tu vois par toi-même. Cela peut être un piège, ou une... confusion. Entrer dans le sanctuaire est difficile. L'entrée est scellée, et tu dois trouver comment l'ouvrir. Mes ancêtres n'étaient pas seulement de grands guerriers et chamans, mais aussi de grands bâtisseurs, pour l'ouvrir tu dois réfléchir.";
			link.l1 = "Heh! Cela semble effrayant, mais laissez-les tous venir ! Je ne vais pas perdre de temps. Je mets les voiles immédiatement !";
			link.l1.go = "Tuttuat_60";
		break;
		
		case "Tuttuat_60":
			dialog.text = "Va, guerrier blanc. Moi invoquerai les esprits pour t'aider contre les guerriers jaguars et le Caleuche. Souviens-toi, si tu utilises des amulettes je peux t'aider, sinon tu périras";
			link.l1 = "Merci grand chaman...Je m'en chargerai.";
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
			sld.picIndex = 13;
			sld.picTexture = "ITEMS_36";
			sld.groupID = TALISMAN_ITEM_TYPE;
			sld.unique = true;	
			sld.ItemType = "ARTEFACT";
			sld = ItemsFromID("kaleuche_amulet3");
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
				dialog.text = "Moi parler avec les esprits. Tu étais sur l'île dans le temple de Yum Cimil. As-tu trouvé le Caleuche et l'amulette ?";
				link.l1 = "Tu as raison, grand chaman. J'ai trouvé l'île, suis entré dans le temple et ai laissé le crâne de jade à l'intérieur.";
				link.l1.go = "Tuttuat_63";
			}
			else
			{
				dialog.text = "Va, guerrier blanc.";
				if (CheckAttribute(pchar, "questTemp.Caleuche.AmuletOver"))
				{
					link.l1 = "Tuttuathapak, tu vois... Je n'ai pas apporté le crâne au temple à temps, et tes amulettes ont perdu leur pouvoir.";
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
			dialog.text = "Vous avez levé la malédiction du Caleuche. Elle vous a trouvé ensuite ?";
			link.l1 = "Oui. Nous nous sommes rencontrés directement sur l'île. Je me suis battu avec elle et en suis sorti victorieux. Maintenant, j'ai les trois amulettes. Tiens, prends-les.";
			link.l1.go = "Tuttuat_64";
		break;
		
		case "Tuttuat_64":
			RemoveItems(pchar, "kaleuche_amulet1", 1);
			RemoveItems(pchar, "kaleuche_amulet2", 1);
			RemoveItems(pchar, "kaleuche_amulet3", 1);
			Log_Info("You have given three Chavin amulets");
			PlaySound("interface\important_item.wav");
			dialog.text = "Toi rapide et fort guerrier, visage-pale. Tuttuathapak n'aime pas les hommes blancs, mais moi respecter brave et habile guerrier. Tu as très bien réussi. Tu as débarrassé les mers du Caleuche. Tu m'apportes trois amulettes. Moi te récompenser.";
			link.l1 = "Tu as promis quelque chose à propos du 'pouvoir que je pourrai détenir pour toujours' ?";
			link.l1.go = "Tuttuat_65";
		break;
		
		case "Tuttuat_65":
			dialog.text = "Tu parles vrai. Je te donnerai ce pouvoir. Nul aux Caraïbes ne connaît le secret de la plante que je connais. Écoute-moi, visage pâle ! Chez moi, il y a une plante médicinale. Nous l'appelons Manga Rosa. As-tu entendu parler de cette plante ?";
			if (CheckAttribute(pchar, "questTemp.Mangarosa.Tell"))
			{
				link.l1 = "Oui. Je l'ai tenu dans mes mains. Les gitans montrent un grand intérêt pour cela. Et l'une d'entre elles, la guérisseuse Amelia, peut même...";
				link.l1.go = "Tuttuat_66";
			}
			else
			{
				link.l1 = "Aucune idée...";
				link.l1.go = "Tuttuat_66_1";
			}
		break;
		
		case "Tuttuat_66":
			dialog.text = "Moi entendre parler de l'herboriste Amelia. Elle pas sait peu mais pas beaucoup. Elle pas sait le secret de Manga Rosa. Seulement grand chaman de ma patrie, d'où Manga Rosa être amené ici, peut utiliser son plein pouvoir.";
			link.l1 = "Quel pouvoir ?";
			link.l1.go = "Tuttuat_67";
		break;
		
		case "Tuttuat_66_1":
			dialog.text = "Cette herbe pousse dans mon pays natal, mais elle se trouve aussi dans les Caraïbes. C'est une plante haute de couleur vert clair, avec des feuilles comme un palmier aux doigts écartés, et une odeur agréable. Vous la reconnaîtrez instantanément et ne la confondrez avec rien. Moi, je connais les secrets de cette plante. Je peux en extraire la puissance.";
			link.l1 = "Je comprends, mais quel genre de pouvoir ?";
			link.l1.go = "Tuttuat_67";
		break;
		
		case "Tuttuat_67":
			dialog.text = "Moi, je peux préparer des potions de Manga Rosa. Des potions très fortes. Personne d'autre que moi aux Caraïbes ne peut faire cela. Mes potions rendent l'homme toujours plus fort, plus rapide, plus intelligent, plus perspicace, plus beau et plus chanceux. Je te prépare trois de ces potions.";
			link.l1 = "Très intéressant !";
			link.l1.go = "Tuttuat_68";
		break;
		
		case "Tuttuat_68":
			dialog.text = "Toi, grand guerrier, tu as d'abord besoin d'une potion pour te rendre plus robuste et une autre pour te rendre plus rapide. Et tu choisiras la troisième potion après que j'aie préparé les deux premières. Mais tu dois m'apporter de la Manga Rosa pour les fabriquer - je n'en ai point.";
			link.l1 = "Où dois-je chercher Manga Rosa ?";
			link.l1.go = "Tuttuat_69";
		break;
		
		case "Tuttuat_69":
			dialog.text = "Manga Rosa est une herbe rare dans les Caraïbes. Elle pousse là où les gens ne marchent guère. Les idiots la cueillent, la sèchent et la fument. De vrais imbéciles. NE LA FUME PAS ! Ce serait un gâchis de pouvoir... Cherchez dans la jungle et les criques, des endroits secrets où les sots ne s'aventurent pas. Regardez attentivement. Pour chaque potion, j'ai besoin de cinq tiges de Manga Rosa.";
			link.l1 = "D'accord, grand chaman. Je reviendrai vers toi une fois que j'aurai assez de Manga Rosa.";
			link.l1.go = "Tuttuat_70";
		break;
		
		case "Tuttuat_70":
			dialog.text = "Va, guerrier blanc. Apporte-moi la Manga Rosa. Tu ne le regretteras pas. Mes potions sont les meilleures. Moi dire aux esprits de t'aider dans ta quête.";
			link.l1 = "Merci ! A bientôt, chaman !";
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
			dialog.text = "Tu apportes cinq tiges de Manga Rosa pour la potion ?";
			if (GetCharacterItem(pchar, "cannabis7") >= 5)
			{
				link.l1 = "Oui. Voici cinq plantes dont vous avez besoin.";
				link.l1.go = "Tuttuat_73";
			}
			link.l2 = "Pas encore, grand chaman. Ma quête continue...";
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
					dialog.text = "Très bien. Reviens demain, une fois que le soleil sera couché. Je te préparerai des potions qui augmenteront ta réactivité et ta dextérité.";
					link.l1 = "D'accord, chaman. Je viendrai demain soir.";
					link.l1.go = "Tuttuat_74";
					pchar.questTemp.Caleuche.Mangarosa = 1;
				break;
				
				case 1:
					dialog.text = "Très bien. Reviens demain, une fois le soleil couché. Je te préparerai des potions qui augmenteront ton endurance.";
					link.l1 = "D'accord, chaman. Je viendrai demain soir.";
					link.l1.go = "Tuttuat_74";
					pchar.questTemp.Caleuche.Mangarosa = 2;
				break;
				
				case 2:
					dialog.text = "Très bien. Quelle est ta potion à choisir ? Potion de force, vision perçante, intelligence, beauté ou chance ?";
					link.l1 = "Potion de force.";
					link.l1.go = "Tuttuat_77_1";
					link.l2 = "Potion de vision perçante.";
					link.l2.go = "Tuttuat_77_2";
					link.l3 = "Potion d'intelligence.";
					link.l3.go = "Tuttuat_77_3";
					link.l4 = "Potion de beauté.";
					link.l4.go = "Tuttuat_77_4";
					link.l5 = "Potion de chance.";
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
				dialog.text = "Potion prete, guerrier au visage pale. Prends-la."+sTemp+"";
				link.l1 = "Merci, grand chaman.";
				link.l1.go = "Tuttuat_76";
			}
			else
			{
				dialog.text = "Ce n'est pas encore prêt, homme blanc. Reviens plus tard. Ne me dérange pas.";
				link.l1 = "Très bien...";
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
				dialog.text = "Je prépare pour vous toutes les potions que j'ai promises. Vous devenez plus fort. Vous êtes content ?";
				link.l1 = "Oui, grand chaman. Ce fut en effet une récompense digne.";
				link.l1.go = "Tuttuat_78";
			}
			else
			{
				dialog.text = "Tu trouves cinq autres tiges de Manga Rosa, tu me les apportes. Je te prépare une autre potion.";
				link.l1 = "Je t'en apporterai plus. À la prochaine!";
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
			dialog.text = "Viens demain, comme d'habitude. Je te prépare une potion pour te rendre plus fort, et tu ferais mieux de te battre avec une grande hache.";
			link.l1 = "Bien.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 31;
		break;
		
		case "Tuttuat_77_2":
			dialog.text = "Viens demain, comme d'habitude. Je te prépare une potion pour aiguiser tes yeux afin que tu voies chaque cible, et tu ferais mieux de frapper avec des armes ardentes qui rugissent.";
			link.l1 = "D'accord.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 32;
		break;
		
		case "Tuttuat_77_3":
			dialog.text = "Viens demain, comme d'habitude. Je te prépare une potion pour te rendre plus intelligent, et il vaut mieux te cacher des ennemis.";
			link.l1 = "D'accord.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 33;
		break;
		
		case "Tuttuat_77_4":
			dialog.text = "Viens demain, comme d'habitude. Je te prépare une potion pour te rendre plus beau, et tu persuaderas mieux les gens.";
			link.l1 = "Bien.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 34;
		break;
		
		case "Tuttuat_77_5":
			dialog.text = "Viens demain, comme d'habitude. Je te prépare une potion pour te rendre plus chanceux, et tu auras bonne fortune.";
			link.l1 = "D'accord.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 35;
		break;
		
		case "Tuttuat_78":
			dialog.text = "Moi content que tu aimes mon art, l'art du grand chaman.";
			link.l1 = "Dis-moi, Tuttuathapak, pourquoi avais-tu besoin de ces trois amulettes? Juste par curiosité...";
			link.l1.go = "Tuttuat_79";
		break;
		
		case "Tuttuat_79":
			dialog.text = "Tu ressens déjà le pouvoir de ces deux amulettes. Les esprits m'aideront à leur donner du pouvoir, et les trois amulettes ensemble offrent la grande sagesse chamanique et l'illumination de mes ancêtres, les grands Chavins.";
			link.l1 = "Je vois. Très bien, merci encore une fois pour vos excellentes potions. Vous êtes vraiment un grand chaman. Il est temps pour moi de partir maintenant. Adieu, Tuttuathapak, j'espère te revoir.";
			link.l1.go = "Tuttuat_80";
		break;
		
		case "Tuttuat_80":
			dialog.text = "Adieu, guerrier blanc. Tu ne me cherches plus. Moi, je pars en retraite, saisir la sagesse de mes ancêtres. Que les esprits t'aident dans tes voyages !";
			link.l1 = "Eh bien alors... hah... que les esprits éclairent également ton chemin, grand chaman. Adieu...";
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
			dialog.text = "Tu me rends triste, visage pâle. Moi faire rituel avec esprits pour donner pouvoir à ces amulettes, et toi gaspiller ça. Moi triste. Toi partir maintenant. Tuttuathapak plus rien à te dire.";
			link.l1 = "Je suis désolé, j'ai vraiment eu de la malchance... Eh bien. Adieu, chaman.";
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
			dialog.text = "Tout est en vain, marin. Tu ne me surpasseras pas. Et tous mes hommes étendus sur le pont rassembleront leurs os et se relèveront avant l'aube. Nous ne pouvons être tués, car la mort nous a abandonnés pour toujours.";
			link.l1 = "Nom de Dieu ! Es-tu mort ou vivant ? Plus probablement encore vivant - les morts ont tendance à rester tranquilles et ne brandissent pas d'épées. Mais qui es-tu et pourquoi as-tu attaqué mon navire ?";
			link.l1.go = "CaleucheCap_1";
		break;
		
		case "CaleucheCap_1":
			dialog.text = "Je suis Balthazar de Cordes du Coeur Volant. Misérables lâches, qui ne savent rien de moi, m'appellent Van der Decken, capitaine du Hollandais Volant. Mais cela n'a pas d'importance. Ce qui importe, c'est que tu as un amulette sur toi, que je vais prendre maintenant. J'en ai besoin! Je le sens! Le grand amulette des Chavins, l'un des trois, sera enfin à moi! Agenouille-toi devant moi, mortel! Et je pourrais rendre ta mort sans douleur!";
			link.l1 = "Va te faire foutre, cadavre !";
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
			dialog.text = "Je n'en reviens pas ! Cela fait si longtemps que je n'ai pas vu mon propre sang ni ressenti de douleur...COMMENT?!";
			link.l1 = "Cette fois tu as perdu, Balthazar de Cordes. Je connais ton histoire. Le crâne de jade a été rendu au temple des Chavins, et la malédiction de Yum Cimil ne pèse plus sur toi ou tes matelots. Tu ne ramèneras plus tes marins à la vie.";
			link.l1.go = "CaleucheCap_4";
		break;
		
		case "CaleucheCap_4":
			dialog.text = "Oh, alors tu dois te considérer comme un rédempteur, peut-être ? Non ! Balthazar de Cordes vendra chèrement le peu de vie qui lui reste !";
			link.l1 = "Le dernier voyage du Coeur Volant se termine ici, à Khael Roa. Et tu ne relèveras pas ton navire du fond de la mer, comme tu l'as fait il y a vingt-cinq ans.";
			link.l1.go = "CaleucheCap_5";
		break;
		
		case "CaleucheCap_5":
			PlaySound("Voice\English\LE\Baltazar_de_Kortes\Baltazar_03.wav");
			dialog.text = "Faucon ! Vingt-cinq ans se sont écoulés, et je m'en souviens encore comme si c'était hier. L'éclat de cet orbe qui nous a aveuglés et a fendu mon navire en deux. Ce fut la première et la dernière défaite du Cœur Volant et de Balthazar de Cordes... Alors croisons le fer une dernière fois, capitaine ! Mourir au combat est léger et bienvenu !";
			link.l1 = "... ";
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
		
		// --> // наш матрос на берегу
		case "on_coast":
			dialog.text = "Enfin, tu t'es réveillé, capitaine... Comment te sens-tu ?";
			link.l1 = "Bon sang, qu'est-il arrivé ? Ma tête est en train d'exploser de douleur...";
			link.l1.go = "on_coast_1";
		break;
		
		case "on_coast_1":
			dialog.text = "Quand nous sommes entrés dans la cabine du capitaine, tu étais allongé sur le sol, sans un seul mouvement. Les gars t'ont ramassé et traîné jusqu'à notre navire - et juste à temps, car les morts allongés sur le pont ont commencé à se relever\nSainte Vierge et tous les Saints ! Nous avons rapidement coupé les amarres et tenté de prendre la mer, mais une salve de leur navire a rapidement transformé notre vieille barque en éclats et nous avons perdu le contrôle. Puis ils ont hissé les voiles et ont disparu en un clin d'œil\nNotre navire s'est échoué, et tous ceux qui ont réussi à survivre ont atteint le rivage en barque. Beaucoup de braves hommes sont morts aujourd'hui... si seulement nous étions restés à bord... Mais nous étions sûrs que la tempête achèverait le navire pour de bon.";
			link.l1 = "Pas votre faute, messieurs. C'était la bonne décision. Merci, je m'en souviendrai.";
			link.l1.go = "on_coast_2";
		break;
		
		case "on_coast_2":
			dialog.text = "Nous t'avons traîné dans le bateau puis nous t'avons amené à terre. Tu étais presque mort...";
			link.l1 = "Je vous dois la vie. Combien de temps suis-je resté ici, inconscient ?";
			link.l1.go = "on_coast_3";
		break;
		
		case "on_coast_3":
			dialog.text = "Pendant toute une journée. Nous avons lavé et bandé vos blessures, vous avons donné des médicaments et versé un peu de rhum en vous. Vous devriez bientôt vous rétablir.";
			link.l1 = "Je ne mourrai sûrement pas cette fois-ci. Bien que je ne me sente pas vraiment bien...";
			link.l1.go = "on_coast_4";
		break;
		
		case "on_coast_4":
			dialog.text = "C'est sûr... Etait-ce le Hollandais Volant, capitaine ? Pourquoi nous ont-ils attaqués ? Et pourquoi ne nous ont-ils pas tiré dessus avant l'abordage, mais ont presque coulé notre navire d'une seule bordée ensuite ?";
			link.l1 = "Leur capitaine avait besoin de l'amulette, dont j'avais parlé à Tuttuathapak, un chaman indien. C'est pourquoi ils ne nous ont pas coulés immédiatement, mais une fois que leur chef a pris l'amulette, ils se sont rapidement débarrassés de nous... Quel cauchemar ! Un navire dirigé par des morts ! Impossible à croire...";
			link.l1.go = "on_coast_5";
		break;
		
		case "on_coast_5":
			dialog.text = "Oui, maintenant c'était notre tour de croiser le Hollandais Volant. Quand j'en aurai l'occasion, j'irai à l'église, allumerai un cierge pour ma délivrance miraculeuse, et prierai notre Seigneur...";
			link.l1 = "Moi aussi... Je suppose. Mais d'abord, je retournerai dans ce village. Je dois tout raconter à Tuttuathapak à ce sujet. Ce maudit navire nous a attaqués à cause de l'amulette ! Je suis sûr que ce diable à la peau rouge avait quelques idées, pourquoi diable ces morts-vivants en auraient eu besoin.";
			link.l1.go = "on_coast_6";
		break;
		
		case "on_coast_6":
			dialog.text = "D'accord. Mais fais attention, capitaine, tes blessures ont à peine guéri, prends au moins quelqu'un avec toi au cas où.";
			link.l1 = "Je serai prudent, je te le promets. Merci de ne pas m'abandonner !";
			link.l1.go = "on_coast_7";
		break;
		
		case "on_coast_7":
			dialog.text = "De quoi parlez-vous, capitaine ! Nous irions jusqu'au bout du monde pour vous et combattrions des milliers de morts-vivants ! C'est une sacrée honte que nous ayons perdu tant, mais cette histoire vivra dans les légendes.";
			link.l1 = "... ";
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
			dialog.text = "Hey ! Je n'ai pas encore rassemblé assez de peaux de serpent pour te les vendre, alors fous le camp !";
			link.l1 = "Hmm... Êtes-vous Fergus Hooper ?";
			link.l1.go = "fergus_1";
		break;
		
		case "fergus_1":
			dialog.text = "Non, mon nom est Tuttuathapak, et je te maudirai si tu ne déguerpis pas sur-le-champ. Alors tu ferais mieux de te dépêcher, ou tu vas...";
			link.l1 = "...perdre la raison, brûler mon propre navire, et mes marins me tueront et prendront tous mes biens. N'est-ce pas ?";
			link.l1.go = "fergus_2";
		break;
		
		case "fergus_2":
			sld = characterFromId(pchar.questTemp.Caleuche.Amuletmaster);
			dialog.text = "Arrgh... Bon sang, qui es-tu!? Comment as-tu...";
			link.l1 = "Nous avons un ami commun, Fergus. C'est un gardien de phare, et son nom est "+GetFullName(sld)+". Il m'a parlé de toi et m'a envoyé te chercher. Au fait, je connais personnellement le chaman Tuttuathapak, donc ta blague n'a pas marché, désolé. Écoute, je ne cherche pas d'ennuis. Je veux t'acheter quelque chose, et ce n'est pas les peaux de serpent.";
			link.l1.go = "fergus_3";
		break;
		
		case "fergus_3":
			dialog.text = "Oh, alors tu connais mon vieil ami ! Comment va-t-il ? N'est-il pas encore mort d'ennui dans son phare ? Assieds-toi, marin, prends un verre avec moi !";
			link.l1 = "Je suis désolé, Fergus, je n'ai vraiment pas beaucoup de temps. Écoute, j'ai besoin de cet amulette indienne, une de celles que ton défunt capitaine a prises du Continent avec Tuttuathapak. J'en donnerai un bon prix, et tu te débarrasseras d'un bibelot dangereux.";
			link.l1.go = "fergus_4";
		break;
		
		case "fergus_4":
			dialog.text = "Et qu'y a-t-il de si dangereux à cela ? Je n'en ai vu aucun mal jusqu'à présent. C'est juste une pierre inutile";
			link.l1 = "C'est parce que tu ne vogues plus sur les mers. J'avais un amulette similaire jusqu'à récemment. Un navire fantôme chasse ces choses.";
			link.l1.go = "fergus_5";
		break;
		
		case "fergus_5":
			dialog.text = "Tu plaisantes, l'ami ? Peut-être que connaître Tuttuathapak t'a trop coûté ? Fais attention, cap', ce démon à la peau rouge dévorera ton esprit...";
			link.l1 = "Crois-moi ou non, mais je dis la vérité. Je ne l'aurais pas cru moi-même si je ne l'avais pas vu de mes propres yeux, je peux jurer sur le Livre ou tu peux demander à ceux qui étaient avec moi. J'ai à peine survécu après cette rencontre avec le Caleuche.";
			link.l1.go = "fergus_6";
		break;
		
		case "fergus_6":
			dialog.text = "Le Caleuche ?";
			link.l1 = "Eh bien, la plupart l'appellent le Hollandais Volant mais son vrai nom est Coeur Volant. Qu'importe. Vends-moi donc ce talisman. De toute façon, il ne te sert à rien, je le sais.";
			link.l1.go = "fergus_7";
		break;
		
		case "fergus_7":
			dialog.text = "C'est exact. Ce n'est qu'un bibelot inutile, bien que fort joli. Écoutez, je vous l'aurais vendu sans plus tarder, mais voyez-vous - je ne l'ai plus. Il a été volé de ma hutte parmi d'autres choses, pendant que je chassais dans la jungle. Cela s'est passé assez récemment, il y a environ un mois. Désolé, mais je ne peux rien faire pour vous aider.";
			link.l1 = "Et qui l'a volé ?";
			link.l1.go = "fergus_8";
		break;
		
		case "fergus_8":
			dialog.text = "Tu penses sérieusement que je serais assis ici si je savais qui a pillé ma maison ? Il y a une bande de voleurs et de brigands qui opèrent près de Belize, et ils ont des informateurs en ville. Eh bien, c'est du moins ce que pense le commandant. Je suis sûr que c'était eux.";
			link.l1 = "Le commandant est au courant des bandits et pourtant ne fait rien ?";
			link.l1.go = "fergus_9";
		break;
		
		case "fergus_9":
			dialog.text = "Qu'il fasse quelque chose ou non, je ne sais pas. La seule chose dont je suis sûr, c'est que mes affaires ont disparu, et votre précieux amulette avec elles. Essayez de retrouver ces bandits - peut-être la trouverez-vous dans leurs poches. Il est peu probable qu'ils aient réussi à la vendre - les marchands n'ont pas besoin de telles choses.";
			link.l1 = "D'accord, je vais aller voir le commandant. Bonne chance, Fergus !";
			link.l1.go = "fergus_10";
		break;
		
		case "fergus_10":
			DialogExit();
			AddQuestRecord("Caleuche", "9");
			pchar.questTemp.Caleuche.Bandos = "start"; 
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		// бандит в городе
		case "Beliz_townbandos":
			dialog.text = "Hé ! Qu'est-ce que tu veux ? Je n'attends aucun invité. Déguerpis !";
			link.l1 = "Pourquoi si grossier, ami ? Je voulais juste demander...";
			link.l1.go = "Beliz_townbandos_1";
		break;
		
		case "Beliz_townbandos_1":
			dialog.text = "As-tu pas entendu ? Dégage, ou je te fous dehors !";
			link.l1 = "Hmm... Eh bien, peut-être que tu es la personne que je cherche après tout. Tu sembles bien trop nerveux, camarade...";
			link.l1.go = "Beliz_townbandos_2";
		break;
		
		case "Beliz_townbandos_2":
			dialog.text = "Te crois-tu trop malin, n'est-ce pas ? Encore une fois : soit tu déguerpis sur-le-champ, soit j'appelle les gardes, et ils te jetteront en prison !";
			link.l1 = "Me jeter derrière les barreaux ? Comme c'est intéressant. Vous savez, maintenant je suis presque certain d'avoir trouvé celui que je cherchais. Très bien, je suis d'accord. Appelons les gardes, et puis nous marcherons ensemble au bureau du commandant, comme une famille heureuse. J'y étais il y a peu, donc je me souviens du chemin... Gardes ! GARDES !";
			link.l1.go = "Beliz_townbandos_3";
		break;
		
		case "Beliz_townbandos_3":
			dialog.text = "Va te faire foutre ! Je vais te transpercer !";
			link.l1 = "Oh ho-ho! Eh bien, tu peux essayer!";
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
			dialog.text = "Hé, voyageur ! Bienvenue, bienvenue... Souper, logis - tout pour votre argent. Alors, prépare-toi à vider tes poches !";
			link.l1 = "Pas si vite, mon bonhomme. J'ai affaire avec toi.";
			link.l1.go = "Beliz_forestbandos_1";
		break;
		
		case "Beliz_forestbandos_1":
			dialog.text = "Affaires ? Ha-ha ! Ton seul affaire est de me donner tout ton argent et ton or !";
			link.l1 = "Tais-toi déjà. Je t'ai apporté une lettre de Belize que tu attendais. Le messager n'a pas pu s'entendre avec les gardes et m'a confié l'affaire.";
			link.l1.go = "Beliz_forestbandos_2";
		break;
		
		case "Beliz_forestbandos_2":
			dialog.text = "Montre - moi !";
			link.l1 = "Voici...";
			link.l1.go = "Beliz_forestbandos_3";
		break;
		
		case "Beliz_forestbandos_3":
			Log_Info("You have given a note");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "kaleuche_letter", 1);
			dialog.text = "(lisant) Hm... C'est sûrement étrange... Comment t'es-tu impliqué ?";
			link.l1 = "Je t'ai déjà dit, ils ont capturé ton gars, alors j'ai pris son poste. Il a promis de l'argent et un accueil chaleureux de ta part...";
			link.l1.go = "Beliz_forestbandos_4";
		break;
		
		case "Beliz_forestbandos_4":
			dialog.text = "A warm welcome? Alright, pal. We'll warm you up, feed you, give you money and all that stuff - but you, you too, will have to prove us that you're not a guards' hound. We've got a score to settle now\nA merchant has recently arrived to a nearby cove; apparently, he wants to sneak into the city with his wares past the customs office. But we will still exact the duty from him. We are lawful folk after all! You'll come with us. Do you know which end of the sword goes where?";
			link.l1 = "Et aurai-je une part de cette mission ?";
			link.l1.go = "Beliz_forestbandos_5";
		break;
		
		case "Beliz_forestbandos_5":
			dialog.text = "Bien sûr que tu le feras ! Si tu es courageux au combat et si tu restes en vie. Mais ne t'attends pas à une promenade de santé, le marchand n'est pas seul, il a une escorte, et une très grande escorte. Eh bien, il est temps de partir - notre proie est proche. Garçons ! Préparez vos armes, nous partons !";
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
			dialog.text = "Je vois que tu n'es pas un lâche. Bien joué ! Tu as gagné ta part. Comment la veux-tu ? En espèces ? En marchandises ? Ils transportaient beaucoup d'alcool, c'est sûr que ça vaut cher.";
			link.l1 = "Du fric.";
			link.l1.go = "Beliz_forestbandos_8_1";
			link.l2 = "Marchandise.";
			link.l2.go = "Beliz_forestbandos_8_2";
		break;
		
		case "Beliz_forestbandos_8_1":
			Log_Info("You have received 100 doubloons");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "gold_dublon", 100);
			dialog.text = "Voilà ! Et cette bourse est pour la livraison de la lettre.";
			link.l1 = "Merci ! Voila comment j'aime ça !";
			link.l1.go = "Beliz_forestbandos_9";
		break;
		
		case "Beliz_forestbandos_8_2":
			Log_Info("You have received 30 bottles of rum");
			Log_Info("You have received 12 bottles of wine");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "potionrum", 30);
			TakeNItems(pchar, "potionwine", 12);
			dialog.text = "Voilà ! Ne va pas te saouler à mort, ha-ha-ha ! Et cette bourse, c'est pour livrer la lettre.";
			link.l1 = "Merci ! Voilà comment j'aime ça !";
			link.l1.go = "Beliz_forestbandos_9";
		break;
		
		case "Beliz_forestbandos_9":
			Log_Info("You have received a purse");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "purse2", 1);
			dialog.text = "Tu m'as l'air d'un gaillard honnête. Que dirais-tu d'une autre affaire ? C'est à propos de cette lettre que tu m'as fait livrer.";
			link.l1 = "D'accord.";
			link.l1.go = "Beliz_forestbandos_10";
		break;
		
		case "Beliz_forestbandos_10":
			dialog.text = "Alors viens à la caverne. Il y en a deux. Va dans la jungle jusqu'à l'endroit où nous nous sommes rencontrés la dernière fois, puis prends le chemin de gauche. Nous nous rassemblons dans trois jours à l'entrée de la caverne, de minuit à une heure. Compris ? Si tu es un bon garçon, nous t'accepterons dans notre bande. Mais garde à l'esprit - si tu débites quoi que ce soit en ville, tu es fini. J'ai le bras long.";
			link.l1 = "Arrête de me faire peur. J'ai compris. Je serai muet comme une carpe. Attends-moi dans trois jours, j'y serai. J'adore l'argent facile !";
			link.l1.go = "Beliz_forestbandos_11";
		break;
		
		case "Beliz_forestbandos_11":
			dialog.text = "D'accord, l'ami. Maintenant, file avant que les gardes n'arrivent ici. Nous partons aussi.";
			link.l1 = "À la prochaine, l'ami...";
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
		break;
		
		// спалили бандосы в пещере
		case "Beliz_cavebandos":
			dialog.text = "Quoi ! Je suppose que tu as décidé de t'approprier certains de nos biens ? Tu ne t'en tireras pas comme ça, sale vermine !";
			link.l1 = "Qui viens-tu de traiter de vermisseau, espèce de racaille ?!";
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
			dialog.text = "Bonjour, collègue ! Qu'est-ce qui t'amène ici ?";
			link.l1 = TimeGreeting()+", monsieur Jackson. Je suis heureux de vous trouver enfin.";
			link.l1.go = "reginald_1";
		break;
		
		case "reginald_1":
			dialog.text = "'Mynheer Jackson', ha-ha ! Eh bien, pour être honnête, bientôt je vais m'appeler ainsi moi aussi. Je travaille pour cette foutue Compagnie sans arrêt... mais ils paient bien, très bien !.. Alors, qu'est-ce qui t'amène ici, camarade ?";
			link.l1 = "Notre connaissance commune, le gardien du phare, m'a dit que tu avais un ancien amulette indienne. Je suppose que tu ne t'en es jamais servi, et j'en ai vraiment besoin. Je veux te l'acheter.";
			link.l1.go = "reginald_2";
		break;
		
		case "reginald_2":
			dialog.text = "Oh, tu parles de ce bijou raffiné dont j'avais demandé à ce bosco retraité ? Oui, ami, tu as raison, il ne m'a en fait jamais été utile, il est juste joli.";
			link.l1 = "Combien en veux-tu ?";
			link.l1.go = "reginald_3";
		break;
		
		case "reginald_3":
			dialog.text = "Vous voyez, il y a un petit problème... Laissez-moi vous expliquer. Je ne l'ai pas sur moi pour le moment. Comme je n'en ai jamais trouvé d'utilité, je l'ai laissé dans mon coffre sur le rivage, parmi mes autres affaires.";
			link.l1 = "Oh, cela explique que vous êtes encore... eh bien, peu importe. Allons simplement à ce coffre à vous, et j'achèterai l'amulette de vous. Aussi simple que cela. Où l'avez-vous ?";
			link.l1.go = "reginald_4";
		break;
		
		case "reginald_4":
			dialog.text = "Ce n'est pas si simple que ça. Mon coffre est situé à la Barbade, dans la tour du phare, et il est bien verrouillé, pour que personne ne puisse en profiter en mon absence. Et je suis vraiment désolé, mais je ne peux pas vous accompagner à la Barbade, selon mon contrat avec les Hollandais, je dois naviguer entre Philipsburg et Port Royal et respecter scrupuleusement l'horaire. Et la Barbade n'est pas du tout sur cet itinéraire.";
			link.l1 = "Et que pouvons-nous faire? J'ai vraiment, vraiment besoin de cet amulette!";
			link.l1.go = "reginald_5";
		break;
		
		case "reginald_5":
			dialog.text = "Hmm... Eh bien, il y a une option. Je te donne la clef de mon coffre, et tu navigues vers la Barbade par toi-même. Mais tu devras me dédommager pour tout ce qui s'y trouve et tu pourras les garder. Je suis désolé pour la méfiance - mais tu dois comprendre. Je ne t'ai jamais vu auparavant.";
			link.l1 = "Combien?";
			link.l1.go = "reginald_6";
		break;
		
		case "reginald_6":
			dialog.text = "Cinq cents pièces d'or. Pas moins.";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Tu l'as! Voici ton or.";
				link.l1.go = "reginald_10";
			}
			link.l2 = "Hmm... Je n'ai pas autant de doublons sur moi.";
			link.l2.go = "reginald_7";
		break;
		
		case "reginald_7":
			dialog.text = "Alors viens me revoir une fois que tu auras rassemblé l'argent. Si tu m'as trouvé une fois, tu me trouveras à nouveau. Je vais naviguer entre Saint-Martin et la Jamaïque pendant un bon moment maintenant.";
			link.l1 = "D'accord, marché conclu.";
			link.l1.go = "reginald_8";
		break;
		
		case "reginald_8":
			DialogExit();
			NextDiag.CurrentNode = "reginald_9";
			npchar.DeckDialogNode = "reginald_9";
		break;
		
		case "reginald_9":
			dialog.text = "Toi encore, l'ami? Tu as 500 pièces?";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Oui. Voici votre or.";
				link.l1.go = "reginald_10";
			}
			link.l2 = "Pas encore, mais j'y travaille.";
			link.l2.go = "reginald_8";
		break;
		
		case "reginald_10":
			Log_Info("You have given 500 doubloons");
			PlaySound("interface\important_item.wav");
			RemoveDublonsFromPCharTotal(500);
			DeleteAttribute(pchar, "GenQuest.SeaHunter2Pause"); // вертаем морских ОЗГов
			dialog.text = "Génial ! Et voici votre clé. Et je n'ai qu'une requête : après avoir pris tout ce qu'il y a dedans, veuillez laisser la clé dans la serrure. Je détesterais devoir commander une nouvelle serrure et une clé pour celle-ci.";
			link.l1 = "D'accord.";
			link.l1.go = "reginald_11";
		break;
		
		case "reginald_11":
			dialog.text = "Alors bonne chance à toi, ami ! Bon voyage !";
			link.l1 = "Et pareillement... Bon voyage, monsieur Jackson !";
			link.l1.go = "reginald_12";
		break;
		
		case "reginald_12":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true;
			DeleteAttribute(pchar, "questTemp.Caleuche.Garpiya");
			DeleteAttribute(pchar, "questTemp.Garpiya");
			GiveItem2Character(pchar, "kaleuche_key"); 
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key");
			AddQuestRecord("Caleuche", "20");
			// сундук со схроном
			i = Findlocation("Mayak2");
			Locations[i].models.always.locators = "lighthouse_Blocators";
			locations[i].private1.key = "kaleuche_key";
			locations[i].private1.key.delItem = true;
			locations[i].private1.items.kaleuche_amulet3 = 1;
			locations[i].private1.items.pistol9 = 1;
			locations[i].private1.items.indian_6 = 1;
			locations[i].private1.items.map_barbados = 1;
			locations[i].private1.items.map_part2 = 1;
			locations[i].private1.items.jewelry22 = 5;
			locations[i].private1.items.jewelry17 = 6;
			locations[i].private1.items.jewelry12 = 3;
			locations[i].private1.items.jewelry16 = 2;
			locations[i].private1.items.jewelry20 = 7;
			locations[i].private1.items.jewelry53 = 11;
			locations[i].private1.items.mineral25 = 1;
			locations[i].private1.items.mineral21 = 1;
			locations[i].private1.items.mineral22 = 5;
			locations[i].private1.items.mineral26 = 1;
			locations[i].private1.items.mineral10 = 1;
			locations[i].private1.items.mineral3 = 10;
			pchar.quest.caleuche_amulet3.win_condition.l1 = "item";
			pchar.quest.caleuche_amulet3.win_condition.l1.item = "kaleuche_amulet3";
			pchar.quest.caleuche_amulet3.function = "Caleuche_ThirdAmuletFind";
		break;
		
		// монах в Виллемстаде
		case "monk_caleuche":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("villemstad");
			npchar.lifeday = 1;
			dialog.text = "Bonjour, capitaine "+GetFullName(pchar)+". Heureux de vous accueillir à Willemstad.";
			link.l1 = "Bonjour, mon Pere. Je ne me souviens pas de vous. Nous connaissons-nous ?";
			link.l1.go = "monk_caleuche_1";
		break;
		
		case "monk_caleuche_1":
			dialog.text = "Je me suis renseigné sur vous dès que votre navire a accosté. Et je pense que je peux vous demander de l'aide.";
			link.l1 = "Très intéressant. Et pourquoi moi ?";
			link.l1.go = "monk_caleuche_2";
		break;
		
		case "monk_caleuche_2":
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				dialog.text = "Parce que vous avez beaucoup fait pour la République des Provinces Libres. Vous êtes en bons termes avec la Compagnie et vous êtes ami avec le gouverneur. J'ai déjà fait appel à plusieurs instances et ai été réprimandé, mais j'espère qu'une personne noble comme vous ne refuserait pas une humble demande d'un serviteur de notre Seigneur.";
			}
			else
			{
				dialog.text = "Parce que vous n'êtes pas au service de notre gouverneur. Vous ne travaillez pas pour la Compagnie et vous n'avez aucune affaire avec notre armée - sinon vous m'auriez probablement écarté comme une mouche agaçante, puisque j'ai déjà fait appel à plusieurs instances et j'ai été repoussé.";
			}
			link.l1 = "Très bien, alors. Quelle est la nature de votre requête ?";
			link.l1.go = "monk_caleuche_3";
		break;
		
		case "monk_caleuche_3":
			sld = characterFromId("Villemstad_Priest");
			dialog.text = "Il y a une maison derrière la banque. Une dame qui y vivait louait une chambre à un type très suspect, pas du coin, et pas un Hollandais. Et ainsi notre père supérieur, Père "+sld.name+", l'avait reconnu\nC'était Joachim Merriman, un Portugais accusé par l'Inquisition de sorcellerie et de commerce avec des puissances impies. Il s'était caché de l'Inquisition dans le Nouveau Monde. Vous savez, les Espagnols accusent souvent ceux qui sont en disgrâce d'hérésie et de sorcellerie pour les brûler sur le bûcher, mais... Dans ce cas, ils avaient raison. Merriman est un sorcier\nIl avait donc vécu quelque temps à Willemstad, puis il a disparu aussi soudainement qu'il était apparu. Et après un certain temps, une femme, celle qui lui avait loué la chambre, n'a jamais été vue sortant de cette maison. Jamais ! Et elle n'a jamais été vue nulle part depuis\nEt la nuit, les citoyens peuvent parfois voir des lumières rouge-bleu clignoter aux fenêtres du deuxième étage et entendre des sons étranges, presque comme des cris impies. Père "+sld.name+" sollicité auprès du commandant. Il a envoyé une patrouille de quatre soldats, ils ont fouillé la maison, mais n'ont rien trouvé : ni la logeuse elle-même, ni personne d'autre, ni rien de suspect du tout\nMais ces choses étranges continuent à se produire. La logeuse ne s'est jamais montrée, et cette lumière infernale peut encore être vue là-bas la nuit. De plus, deux mendiants ont récemment disparu également. Je les ai entendus, parlant au parvis - ils savaient qu'il n'y avait pas de propriétaires dans la maison, et donc ils ont décidé de s'y installer. Personne ne les a vus depuis.";
			link.l1 = "Je suppose que tu veux que j'entre dans cette maison et vérifie ce qui s'est vraiment passé ?";
			link.l1.go = "monk_caleuche_4";
		break;
		
		case "monk_caleuche_4":
			dialog.text = "Exactement, noble sir. Aidez, je vous prie, la Sainte Eglise. Le commandant dit que nous nous faisons des idées, car sa patrouille n'a jamais rien trouvé. Le gouvernement pense de même. Les gens du commun s'en moquent tout simplement, car ils ne voient pas cela comme une menace claire pour eux.";
			link.l1 = "Hmm... Et devrai-je m'y rendre la nuit ?";
			link.l1.go = "monk_caleuche_5";
		break;
		
		case "monk_caleuche_5":
			sld = characterFromId("Villemstad_Priest");
			dialog.text = "Oui, monsieur. C'est calme là-bas pendant la journée, c'est pourquoi les soldats n'ont rien trouvé, je pense que le commandant a peur pour ses hommes, moi aussi je le serais. Mais s'il vous plaît, je vous en supplie. Mon père "+sld.name+" te remerciera et te récompensera pour ton service. Une fois que tu te seras rendu dans cette tanière pendant la nuit, s'il te plaît, dis-lui ce que tu y trouves. Je t'assure, nos appréhensions sont bien fondées.";
			link.l1 = "D'accord. J'y réfléchirai.";
			link.l1.go = "monk_caleuche_6";
		break;
		
		case "monk_caleuche_6":
			dialog.text = "Merci, capitaine. J'espère que vous ne rejeterez pas ma humble requête. Je vous en prie, faites-le au nom de notre Seigneur, notre foi et tout ce qui est sacré. Allez avec mes bénédictions.";
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
			dialog.text = "Attends, mon gars. Tu ferais mieux de ne pas y aller, si tu tiens à ta vie.";
			link.l1 = "Et quel est le marché ?";
			link.l1.go = "cavehunter_1";
		break;
		
		case "cavehunter_1":
			dialog.text = "Croyez-moi, vous ne voulez pas savoir. Mais la Mort elle-même est au tournant, et je peux jurer sur le Livre que vous ne reviendrez pas vivant, il y a des choses au-delà de votre imagination.";
			link.l1 = "Eh bien, si vous le dites, je ne tenterai pas le destin. Merci pour l'avertissement.";
			link.l1.go = "cavehunter_2";
		break;
		
		case "cavehunter_2":
			dialog.text = "Je vous en prie. Evitez ce chemin.";
			link.l1 = "...";
			link.l1.go = "cavehunter_3";
		break;
		
		case "cavehunter_3":
			DialogExit();
			npchar.dialog.currentnode = "cavehunter_4";
		break;
		
		case "cavehunter_4":
			dialog.text = "Reste à l'écart de ce chemin, camarade.";
			link.l1 = "Ouais, je me souviens...";
			link.l1.go = "cavehunter_4_1";
		break;
		
		case "cavehunter_4_1":
			DialogExit();
			npchar.dialog.currentnode = "cavehunter_4";
		break;
		
		case "cavehunter_5":
			sld = characterFromId("Havana_Priest");
			dialog.text = "Es-tu sûr de vouloir y aller?";
			link.l1 = "Absolument. "+sld.name+", père supérieur de l'église à La Havane, m'a envoyé ici. Je dois déterminer ce qui se passe ici, et prendre les mesures adéquates.";
			link.l1.go = "cavehunter_6";
		break;
		
		case "cavehunter_6":
			dialog.text = "Que se passe-t-il ici ? J'ai bien peur que vous ne trembliez de peur, une fois que vous verrez ce qui se passe ici de vos propres yeux.";
			link.l1 = "Tu veux dire les morts-vivants ?";
			link.l1.go = "cavehunter_7";
		break;
		
		case "cavehunter_7":
			dialog.text = "Oui. Et tu ferais bien de croire mes paroles.";
			link.l1 = "Et je te crois. J'ai déjà rencontré cette chose impie à Willemstad et je l'ai détruite. Et maintenant, j'irai là-dedans et détruirai toute la vermine qui se terre dans cette caverne.";
			link.l1.go = "cavehunter_8";
		break;
		
		case "cavehunter_8":
			int icpy = GetOfficersQuantity(pchar);
			switch (icpy)
			{
				case 0:
					dialog.text = "Tu comptes y aller seul ? T'es un homme mort, camarade. Tu n'as pas idée du nombre de ces choses-là. Eh bien, vas-y, si tu y tiens, et j'irai à l'église allumer un cierge pour la paix de ton âme.";
					link.l1 = "Ne sois pas trop pressé de m'enterrer. J'ai vu pire.";
					link.l1.go = "cavehunter_exit";
				break;
				
				case 1:
					dialog.text = "Juste vous deux ? J'ai bien peur que vous n'alliez pas loin. Vous n'avez aucune idée du nombre de ces choses qui sont là-bas. C'est un suicide.";
					link.l1 = "Tu ne nous connais pas bien, ami. Ecarte-toi, et nous purifierons cette antre impie.";
					link.l1.go = "cavehunter_exit";
				break;
				
				case 2:
					dialog.text = "Juste vous trois ? Vous devez être des combattants aguerris pour oser cela. Mais j'ai toujours peur que vous n'y arriviez pas. Vous n'avez aucune idée du nombre de ces choses qui se trouvent à l'intérieur de cette grotte.";
					link.l1 = "Tu ne nous connais pas bien, l'ami. Ecarte-toi, et nous purifierons ce repaire impie.";
					link.l1.go = "cavehunter_exit";
				break;
				
				case 3:
					dialog.text = "Vous n'etes pas des lâches, je vois. Mais vous n'avez vraiment aucune idée du nombre de ces choses là-bas. Dans une telle affaire, chaque homme compte. Que diable, je viendrai avec vous et je tirerai sur cette vermine avec mon mousquet !";
					link.l1 = "Tu es une âme courageuse, ami. Je n'refuserai pas ton aide. Allons-y !";
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
			dialog.text = "Allons-y ! Mort aux immondes morts-vivants !";
			link.l1 = "I'm sorry, I need some text to translate. Could you please provide the dialogue or text you want translated?";
			link.l1.go = "cavehunter_10_1";
		break;
		
		case "cavehunter_10_1":
			DialogExit();
			npchar.dialog.currentnode = "cavehunter_10";
		break;
		
		case "cavehunter_11":
			dialog.text = "Eh bien, c'était un véritable massacre ! Qui aurait pu penser que tant de morts se cachaient en ce lieu ! Eh bien, au moins nous pouvons nous reposer maintenant... S'il te plaît, informe ton père supérieur à ce sujet, celui qui t'a envoyé ici. J'espère bien que l'Inquisition va s'occuper de cela après ton rapport. Traiter avec les morts-vivants, c'est leur affaire, après tout, je ne suis qu'un simple chasseur.";
			link.l1 = "Je lui dirai certainement. Merci pour l'aide, compagnon. Tu es une espèce rare, peu oseraient défier la mort elle-même ! Bonne chance !";
			link.l1.go = "cavehunter_exit";
		break;
		
		// солдат в крипте при провале
		case "cryptguard":
			dialog.text = "Restez où vous êtes ! Cet endroit est interdit !";
			link.l1 = "Ehh... Et qu'est-ce qu'il y a là-dedans ?";
			link.l1.go = "cryptguard_1";
		break;
		
		case "cryptguard_1":
			dialog.text = "Un sorcier dangereux a été trouvé là-bas. Seuls les saints pères et les soldats qui les accompagnent peuvent entrer.";
			link.l1 = "Je vois. Le sorcier a-t-il été arrêté ?";
			link.l1.go = "cryptguard_2";
		break;
		
		case "cryptguard_2":
			dialog.text = "Je ne suis pas autorisé à répondre à de telles questions, señor. Il est temps pour vous de partir.";
			link.l1 = "D'accord, j'ai compris. Bonne chance !";
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
			dialog.text = "Reste immobile, humain! Tu es au cœur même du temple, et tu es allé trop loin pour reculer maintenant.";
			link.l1 = "Qui es-tu?!";
			link.l1.go = "Chavinavi_1";
		break;
		
		case "Chavinavi_1":
			dialog.text = "Je suis le chef des Chavinavi, le gardien et le protecteur de ce lieu sacré. Tu n'es pas le premier à entrer dans ce temple, mais seuls deux hommes et une femme y sont entrés et en sont sortis vivants avant toi. C'est la seule raison pour laquelle je daigne te parler maintenant. Pourquoi es-tu venu ici, visage pâle ?";
			link.l1 = "J'ai apporté une relique ancienne ici, le crâne de jade. Il y a cinquante ans, il a été pris dans un temple indien au cœur du continent. J'allais trouver le sanctuaire et rendre la relique à votre dieu.";
			link.l1.go = "Chavinavi_2";
		break;
		
		case "Chavinavi_2":
			dialog.text = "Il est étrange d'entendre de tels mots de la part de l'un des vôtres. Je ne vous crois pas. Vous, les visages pâles, venez toujours pour prendre quelque chose, mais jamais pour rendre quoi que ce soit.";
			link.l1 = "Je ne mens point. En rendant le crâne, je lèverai la malédiction jetée sur le capitaine du navire fantôme qui terrorise la mer des Caraïbes, ce qui le rendra mortel à nouveau, et je débarrasserai le monde de lui pour de bon.";
			link.l1.go = "Chavinavi_3";
		break;
		
		case "Chavinavi_3":
			dialog.text = "Comment sais-tu que notre Dieu lèvera cette malédiction, visage pâle? Est-ce que notre Dieu te parle?";
			link.l1 = "Non. Je suis venu ici sur les conseils d'un grand chaman du nom de Tuttuathapak. Comme il l'a dit, le crâne est la clé de la malédiction, et c'est le seul temple des Caraïbes. Et tu sais quoi - je pense qu'il peut effectivement converser avec les esprits du passé. Peut-être même avec toi, chef des guerriers jaguars.";
			link.l1.go = "Chavinavi_4";
		break;
		
		case "Chavinavi_4":
			dialog.text = "Tes paroles me surprennent, visage pâle, mais je ne peux toujours pas te faire entièrement confiance. Pourtant, si tu es venu à ce temple pour rendre notre relique, sûrement notre chaman t'a parlé de cet endroit, de sa création, de son histoire et de ses habitants\nSi c'est le cas, tu répondras aisément à toutes mes questions. Alors j'admettrai que tu as été sincère avec moi, te laisserai passer et, de plus, te récompenserai.";
			link.l1 = "Alors demande !";
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
			dialog.text = "Avant que votre peuple au visage pâle n'arrive, cette terre entière, depuis la grande neige au nord jusqu'aux vastes plaines au sud, nous appartenait, frères d'une même famille...";
			link.l1 = "";
			link.l1.go = "question2";
		break;
		
		case "question1_l":
			dialog.text = "Avant que vos gens à la face pâle ne viennent, toute cette terre, du grand neige au nord aux grandes plaines au sud, nous appartenait, frères d'une même famille...";
			link.l1 = "";
			link.l1.go = "question2";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question2":
			dialog.text = "Quelle tribu indienne a construit ce temple ?";
			link.l1 = "Inca.";
			link.l1.go = "question2_l";
			link.l2 = "Chavins.";
			link.l2.go = "question2_r";
			link.l3 = "Maya.";
			link.l3.go = "question2_l";
			link.l4 = "Azteque.";
			link.l4.go = "question2_l";
			link.l5 = "Arawac.";
			link.l5.go = "question2_l";
		break;
		
		case "question2_r":
			dialog.text = "Nos gens ont progressé, apprenant la sagesse, et ont soumis de nouvelles forêts, plaines et îles. Les gens, qui avaient construit ce temple, sont arrivés des bois à travers la Grande Eau...";
			link.l1 = "";
			link.l1.go = "question3";
		break;
		
		case "question2_l":
			dialog.text = "Notre peuple a progressé, apprenant la sagesse, et a soumis de nouvelles forêts, plaines et îles. Les gens qui avaient construit ce temple sont arrivés des bois à travers la Grande Eau...";
			link.l1 = "";
			link.l1.go = "question3";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question3":
			dialog.text = "Qui a mene le groupe de ces glorieux gens?";
			link.l1 = "Grand chef.";
			link.l1.go = "question3_l";
			link.l2 = "Grand pretre.";
			link.l2.go = "question3_l";
			link.l3 = "Fils du grand chef.";
			link.l3.go = "question3_r";
			link.l4 = "Fils du grand pretre.";
			link.l4.go = "question3_l";
			link.l5 = "Le groupe n'avait pas de chef.";
			link.l5.go = "question3_l";
		break;
		
		case "question3_r":
			dialog.text = "Les Indiens, vaillants guerriers et voyageurs, ont toujours aimé et vénéré leur patrie, même après s'être installés dans un nouvel endroit. En signe de leur amour pour leur foyer, ils ont érigé une statue dans le temple sous la forme d'un oiseau, le symbole de leur maison. C'est derrière moi...";
			link.l1 = "";
			link.l1.go = "question4";
		break;
		
		case "question3_l":
			dialog.text = "Les Indiens, vaillants guerriers et voyageurs, ont toujours aimé et vénéré leur terre natale, même après s'être installés dans un nouvel endroit. En signe de leur amour pour leur foyer, ils ont érigé une statue dans le temple sous la forme d'un oiseau, symbole de leur maison. Elle est derrière moi...";
			link.l1 = "";
			link.l1.go = "question4";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question4":
			dialog.text = "Quel est le nom de cet oiseau ?";
			link.l1 = "Albatros.";
			link.l1.go = "question4_l";
			link.l2 = "Aigle.";
			link.l2.go = "question4_l";
			link.l3 = "Vautour.";
			link.l3.go = "question4_l";
			link.l4 = "Roc.";
			link.l4.go = "question4_l";
			link.l5 = "Condor.";
			link.l5.go = "question4_r";
		break;
		
		case "question4_r":
			dialog.text = "Des années de prospérité ont passé et se sont éteintes, comme la flamme de la lampe, et la vie a abandonné l'île. Seul le temple est resté là comme un rappel de la grande puissance des anciens Indiens. Le dernier chaman a laissé sur un piédestal un orbe solaire sacré, qui donnait du pouvoir aux courageux et punissait les méchants. Il a été pris par l'homme qui était ici avant vous.";
			link.l1 = "";
			link.l1.go = "question5";
		break;
		
		case "question4_l":
			dialog.text = "Les années de prospérité ont passé et se sont évanouies, comme la flamme de la lampe, et la vie a abandonné l'île. Seul le temple est resté ici en tant que rappel du grand pouvoir des anciens Indiens. Le dernier chaman a laissé sur un piédestal un orbe solaire sacré, qui donnait du pouvoir aux courageux et punissait les méchants. Il a été pris par l'homme qui était ici avant vous.";
			link.l1 = "";
			link.l1.go = "question5";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question5":
			dialog.text = "Quel était le nom de cet orbe sacré?";
			link.l1 = "Orbe du soleil brillant.";
			link.l1.go = "question5_l";
			link.l2 = "Orbe des rayons du soleil.";
			link.l2.go = "question5_l";
			link.l3 = "Orbe du soleil de midi.";
			link.l3.go = "question5_l";
			link.l4 = "Orbe du soleil levant.";
			link.l4.go = "question5_r";
			link.l5 = "Orbe du soleil couchant.";
			link.l5.go = "question5_l";
		break;
		
		case "question5_r":
			if (CheckAttribute(pchar, "questTemp.Caleuche.QuestionFail"))
			{
				PlaySound("Voice\English\LE\Chavinavi\Chavinavi_02.wav");
				dialog.text = "Mauvaises reponses indiquent que tu m'as menti, homme blanc ! Tu es venu avec de mauvaises intentions ! Tu as reussi à te faufiler devant les gardiens du temple et du sanctuaire, tu as compris comment fonctionnait le mecanisme de la porte - mais tu n'echapperas pas à un combat mortel avec moi. Prepare-toi à mourir, visage pale !";
				link.l1 = "Eh bien, si tu y insistes - voyons voir, quel grand guerrier tu es...";
				link.l1.go = "chavinavi_fight";
			}
			else
			{
				dialog.text = "Votre connaissance de mon peuple et de mon temple vous fait honneur, visage pâle. Maintenant je vous crois. Allez et accomplissez ce pour quoi vous êtes venu ici. Placez la relique sacrée sur un piédestal devant le condor, là où l'orbe du soleil levant résidait autrefois.\nPuis revenez vers moi. Votre vénération pour Yum Cimil et la décision de rendre volontairement ce qui avait été volé par vos frères doivent être récompensées.";
				link.l1 = "Merci pour votre confiance, grand chef.";
				link.l1.go = "chavinavi_exit";
			}
		break;
		
		case "question5_l":
			PlaySound("Voice\English\LE\Chavinavi\Chavinavi_02.wav");
			dialog.text = "Des mauvaises réponses indiquent que tu m'as menti, homme blanc ! Tu es venu avec de mauvaises intentions ! Tu as réussi à te faufiler devant les gardiens du temple et du sanctuaire, tu as compris comment fonctionnait le mécanisme de la porte - mais tu n'échapperas toujours pas à un combat mortel avec moi. Prépare-toi à mourir, visage pâle !";
			link.l1 = "Eh bien, si tu insistes - voyons voir, à quel point tu es un grand guerrier...";
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
			dialog.text = "Tu as fait ce que tu avais promis, visage pâle. Je suis content que tu n'étais pas un menteur comme la plupart de tes frères. Je tiendrai aussi ma parole. Tiens, prends ce cadeau de ma part - le symbole de la puissance des guerriers jaguars. Yum Cimil lui-même a imprégné cette peau d'un peu de sa force.";
			link.l1 = "Wow! C'est si beau!";
			link.l1.go = "Chavinavi_6";
		break;
		
		case "Chavinavi_6":
			GiveItem2Character(pchar, "KhaelRoa_item");
			Log_Info("You have received jaguar's pelt");
			PlaySound("interface\important_item.wav");
			dialog.text = "Ce n'est pas une simple peau. Une fois que tu la porteras, tu gagneras la force du guerrier jaguar. La puissance de ton arme qui crache le feu et tire du plomb augmentera dix fois, et tu pourras joncher le champ de bataille des cadavres de tes ennemis\nMais aucun mortel ne peut contenir le pouvoir que Yum Cimil a mis dans cette peau. Une fois libéré, il ne t'accompagnera que jusqu'à la prochaine minuit, puis il s'évanouira. Prends-en soin, visage pâle, et ne gâche pas son pouvoir dans une petite escarmouche.";
			link.l1 = "Merci ! Je ne l'utiliserai que lorsque je serai totalement submergé par des ennemis.";
			link.l1.go = "Chavinavi_7";
		break;
		
		case "Chavinavi_7":
			dialog.text = "Maintenant, va. Et avertis tes frères de ne pas empiéter sur la sérénité de ces chambres sacrées. Les guerriers jaguar ne montrent aucune pitié pour les visages pâles et ne leur accorderont aucun quartier.";
			link.l1 = "Adieu, chef.";
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
